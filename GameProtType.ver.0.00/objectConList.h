#pragma once
// �z�E�d�A�����X�g(�w�b�_��)

#include "object.h"


//�I�u�W�F�N�g�֌W
	// �m�[�h
	typedef struct __node_objCon {
		const ObjStr* mp_objL;				// �f�[�^1(���ɂ���)
		const ObjStr* mp_objR;				// �f�[�^2(�E�ɂ���)
		bool use_objCon;					// ���̃I�u�W�F�N�g�֌W�̓����蔻�肪�ǂ���������
		struct __node_objCon *prev;			// ��s�m�[�h�ւ̃|�C���^
		struct __node_objCon *next;			// �㑱�m�[�h�ւ̃|�C���^
	}Dn_objCon;

	// �z�E�d�A�����X�g
	typedef struct {
		Dn_objCon *head;					// �擪�_�~�[�m�[�h�ւ̃|�C���^
		Dn_objCon *crnt;					// ���ڃm�[�h�ւ̃|�C���^
	}Dl_objCon;

// ���X�g��������
void Initialize(Dl_objCon *list);

// ���ڃm�[�h�̃f�[�^��\��
void PrintCurrent(const Dl_objCon *list);

// ���ڃm�[�h�̃f�[�^��\���i���s�t���j
void PrintLnCurrent(const Dl_objCon *list);

// �֐�compare�ɂ����(x)/(x1,x2)�ƈ�v����Ɣ��肳���m�[�h��T��
Dn_objCon* Search(Dl_objCon *list, const ObjStr* x1, const ObjStr* x2,
	int compare1(const ObjStr* x1, const ObjStr* y1), int compare2(const ObjStr* x2, const ObjStr* y2));

// �S�m�[�h�̃f�[�^�����X�g���ɕ\��
void Print(const Dl_objCon* list);

// �S�m�[�h�̃f�[�^�����X�g�̋t���ɕ\��
void PrintReverse(const Dl_objCon* list);

// ���ڃm�[�h�������ɐi�߂�
int Next(Dl_objCon* list);

// ���ڃm�[�h����O���ɖ߂�
int Prev(Dl_objCon* list);

// p���w���m�[�h�̒���Ƀm�[�h��}��
void InsertAfter(Dl_objCon* list, Dn_objCon* p, const ObjStr* x1, const ObjStr* x2);

// �擪�Ƀm�[�h��}��
void InsertFront(Dl_objCon* list, const ObjStr* x1, const ObjStr* x2);

// �����Ƀm�[�h��}��
void InsertRear(Dl_objCon* list, const ObjStr* x1, const ObjStr* x2);

// �擪�m�[�h���폜
void RemoveFront(Dl_objCon* list);

// �����m�[�h���폜
void RemoveRear(Dl_objCon* list);

// ���ڃm�[�h���폜
void RemoveCurrent(Dl_objCon* list);

// �S�m�[�h���폜
void Clear(Dl_objCon* list);

// �m�[�h1���m�[�h2�̒���Ɉړ�
void MoveDnode(Dn_objCon* p_is, Dn_objCon* p_to);

// �z�E�d�A�����X�g�̌�n��
void Terminate(Dl_objCon* list);

// �f�[�^�̕\���i���s�Ȃ��j
void PrintObjCon(const ObjStr* d);
