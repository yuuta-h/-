#pragma once
#ifndef _READ_TEXT_H_
#define _READ_TEXT_H_

#include <fstream>//����0.02
#include <iostream>//����0.02
#include <string>//����0.02
#include <sstream>//����0.02
using namespace std;//����0.02


// �R�����g�̕t������ϐ����ɂ��ăA�h�o�C�X���������B

//**************************************************************************
// �I�u�W�F�N�g�\����
//**************************************************************************
typedef struct
{
	int hp;
	int mp;
	int pos;
	// D3DXVECTOR2 pos;

}Object;

typedef struct
{

	//string *stage_file;
	Object *m_pObj = NULL;
	int num_m_pObj;	// �s�� = �I�u�W�F�N�g�̐�
}Stage;

enum
{
	HP = 0,
	MP,
	POS,
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

// �Ăяo���p�֐��@�g���Ƃ��͂��̊֐�����
void read_Status_File(string file_name);

// �\����Stage�̏������ƃe�L�X�g�t�@�C�������Ԃɓn���Ă����֐�
void open_All_txt(string file_name, stringstream &strstream, string *information);  // �e�L�X�g�t�@�C���̐��ƃt�@�C�������t�@�C���̐���������Ă���
void file_Open(string file_name, string *stream_txt_name, stringstream &strstream); // �t�@�C�����I�[�v�����Astring��stream�ɏ����i�[����B

// �\����Object�Ɋւ���֐�
void create_Origin_Object(stringstream &istream_single_txt, int current_txt); // �\���̂����ۂɍ���Ă����֐�
int how_Much_Line_and_Comma(int &line, string str, int current_txt); // �s�����\���̂̐��Ɓ@,���ϐ��̐��𐔂���
void substitution_Status_for_Structures_Var(istringstream &stream, int num_obj, int num_comma, int &obj_number, int current_txt); // �\���̓��̕ϐ��̐�����������J��Ԃ��֐�

// ���̑�
void uninit_Stage_Struct();
Stage *get_g_pStage(int no);

#endif



