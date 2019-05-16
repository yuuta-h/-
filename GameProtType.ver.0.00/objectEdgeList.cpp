#include "objectEdgeList.h"
#include "textDX.h"

// ��̃m�[�h�𓮓I�ɐ���
static Dn_objEdge* AllocDnode(void)
{
	return (Dn_objEdge*)calloc(1, sizeof(Dn_objEdge));
}

// �m�[�h�̊e�����o�ɒl��ݒ�
static void SetDnode(Dn_objEdge* n,const ObjStr* x, Dn_objEdge* prev, Dn_objEdge* next)
{
	n->mp_obj = x;		// �f�[�^
	n->prev = prev;		// ��s�m�[�h�ւ̃|�C���^
	n->next = next;		// �㑱�m�[�h�ւ̃|�C���^
}

// ���X�g�͋�
static int IsEmpty(const Dl_objEdge* list)
{
	return list->head->next == list->head;
}

// p���w���m�[�h���폜
void Remove(Dl_objEdge* list, Dn_objEdge* p)
{
	p->prev->next = p->next;
	p->next->prev = p->prev;
	list->crnt = p->prev;	// �폜�����m�[�h�̐�s�m�[�h�ɒ���
	free(p);
	if (list->crnt == list->head)
		list->crnt = list->head->next;
};

// ���ڃm�[�h�ƒ��ڂ̎��m�[�h���Ax���W�ɂ��Ĕ�ׂ�
static int compareCurrentNextByX(Dl_objEdge* list) {
	if (list->crnt == list->head || list->crnt->next == list->head)
		return -1;// �ǂ��炩���_�~�[�m�[�h�Ŕ�ׂ��Ȃ��A�Ƃ�������-1
	if (list->crnt->mp_obj->m_pos.x + list->crnt->m_dst <= 
		list->crnt->next->mp_obj->m_pos.x + list->crnt->next->m_dst) return 1;//x�����ɂȂ��Ă����
	return 0;//NOT x�����Ȃ��
}

// �m�[�h1�ƃm�[�h2���Ax���W�ɂ��Ĕ�ׂ�
static int compareByX(const Dl_objEdge* list, const Dn_objEdge* p1, const  Dn_objEdge* p2) {
	if (p1 == list->head || p2 == list->head)
		return -1;// �ǂ��炩���_�~�[�m�[�h�Ŕ�ׂ��Ȃ��A�Ƃ�������-1
	if (p1->mp_obj->m_pos.x + p1->m_dst <= p2->mp_obj->m_pos.x + p2->m_dst) return 1;//x�����ɂȂ��Ă����
	return 0;//NOT x�����Ȃ��
}

// �f�[�^�̔ԍ��̔�r�֐�
int objPntrCmp(const ObjStr* x, const ObjStr* y)
{
	// x�̔ԍ���y�̔ԍ���菬��������-1��߂�
	// x�̔ԍ���y�̔ԍ����傫������1��߂�
	// x�̔ԍ���y�̔ԍ�������������0��߂�
	return x < y ? -1 : x > y ? 1 : 0;
};

//�����[�J���֐�

// ���X�g��������
void Initialize(Dl_objEdge* list)
{
	Dn_objEdge* dummyNode = AllocDnode(); // �_�~�[�m�[�h�𐶐�
	list->head = list->crnt = dummyNode;
	dummyNode->prev = dummyNode->next = dummyNode;
}

// ���ڃm�[�h�̃f�[�^��\��
void PrintCurrent(const Dl_objEdge* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "���ڃm�[�h������܂���B", 0, txtLineBreak());
	else {
		PrintObjEdge(list->crnt);
	}
}

// ���ڃm�[�h�̃f�[�^��\���i���s�t���j
void PrintLnCurrent(const Dl_objEdge* list)
{
	PrintCurrent(list);
	//	putchar('\n');
	printTextDX(getDebugFont(), "", 0, txtLineBreak());
}

// �֐�compare�ɂ����x�ƃf�[�^���e����v���Ă���m�[�h��T��
Dn_objEdge* Search(Dl_objEdge *list, const ObjStr* x)
{
	Dn_objEdge* ptr = list->head->next;
	while (ptr != list->head)
	{
		if (objPntrCmp(ptr->mp_obj, x) == 0)
		{
			list->crnt = ptr;
			return ptr;			// �T������
		}
		ptr = ptr->next;
	}
	return NULL;				// �T�����s
};

// �S�m�[�h�̃f�[�^�����X�g���ɕ\��
void Print(const Dl_objEdge* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "�m�[�h������܂���B", 0, txtLineBreak());
	else {
		Dn_objEdge* ptr = list->head->next;
		printTextDX(getDebugFont(), "�y�ꗗ�\�z", 0, txtLineBreak());
		while (ptr != list->head) {
			PrintObjEdge(list->crnt);
			ptr = ptr->next;		// �㑱�m�[�h�ɒ���	
		}
	}
};

// �S�m�[�h�̃f�[�^�����X�g�̋t���ɕ\��
void PrintReverse(const Dl_objEdge* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "�m�[�h������܂���B", 0, txtLineBreak());
	else {
		Dn_objEdge* ptr = list->head->prev;
		printTextDX(getDebugFont(), "�y�ꗗ�\�z", 0, txtLineBreak());
		while (ptr != list->head) {
			PrintObjEdge(list->crnt);
			ptr = ptr->prev;		// ��s�m�[�h�ɒ���
		}
	}
};

// ���ڃm�[�h�������ɐi�߂�
int Next(Dl_objEdge* list)
{
	if (IsEmpty(list) || list->crnt->next == list->head)
		return 0;	// �i�߂邱�Ƃ͂ł��Ȃ�
	list->crnt = list->crnt->next;
	return 1;
};

