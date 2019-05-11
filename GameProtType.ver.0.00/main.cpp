#include "main.h"
#include "input.h"
#include "game.h"
#include "textDX.h"
#include "Timer.h"

// �O���[�o���ϐ�
HWND g_hWnd = NULL;
LARGE_INTEGER timeStart;	// �p�t�H�[�}���X�J�E���^�[�̊J�n�l
LARGE_INTEGER timeEnd;		// �p�t�H�[�}���X�J�E���^�[�̏I���l
LARGE_INTEGER timerFreq;	// �p�t�H�[�}���X�J�E���^�[�̎��g��
float frameTime;						// �t���[���^�C��
float fps = FRAME_RATE;		// �t���[�����[�g�i1�b������̃t���[�����j
DWORD sleepTime;			// �t���[���ԂŃX���[�v���鎞�ԁi�~���b�j
Timer gameTimer = Timer(1000000000);//�Q�[���^�C�}�[
Audio audio;
bool initialized = false;


LPDIRECT3D9 pD3D = nullptr;
LPDIRECT3DDEVICE9 pDevice = nullptr;
LPDIRECT3DVERTEXBUFFER9 pVBuffer = nullptr;
LPD3DXSPRITE sprite; // �e�L�X�g�`��p�X�v���C�g

//�֐��v���g�^�C�v�̐錾
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void initialize(HINSTANCE hInstance, HWND hWnd);
void update();
void draw();
void printText();
void unInitialize();

HRESULT InitDX9(HWND hwnd);
void ExitDX9();
void RenderDX9();

// �G���g���[�֐�
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT nCmdShow)
{
	//���������[�N�f�o�b�O
#ifdef _DEBUG	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// �E�B���h�E�쐬
	if (FAILED(InitWindow(hInst, nCmdShow)))
	{
		return 0;//�쐬���s
	}

	// DirectX9�f�o�C�X�̏�����
	if (FAILED(InitDX9(g_hWnd))) {
		ExitDX9();
		return 0;
	}
	
	// ����������
	initialize(hInst,g_hWnd);


	// ���b�Z�[�W���[�v
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{// ���b�Z�[�W������ꍇ
			TranslateMessage(&msg);// DispatchMessage�Ƒ΂Ɏg�p����
			DispatchMessage(&msg);// �E�B���h�E�v���V�[�W���Ƀ��b�Z�[�W��]������
		}
		else
		{// ���b�Z�[�W���Ȃ��ꍇ
		 

			// �A�v���P�[�V��������
			update();
			RenderDX9();
		}
	}

	// �I������
	unInitialize();
	ExitDX9();

	// �I��
	return (INT)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{// �E�B���h�E�v���V�[�W��
	if (!initialized)
	{
		return DefWindowProc(hWnd, iMsg, wParam, lParam);
	}
	switch (iMsg)
	{
	case WM_KEYDOWN:
		switch ((char)wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);// �A�v���P�[�V�����I��
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CHAR:					// ���������͂��ꂽ
		keyIn(wParam);
		return 0;
	case WM_MOUSEMOVE:				// �}�E�X���ړ����ꂽ
		mouseIn(lParam);
		return 0;
	case WM_INPUT:					// �}�E�X����̃��[�f�[�^����
		mouseRawIn(lParam);
		return 0;
	case WM_LBUTTONDOWN:			// ���}�E�X�{�^���������ꂽ
		setMouseLButton(true);
		mouseIn(lParam);
		return 0;
	case WM_LBUTTONUP:				// ���}�E�X�{�^���������ꂽ
		setMouseLButton(false);
		mouseIn(lParam);
		return 0;
	case WM_MBUTTONDOWN:			// �����}�E�X�{�^���������ꂽ
		setMouseMButton(true);
		mouseIn(lParam);
		return 0;
	case WM_MBUTTONUP:				// �����}�E�X�{�^���������ꂽ
		setMouseMButton(false);
		mouseIn(lParam);
		return 0;
	case WM_RBUTTONDOWN:			// �E�}�E�X�{�^���������ꂽ
		setMouseRButton(true);
		mouseIn(lParam);
		return 0;
	case WM_RBUTTONUP:				// �E�}�E�X�{�^���������ꂽ
		setMouseRButton(false);
		mouseIn(lParam);
		return 0;
		// �}�E�X��X�{�^���������ꂽ/�����ꂽ
	case WM_XBUTTONDOWN:case WM_XBUTTONUP:
		setMouseXButton(wParam);
		mouseIn(lParam);
		return 0;
	}

	// �A�v���P�[�V�����ŏ������Ȃ����b�Z�[�W��OS�ɏ������Ă��炤
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	// �E�B���h�E�̏�����
	static char szAppName[] = "GameProtType.ver.0.02";

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	// �E�B���h�E�\���̂̒�`
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszClassName = szAppName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// �E�B���h�E�̓o�^
	if (!RegisterClassEx(&wc))
	{
		return E_FAIL;
	}

	//�E�C���h�E�̃N���C�A���g�̈�i=DirectX�̕`��̈�j���w��
	RECT rc = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	// �E�B���h�E�̍쐬
	g_hWnd = CreateWindow(szAppName, szAppName, WS_OVERLAPPEDWINDOW,
		0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, hInstance, 0);

	// �N���C�A���g�̈悪GAME_WIDTH x GAME_HEIGHT�ƂȂ�悤��
	// �E�B���h�E�T�C�Y�𒲐�
	RECT clientRect;
	// �E�B���h�E�̃N���C�A���g�̈�̃T�C�Y���擾
	GetClientRect(g_hWnd, &clientRect);
	MoveWindow(g_hWnd,
		0,												// ��
		0,												// ��
		WINDOW_WIDTH + (WINDOW_WIDTH - clientRect.right),	// �E
		WINDOW_HEIGHT + (WINDOW_HEIGHT - clientRect.bottom),// ��
		TRUE);											// �E�B���h�E���ĕ`��

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	return S_OK;
}


