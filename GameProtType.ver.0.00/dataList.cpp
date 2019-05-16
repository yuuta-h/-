#include "dataList.h"
#include "textDX.h"

// ��̃m�[�h�𓮓I�ɐ���
static DataNode* AllocDnode(void)
{
	return (DataNode*)calloc(1, sizeof(DataNode));
}

// �m�[�h�̊e�����o�ɒl��ݒ�
static void SetDnode(DataNode* n,const UnionData x, DataNode* prev, DataNode* next)
{
	n->d = x;
	n->prev = prev;		// ��s�m�[�h�ւ̃|�C���^
	n->next = next;		// �㑱�m�[�h�ւ̃|�C���^
}

// �f�[�^�^���Ƃ̃f�[�^���Z�b�g
static UnionData SetDataObjectEdge(ObjStr *p_obj, float dst, __data_objEdge *p_L) {
	UnionData d;
	d._oE.dType = DATA_OBJ_EDGE;
	d._oE.mp_obj = p_obj; d._oE.m_dst = dst; d._oE.mp_L = p_L;
	return d;
}
static UnionData SetDataObjectCon(ObjStr *p_objL, ObjStr *p_objR, bool use) {
	UnionData d;
	d._oC.dType = DATA_OBJ_CON;
	d._oC.mp_objL = p_objL; d._oC.mp_objR = p_objR; d._oC.m_use = use;
	return d;
}
static UnionData SetDataTypeCompat(objTypes p_type1, objTypes p_type2, bool act,bool pas) {
	UnionData d;
	d._tC.dType = DATA_TYPE_COMPAT;
	d._tC.mp_type1 = p_type1; d._tC.mp_type2 = p_type2; d._tC.m_act = act; d._tC.m_pas = pas;
	return d;
}

// ���X�g�͋�
static int IsEmpty(const DataList* list)
{
	return list->head->next == list->head;
}

// p���w���m�[�h���폜
void Remove(DataList* list, DataNode* p)
{
	p->prev->next = p->next;
	p->next->prev = p->prev;
	list->crnt = p->prev;	// �폜�����m�[�h�̐�s�m�[�h�ɒ���
	free(p);
	if (list->crnt == list->head)
		list->crnt = list->head->next;
};

//a->b=(*a).b
//DataList->DataNode

// ���ڃm�[�h�ƒ��ڂ̎��m�[�h���Ax���W�ɂ��Ĕ�ׂ�
static int compareObjEdgeCurrentNextByX(DataList* list) {
	if (list->crnt == list->head || list->crnt->next == list->head)
		return -1;// �ǂ��炩���_�~�[�m�[�h�Ŕ�ׂ��Ȃ��A�Ƃ�������-1
	if (list->crnt->d._oE.mp_obj->m_pos.x + list->crnt->d._oE.m_dst <=
		list->crnt->next->d._oE.mp_obj->m_pos.x + list->crnt->next->d._oE.m_dst) return 1;//x�����ɂȂ��Ă����
	return 0;//NOT x�����Ȃ��
}

// �m�[�h1�ƃm�[�h2���Ax���W�ɂ��Ĕ�ׂ�
static int compareObjEdgeByX(const DataList* list, const DataNode* n1, const DataNode* n2) {
	if (n1 == list->head || n2 == list->head)
		return -1;// �ǂ��炩���_�~�[�m�[�h�Ŕ�ׂ��Ȃ��A�Ƃ�������-1
	if (n1->d._oE.mp_obj->m_pos.x + n1->d._oE.m_dst <=
		n2->d._oE.mp_obj->m_pos.x + n2->d._oE.m_dst) return 1;//x�����ɂȂ��Ă����
	return 0;//NOT x�����Ȃ��
}

// �f�[�^�̃|�C���^�̔�r�֐�
int ObjPntrCmp(const ObjStr* x, const ObjStr* y)
{
	// x�̃|�C���^��y�̃|�C���^��菬��������-1��߂�
	// x�̃|�C���^��y�̃|�C���^���傫������1��߂�
	// x�̃|�C���^��y�̃|�C���^������������0��߂�
	return x < y ? -1 : x > y ? 1 : 0;
};
// �m�[�h�̃|�C���^�̔�r�֐�
int NodeCmp(const DataNode* x, const DataNode* y)
{
	return x < y ? -1 : x > y ? 1 : 0;
};
// �f�[�^�^�̊m�F�֐�
int DataTypeCmp(const UnionData* x, const UnionData* y)
{
	return x->_oE.dType < y->_oE.dType ? -1 : x->_oE.dType > y->_oE.dType ? 1 : 0;
};
// ���X�g�̊m�F�֐�
int DataTypeCmp(const DataList* x, const DataList* y)
{
	return x < y ? -1 : x > y ? 1 : 0;
};

