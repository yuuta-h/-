#pragma once
#include "object.h"

// �f�[�^Data�i�w�b�_���j
typedef struct {
//	int no;					// �ԍ�
//	char name[20];			// ���O
	ObjStr *p_obj;
	objTypes *p_objType;
	short *p_objId;
}Data;

enum {
//	DATA_NO = 1,			// �ԍ���\���萔�l
//	DATA_NAME,				// ���O��\���萔�l
	DATA_OBJ_POINTER,
	DATA_OBJ_TYPE,			// ��ނ�\���萔�l
	DATA_OBJ_ID,			// �ԍ���\���萔�l
};

// �f�[�^�̔ԍ��̔�r�֐�
int DataNoCmp(const Data* x, const Data* y);

// �f�[�^�̖��O�̔�r�֐�
int DataNameCmp(const Data* x, const Data* y);

// �f�[�^�̕\���i���s�Ȃ��j
void PrintData(const Data* d);

/*
// �f�[�^�̕\���i���s����j
void PrintLnData(const Data* d);
*/

// �f�[�^�̓ǂݍ���
Data ScanData(const char* message, int sw);
