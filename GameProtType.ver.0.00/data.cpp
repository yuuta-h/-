// �f�[�^Data�i�w�b�_���j
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "data.h"

#include "textDX.h"


// �f�[�^�̔ԍ��̔�r�֐�
int DataNoCmp(const Data* x, const Data* y)
{
	// x�̔ԍ���y�̔ԍ���菬��������-1��߂�
	// x�̔ԍ���y�̔ԍ����傫������1��߂�
	// x�̔ԍ���y�̔ԍ�������������0��߂�
//	return x->no < y->no ? -1 : x->no > y->no ? 1 : 0;
	return &(x->p_objId) < &(y->p_objId) ? -1 : &(x->p_objId) > &(y->p_objId) ? 1 : 0;
};

// �f�[�^�̖��O�̔�r�֐�
// �����R�[�h�̒l�ɂ���Ĕ�r
// ��v�����0��߂�
// ��1���� < ��2�����@�̏ꍇ�̓}�C�i�X�̒l
// ��1���� > ��2�����@�̏ꍇ�̓v���X�̒l
int DataNameCmp(const Data* x, const Data* y)
{
//	return strcmp(x->name, y->name);
	return int(&(x->p_objType)) - int(&(y->p_objType));
};

// �f�[�^�̕\���i���s�Ȃ��j
void PrintData(const Data* d)
{
//	printf("%d %s", d->no, d->name);
	printTextDX(getDebugFont(), "id�F", 0, txtLineBreak(), int(&(d->p_objId)));
	printTextDX(getDebugFont(), "type�F", 0, txtLineBreak(), int(&(d->p_objType)));
};

/*
// �f�[�^�̕\���i���s����j
void PrintLnData(const Data* d)
{
	printf("%d %s\n", d->no, d->name);
};
*/

// �f�[�^�̓ǂݍ���
Data ScanData(const char* message, int sw)
{
	Data temp;
//	printf("%s����f�[�^����͂��Ă��������B\n", message);
//	if (sw & DATA_NO) { printf("�ԍ��F"); scanf("%d", &temp.no); }
//	if (sw & DATA_NAME) { printf("���O�F"); scanf("%s", temp.name); }
	printTextDX(getDebugFont(), "%s����f�[�^����͂��Ă��������B\n", 0, txtLineBreak());
	if (sw & DATA_OBJ_POINTER) { printTextDX(getDebugFont(), "", 0, txtLineBreak(), int(&(temp.p_obj))); }
	if (sw & DATA_OBJ_ID) { printTextDX(getDebugFont(), "", 0, txtLineBreak(), int(&(temp.p_objId)));}
	if (sw & DATA_OBJ_TYPE) { printTextDX(getDebugFont(), "", 0, txtLineBreak(), int(&(temp.p_objType))); }
	return temp;
};

