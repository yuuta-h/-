//����
#pragma once

#include "main.h"
#include "Image.h"
#include "input.h"
enum objTypes{
	NO_TYPE = -1,
		CHARA_PLAYER,
		CHARA_BLACKHOLE,
		CHARA_WHITEHOLE,
		CHARA_COMET,
		CHARA_KEY,
		CHARA_COIN,
		STAGE_HURDLE,
		STAGE_WALL,
		STAGE_LOCK,
		EVENT_GOAL,
	FROMFILE_TYPE_MAX,
		UI_CURSOR,
		UI_EFFECT,
		UI_HP,
	TYPE_MAX
};

//short��-0.5�}32767.5�Aint��-0.5�}2147483647.5

//************************************************************************
//�I�u�W�F�N�g�̈���
// �Ƃ肠���������o�ϐ��͎b��B�K�v�ɉ����đ��₵���茸�炵���肷�邩���B
// ���̏ꍇ�͊֘A����(�֐��Ƃ�)�C�����Ă����Ƃ��肪�����B
//************************************************************************
typedef struct _obj{
	objTypes m_type;					//�I�u�W�F�N�g�^�C�v
	short	 m_id;						//�S�^�C�v�������Ă���z����́A�����̔ԍ�
	bool	 m_use;						//use�t���O
	_obj*	 m_ptr;						//���g�ւ̃|�C���^
	_obj*	 m_tar;						//�^�[�Q�b�g�̃|�C���^(��{�̓u���b�N�z�[��)

	D3DXVECTOR2	m_pos;					//���W
	float		m_rot;					//�p�x
	D3DXVECTOR2 m_scl;					//�傫��

	D3DXVECTOR2 m_speed;				//���x
	D3DXVECTOR2 m_accel;				//�����x(���̃I�u�W�F�N�g����y�ڂ����́A�����Ƃ�)
	D3DXVECTOR2 m_attract;				//���́@(�����ȊO�̃I�u�W�F�N�g�ɋy�ڂ��͂Ƃ�)

	int		m_time;						//�v���C���[�Ƃ͓Ɨ����ď���ɓ����I�u�W�F�N�g������Ύg��(�X�e�[�W�M�~�b�N�n)
	short	m_mode;						//����A�s���p�^�[���Ƃ��͂�����


	float m_rad;						//���a(�v���C���[�̓����蔻��Ƃ�)
	D3DXVECTOR2 m_rect;					//��`�̕Ӓ�(�X�e�[�W�̓����蔻��Ƃ�)
	//�ՓˈȊO�ł��g���Ȃ�z��ɂȂ邩��(�ߊ��Ɠ����o���Ƃ��A�u���b�N�z�[�����z���񂹎n�߂�͈͂Ƃ�)

	Image m_image;						//�`����
}ObjStr;//Structure

typedef struct {//�S�������Ă�\����
	int m_STAGE;						//�X�e�[�W�ԍ�
	int m_OBJNUM;						//�I�u�W�F�N�g��
	ObjStr *m_Obj;						//�I�u�W�F�N�g
}StageObj;

#define STUB_OBJNUM (100)	//�X�e�[�W�̃f�[�^���ɂ���I�u�W�F�N�g�̑���/���ۂɂ͊O������炤�l
#define PLUS_OBJNUM (5)		//�X�e�[�W���ŕۑ�����K�v�̂Ȃ��I�u�W�F�N�g���(UI�Ȃ�)������΂���̐�


void initializeObject(StageObj* p_stgobj,int stage);
void uninitializeObject(StageObj* p_stgobj);
void updateObject(StageObj* p_stgobj);
void drawObject(StageObj* p_stgobj);
void printObject(StageObj* p_stgobj);
