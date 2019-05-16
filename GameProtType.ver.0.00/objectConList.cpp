#include "objectConList.h"
#include "textDX.h"

// ��̃m�[�h�𓮓I�ɐ���
static Dn_objCon* AllocDnode_(void)
{
	return (Dn_objCon*)calloc(1, sizeof(Dn_objCon));
}

// �m�[�h�̊e�����o�ɒl��ݒ�
static void SetDnode_(Dn_objCon* n, const ObjStr* x1, const ObjStr* x2, Dn_objCon* prev, Dn_objCon* next)
{
	n->mp_objL = x1;	// �f�[�^1(��)
	n->mp_objR = x2;	// �f�[�^2(�E)
	n->prev = prev;		// ��s�m�[�h�ւ̃|�C���^
	n->next = next;		// �㑱�m�[�h�ւ̃|�C���^
}

// ���X�g�͋�
static int IsEmpty(const Dl_objCon* list)
{
	return list->head->next == list->head;
}

// p���w���m�[�h���폜
void Remove(Dl_objCon* list, Dn_objCon* p)
{
	p->prev->next = p->next;
	p->next->prev = p->prev;
	list->crnt = p->prev;	// �폜�����m�[�h�̐�s�m�[�h�ɒ���
	free(p);
	if (list->crnt == list->head)
		list->crnt = list->head->next;
};

//�����[�J���֐�

// ���X�g��������
void Initialize(Dl_objCon* list)
{
	Dn_objCon* dummyNode = AllocDnode_(); // �_�~�[�m�[�h�𐶐�
	list->head = list->crnt = dummyNode;
	dummyNode->prev = dummyNode->next = dummyNode;
}

// ���ڃm�[�h�̃f�[�^��\��
void PrintCurrent(const Dl_objCon* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "���ڃm�[�h������܂���B", 0, txtLineBreak());
	else {
		PrintObjCon(list->crnt->mp_objL);
		PrintObjCon(list->crnt->mp_objR);
	}
}

// ���ڃm�[�h�̃f�[�^��\���i���s�t���j
void PrintLnCurrent(const Dl_objCon* list)
{
	PrintCurrent(list);
	//	putchar('\n');
	printTextDX(getDebugFont(), "", 0, txtLineBreak());
}

// �֐�compare�ɂ����(x)/(x1,x2)�ƈ�v����Ɣ��肳���m�[�h��T��
Dn_objCon* Search(Dl_objCon *list, const ObjStr* x1, const ObjStr* x2,
	int compare1(const ObjStr* x1, const ObjStr* y1), int compare2(const ObjStr* x2, const ObjStr* y2))
{
	Dn_objCon* ptr = list->head->next;
	while (ptr != list->head)
	{
		if (compare1(ptr->mp_objL, x1) == 0 && compare2(ptr->mp_objR, x2) == 0)
		{
			list->crnt = ptr;
			return ptr;			// �T������
		}
		ptr = ptr->next;
	}
	return NULL;				// �T�����s
};


// �S�m�[�h�̃f�[�^�����X�g���ɕ\��
void Print(const Dl_objCon* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "�m�[�h������܂���B", 0, txtLineBreak());
	else {
		Dn_objCon* ptr = list->head->next;
		printTextDX(getDebugFont(), "�y�ꗗ�\�z", 0, txtLineBreak());
		while (ptr != list->head) {
			PrintObjCon(list->crnt->mp_objL);
			PrintObjCon(list->crnt->mp_objR);
			ptr = ptr->next;		// �㑱�m�[�h�ɒ���	
		}
	}
};


// �S�m�[�h�̃f�[�^�����X�g�̋t���ɕ\��
void PrintReverse(const Dl_objCon* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "�m�[�h������܂���B", 0, txtLineBreak());
	else {
		Dn_objCon* ptr = list->head->prev;
		printTextDX(getDebugFont(), "�y�ꗗ�\�z", 0, txtLineBreak());
		while (ptr != list->head) {
			PrintObjCon(list->crnt->mp_objL);
			PrintObjCon(list->crnt->mp_objR);
			ptr = ptr->prev;		// ��s�m�[�h�ɒ���
		}
	}
};

// ���ڃm�[�h�������ɐi�߂�
int Next(Dl_objCon* list)
{
	if (IsEmpty(list) || list->crnt->next == list->head)
		return 0;	// �i�߂邱�Ƃ͂ł��Ȃ�
	list->crnt = list->crnt->next;
	return 1;
};

// ���ڃm�[�h����O���ɖ߂�
int Prev(Dl_objCon* list)
{
	if (IsEmpty(list) || list->crnt->prev == list->head)
		return 0;	// �߂����Ƃ͂ł��Ȃ�
	list->crnt = list->crnt->prev;
	return 1;
};


// p���w���m�[�h�̒���Ƀm�[�h��}��
void InsertAfter(Dl_objCon* list, Dn_objCon* p, const ObjStr* x1, const ObjStr* x2)
{
	Dn_objCon* ptr = AllocDnode_();
	Dn_objCon* nxt = p->next;
	p->next = p->next->prev = ptr;
	SetDnode_(ptr, x1, x2, p, nxt);
	list->crnt = ptr;
};

// �擪�Ƀm�[�h��}��
void InsertFront(Dl_objCon* list, const ObjStr* x1, const ObjStr* x2)
{
	InsertAfter(list, list->head, x1,x2);
};

// �����Ƀm�[�h��}��
void InsertRear(Dl_objCon* list, const ObjStr* x1, const ObjStr* x2)
{
	InsertAfter(list, list->head->prev, x1, x2);
};

// �擪�m�[�h���폜
void RemoveFront(Dl_objCon* list)
{
	if (!IsEmpty(list))
		Remove(list, list->head->next);
};

// �����m�[�h���폜
void RemoveRear(Dl_objCon* list)
{
	if (!IsEmpty(list))
		Remove(list, list->head->prev);
};

// ���ڃm�[�h���폜
void RemoveCurrent(Dl_objCon* list)
{
	if (list->crnt != list->head)
		Remove(list, list->crnt);
};

// �S�m�[�h���폜
void Clear(Dl_objCon* list)
{
	while (!IsEmpty(list))	// ��ɂȂ�܂�
		RemoveFront(list);	// �擪�m�[�h���폜
};


// �m�[�h1���m�[�h2�̒���Ɉړ�
void MoveDnode(Dn_objCon* p_is, Dn_objCon* p_to) {
	if (p_is != p_to) {
		//(�ǂ�����_�~�[�m�[�h�ł͂Ȃ����̂Ƃ���)

		//p_is�̑O���p_is��Y�ꂳ����
		p_is->prev->next = p_is->next;
		p_is->next->prev = p_is->prev;

		//p_is�ɐV�����O��m�[�h���o��������
		p_is->prev = p_to;
		p_is->next = p_to->next;

		//p_to�Ǝ��̃m�[�h��p_is���o��������
		p_to->next->prev = p_is;
		p_to->next = p_is;
	}
};

// �z�E�d�A�����X�g�̌�n��
void Terminate(Dl_objCon* list)
{
	Clear(list);			// �S�m�[�h���폜
	free(list->head);		// �_�~�[�m�[�h���폜
};

// �f�[�^�̕\���i���s�Ȃ��j
void PrintObjCon(const ObjStr* d)
{
	printTextDX(getDebugFont(), "id�F", 0, txtLineBreak(), int(d->m_id));
	printTextDX(getDebugFont(), "type�F", 0, txtLineBreak(), int(d->m_type));
};