template<typename LPD3D>
void Release(LPD3D& p)
{
	if (p)p->Release();
	p = nullptr;
}

HRESULT InitDX9(HWND hwnd)
{
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!pD3D)return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	HRESULT hr = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &pDevice);

	if (FAILED(hr))return hr;

	// �X�v���C�g�̍쐬
	D3DXCreateSprite(pDevice, &sprite);

	return S_OK;
}

void ExitDX9()
{
	safeRelease(sprite);
	Release(pDevice);
	Release(pD3D);
}

void RenderDX9()
{
	pDevice->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	pDevice->BeginScene();
	// �`��
	draw();

	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	// �e�L�X�g���̕`��
	printText();
	sprite->End();

	pDevice->EndScene();
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	pDevice->Present(NULL, NULL, NULL, NULL);
}

// ����������
void initialize(HINSTANCE hInstance, HWND hWnd)
{
	// ������\�^�C�}�[�̏��������݂�
	QueryPerformanceFrequency(&timerFreq);
	QueryPerformanceCounter(&timeStart); // �J�n���Ԃ��擾
	
	audio.initialize();
	InitInput(hInstance,hWnd,false);
	initializeTextDX();
	initializeGame();
	initialized = true;
}

// �X�V����
void update()
{// �Ō�̃t���[������̌o�ߎ��Ԃ��v�Z�AframeTime�ɕۑ�
	QueryPerformanceCounter(&timeEnd);
	frameTime = (float)(timeEnd.QuadPart - timeStart.QuadPart) / (float)timerFreq.QuadPart;

	// �ȓd�̓R�[�h(winmm.h���K�v)
	// ��]����t���[�����[�g�ɑ΂��Čo�ߎ��Ԃ��Z���ꍇ
	if (frameTime < MIN_FRAME_TIME)
	{
		sleepTime = (DWORD)((MIN_FRAME_TIME - frameTime) * 1000);
		timeBeginPeriod(1);		// 1�~���b�̕���\��Windows�^�C�}�[�ɗv��
		Sleep(sleepTime);		// sleepTime�̊ԁACPU�����
		timeEndPeriod(1);		// 1�~���b�̃^�C�}�[����\���I��
		return;
	}

	if (frameTime > 0.0)
	{
		fps = (fps*0.99f) + (0.01f / frameTime);	// ����fps
	}

	if (frameTime > MAX_FRAME_TIME)					// �t���[�����[�g�����ɒx���ꍇ
	{
		frameTime = MAX_FRAME_TIME;					// �ő�t���[�����[�g�𐧌�
	}

	timeStart = timeEnd;

	gameTimer.update(frameTime);

	audio.run();
	UpdateInput();
	updateGame();
}

