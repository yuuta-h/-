#include "image.h"

void InitImage(Image* image, LPDIRECT3DTEXTURE9* texture,
	float x, float y, float width, float height)
{
	LPDIRECT3DDEVICE9 pDevice = getDevice();
	image->g_pD3DTexture = *texture;
	image->position = D3DXVECTOR3(x, y, 0.0f);
	image->width = width;
	image->height = height;
	image->color[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	image->color[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	image->color[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	image->color[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	image->playAnime = false;
	image->g_nCountAnime = 0;
	image->g_nPatternAnime = 0;
	image->ANIME_TIME = 1;
	image->ANIME_PATTERN = 1;
	image->DIVIDE_U = 1;
	image->DIVIDE_V = 1;
	image->renderFlag = true;
	// ���_���̍쐬
	MakeVertex(image, pDevice);
}

void InitAnimeImage(Image* image, LPDIRECT3DTEXTURE9* texture,
	float x, float y, float width, float height,
	int time, int pattern, int divide_u, int divide_v)
{
	InitImage(image, texture, x, y, width, height);//�W��������
	image->playAnime = true;
	image->g_nCountAnime = 0;
	image->g_nPatternAnime = 0;
	image->ANIME_TIME = time;
	if (pattern == 0) { image->ANIME_PATTERN = 1; }
	else { image->ANIME_PATTERN = pattern; }
	image->DIVIDE_U = divide_u;
	image->DIVIDE_V = divide_v;
}

void UninitImage(Image* image)
{
	if (image->g_pD3DTexture != NULL)
	{// �e�N�X�`���̊J��
		image->g_pD3DTexture->Release();
		image->g_pD3DTexture = NULL;
	}
	if (image->g_pD3DVtxBuffer != NULL)
	{// �e�N�X�`���̊J��
		image->g_pD3DVtxBuffer->Release();
		image->g_pD3DVtxBuffer = NULL;
	}
}

void DrawImage(Image* image)
{
	if (!image->renderFlag)return;//�`��t���O��true�łȂ��ꍇ�A�`�悵�Ȃ�
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	if (image->playAnime) {
		// �A�j���[�V����
		image->g_nCountAnime++;

		// �A�j���[�V����Wait�`�F�b�N
		if ((image->g_nCountAnime % image->ANIME_TIME) == 0)
		{
			// �p�^�[���̐؂�ւ�
			image->g_nPatternAnime = (image->g_nPatternAnime + 1) % image->ANIME_PATTERN;
			SetTexture(image);
		}
	}
	// �����_�����O���[�h�̐ݒ�
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, image->g_pD3DVtxBuffer, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, image->g_pD3DTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}


void setSize(Image* image, float _width, float _height) {
	image->width = _width;
	image->height = _height;

	float x = image->position.x;
	float y = image->position.y;
	float width = image->width;
	float height = image->height;
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		image->g_pD3DVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(x, y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(x + width, y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(x, y + height, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(x + width, y + height, 0.0f);

		// ���_�f�[�^���A�����b�N����
		image->g_pD3DVtxBuffer->Unlock();
	}
};

void setPosition(Image* image, float _x, float _y)
{
	image->position.x = _x;
	image->position.y = _y;
	float x = image->position.x;
	float y = image->position.y;
	float width = image->width;
	float height = image->height;
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		image->g_pD3DVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(x, y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(x + width, y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(x, y + height, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(x + width, y + height, 0.0f);

		// ���_�f�[�^���A�����b�N����
		image->g_pD3DVtxBuffer->Unlock();
	}
};

// Image�̃J���[��ύX����
void SetColorImage(Image* image, D3DXCOLOR color)
{
	image->color[0] = color;
	image->color[1] = color;
	image->color[2] = color;
	image->color[3] = color;

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		image->g_pD3DVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = image->color[0];
		pVtx[1].diffuse = image->color[1];
		pVtx[2].diffuse = image->color[2];
		pVtx[3].diffuse = image->color[3];

		// ���_�f�[�^���A�����b�N����
		image->g_pD3DVtxBuffer->Unlock();
	}

}



void SetTexture(Image* image)
{
	// �e�N�X�`�����W�̐ݒ�
	int x = image->g_nPatternAnime % image->DIVIDE_U;
	int y = image->g_nPatternAnime / image->DIVIDE_U;
	float sizeX = 1.0f / image->DIVIDE_U;
	float sizeY = 1.0f / image->DIVIDE_V;

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		image->g_pD3DVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		pVtx[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		pVtx[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		pVtx[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

		// ���_�f�[�^���A�����b�N����
		image->g_pD3DVtxBuffer->Unlock();
	}
}

void SetTexture(Image* image, float ratioU, float ratioV)
{
	// �e�N�X�`�����W�̐ݒ�
	int x = 0;
	int y = 0;
	float sizeX = ratioU;
	float sizeY = ratioV;

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		image->g_pD3DVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		pVtx[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		pVtx[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		pVtx[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

		// ���_�f�[�^���A�����b�N����
		image->g_pD3DVtxBuffer->Unlock();
	}
}

HRESULT MakeVertex(Image* image, LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&image->g_pD3DVtxBuffer,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		image->g_pD3DVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

		float x = image->position.x;
		float y = image->position.y;
		float width = image->width;
		float height = image->height;


		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(x, y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(x + width, y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(x, y + height, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(x + width, y + height, 0.0f);

		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = image->color[0];
		pVtx[1].diffuse = image->color[1];
		pVtx[2].diffuse = image->color[2];
		pVtx[3].diffuse = image->color[3];

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		image->g_pD3DVtxBuffer->Unlock();
	}

	return S_OK;
}
