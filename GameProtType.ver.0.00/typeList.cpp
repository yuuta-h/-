#include "typeList.h"
#include "textDX.h"

// ��̃m�[�h�𓮓I�ɐ���
static Dn_typeCmp* AllocDnode_(void)
{
	return (Dn_typeCmp*)calloc(1, sizeof(Dn_typeCmp));
}

// �m�[�h�̊e�����o�ɒl��ݒ�
static void SetDnode_(Dn_typeCmp* n, const objTypes* x1, const objTypes* x2, Dn_typeCmp* prev, Dn_typeCmp* next)
{
	n->mp_type1 = x1;	// �f�[�^1(��)
	n->mp_type2 = x2;	// �f�[�^2(�E)
	n->prev = prev;		// ��s�m�[�h�ւ̃|�C���^
	n->next = next;		// �㑱�m�[�h�ւ̃|�C���^
}

// ���X�g�͋�
static int IsEmpty(const Dl_typeCmp* list)
{
	return list->head->next == list->head;
}

// p���w���m�[�h���폜
void Remove(Dl_typeCmp* list, Dn_typeCmp* p)
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
void Initialize(Dl_typeCmp* list)
{
	Dn_typeCmp* dummyNode = AllocDnode_(); // �_�~�[�m�[�h�𐶐�
	list->head = list->crnt = dummyNode;
	dummyNode->prev = dummyNode->next = dummyNode;
}

// ���ڃm�[�h�̃f�[�^��\��
void PrintCurrent(const Dl_typeCmp* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "���ڃm�[�h������܂���B", 0, txtLineBreak());
	else {
		PrintobjTypes(list->crnt->mp_type1);
		PrintobjTypes(list->crnt->mp_type2);
	}
}

// ���ڃm�[�h�̃f�[�^��\���i���s�t���j
void PrintLnCurrent(const Dl_typeCmp* list)
{
	PrintCurrent(list);
	//	putchar('\n');
	printTextDX(getDebugFont(), "", 0, txtLineBreak());
}

// �֐�compare�ɂ����(x)/(x1,x2)�ƈ�v����Ɣ��肳���m�[�h��T��
Dn_typeCmp* Search(Dl_typeCmp *list, const objTypes* x1, const objTypes* x2,
	int compare1(const objTypes* x1, const objTypes* y1), int compare2(const objTypes* x2, const objTypes* y2))
{
	Dn_typeCmp* ptr = list->head->next;
	while (ptr != list->head)
	{
		if (compare1(ptr->mp_type1, x1) == 0 && compare2(ptr->mp_type2, x2) == 0)
		{
			list->crnt = ptr;
			return ptr;			// �T������
		}
		ptr = ptr->next;
	}
	return NULL;				// �T�����s
};


// �S�m�[�h�̃f�[�^�����X�g���ɕ\��
void Print(const Dl_typeCmp* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "�m�[�h������܂���B", 0, txtLineBreak());
	else {
		Dn_typeCmp* ptr = list->head->next;
		printTextDX(getDebugFont(), "�y�ꗗ�\�z", 0, txtLineBreak());
		while (ptr != list->head) {
			PrintobjTypes(list->crnt->mp_type1);
			PrintobjTypes(list->crnt->mp_type2);
			ptr = ptr->next;		// �㑱�m�[�h�ɒ���	
		}
	}
};


// �S�m�[�h�̃f�[�^�����X�g�̋t���ɕ\��
void PrintReverse(const Dl_typeCmp* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "�m�[�h������܂���B", 0, txtLineBreak());
	else {
		Dn_typeCmp* ptr = list->head->prev;
		printTextDX(getDebugFont(), "�y�ꗗ�\�z", 0, txtLineBreak());
		while (ptr != list->head) {
			PrintobjTypes(list->crnt->mp_type1);
			PrintobjTypes(list->crnt->mp_type2);
			ptr = ptr->prev;		// ��s�m�[�h�ɒ���
		}
	}
};

// ���ڃm�[�h�������ɐi�߂�
int Next(Dl_typeCmp* list)
{
	if (IsEmpty(list) || list->crnt->next == list->head)
		return 0;	// �i�߂邱�Ƃ͂ł��Ȃ�
	list->crnt = list->crnt->next;
	return 1;
};

// ���ڃm�[�h����O���ɖ߂�
int Prev(Dl_typeCmp* list)
{
	if (IsEmpty(list) || list->crnt->prev == list->head)
		return 0;	// �߂����Ƃ͂ł��Ȃ�
	list->crnt = list->crnt->prev;
	return 1;
};


// p���w���m�[�h�̒���Ƀm�[�h��}��
void InsertAfter(Dl_typeCmp* list, Dn_typeCmp* p, const objTypes* x1, const objTypes* x2)
{
	Dn_typeCmp* ptr = AllocDnode_();
	Dn_typeCmp* nxt = p->next;
	p->next = p->next->prev = ptr;
	SetDnode_(ptr, x1, x2, p, nxt);
	list->crnt = ptr;
};

// �擪�Ƀm�[�h��}��
void InsertFront(Dl_typeCmp* list, const objTypes* x1, const objTypes* x2)
{
	InsertAfter(list, list->head, x1, x2);
};

// �����Ƀm�[�h��}��
void InsertRear(Dl_typeCmp* list, const objTypes* x1, const objTypes* x2)
{
	InsertAfter(list, list->head->prev, x1, x2);
};

// �擪�m�[�h���폜
void RemoveFront(Dl_typeCmp* list)
{
	if (!IsEmpty(list))
		Remove(list, list->head->next);
};

// �����m�[�h���폜
void RemoveRear(Dl_typeCmp* list)
{
	if (!IsEmpty(list))
		Remove(list, list->head->prev);
};

// ���ڃm�[�h���폜
void RemoveCurrent(Dl_typeCmp* list)
{
	if (list->crnt != list->head)
		Remove(list, list->crnt);
};

// �S�m�[�h���폜
void Clear(Dl_typeCmp* list)
{
	while (!IsEmpty(list))	// ��ɂȂ�܂�
		RemoveFront(list);	// �擪�m�[�h���폜
};


// �z�E�d�A�����X�g�̌�n��
void Terminate(Dl_typeCmp* list)
{
	Clear(list);			// �S�m�[�h���폜
	free(list->head);		// �_�~�[�m�[�h���폜
};

// �f�[�^�̕\���i���s�Ȃ��j
void PrintobjTypes(const objTypes* d)
{
	printTextDX(getDebugFont(), "type�F", 0, txtLineBreak(), int(d));
};