//�����[�J���֐�

// ���X�g��������
void Initialize(DataList* list)
{
	DataNode* dummyNode = AllocDnode(); // �_�~�[�m�[�h�𐶐�
	list->head = list->crnt = dummyNode;
	dummyNode->prev = dummyNode->next = dummyNode;
}

// ���ڃm�[�h�̃f�[�^��\��
void PrintCurrent(const DataList* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "���ڃm�[�h������܂���B", WINDOW_CENTER_X, WINDOW_CENTER_Y);
	else {
		PrintData(list->crnt);
	}
}

// �֐�compare�ɂ����x�ƃf�[�^���e����v���Ă���m�[�h��T��
DataNode* SearchObjEdge(DataList *list, const ObjStr* x)
{
	DataNode* ptr = list->head->next;
	while (ptr != list->head)
	{
		if (ObjPntrCmp(ptr->d._oE.mp_obj, x) == 0)
		{
			list->crnt = ptr;
			return ptr;			// �T������
		}
		ptr = ptr->next;
	}
	return NULL;				// �T�����s
};
DataNode* SearchObjCon(DataList *list, const ObjStr* x1, const ObjStr* x2)
{
	DataNode* ptr = list->head->next;
	while (ptr != list->head)
	{
		if (ObjPntrCmp(ptr->d._oC.mp_objL, x1) == 0 && ObjPntrCmp(ptr->d._oC.mp_objR, x2) == 0)
		{
			list->crnt = ptr;
			return ptr;			// �T������
		}
		ptr = ptr->next;
	}
	return NULL;				// �T�����s
};
DataNode* Search(DataList *list, DataNode* n)
{
	DataNode* ptr = list->head->next;
	while (ptr != list->head)
	{
		if (NodeCmp(ptr, n) == 0 && DataTypeCmp(&ptr->d, &n->d) == 0)
		{
			list->crnt = ptr;
			return ptr;			// �T������
		}
		ptr = ptr->next;
	}
	return NULL;				// �T�����s
};

// �S�m�[�h�̃f�[�^�����X�g���ɕ\��
void Print(const DataList* list)
{
	txtColorChange(getDebugFont(), 191, 95, 191, 63);//�F�ύX
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "�m�[�h������܂���B", WINDOW_CENTER_X, WINDOW_CENTER_Y);
	else {
		DataNode* ptr = list->head->next;
		printTextDX(getDebugFont(), "�y�ꗗ�\�z", WINDOW_CENTER_X, WINDOW_CENTER_Y);
		while (ptr != list->head) {
			PrintData(ptr);
			ptr = ptr->next;		// �㑱�m�[�h�ɒ���
		}
	}
	txtColorChange(getDebugFont(), 255, 255, 255, 255);//�F�ύX
};

// �S�m�[�h�̃f�[�^�����X�g�̋t���ɕ\��
void PrintReverse(const DataList* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "�m�[�h������܂���B", WINDOW_CENTER_X, WINDOW_CENTER_Y);
	else {
		DataNode* ptr = list->head->prev;
		printTextDX(getDebugFont(), "�y�ꗗ�\�z", WINDOW_CENTER_X, WINDOW_CENTER_Y);
		while (ptr != list->head) {
			PrintData(ptr);
			ptr = ptr->prev;		// ��s�m�[�h�ɒ���
		}
	}
};

