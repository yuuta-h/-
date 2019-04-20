#pragma once

#include "main.h"

typedef struct {
	LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffer = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
	D3DXCOLOR color[4]; // �摜�̒��_�J���[
	D3DXVECTOR3 position; // �摜�̈ʒu
	float width; // ��
	float height; // ����
	bool playAnime; // �A�j���[�V�����Đ��t���O
	int	g_nCountAnime; // �A�j���[�V�����J�E���g(�X�V�t���[�����̕ۑ�)
	int	g_nPatternAnime;	// �A�j���[�V�����p�^�[���i���o�[
	int ANIME_TIME; // �A�j���[�V��������(�t���[����)
	int ANIME_PATTERN; // �A�j���[�V�����p�^�[����
	int DIVIDE_U; // �e�N�X�`��U����[��/x����]������ 
	int DIVIDE_V; // �e�N�X�`��V����[�c/y����]������
	bool renderFlag; // �`��t���O
}Image;

// image: ����������Image�\����
// texture: Image�Ɏg�p����e�N�X�`���|�C���^
// x:��ʏ�Ŕz�u����x�ʒu
// y:��ʏ�Ŕz�u����y�ʒu
// width:Image�I�u�W�F�N�g�̕�
// height:Image�I�u�W�F�N�g�̍���
void InitImage(Image* image, LPDIRECT3DTEXTURE9* texture,
	float x, float y, float width, float height);

// �A�j���[�V�����t��Image�̏�����
// image: ����������Image�\����
// texture: Image�Ɏg�p����e�N�X�`���|�C���^
// x:��ʏ�Ŕz�u����x�ʒu
// y:��ʏ�Ŕz�u����y�ʒu
// width:Image�I�u�W�F�N�g�̕�
// height:Image�I�u�W�F�N�g�̍���
// time:�P�A�j���[�V����������̃t���[����
// pattern:�A�j���[�V�����̃p�^�[����
// divide_u:��[U]�����̕�����
// divide_v:��[V]�����̕�����
void InitAnimeImage(Image* image, LPDIRECT3DTEXTURE9* texture,
	float x, float y, float width, float height,
	int time, int pattern, int divide_u, int divide_v);


void UninitImage(Image* image);
void DrawImage(Image* image);

// Image�̃e�N�X�`���ʒu���Z�b�g����
void SetTexture(Image* image);
void SetTexture(Image* image, float ratioU, float ratioV);


// Image�̈ʒu��ύX����
void setPosition(Image* image, float _x, float _y);
// Image�̃T�C�Y��ύX����
void setSize(Image* image, float _width, float _height);
// Image�̃J���[��ύX����
void SetColorImage(Image* image, D3DXCOLOR color);
HRESULT MakeVertex(Image* image, LPDIRECT3DDEVICE9 pDevice);

