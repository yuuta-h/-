//����
#include "listUse.h"

//���[�J���֐�
bool stubProcess(ObjStr* obj1, ObjStr* obj2);//�Ȃ�炩�̏���
static int compareCurrentNextByX(Dl_obj* list);
static int compareByX(const Dl_obj* list, const Dn_obj* p1, const  Dn_obj* p2);

Dl_typeCmp compatList;				// �^�C�v�����\
Dl_obj xBasedList;					// x���W���E�I�u�W�F�N�g�E���X�g(�Q�[�����ʗp)
Dl_objCon resultList;				// �m���ߌ��ʁE�I�u�W�F�N�g�֌W�E���X�g(���t���[���g���̂�)

void initializeObjList(StageObj *p_stageobj) {
	Initialize(&xBasedList);
	for (int i = 0; i < p_stageobj->m_OBJNUM; i++)
		InsertAfter(&xBasedList, xBasedList.crnt, &p_stageobj->m_Obj[i]);
			//�I�u�W�F�N�g�S�Ă�{���X�g�̃J�����g�̎�}�ɏ����}��
			//�ł���΂����ŁA�^�C�v�֌W�I�ɔ\���ł��󓮂ł������蔻�肪�N���肦�Ȃ�����(UI�Ƃ�)�͔r��
}
void uninitializeObjList(void) {
	Terminate(&xBasedList);
}

void updateObjList(void){//��
	sortObjListByX(&xBasedList);

//	optimizeObjList(&compatList,&xBasedList, &resultList);

	Terminate(&resultList);
}


// �I�u�W�F�N�g���X�g��x�����ɕ��ёւ�
void sortObjListByX(Dl_obj* list) {
	list->crnt = list->head;//���ڃm�[�h�����Z�b�g
	while (Next(list)) {//�Ō�܂�x���W���ɂȂ�����0�ɂȂ��ďI��

		if (compareCurrentNextByX(list) == 0) {//(�擪�m�[�h�łȂ�)x���W���ɂȂ��Ă��Ȃ����̂������Ă�����
			if (compareByX(list, list->crnt->prev, list->crnt->next) == 1) {
					// �J�����g�̎����J�����g�̑O�Ə��������Ă����==���������̂��J�����g�m�[�h�Ȃ�΁A�J�����g���g���E������
				Dn_obj *crnt_prev = list->crnt->prev, *crnt = list->crnt;
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
				Dn_obj *crnt = list->crnt, *crnt_next = list->crnt->next;
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


void optimizeObjList(Dl_typeCmp* compat,Dl_obj* xBased, Dl_objCon* result) {
	xBased->crnt = xBased->head;//���ڃm�[�h�����Z�b�g
	while (Next(xBased)) {
		
	}

}




////////���[�J���֐�
bool stubProcess(ObjStr* obj1, ObjStr* obj2){//�Ȃ�炩�̏���
	return true;
}


// ���ڃm�[�h�ƒ��ڂ̎��m�[�h���Ax���W�ɂ��Ĕ�ׂ�
static int compareCurrentNextByX(Dl_obj* list) {
	if (list->crnt == list->head || list->crnt->next == list->head)
		return -1;// �ǂ��炩���_�~�[�m�[�h�Ŕ�ׂ��Ȃ��A�Ƃ�������-1
	if (list->crnt->mp_obj->m_pos.x <= list->crnt->next->mp_obj->m_pos.x) return 1;//x�����ɂȂ��Ă����
	return 0;//NOT x�����Ȃ��
}

// �m�[�h1�ƃm�[�h2���Ax���W�ɂ��Ĕ�ׂ�
static int compareByX(const Dl_obj* list, const Dn_obj* p1, const  Dn_obj* p2) {
	if (p1 == list->head || p2 == list->head)
		return -1;// �ǂ��炩���_�~�[�m�[�h�Ŕ�ׂ��Ȃ��A�Ƃ�������-1
	if (p1->mp_obj->m_pos.x <= p2->mp_obj->m_pos.x) return 1;//x�����ɂȂ��Ă����
	return 0;//NOT x�����Ȃ��
}