// �f�[�^�̕\��
void PrintData(const DataNode* n) {
	switch (n->d._oE.dType) {
	case DATA_OBJ_EDGE:
		PrintObjEdge(n);
		break;
	case DATA_OBJ_CON:
		PrintObjCon(n);
		break;
	case DATA_TYPE_COMPAT:
		PrintTypeCompat(n);
		break;
	default://���݂��Ȃ��^
		printTextDX(getDebugFont(), "�H", WINDOW_CENTER_X, txtLineReset(txtLineReset(0)));
		break;
	}
}
void PrintObjEdge(const DataNode* n)
{
	int x = int(n->d._oE.mp_obj->m_pos.x + n->d._oE.m_dst);
	txtLineReset(int(n->d._oE.mp_obj->m_pos.y));

	printTextDX(getDebugFont(), "id�F", x, txtLineBreak(), int(n->d._oE.mp_obj->m_id));
	printTextDX(getDebugFont(), "type�F", x, txtLineBreak(), int(n->d._oE.mp_obj->m_type));
	printTextDX(getDebugFont(), "distance�F", x, txtLineBreak(), int(n->d._oE.m_dst));
	if (n->d._oE.mp_L == NULL) printTextDX(getDebugFont(), "���[", x, txtLineBreak());
	else printTextDX(getDebugFont(), "�E�[", x, txtLineBreak());
};
void PrintObjCon(const DataNode* n)
{
	int x = int((n->d._oC.mp_objL->m_pos.x + n->d._oC.mp_objR->m_pos.x) / 2.0f);
	txtLineReset(int((n->d._oC.mp_objL->m_pos.y + n->d._oC.mp_objR->m_pos.y) / 2.0f));

	printTextDX(getDebugFont(), "��id�F", x, txtLineBreak(), int(n->d._oC.mp_objL->m_id));
	printTextDX(getDebugFont(), "��type�F", x, txtLineBreak(), int(n->d._oC.mp_objL->m_type));
	printTextDX(getDebugFont(), "�Eid�F", x, txtLineBreak(), int(n->d._oC.mp_objR->m_id));
	printTextDX(getDebugFont(), "�Etype�F", x, txtLineBreak(), int(n->d._oC.mp_objR->m_type));
	if (n->d._oC.m_use) printTextDX(getDebugFont(), "�ڐG", x, txtLineBreak());
	else printTextDX(getDebugFont(), "��ڐG", x, txtLineBreak());
};
void PrintTypeCompat(const DataNode* n)
{
	txtLineReset(txtLineReset(0));

	printTextDX(getDebugFont(), "��type�F", 0, txtLineBreak(), int(n->d._tC.mp_type1));
	printTextDX(getDebugFont(), "��type�F", 0, txtLineBreak(), int(n->d._tC.mp_type2));
	if (n->d._tC.m_act == true) printTextDX(getDebugFont(), "�偨��F�L��", 0, txtLineBreak());
	else printTextDX(getDebugFont(), "�偨��F����", 0, txtLineBreak());
	if (n->d._tC.m_pas == true) printTextDX(getDebugFont(), "�󁨎�F�L��", 0, txtLineBreak());
	else printTextDX(getDebugFont(), "�󁨎�F����", 0, txtLineBreak());
};

// ���ڃm�[�h�������ɐi�߂�
int Next(DataList* list)
{
	if (IsEmpty(list) || list->crnt->next == list->head)
		return 0;	// �i�߂邱�Ƃ͂ł��Ȃ�
	list->crnt = list->crnt->next;
	return 1;
};

// ���ڃm�[�h����O���ɖ߂�
int Prev(DataList* list)
{
	if (IsEmpty(list) || list->crnt->prev == list->head)
		return 0;	// �߂����Ƃ͂ł��Ȃ�
	list->crnt = list->crnt->prev;
	return 1;
};

// p���w���m�[�h�̒���Ƀm�[�h��}��
void InsertAfter(DataList* list, DataNode* p,const UnionData x)
{
	DataNode* ptr = AllocDnode();
	DataNode* nxt = p->next;
	p->next = p->next->prev = ptr;
	SetDnode(ptr, x, p, nxt);
	list->crnt = ptr;
};

// �擪�Ƀm�[�h��}��
void InsertFront(DataList* list, const UnionData x)
{
	InsertAfter(list, list->head, x);
};

// �����Ƀm�[�h��}��
void InsertRear(DataList* list, const UnionData x)
{
	InsertAfter(list, list->head->prev, x);
};

// �����ɃI�u�W�F�N�g�̗��[��}�����A������ݒ�
void InsertRearEdges(DataList* list, const ObjStr* x, float eL, float eR)
{
	InsertAfter(list, list->head->prev, 
		SetDataObjectEdge((ObjStr*)x, eL, NULL));// ���[�ł���

	__data_objEdge* p_L = &list->crnt->d._oE;//���[
	InsertAfter(list, list->head->prev,
		SetDataObjectEdge((ObjStr*)x, eR, p_L));// �E�[�ł���A�Ή����鍶�[�̃f�[�^��p_L�ł���
};

