#pragma once
// �z�E�d�A�����X�g(�w�b�_��)

#include "data.h"

// �m�[�h
typedef struct __node {
	Data	data;						// �f�[�^
	struct __node *prev;		// ��s�m�[�h�ւ̃|�C���^
	struct __node *next;		// �㑱�m�[�h�ւ̃|�C���^
}Dnode;

// �z�E�d�A�����X�g
typedef struct {
	Dnode *head;				// �擪�_�~�[�m�[�h�ւ̃|�C���^
	Dnode *crnt;					// ���ڃm�[�h�ւ̃|�C���^
}Dlist;

// ���X�g��������
void Initialize(Dlist *list);

// ���ڃm�[�h�̃f�[�^��\��
void PrintCurrent(const Dlist *list);

// ���ڃm�[�h�̃f�[�^��\���i���s�t���j
void PrintLnCurrent(const Dlist *list);

// �֐�compare�ɂ����x�ƈ�v����Ɣ��肳���m�[�h��T��
Dnode* Search(Dlist *list, const Data* x, int compare(const Data* x, const Data* y));

// �S�m�[�h�̃f�[�^�����X�g���ɕ\��
void Print(const Dlist* list);

// �S�m�[�h�̃f�[�^�����X�̋t���ɕ\��
void PrintReverse(const Dlist* list);

// ���ڃm�[�h�������ɐi�߂�
int Next(Dlist* list);

// ���ڃm�[�h����O���ɖ߂�
int Prev(Dlist* list);

// p���w���m�[�h�̒���Ƀm�[�h��}��
void InsertAfter(Dlist* list, Dnode* p, const Data* x);

// �擪�Ƀm�[�h��}��
void InsertFront(Dlist* list, const Data* x);

// �����Ƀm�[�h��}��
void InsertRear(Dlist* list, const Data* x);

// p���w���m�[�h���폜
void Remove(Dlist* list, Dnode* p);

// �擪�m�[�h���폜
void RemoveFront(Dlist* list);

// �����m�[�h���폜
void RemoveRear(Dlist* list);

// ���ڃm�[�h���폜
void RemoveCurrent(Dlist* list);

// �S�m�[�h���폜
void Clear(Dlist* list);

// �z�E�d�A�����X�g�̌�n��
void Terminate(Dlist* list);