// �`�揈��
void draw()
{
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	drawGame();

}

void printText() 
{
	int base = 0;
	int line = 30;
	base += line;
	printTextDX(getDebugFont(), "gameTime:", 0, base,gameTimer.getTime()); base += line;
	printTextDX(getDebugFont(), "FPS:", 0, base,(int)fps); base += line;
	printGame();
}

// �I������
void unInitialize()
{
	UninitInput();
	unInitializeTextDX();
	unInitializeGame();
}

//=============================================================================
// �E�B���h�E�n���h���̎擾
//=============================================================================
HWND getHWnd()
{
	return g_hWnd;
}
//=============================================================================
// �f�o�C�X�̎擾
//=============================================================================
LPDIRECT3DDEVICE9 getDevice(void)
{
	return pDevice;
}
//=============================================================================
// �X�v���C�g�̎擾
//=============================================================================
Audio* getAudio(void)
{
	return &audio;
}
//=============================================================================
// �X�v���C�g�̎擾
//=============================================================================
LPD3DXSPRITE getSprite(void)
{
	return sprite;
}

//=============================================================================
// �t���[���^�C���̎擾
//=============================================================================
float getFrameTime(void)
{
	return frameTime;
}

//=============================================================================
// �A���t�@�����x�����N���b�h�i�l�p�`�j��\�����܂��B
// ���s�O�FcreateVertexBuffer�́A���v���̏����ŃN���b�h���`����4�̒��_���܂�
//         vertexBuffer���쐬���邽�߂Ɏg�p���ꂽ�B
//         g3ddev-> BeginScene���Ăяo���ꂽ�B
//=============================================================================
bool drawQuad(LPDIRECT3DVERTEXBUFFER9 vertexBuffer)
{
	HRESULT result = E_FAIL;	// �E�B���h�E�Y�̕W���߂�l

	if (vertexBuffer == NULL)
	{
		return false;
	}

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);	// �A���t�@�u�����h�L���ɂ���

	pDevice->SetStreamSource(0, vertexBuffer, 0, sizeof(VertexC));
	pDevice->SetFVF(D3DFVF_VERTEX);
	result = pDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false); // �A���t�@�u�����h�����ɂ���

	if (FAILED(result))
	{
		return false;
	}
	return true;

}
//=============================================================================
// ���_�o�b�t�@���쐬���܂��B
// ���s�O�Fverts[]�͒��_�f�[�^���܂�ł��܂��B
//         size = verts[]�̃T�C�Y
// ���s��F���������ꍇ�A&vertexBuffer�̓o�b�t�@�[���w���܂��B
//=============================================================================
HRESULT createVertexBuffer(VertexC verts[], UINT size, LPDIRECT3DVERTEXBUFFER9 &vertexBuffer)
{
	// �E�B���h�E�Y�̕W���߂�l
	HRESULT result = E_FAIL;

	// ���_�o�b�t�@���쐬
	result = pDevice->CreateVertexBuffer(size, D3DUSAGE_WRITEONLY, D3DFVF_VERTEX, D3DPOOL_DEFAULT, &vertexBuffer, NULL);

	if (FAILED(result))
	{
		return result;
	}

	void *ptr;

	//�f�[�^���]������Ă���O�ɁA�o�b�t�@�����b�N����K�v������܂�
	result = vertexBuffer->Lock(0, size, (void**)&ptr, 0);
	if (FAILED(result))
	{
		return result;
	}
	memcpy(ptr, verts, size);	// ���_�f�[�^���o�b�t�@�ɃR�s�[����
	vertexBuffer->Unlock();		// �o�b�t�@���A�����b�N

	return result;
}