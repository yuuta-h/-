//����
#pragma once

#include "main.h"
#include "Image.h"

enum objTypes{
	NO_TYPE = -1,
		CHARA_PLAYER,
		CHARA_BLACKHOLE,
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

//�I�u�W�F�N�g�̈���
//�G[0]���A�G[1]���A�G[2]���cetc
typedef struct{
	objTypes m_type;					//�I�u�W�F�N�g�^�C�v
	short m_id;							//�S�^�C�v�������Ă���z����́A�����̔ԍ�
	bool m_use;							//use�t���O

	int m_time;							//�v���C���[�Ƃ͓Ɨ����ď���ɓ����I�u�W�F�N�g������Ύg������
	short m_mode;						//����

	D3DXVECTOR2 m_pos;					//���W
	float m_rot;						//�p�x
	D3DXVECTOR2 m_scl;					//�傫��

	float m_rad;						//���a(�v���C���[�̓����蔻��Ƃ�)
	D3DXVECTOR2 m_rect;					//��`�̕Ӓ�(�X�e�[�W�̓����蔻��Ƃ�)
	//�ՓˈȊO�ł��g���Ȃ�z��ɂȂ邩��(�ߊ��Ɠ����o���Ƃ��A�u���b�N�z�[�����z���񂹎n�߂�͈͂Ƃ�)

	Image m_image;						//�`����
}ObjStr;//Structure


bool initializeObject(int stage);
void uninitializeObject(void);
void updateObject(void);
void drawObject(void);