// �����ɂQ�̃I�u�W�F�N�g��H���m�[�h�A���ʂ�}��
void InsertRearCon(DataList* list, const ObjStr* x1, const ObjStr* x2, bool use)
{
	InsertAfter(list, list->head->prev,
		SetDataObjectCon((ObjStr*)x1, (ObjStr*)x2, use));
};

// �擪�m�[�h���폜
void RemoveFront(DataList* list)
{
	if (!IsEmpty(list))
		Remove(list, list->head->next);
};

// �����m�[�h���폜
void RemoveRear(DataList* list)
{
	if (!IsEmpty(list))
		Remove(list, list->head->prev);
};

// ���ڃm�[�h���폜
void RemoveCurrent(DataList* list)
{
	if (list->crnt != list->head)
		Remove(list, list->crnt);
};

// �S�m�[�h���폜
void Clear(DataList* list)
{
	while (!IsEmpty(list))	// ��ɂȂ�܂�
		RemoveFront(list);	// �擪�m�[�h���폜
};

// �m�[�h1���m�[�h2�̒��O�Ɉړ�
void MoveDnodeBefore(DataNode* p_is, DataNode* p_to) {
	MoveDnodeAfter(p_to->prev,p_is);
};

// �m�[�h2���m�[�h1�̒���Ɉړ�
void MoveDnodeAfter(DataNode* p_to, DataNode* p_is) {
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
void Terminate(DataList* list)
{
	if (list->head != NULL) {
		Clear(list);			// �S�m�[�h���폜
		free(list->head);		// �_�~�[�m�[�h���폜
	}
};

// �I�u�W�F�N�g�[���X�g��x�����ɕ��ёւ�
void sortObjEdgeListByX(DataList* list) {
	list->crnt = list->head;//���ڃm�[�h�����Z�b�g
	while (Next(list)) {//�Ō�܂�x���W���ɂȂ�����0�ɂȂ��ďI��
		if (compareObjEdgeCurrentNextByX(list) == 0) {
			//(�擪�m�[�h�ȊO��)x���W���ɂȂ��Ă��Ȃ����̂������Ă�����

			if (compareObjEdgeByX(list, list->crnt->prev, list->crnt->next) == 1) {
				// �J�����g�̑O�ƃJ�����g�̎������������Ă����==���������̂��J�����g�m�[�h�Ȃ�΁A�J�����g���g���E������

				DataNode *crnt_prev = list->crnt->prev, *crnt_ = list->crnt;
				while (Next(list)) {
					//-1(head) , 0(>) , 1(<)
					if (compareObjEdgeByX(list, crnt_, list->crnt->next) != 0) {
						MoveDnodeBefore(crnt_, list->crnt->next);//�J�����g���A����炵���m�[�h�̑O�Ɉړ�
							//crnt->next�Ȃ̂́Acrnt_->next < crnt_�Ȃ̂͊m�肵�Ă���̂ƁAwhile(Next(list))��crnt��head(����)�ɓ��B�������_�Ŕ����Ă��܂�����
						break;
					}
				}
				list->crnt = crnt_prev;
			}
			else if (compareObjEdgeByX(list, list->crnt->prev, list->crnt->next) == 0) {//�łȂ����
				// �łȂ����==���������̂��J�����g�̎��m�[�h�Ȃ�΁A�J�����g�̎����������ֈړ�
				DataNode *crnt_prev = list->crnt->prev, *crnt_next = list->crnt->next;
				while (Prev(list)) {
					//-1(head) , 0(>) , 1(<)
					if (compareObjEdgeByX(list, list->crnt->prev, crnt_next) != 0) {
						MoveDnodeAfter(list->crnt->prev, crnt_next);//�J�����g�̎����A����炵���m�[�h�̎��Ɉړ�
							//crnt->prev�Ȃ̂́Acrnt_next < crnt_->prev�Ȃ̂͊m�肵�Ă���̂ƁAwhile(Prev(list))��crnt��head(�擪)�ɓ��B�������_�Ŕ����Ă��܂�����
						break;
					}
				}
//				list->crnt = crnt_;
				list->crnt = crnt_prev;
			}
		}
	}
}
//if��while�Ȃǂ̏��������Ŋ֐����Ă񂾏ꍇ�ɂ��l�͏����ς��B
