//=============================================================================
// ���͏��� [input.cpp]
//=============================================================================
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_KEY_MAX			(256)

// game pad�p�ݒ�l
#define DEADZONE		2500			// �e����25%�𖳌��]�[���Ƃ���
#define RANGE_MAX		1000			// �L���͈͂̍ő�l
#define RANGE_MIN		-1000			// �L���͈͂̍ŏ��l

// �����׃}�E�X�p
#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC		((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE		((USHORT) 0x02)
#endif
//--------------------------

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd);
void UninitKeyboard(void);
HRESULT UpdateKeyboard(void);

HRESULT InitializeMouse(HINSTANCE hInst, HWND hWindow, bool capture); // �}�E�X�̏�����
void UninitMouse();						// �}�E�X�̏I������

HRESULT InitializePad(void);			// �p�b�h������
//BOOL CALLBACK SearchPadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID);	// �p�b�h�����R�[���o�b�N
void UpdatePad(void);
void UninitPad(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

std::string textIn;	// ���[�U�[�����͂����e�L�X�g
char charIn;									// �Ō�ɓ��͂�������
bool newLine;									// ���s�̊J�n����true
//------------------------------- keyboard
LPDIRECTINPUT8			g_pDInput = NULL;					// IDirectInput8�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECTINPUTDEVICE8	g_pDIDevKeyboard = NULL;			// IDirectInputDevice8�C���^�[�t�F�[�X�ւ̃|�C���^(�L�[�{�[�h)
BYTE					g_keyState[NUM_KEY_MAX];			// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
BYTE					g_keyStateTrigger[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
BYTE					g_keyStateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
BYTE					g_keyStateRelease[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
int						g_keyStateRepeatCnt[NUM_KEY_MAX];	// �L�[�{�[�h�̃��s�[�g�J�E���^

//--------------------------------- mouse
int mouseRawX, mouseRawY;						// ���𑜓x�̃}�E�X�f�[�^
int mouseX, mouseY;								// �}�E�X�̉�ʍ��W
RAWINPUTDEVICE Rid[1];							// �����׃}�E�X�p
bool mouseCaptured;								// �}�E�X���L���v�`�����ꂽ�ꍇ��true
bool mouseLButton;								// �}�E�X�̍��{�^����������Ă���ꍇ��true
bool mouseMButton;								// ���}�E�X�{�^����������Ă���ꍇ��true
bool mouseRButton;								// �}�E�X�̉E�{�^����������Ă���ꍇ��true
bool mouseX1Button;								// X1�̃}�E�X�{�^����������Ă���ꍇ��true
bool mouseX2Button;								// X2�̃}�E�X�{�^����������Ă���ꍇ��true

//--------------------------------- game pad
static LPDIRECTINPUTDEVICE8	pGamePad[GAMEPADMAX] = { NULL,NULL,NULL,NULL };// �p�b�h�f�o�C�X

static DWORD	padState[GAMEPADMAX];	// �p�b�h���i�����Ή��j
static DWORD	padTrigger[GAMEPADMAX];
static int		padCount = 0;			// ���o�����p�b�h�̐�


//=============================================================================
// ���͏����̏�����
//=============================================================================
HRESULT InitInput(HINSTANCE hInst, HWND hWnd,bool capture)
{
	HRESULT hr;

	if (!g_pDInput)
	{
		// DirectInput�I�u�W�F�N�g�̍쐬
		hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&g_pDInput, NULL);
	}
	newLine = true;			// �V�����s���J�n
	textIn = "";			// textIn���N���A
	charIn = 0;				// charIn���N���A
	// �L�[�{�[�h�̏�����
	InitKeyboard(hInst, hWnd);

	// �}�E�X�̏�����
	InitializeMouse(hInst, hWnd,capture);

	// �p�b�h�̏�����
	InitializePad();

	return S_OK;
}

//=============================================================================
// ���͏����̏I������
//=============================================================================
void UninitInput(void)
{
	// �L�[�{�[�h�̏I������
	UninitKeyboard();

	// �}�E�X�̏I������
	UninitMouse();

	// �p�b�h�̏I������
	UninitPad();

	if (g_pDInput)
	{
		g_pDInput->Release();
		g_pDInput = NULL;
	}
}

//=============================================================================
// ���͏����̍X�V����
//=============================================================================
void UpdateInput(void)
{
	// �L�[�{�[�h�̍X�V
	UpdateKeyboard();

	// �}�E�X�̍X�V
	//UpdateMouse();

	// �p�b�h�̍X�V
	UpdatePad();

}

//=============================================================================
// �L�[�{�[�h�̏�����
//=============================================================================
HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	// �f�o�C�X�I�u�W�F�N�g���쐬
	hr = g_pDInput->CreateDevice(GUID_SysKeyboard, &g_pDIDevKeyboard, NULL);
	if (FAILED(hr) || g_pDIDevKeyboard == NULL)
	{
		MessageBox(hWnd, "�L�[�{�[�h���˂��I", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = g_pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = g_pDIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	g_pDIDevKeyboard->Acquire();

	return S_OK;
}

//=============================================================================
// �L�[�{�[�h�̏I������
//=============================================================================
void UninitKeyboard(void)
{
	if (g_pDIDevKeyboard)
	{
		g_pDIDevKeyboard->Release();
		g_pDIDevKeyboard = NULL;
	}
}

//=============================================================================
// �L�[�{�[�h�̍X�V
//=============================================================================
HRESULT UpdateKeyboard(void)
{
	HRESULT hr;
	BYTE keyStateOld[256];

	// �O��̃f�[�^��ۑ�
	memcpy(keyStateOld, g_keyState, NUM_KEY_MAX);

	// �f�o�C�X����f�[�^���擾
	hr = g_pDIDevKeyboard->GetDeviceState(sizeof(g_keyState), g_keyState);
	if (SUCCEEDED(hr))
	{
		for (int cnt = 0; cnt < NUM_KEY_MAX; cnt++)
		{
			g_keyStateTrigger[cnt] = (keyStateOld[cnt] ^ g_keyState[cnt]) & g_keyState[cnt];
			g_keyStateRelease[cnt] = (keyStateOld[cnt] ^ g_keyState[cnt]) & ~g_keyState[cnt];
			g_keyStateRepeat[cnt] = g_keyStateTrigger[cnt];

			if (g_keyState[cnt])
			{
				g_keyStateRepeatCnt[cnt]++;
				if (g_keyStateRepeatCnt[cnt] >= 20)
				{
					g_keyStateRepeat[cnt] = g_keyState[cnt];
				}
			}
			else
			{
				g_keyStateRepeatCnt[cnt] = 0;
				g_keyStateRepeat[cnt] = 0;
			}
		}
	}
	else
	{
		// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
		g_pDIDevKeyboard->Acquire();
	}

	return S_OK;
}

// �N���A�e�L�X�g���̓o�b�t�@
void clearTextIn()
{
	textIn.clear(); 
}
// �e�L�X�g���͂𕶎���Ƃ��ĕԂ�
std::string getTextIn()
{
	return textIn; 
}

// �Ō�ɓ��͂���������Ԃ��܂�
char getCharIn() 
{
	return charIn; 
}

//=============================================================================
// ���͂��ꂽ������textIn������ɕۑ�
// ���s�O�FwParam�ɁA�������i�[����Ă���
//=============================================================================
void keyIn(WPARAM wParam)
{
	if (newLine)					// �V�����s�̊J�n�̏ꍇ
	{
		textIn.clear();
		newLine = false;
	}

	if (wParam == '\b')				// �o�b�N�X�y�[�X�L�[�̏ꍇ
	{
		if (textIn.length() > 0)		// ���������݂���ꍇ
		{
			textIn.erase(textIn.size() - 1);	// �Ō�ɓ��͂��ꂽ����������
		}
	}
	else {
		textIn += wParam;						// ������textIn�ɒǉ�
		charIn = wParam;						// �Ō�ɓ��͂��ꂽ������ۑ�
	}
	if ((char)wParam == '\r')					// ���^�[���L�[�̏ꍇ
	{
		newLine = true;							// �V�����s���J�n
	}
}
//=============================================================================
// �L�[�{�[�h�̃v���X��Ԃ��擾
//=============================================================================
bool GetKeyboardPress(int key)
{
	return (g_keyState[key] & 0x80) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̃g���K�[��Ԃ��擾
//=============================================================================
bool GetKeyboardTrigger(int key)
{
	return (g_keyStateTrigger[key] & 0x80) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̃��s�[�g��Ԃ��擾
//=============================================================================
bool GetKeyboardRepeat(int key)
{
	return (g_keyStateRepeat[key] & 0x80) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̃����|�X��Ԃ��擾
//=============================================================================
bool GetKeyboardRelease(int key)
{
	return (g_keyStateRelease[key] & 0x80) ? true : false;
}


//=============================================================================
// �}�E�X�֌W�̏���
//=============================================================================
// �}�E�X�̏�����
HRESULT InitializeMouse(HINSTANCE hInst, HWND hWindow,bool capture)
{
	// �}�E�X�f�[�^
	mouseX = 0;				// ���X
	mouseY = 0;				// ���Y
	mouseRawX = 0;			// ������X
	mouseRawY = 0;			// ������Y
	mouseLButton = false;	// ���}�E�X�{�^����������Ă���ꍇ��true
	mouseMButton = false;	// �����}�E�X�{�^����������Ă���ꍇ��true
	mouseRButton = false;	// �E�}�E�X�{�^����������Ă���ꍇ��true
	mouseX1Button = false;	// X1�}�E�X�{�^����������Ă���ꍇ��true
	mouseX2Button = false;	// X2�}�E�X�{�^����������Ă���ꍇ��true

	mouseCaptured = capture;

	// �����׃}�E�X��o�^
	Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
	Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
	Rid[0].dwFlags = RIDEV_INPUTSINK;
	Rid[0].hwndTarget = hWindow;
	RegisterRawInputDevices(Rid, 1, sizeof(Rid[0]));

	if (mouseCaptured)
	{
		SetCapture(hWindow);	// �}�E�X���L���v�`��
	}
	return S_OK;
}
//---------------------------------------------------------
void UninitMouse()
{
	if (mouseCaptured)
	{
		ReleaseCapture(); // �}�E�X�����
	}
}
//=============================================================================
// �}�E�X�̉�ʈʒu��ǂݎ��AmouseX��mouseY�ɕۑ�
//=============================================================================

void mouseIn(LPARAM lParam)
{
	mouseX = GET_X_LPARAM(lParam);
	mouseY = GET_Y_LPARAM(lParam);
}
//=============================================================================
// �}�E�X����̃��[�f�[�^��ǂݎ��AmouseRawX��mouseRawY�ɕۑ�
// ���̃��[�`���́A�����׃}�E�X�ɑΉ����Ă��܂��B
//=============================================================================

void mouseRawIn(LPARAM lParam)
{
	UINT dwSize = 40;
	static BYTE lpb[40];
	GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));

	RAWINPUT* raw = (RAWINPUT*)lpb;

	if (raw->header.dwType == RIM_TYPEMOUSE)
	{
		mouseRawX = raw->data.mouse.lLastX;
		mouseRawY = raw->data.mouse.lLastY;
	}
}
//-----------------------------------------------------------
void mouseClear(UCHAR what)
{
	// �}�E�X���N���A����ꍇ
	if (what & MOUSE)
	{
		mouseX = 0;
		mouseY = 0;
		mouseRawX = 0;
		mouseRawY = 0;
	}
}

//---------------------------- mouse
// �}�E�X�{�^���̏�Ԃ�ۑ�
void setMouseLButton(bool b) { mouseLButton = b; }

// �}�E�X�{�^���̏�Ԃ�ۑ�
void setMouseMButton(bool b) { mouseMButton = b; }

// �}�E�X�{�^���̏�Ԃ�ۑ�
void setMouseRButton(bool b) { mouseRButton = b; }

// �}�E�X�{�^���̏�Ԃ�ۑ�
void setMouseXButton(WPARAM wParam) {
	mouseX1Button = (wParam & MK_XBUTTON1) ? true : false;
	mouseX2Button = (wParam & MK_XBUTTON2) ? true : false;
}

// �}�E�X��X�ʒu��߂�
int getMouseX() { return mouseX; }

// �}�E�X��Y�ʒu��߂�
int getMouseY() { return mouseY; }

// �}�E�X��X�ʒu�̈ړ��̃��[�f�[�^��߂��B���ւ̈ړ���<0�A�E�ւ̈ړ���>0
//�����׃}�E�X�ƌ݊���������܂��B
int getMouseRawX() { return mouseRawX; }

// �}�E�X��Y�ʒu�̈ړ��̃��[�f�[�^��߂��B���ւ̈ړ���<0�A�E�ւ̈ړ���>0
// �����׃}�E�X�ƌ݊���������܂��B
int getMouseRawY() { return mouseRawY; }

// ���}�E�X�{�^���̏�Ԃ�߂�
bool getMouseLButton() { return mouseLButton; }

// �����}�E�X�{�^���̏�Ԃ�߂�
bool getMouseMButton() { return mouseMButton; }

// �E�}�E�X�{�^���̏�Ԃ�߂�
bool getMouseRButton() { return mouseRButton; }

// X1�}�E�X�{�^���̏�Ԃ�߂�
bool getMouseX1Button() { return mouseX1Button; }

// X2�}�E�X�{�^���̏�Ԃ�߂�
bool getMouseX2Button() { return mouseX2Button; }

//================================================= game pad
//---------------------------------------- �R�[���o�b�N�֐�
BOOL CALLBACK SearchGamePadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID)
{
	HRESULT result;

	result = g_pDInput->CreateDevice(lpddi->guidInstance, &pGamePad[padCount++], NULL);
	return DIENUM_CONTINUE;	// ���̃f�o�C�X���

}
//---------------------------------------- ������
HRESULT InitializePad(void)			// �p�b�h������
{
	HRESULT		result;
	int			i;

	padCount = 0;
	// �W���C�p�b�h��T��
	g_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, (LPDIENUMDEVICESCALLBACK)SearchGamePadCallback, NULL, DIEDFL_ATTACHEDONLY);
	// �Z�b�g�����R�[���o�b�N�֐����A�p�b�h�𔭌������������Ă΂��B

	for (i = 0; i<padCount; i++) {
		// �W���C�X�e�B�b�N�p�̃f�[�^�E�t�H�[�}�b�g��ݒ�
		result = pGamePad[i]->SetDataFormat(&c_dfDIJoystick);
		if (FAILED(result))
			return false; // �f�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s

						  // ���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
						  //		result = pGamePad[i]->SetCooperativeLevel(hWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
						  //		if ( FAILED(result) )
						  //			return false; // ���[�h�̐ݒ�Ɏ��s

						  // ���̒l�͈̔͂�ݒ�
						  // X���AY���̂��ꂼ��ɂ��āA�I�u�W�F�N�g���񍐉\�Ȓl�͈̔͂��Z�b�g����B
						  // (max-min)�́A�ő�10,000(?)�B(max-min)/2�������l�ɂȂ�B
						  // ����傫������΁A�A�i���O�l�ׂ̍��ȓ�����߂炦����B(�p�b�h�̐��\�ɂ��)
		DIPROPRANGE				diprg;
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = RANGE_MIN;
		diprg.lMax = RANGE_MAX;
		// X���͈̔͂�ݒ�
		diprg.diph.dwObj = DIJOFS_X;
		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Y���͈̔͂�ݒ�
		diprg.diph.dwObj = DIJOFS_Y;
		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �e�����ƂɁA�����̃]�[���l��ݒ肷��B
		// �����]�[���Ƃ́A��������̔����ȃW���C�X�e�B�b�N�̓����𖳎�����͈͂̂��ƁB
		// �w�肷��l�́A10000�ɑ΂��鑊�Βl(2000�Ȃ�20�p�[�Z���g)�B
		DIPROPDWORD				dipdw;
		dipdw.diph.dwSize = sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
		dipdw.diph.dwHow = DIPH_BYOFFSET;
		dipdw.dwData = DEADZONE;
		//X���̖����]�[����ݒ�
		dipdw.diph.dwObj = DIJOFS_X;
		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//Y���̖����]�[����ݒ�
		dipdw.diph.dwObj = DIJOFS_Y;
		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);

		//�W���C�X�e�B�b�N���͐���J�n
		pGamePad[i]->Acquire();
	}

	return true;

}
//------------------------------------------- �I������
void UninitPad(void)
{
	for (int i = 0; i<GAMEPADMAX; i++) {
		if (pGamePad[i])
		{
			pGamePad[i]->Unacquire();
			pGamePad[i]->Release();
		}
	}

}

//------------------------------------------ �X�V
void UpdatePad(void)
{
	HRESULT			result;
	DIJOYSTATE2		dijs;
	int				i;

	for (i = 0; i<padCount; i++)
	{
		DWORD lastPadState;
		lastPadState = padState[i];
		padState[i] = 0x00000000l;	// ������

		result = pGamePad[i]->Poll();	// �W���C�X�e�B�b�N�Ƀ|�[����������
		if (FAILED(result)) {
			result = pGamePad[i]->Acquire();
			while (result == DIERR_INPUTLOST)
				result = pGamePad[i]->Acquire();
		}

		result = pGamePad[i]->GetDeviceState(sizeof(DIJOYSTATE), &dijs);	// �f�o�C�X��Ԃ�ǂݎ��
		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED) {
			result = pGamePad[i]->Acquire();
			while (result == DIERR_INPUTLOST)
				result = pGamePad[i]->Acquire();
		}

		// �R�Q�̊e�r�b�g�ɈӖ����������A�{�^�������ɉ����ăr�b�g���I���ɂ���
		//* y-axis (forward)
		if (dijs.lY < 0)					padState[i] |= BUTTON_UP;
		//* y-axis (backward)
		if (dijs.lY > 0)					padState[i] |= BUTTON_DOWN;
		//* x-axis (left)
		if (dijs.lX < 0)					padState[i] |= BUTTON_LEFT;
		//* x-axis (right)
		if (dijs.lX > 0)					padState[i] |= BUTTON_RIGHT;
		//* �`�{�^��
		if (dijs.rgbButtons[0] & 0x80)	padState[i] |= BUTTON_A;
		//* �a�{�^��
		if (dijs.rgbButtons[1] & 0x80)	padState[i] |= BUTTON_B;
		//* �b�{�^��
		if (dijs.rgbButtons[2] & 0x80)	padState[i] |= BUTTON_C;
		//* �w�{�^��
		if (dijs.rgbButtons[3] & 0x80)	padState[i] |= BUTTON_X;
		//* �x�{�^��
		if (dijs.rgbButtons[4] & 0x80)	padState[i] |= BUTTON_Y;
		//* �y�{�^��
		if (dijs.rgbButtons[5] & 0x80)	padState[i] |= BUTTON_Z;
		//* �k�{�^��
		if (dijs.rgbButtons[6] & 0x80)	padState[i] |= BUTTON_L;
		//* �q�{�^��
		if (dijs.rgbButtons[7] & 0x80)	padState[i] |= BUTTON_R;
		//* �r�s�`�q�s�{�^���i�E�X�e�B�b�N�A-�{�^���j
		if (dijs.rgbButtons[8] & 0x80)	padState[i] |= BUTTON_START;
		//* �l�{�^��(���X�e�B�b�N�A+�{�^��)
		if (dijs.rgbButtons[9] & 0x80)	padState[i] |= BUTTON_M;

		// �z�[���{�^���i�E�X�e�B�b�N�j
		if (dijs.rgbButtons[12] & 0x80)	padState[i] |= BUTTON_HOME;

		//ZR�{�^���i�W���C�R���j
		if (dijs.rgbButtons[14] & 0x80)	padState[i] |= BUTTON_LR;

		if (dijs.rgbButtons[15] & 0x80)	padState[i] |= BUTTON_ZLR;

		//�W���C�R���X�e�B�b�N����*���쎲�ɒ���*
		if (dijs.rgdwPOV[0] == POV::UP)				padState[i] |= STICK_UP;

		if (dijs.rgdwPOV[0] == POV::RIGHT)			padState[i] |= STICK_RIGHT;

		if (dijs.rgdwPOV[0] == POV::DOWN)			padState[i] |= STICK_DOWN;

		if (dijs.rgdwPOV[0] == POV::LEFT)			padState[i] |= STICK_LEFT;

		//�΂ߓ���
		if (dijs.rgdwPOV[0] == POV::RIGHTUP)		padState[i] |= STICK_RIGHTUP;

		if (dijs.rgdwPOV[0] == POV::RIGHTDOWN)		padState[i] |= STICK_RIGHTDOWN;

		if (dijs.rgdwPOV[0] == POV::LEFTUP)			padState[i] |= STICK_LEFTUP;

		if (dijs.rgdwPOV[0] == POV::LEFTDOWN)		padState[i] |= STICK_LEFTDOWN;

		// Trigger�ݒ�
		padTrigger[i] = ((lastPadState ^ padState[i])	// �O��ƈ���Ă���
			& padState[i]);					// ��������ON�̂��

	}

}
//----------------------------------------------- ����
BOOL IsButtonPressed(int padNo, DWORD button)
{
	return (button & padState[padNo]);
}

BOOL IsButtonTriggered(int padNo, DWORD button)
{
	return (button & padTrigger[padNo]);
}