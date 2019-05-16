#pragma once
// �z�E�d�A�����X�g(�w�b�_��)

#include "object.h"


//�I�u�W�F�N�g�̒[ ��
	// �m�[�h
	typedef struct __node_obj {
		const ObjStr* mp_obj;				// �f�[�^
		float m_dst;						// �I�u�W�F�N�g�̍��W���炻�̒[�܂ł̋���
		struct __node_obj *prev;			// �O�m�[�h�ւ̃|�C���^
		struct __node_obj *next;			// ��m�[�h�ւ̃|�C���^
		struct __node_obj *mp_L;			// �I�u�W�F�N�g�̍��[���o�����m�[�h�ւ̃|�C���^(���������[�������ꍇ��NULL)
	}Dn_objEdge;

	// �z�E�d�A�����X�g
	typedef struct {
		Dn_objEdge *head;						// �擪(���[)�_�~�[�m�[�h�ւ̃|�C���^
		Dn_objEdge *crnt;						// ���ڃm�[�h�ւ̃|�C���^
	}Dl_objEdge;

// ���X�g��������
void Initialize(Dl_objEdge *list);

// ���ڃm�[�h�̃f�[�^��\��
void PrintCurrent(const Dl_objEdge *list);

// ���ڃm�[�h�̃f�[�^��\���i���s�t���j
void PrintLnCurrent(const Dl_objEdge *list);

// �֐�compare�ɂ����x�ƃf�[�^���e����v���Ă���m�[�h��T��
Dn_objEdge* Search(Dl_objEdge *list, const ObjStr* x,int compare(const ObjStr* x, const ObjStr* y));

// �S�m�[�h�̃f�[�^�����X�g���ɕ\��
void Print(const Dl_objEdge* list);

// �S�m�[�h�̃f�[�^�����X�g�̋t���ɕ\��
void PrintReverse(const Dl_objEdge* list);

// ���ڃm�[�h�������ɐi�߂�
int Next(Dl_objEdge* list);

// ���ڃm�[�h����O���ɖ߂�
int Prev(Dl_objEdge* list);

// p���w���m�[�h�̒���Ƀm�[�h��}��
void InsertAfter(Dl_objEdge* list, Dn_objEdge* p, const ObjStr* x);

// �擪�Ƀm�[�h��}��
void InsertFront(Dl_objEdge* list, const ObjStr* x);

// �����Ƀm�[�h��}��
void InsertRear(Dl_objEdge* list, const ObjStr* x);

// �����ɃI�u�W�F�N�g�̗��[��}�����A������ݒ�
void InsertAfterEdges(Dl_objEdge* list, const ObjStr* x, float eL, float eR);

// ������copyed�̃R�s�[��}��
void CopyRear(Dl_objEdge* list, Dn_objEdge* copied);

// �擪�m�[�h���폜
void RemoveFront(Dl_objEdge* list);

// �����m�[�h���폜
void RemoveRear(Dl_objEdge* list);

// ���ڃm�[�h���폜
void RemoveCurrent(Dl_objEdge* list);

// �S�m�[�h���폜
void Clear(Dl_objEdge* list);

// �m�[�h1���m�[�h2�̒���Ɉړ�
void MoveDnode(Dn_objEdge* p_is, Dn_objEdge* p_to);

// �z�E�d�A�����X�g�̌�n��
void Terminate(Dl_objEdge* list);

// �f�[�^�̕\��
void PrintObjEdge(const Dn_objEdge* n);

// ���X�g�ɓo�^����Ă���I�u�W�F�N�g�̒[��S��x���Ƀ\�[�g
void sortObjListByX(Dl_objEdge* list);