// ���ڃm�[�h����O���ɖ߂�
int Prev(Dl_objEdge* list)
{
	if (IsEmpty(list) || list->crnt->prev == list->head)
		return 0;	// �߂����Ƃ͂ł��Ȃ�
	list->crnt = list->crnt->prev;
	return 1;
};


// p���w���m�[�h�̒���Ƀm�[�h��}��
void InsertAfter(Dl_objEdge* list, Dn_objEdge* p, const ObjStr* x)
{
	Dn_objEdge* ptr = AllocDnode();
	Dn_objEdge* nxt = p->next;
	p->next = p->next->prev = ptr;
	SetDnode(ptr, x, p, nxt);
	list->crnt = ptr;
};

// �擪�Ƀm�[�h��}��
void InsertFront(Dl_objEdge* list, const ObjStr* x)
{
	InsertAfter(list, list->head, x);
};

// �����Ƀm�[�h��}��
void InsertRear(Dl_objEdge* list, const ObjStr* x)
{
	InsertAfter(list, list->head->prev, x);
};

// �����ɃI�u�W�F�N�g�̗��[��}�����A������ݒ�
void InsertAfterEdges(Dl_objEdge* list, const ObjStr* x, float eL, float eR)
{
	InsertAfter(list, list->head->prev, x);
	list->crnt->m_dst = eL;// ���[�̋�����ݒ�
	list->crnt->mp_L = NULL;// �E�[�łȂ�

	Dn_objEdge* p_L = list->crnt;//���[
	InsertAfter(list, list->head->prev, x);
	list->crnt->m_dst = eR;// �E�[�̋�����ݒ�
	list->crnt->mp_L = p_L;// �����͉E�[�ł���A���[�̃m�[�h��mp_L
};

// ������copyed�̃R�s�[��}��
void CopyRear(Dl_objEdge* list, Dn_objEdge* copied)
{
	InsertAfter(list, list->head->prev, copied->mp_obj);
	list->crnt->m_dst = copied->m_dst; list->crnt->mp_L = copied->mp_L;//prev,next,mp_obj�ȊO���]��
};

// �擪�m�[�h���폜
void RemoveFront(Dl_objEdge* list)
{
	if (!IsEmpty(list))
		Remove(list, list->head->next);
};

// �����m�[�h���폜
void RemoveRear(Dl_objEdge* list)
{
	if (!IsEmpty(list))
		Remove(list, list->head->prev);
};

// ���ڃm�[�h���폜
void RemoveCurrent(Dl_objEdge* list)
{
	if (list->crnt != list->head)
		Remove(list, list->crnt);
};

// �S�m�[�h���폜
void Clear(Dl_objEdge* list)
{
	while (!IsEmpty(list))	// ��ɂȂ�܂�
		RemoveFront(list);	// �擪�m�[�h���폜
};

// �m�[�h1���m�[�h2�̒���Ɉړ�
void MoveDnode(Dn_objEdge* p_is, Dn_objEdge* p_to) {
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
void Terminate(Dl_objEdge* list)
{
	Clear(list);			// �S�m�[�h���폜
	free(list->head);		// �_�~�[�m�[�h���폜
};

// �f�[�^�̕\���i���s�Ȃ��j
void PrintObjEdge(const Dn_objEdge* n)
{
	printTextDX(getDebugFont(), "id�F", 0, txtLineBreak(), int(n->mp_obj->m_id));
	printTextDX(getDebugFont(), "type�F", 0, txtLineBreak(), int(n->mp_obj->m_type));
	printTextDX(getDebugFont(), "distance�F", 0, txtLineBreak(), int(n->m_dst));
};

// �I�u�W�F�N�g���X�g��x�����ɕ��ёւ�
void sortObjListByX(Dl_objEdge* list) {
	list->crnt = list->head;//���ڃm�[�h�����Z�b�g
	while (Next(list)) {//�Ō�܂�x���W���ɂȂ�����0�ɂȂ��ďI��

		if (compareCurrentNextByX(list) == 0) {//(�擪�m�[�h�łȂ�)x���W���ɂȂ��Ă��Ȃ����̂������Ă�����
			if (compareByX(list, list->crnt->prev, list->crnt->next) == 1) {
				// �J�����g�̎����J�����g�̑O�Ə��������Ă����==���������̂��J�����g�m�[�h�Ȃ�΁A�J�����g���g���E������
				Dn_objEdge *crnt_prev = list->crnt->prev, *crnt = list->crnt;
				while (Next(list)) {
					if (compareByX(list, crnt, list->crnt) != 1) {
						if (compareByX(list, crnt, list->crnt) == 0)
							Prev(list);//�����łȂ���ΐi�݉߂��Ă�̂ň�߂�
						MoveDnode(crnt, list->crnt);
						break;
					}
				}
				list->crnt = crnt_prev;
			}
			else if (compareByX(list, list->crnt->prev, list->crnt->next) == 0) {//�łȂ����
					// �łȂ����==���������̂��J�����g�̎��m�[�h�Ȃ�΁A�J�����g�̎����������ֈړ�
				Dn_objEdge *crnt = list->crnt, *crnt_next = list->crnt->next;
				while (Prev(list)) {
					if (compareByX(list, crnt_next, list->crnt) != 1) {
						if (compareByX(list, crnt, list->crnt) == 0)
							Next(list);//�擪�łȂ���Ζ߂�߂��Ă�̂ň�i��
						MoveDnode(crnt_next, list->crnt);
						break;
					}
				}
				list->crnt = crnt;
			}
		}
	}
}
//if��while�Ȃǂ̏��������Ŋ֐����Ă񂾏ꍇ�ɂ��l�͏����ς��B
