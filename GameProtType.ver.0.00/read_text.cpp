#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS//����0.02
//#include <fstream>//����0.02
//#include <iostream>//����0.02
//#include <string>//����0.02
//#include <sstream>//����0.02
//using namespace std;//����0.02
#include "read_text.h"

////=============================================================================
////�@�O���[�o���ϐ�
////=============================================================================
Stage *g_pStage;

// �Ăяo���p�֐�
void read_Status_File(string file_name)
{
	string *information = NULL; // �ǂݍ��񂾃t�@�C���̏��̊i�[��
	stringstream stream_txt_name; // �ǂݍ��񂾃t�@�C�����𕶎���f�[�^�֕ϊ�����

	// �C���t�H���[�V�����t�@�C�����J��
	file_Open(file_name, information, stream_txt_name);
	open_All_txt(file_name, stream_txt_name, information);
}

// �e�L�X�g�̐��������ꂼ��̕ϐ��ɓ��ꍞ��ł����B
void substitution_Status_for_Structures_Var(istringstream &stream, int num_obj, int num_comma, int &obj_number, int current_txt)
{
	int raw = NULL;	// ����i,�j�ځH
	string status;

	while (getline(stream, status, ','))
	{
		switch (raw)
		{
		case HP:
			g_pStage[current_txt].m_pObj[obj_number].hp = atoi(status.c_str());
			raw++;
			continue;

		case MP:
			g_pStage[current_txt].m_pObj[obj_number].mp = atoi(status.c_str());
			raw++;
			continue;

		case POS:
			g_pStage[current_txt].m_pObj[obj_number].pos = atoi(status.c_str());
			raw++;
			continue;
		}
	}
	printf("%d \n", g_pStage[current_txt].m_pObj[obj_number].hp);
	obj_number++;
}

// �t�@�C�����I�[�v�����Astring��stream�ɏ����i�[����B
void file_Open(string file_name, string *information, stringstream &strstream)
{
	ifstream fin; // �t�@�C���ǂݍ��݃N���X

	file_name.insert(0, "stage\\");

	fin.open(file_name, ios::in); // �w�肵���t�@�C�����J��
	if (!fin) {//�G���[���m
		cout << "Error: cannot open file(" << file_name << ")" << endl;
		// �I���ҋ@
		cout << "Ctrl+Z  Enter �ŏI��\n";
		char  ch;
		while (cin.get(ch));
		//return 0;
	}
	strstream << fin.rdbuf();// �ǂݍ��񂾃t�@�C�����𕶎���X�g���[���֊i�[
	information = &strstream.str();// ������X�g���[���̕��������i�[
	fin.close(); // �t�@�C�������
}

// �e�L�X�g�t�@�C���̐������\���̂����A�I�u�W�F�N�g������Ă���
void open_All_txt(string file_name, stringstream &stream_txt_name, string *information)
{
	string single_txt_name;
	stringstream stream_single_txt;
	int current_txt = 0;
	int number_of_txt = 0;

	while (getline(stream_txt_name, single_txt_name, ','))
	{
		if (current_txt > number_of_txt)
		{
			break;
		}

		istringstream isingle_txt_name(single_txt_name);

		if (number_of_txt == 0)
		{
			// �e�L�X�g�̐������\���̂����
			number_of_txt = atoi(single_txt_name.c_str());
			g_pStage = (Stage*)malloc(number_of_txt * sizeof(Stage));
			current_txt++;
			continue;
		}

		stream_single_txt.str("");
		stream_single_txt.clear(stringstream::goodbit);
		file_Open(single_txt_name, information, stream_single_txt); // stage�t�@�C�������Ԃɓǂ�ł���
		create_Origin_Object(stream_single_txt, current_txt);  // �I�u�W�F�N�g�����
		current_txt++; // ���̃e�L�X�g�Ɉڂ�

	}
}

// ���ۂɍ\���̂ɐ����������Ă���
void create_Origin_Object(stringstream &istream_single_txt, int current_txt)
{
	int num_comma; // �R���}�̐�
	int line_number = NULL;		// �����s�ځH
	int obj_number = 0;
	current_txt--;

	string str_current_line;		// �P�s��ۑ�����

	while (getline(istream_single_txt, str_current_line))
	{
		istringstream istr_current_line(str_current_line);

		// �I�u�W�F�N�g�̐��ƃR���}�̐�����
		if (line_number == 1)
		{
			num_comma = how_Much_Line_and_Comma(line_number, str_current_line, current_txt);
		}
		if (line_number == 0)
		{
			g_pStage[current_txt].num_m_pObj = how_Much_Line_and_Comma(line_number, str_current_line, current_txt);
		}

		if (line_number > 2)
		{
			substitution_Status_for_Structures_Var(istr_current_line, g_pStage[current_txt].num_m_pObj, num_comma, obj_number, current_txt);
		}

		if (line_number == 2)
		{
			line_number++;
		}
	}
}

// �s�̐��� , �̐��𐔂���
int how_Much_Line_and_Comma(int &line, string str, int current_txt)
{
	int num;

	if (line == 0)
	{
		num = atoi(str.c_str());
		g_pStage[current_txt].m_pObj = (Object*)malloc(num * sizeof(Object));
		line++;
		return num;
	}
	else if (line == 1)
	{
		num = atoi(str.c_str());
		line++;
		return num;
	}
}

Stage *get_g_pStage(int no) { return (&g_pStage[no]); }

void uninit_Stage_Struct()
{
	free(g_pStage);
}
