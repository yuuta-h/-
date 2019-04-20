#pragma once

#include <Windows.h>
#include <WindowsX.h>
#include <crtdbg.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "audio.h"

#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"

//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �Q�c�|���S�����_�t�H�[�}�b�g( ���_���W[2D] / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define	NUM_VERTEX		(4)		// ���_��
#define	NUM_POLYGON		(2)		// �|���S����
// ��L�Q�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 vtx;		// ���_���W
	float rhw;				// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR diffuse;		// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
} VERTEX_2D;

struct VertexC				// ���_�J���[
{
	float x, y, z;			// ���_�ʒu
	float rhw;				// �������W�̂������̋t���i1�ɐݒ�j
	unsigned long color;	// ���_�J���[
};

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 900
#define WINDOW_CENTER_X	(WINDOW_WIDTH / 2)	// �E�C���h�E�̒��S�w���W
#define WINDOW_CENTER_Y	(WINDOW_HEIGHT / 2)	// �E�C���h�E�̒��S�x���W

const float FRAME_RATE = 100.0f;						//�^�[�Q�b�g�t���[�����[�g�i�t���[��/�b�j
const float MIN_FRAME_RATE = 30.0f;						// �ŏ��t���[�����[�g
const float	MIN_FRAME_TIME = 1.0f / FRAME_RATE;			// 1�t���[���̍ŏ��K�v����
const float MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE;		// �v�Z�Ɏg�p�����ő厞��

#define VECTOR2 D3DXVECTOR2
#define VECTOR3 D3DXVECTOR3
#define LP_DXFONT	LPD3DXFONT

//�t���L�V�u�����_�t�H�[�}�b�g�R�[�h
// D3DFVF_XYZRHW = ���_���ϊ�����܂��B
// D3DFVF_DIFFUSE = ���_�ɂ͊g�U�F�f�[�^���܂܂�Ă��܂�
#define D3DFVF_VERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

// �F�̒�`
#define COLOR_ARGB DWORD
#define SETCOLOR_ARGB(a,r,g,b) \
	((COLOR_ARGB)(((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff))
namespace colorNS
{
	// ���ʂŎg�p����F
	// ARGB�̐��l�͈̔͂�0?255
	// A =�A���t�@�`���l���i�����x�A255�͕s�����j
	// R = ��, G = ��, B = ��
	const COLOR_ARGB ORANGE = D3DCOLOR_ARGB(255, 255, 165, 0);
	const COLOR_ARGB BROWN = D3DCOLOR_ARGB(255, 139, 69, 19);
	const COLOR_ARGB LTGRAY = D3DCOLOR_ARGB(255, 192, 192, 192);
	const COLOR_ARGB GRAY = D3DCOLOR_ARGB(255, 128, 128, 128);
	const COLOR_ARGB OLIVE = D3DCOLOR_ARGB(255, 128, 128, 0);
	const COLOR_ARGB PURPLE = D3DCOLOR_ARGB(255, 128, 0, 128);
	const COLOR_ARGB MAROON = D3DCOLOR_ARGB(255, 128, 0, 0);
	const COLOR_ARGB TEAL = D3DCOLOR_ARGB(255, 0, 128, 128);
	const COLOR_ARGB GREEN = D3DCOLOR_ARGB(255, 0, 128, 0);
	const COLOR_ARGB NAVY = D3DCOLOR_ARGB(255, 0, 0, 128);
	const COLOR_ARGB WHITE = D3DCOLOR_ARGB(255, 255, 255, 255);
	const COLOR_ARGB YELLOW = D3DCOLOR_ARGB(255, 255, 255, 0);
	const COLOR_ARGB MAGENTA = D3DCOLOR_ARGB(255, 255, 0, 255);
	const COLOR_ARGB RED = D3DCOLOR_ARGB(255, 255, 0, 0);
	const COLOR_ARGB CYAN = D3DCOLOR_ARGB(255, 0, 255, 255);
	const COLOR_ARGB LIME = D3DCOLOR_ARGB(255, 0, 255, 0);
	const COLOR_ARGB BLUE = D3DCOLOR_ARGB(255, 0, 0, 255);
	const COLOR_ARGB BLACK = D3DCOLOR_ARGB(255, 0, 0, 0);
	const COLOR_ARGB SKYBLUE = D3DCOLOR_ARGB(255, 0, 204, 255);
	const COLOR_ARGB WATER = D3DCOLOR_ARGB(255, 0, 255, 255);
}




//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LPDIRECT3DDEVICE9 getDevice(void);
LPD3DXSPRITE getSprite(void);
HWND getHWnd();
Audio* getAudio();
bool drawQuad(LPDIRECT3DVERTEXBUFFER9 vertexBuffer);
HRESULT createVertexBuffer(VertexC verts[], UINT size, LPDIRECT3DVERTEXBUFFER9 &vertexBuffer);
//=============================================================================
// �|�C���^�Q�ƍ��ڂ����S�ɏ������邽�߂̊֐��e���v���[�g�B
// �����̃e���v���[�g�ɂ���Ē�`���ꂽ�֐��́A
// �ʏ�̊֐��Ăяo���\�����g�p���ČĂяo�����Ƃ��ł��܂��B
// �R���p�C���́AT���Ăяo���p�����[�^�̌^�ɒu��������֐����쐬���܂��B
//=============================================================================
// �|�C���^�Q�Ƃ����A�C�e�������S�ɉ��
template<typename T>
inline void safeRelease(T& ptr)
{
	if (ptr)
	{
		ptr->Release();
		ptr = NULL;
	}
}
#define SAFE_RELEASE safeRelease //����݊����̂��߂�
