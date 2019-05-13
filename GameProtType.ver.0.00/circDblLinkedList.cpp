// �z�E�d�A�����X�g�i�\�[�X���j
#include <stdio.h>
#include <stdlib.h>
#include "CircDblLinkedList.h"
#include "textDX.h"

// ��̃m�[�h�𓮓I�ɐ���
static Dnode* AllocDnode(void)
{
	return (Dnode*)calloc(1, sizeof(Dnode));
}

// �m�[�h�̊e�����o�ɒl��ݒ�
static void SetDnode(Dnode* n, const Data* x, Dnode* prev, Dnode* next)
{
	n->data = *x;		// �f�[�^
	n->prev = prev;		// ��s�m�[�h�ւ̃|�C���^
	n->next = next;		// �㑱�m�[�h�ւ̃|�C���^
}

// ���X�g�͋�
static int IsEmpty(const Dlist* list)
{
	return list->head->next == list->head;
}

// ���X�g��������
void Initialize(Dlist* list)
{
	Dnode* dummyNode = AllocDnode(); // �_�~�[�m�[�h�𐶐�
	list->head = list->crnt = dummyNode;
	dummyNode->prev = dummyNode->next = dummyNode;
}

// ���ڃm�[�h�̃f�[�^��\��
void PrintCurrent(const Dlist* list)
{
	if (IsEmpty(list))
//		printf("���ڃm�[�h������܂���B");
		printTextDX(getDebugFont(), "���ڃm�[�h������܂���B", 0, txtLineBreak());
	else
		PrintData(&list->crnt->data);
}

// ���ڃm�[�h�̃f�[�^��\���i���s�t���j
void PrintLnCurrent(const Dlist* list)
{
	PrintCurrent(list);
//	putchar('\n');
	printTextDX(getDebugFont(), "", 0, txtLineBreak());
}

// �֐�compare�ɂ����x�ƈ�v����Ɣ��肳���m�[�h��T��
Dnode* Search(Dlist *list, const Data* x, int compare(const Data* x, const Data* y))
{
	Dnode* ptr = list->head->next;
	while (ptr != list->head)
	{
		if (compare(&ptr->data, x) == 0)
		{
			list->crnt = ptr;
			return ptr;			// �T������
		}
		ptr = ptr->next;
	}
	return NULL;				// �T�����s
};

// �S�m�[�h�̃f�[�^�����X�g���ɕ\��
void Print(const Dlist* list)
{
	if (IsEmpty(list))
//		puts("�m�[�h������܂���B");
		printTextDX(getDebugFont(), "�m�[�h������܂���B", 0, txtLineBreak());
	else {
		Dnode* ptr = list->head->next;
//		puts("�y�ꗗ�\�z");
		printTextDX(getDebugFont(), "�y�ꗗ�\�z", 0, txtLineBreak());
		while (ptr != list->head) {
//			PrintLnData(&ptr->data);
			PrintData(&ptr->data);
			ptr = ptr->next;		// �㑱�m�[�h�ɒ���	
		}
	}
};


// �S�m�[�h�̃f�[�^�����X�g�̋t���ɕ\��
void PrintReverse(const Dlist* list)
{
	if (IsEmpty(list))
//		puts("�m�[�h������܂���B");
		printTextDX(getDebugFont(), "�m�[�h������܂���B", 0, txtLineBreak());
	else {
		Dnode* ptr = list->head->prev;
//		puts("�y�ꗗ�\�z");
		printTextDX(getDebugFont(), "�y�ꗗ�\�z", 0, txtLineBreak());
		while (ptr != list->head) {
//			PrintLnData(&ptr->data);
			PrintData(&ptr->data);
			ptr = ptr->prev;		// ��s�m�[�h�ɒ���
		}
	}
};

// ���ڃm�[�h�������ɐi�߂�
int Next(Dlist* list)
{
	if (IsEmpty(list) || list->crnt->next == list->head)
		return 0;	// �i�߂邱�Ƃ͂ł��Ȃ�
	list->crnt = list->crnt->next;
	return 1;
};

// ���ڃm�[�h����O���ɖ߂�
int Prev(Dlist* list)
{
	if (IsEmpty(list) || list->crnt->prev == list->head)
		return 0;	// �߂����Ƃ͂ł��Ȃ�
	list->crnt = list->crnt->prev;
	return 1;
};


// p���w���m�[�h�̒���Ƀm�[�h��}��
void InsertAfter(Dlist* list, Dnode* p, const Data* x)
{
	Dnode* ptr = AllocDnode();
	Dnode* nxt = p->next;
	p->next = p->next->prev = ptr;
	SetDnode(ptr, x, p, nxt);
	list->crnt = ptr;
};

// �擪�Ƀm�[�h��}��
void InsertFront(Dlist* list, const Data* x)
{
	InsertAfter(list, list->head, x);
};

// �����Ƀm�[�h��}��
void InsertRear(Dlist* list, const Data* x)
{
	InsertAfter(list, list->head->prev, x);
};

// p���w���m�[�h���폜
void Remove(Dlist* list, Dnode* p)
{
	p->prev->next = p->next;
	p->next->prev = p->prev;
	list->crnt = p->prev;	// �폜�����m�[�h�̐�s�m�[�h�ɒ���
	free(p);
	if (list->crnt == list->head)
		list->crnt = list->head->next;
};

// �擪�m�[�h���폜
void RemoveFront(Dlist* list)
{
	if (!IsEmpty(list))
		Remove(list, list->head->next);
};

// �����m�[�h���폜
void RemoveRear(Dlist* list)
{
	if (!IsEmpty(list))
		Remove(list, list->head->prev);
};

// ���ڃm�[�h���폜
void RemoveCurrent(Dlist* list)
{
	if (list->crnt != list->head)
		Remove(list, list->crnt);
};

// �S�m�[�h���폜
void Clear(Dlist* list)
{
	while (!IsEmpty(list))	// ��ɂȂ�܂�
		RemoveFront(list);	// �擪�m�[�h���폜
};

// �z�E�d�A�����X�g�̌�n��
void Terminate(Dlist* list)
{
	Clear(list);					// �S�m�[�h���폜
	free(list->head);		// �_�~�[�m�[�h���폜
};
