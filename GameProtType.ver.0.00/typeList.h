#pragma once
#include "object.h"

// ����^�C�v�̃I�u�W�F�N�g�ɂ��āA���鏈�����A�S�^�C�v���ꂼ��ƍs���邩�ǂ����̕\

	// �m�[�h
	typedef struct __node_type {
		const objTypes* mp_type1;				// �f�[�^1
		const objTypes* mp_type2;				// �f�[�^2

		bool m_act;								// 1��2�Ɋ����邩
		bool m_pas;								// 2��1�Ɋ����邩

		struct __node_type *prev;				// ���m�[�h�ւ̃|�C���^
		struct __node_type *next;				// �E�m�[�h�ւ̃|�C���^
	}Dn_typeCmp;

	// �z�E�d�A�����X�g
	typedef struct {
		Dn_typeCmp *head;						// �擪(���[)�_�~�[�m�[�h�ւ̃|�C���^
		Dn_typeCmp *crnt;						// ���ڃm�[�h�ւ̃|�C���^
	}Dl_typeCmp;

// ���X�g��������
void Initialize(Dl_typeCmp *list);

// ���ڃm�[�h�̃f�[�^��\��
void PrintCurrent(const Dl_typeCmp *list);

// ���ڃm�[�h�̃f�[�^��\���i���s�t���j
void PrintLnCurrent(const Dl_typeCmp *list);

// �֐�compare�ɂ����(x)/(x1,x2)�ƈ�v����Ɣ��肳���m�[�h��T��
Dn_typeCmp* Search(Dl_typeCmp *list, const objTypes* x1, const objTypes* x2,
	int compare1(const objTypes* x1, const objTypes* y1), int compare2(const objTypes* x2, const objTypes* y2));

// �S�m�[�h�̃f�[�^�����X�g���ɕ\��
void Print(const Dl_typeCmp* list);

// �S�m�[�h�̃f�[�^�����X�g�̋t���ɕ\��
void PrintReverse(const Dl_typeCmp* list);

// ���ڃm�[�h�������ɐi�߂�
int Next(Dl_typeCmp* list);

// ���ڃm�[�h����O���ɖ߂�
int Prev(Dl_typeCmp* list);

// p���w���m�[�h�̒���Ƀm�[�h��}��
void InsertAfter(Dl_typeCmp* list, Dn_typeCmp* p, const objTypes* x1, const objTypes* x2);

// �擪�Ƀm�[�h��}��
void InsertFront(Dl_typeCmp* list, const objTypes* x1, const objTypes* x2);

// �����Ƀm�[�h��}��
void InsertRear(Dl_typeCmp* list, const objTypes* x1, const objTypes* x2);

// �擪�m�[�h���폜
void RemoveFront(Dl_typeCmp* list);

// �����m�[�h���폜
void RemoveRear(Dl_typeCmp* list);

// ���ڃm�[�h���폜
void RemoveCurrent(Dl_typeCmp* list);

// �S�m�[�h���폜
void Clear(Dl_typeCmp* list);

// �z�E�d�A�����X�g�̌�n��
void Terminate(Dl_typeCmp* list);

// �f�[�^�̕\���i���s�Ȃ��j
void PrintobjTypes(const objTypes* d);
