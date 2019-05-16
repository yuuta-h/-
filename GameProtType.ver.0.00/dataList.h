#pragma once
// �z�E�d�A�����X�g(�w�b�_��)

#include "object.h"

enum dataTypes{
	DATA_OBJ_EDGE = 0,
	DATA_OBJ_CON,
	DATA_TYPE_COMPAT
};

// �f�[�^�^�@(�I�u�W�F�N�g�[��x���W)
typedef struct __data_objEdge {
	dataTypes dType;					// �f�[�^�̃^�C�v

	ObjStr *mp_obj;						// �f�[�^
	float m_dst;						// �I�u�W�F�N�g�̍��W���炻�̒[�܂ł̋���
	struct __data_objEdge *mp_L;		// �I�u�W�F�N�g�̍��[���o�����f�[�^�ւ̃|�C���^(���������[�������ꍇ��NULL)
}D_objEdge;

// �f�[�^�^�A(������ʂ������ʕԂ��Ă����A�I�u�W�F�N�g���m�̊֌W)
typedef struct{
	dataTypes dType;					// �f�[�^�̃^�C�v

	ObjStr *mp_objL;					// �f�[�^1(���ɂ���I�u�W�F�N�g)
	ObjStr *mp_objR;					// �f�[�^2(�E�ɂ���I�u�W�F�N�g)
	bool m_use;							// ���̃I�u�W�F�N�g�֌W�̔��茋�ʂ��ǂ���������
}D_objCon;

// �f�[�^�^�B(����^�C�v�̃I�u�W�F�N�g�ɂ��āA���鏈�����A�^�C�v���ꂼ��ƍs���邩�ǂ���)
typedef struct{
	dataTypes dType;					// �f�[�^�̃^�C�v

	objTypes mp_type1;					// �f�[�^1
	objTypes mp_type2;					// �f�[�^2
	bool m_act;							// 1��2�Ɋ����邩
	bool m_pas;							// 2��1�Ɋ����邩
}D_typeCmp;

// ����f�[�^�^
typedef union {
	D_objEdge _oE;
	D_objCon _oC;
	D_typeCmp _tC;
}UnionData;


// �m�[�h
typedef struct __node_obj {
	UnionData d;
	struct __node_obj *prev;			// �O�m�[�h�ւ̃|�C���^
	struct __node_obj *next;			// ��m�[�h�ւ̃|�C���^
}DataNode;

// �z�E�d�A�����X�g
typedef struct {
	DataNode *head;						// �擪(���[)�_�~�[�m�[�h�ւ̃|�C���^
	DataNode *crnt;						// ���ڃm�[�h�ւ̃|�C���^
}DataList;


// ���X�g��������
void Initialize(DataList *list);

// ���ڃm�[�h�̃f�[�^��\��
void PrintCurrent(const DataList *list);

// �֐�compare�ɂ����(x)/(x1,x2)�ƃf�[�^���e����v���Ă���m�[�h��T��
DataNode* SearchObjEdge(DataList *list, const ObjStr* x);
DataNode* SearchObjCon(DataList *list, const ObjStr* x1, const ObjStr* x2);
DataNode* Search(DataList *list, DataNode* n);

// �S�m�[�h�̃f�[�^�����X�g���ɕ\��
void Print(const DataList* list);

// �S�m�[�h�̃f�[�^�����X�g�̋t���ɕ\��
void PrintReverse(const DataList* list);

// �f�[�^�̕\���i���s�Ȃ��j
void PrintData(const DataNode* n);
void PrintObjEdge(const DataNode* n);
void PrintObjCon(const DataNode* n);
void PrintTypeCompat(const DataNode* n);

// ���ڃm�[�h�������ɐi�߂�
int Next(DataList* list);

// ���ڃm�[�h����O���ɖ߂�
int Prev(DataList* list);

// p���w���m�[�h�̒���Ƀm�[�h��}��
void InsertAfter(DataList* list, DataNode* p, const UnionData x);

// �擪�Ƀm�[�h��}��
void InsertFront(DataList* list, const UnionData x);

// �����Ƀm�[�h��}��
void InsertRear(DataList* list, const UnionData x);

// �����ɃI�u�W�F�N�g�̗��[��}�����A������ݒ�
void InsertRearEdges(DataList* list, const ObjStr* x, float eL, float eR);
// �����ɂQ�̃I�u�W�F�N�g��H���m�[�h�A���ʂ�}��
void InsertRearCon(DataList* list, const ObjStr* x1, const ObjStr* x2, bool use);

// �擪�m�[�h���폜
void RemoveFront(DataList* list);

// �����m�[�h���폜
void RemoveRear(DataList* list);

// ���ڃm�[�h���폜
void RemoveCurrent(DataList* list);

// �S�m�[�h���폜
void Clear(DataList* list);

// �m�[�h1���m�[�h2�̒���Ɉړ�
void MoveDnodeAfter(DataNode* p_is, DataNode* p_to);

// �z�E�d�A�����X�g�̌�n��
void Terminate(DataList* list);

// ���X�g�ɓo�^����Ă���I�u�W�F�N�g�̒[��S��x���Ƀ\�[�g
void sortObjEdgeListByX(DataList* list);
