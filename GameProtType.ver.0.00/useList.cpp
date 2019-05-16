//����
#include "useList.h"

void optimizeObjList_getResult(DataList* compat, DataList* xBased, DataList* result, bool process(ObjStr* a, ObjStr* b));

void initializeObjList(StageObj* p_stageobj, DataList* xBased, DataList* result) {
	Initialize(xBased);
	for (int i = 0; i < p_stageobj->m_OBJNUM; i++) {
		float size = getObjectSizeLonger(&p_stageobj->m_Obj[i]);//���a�ƕӁA�ǂ��炪�����蔻�肩�͂Ƃ�����������
		InsertRearEdges(xBased, &p_stageobj->m_Obj[i],
			p_stageobj->m_Obj[i].m_image.width / 2.0f - size, p_stageobj->m_Obj[i].m_image.width / 2.0f + size);
			//�I�u�W�F�N�g�S�Ă̍��[�E�E�[���ꂼ����m�[�h�Ƃ��ă��X�g�ɓo�^
	}
	Initialize(result);
}
void uninitializeObjList(DataList* xBased, DataList* result) {
	Terminate(xBased);
	Terminate(result);
}

void updateObjList(DataList* xBased, DataList* result, bool process(ObjStr* a, ObjStr* b)){
	Clear(result);//���t���[���Aresult��(�v��Ȃ��{�����܂łɏ����Ƃ��Ȃ��Ⴂ���Ȃ��̂�)����
	sortObjEdgeListByX(xBased);//x�[���X�g�ɃI�u�W�F�N�g�̈ړ��𔽉f
	optimizeObjList_getResult(NULL, xBased, result, process);
}
void checkResultList(DataList* result, void process(ObjStr* a, ObjStr* b)) {
	while (Next(result))
		if (result->crnt->d._oC.m_use) process(result->crnt->d._oC.mp_objL, result->crnt->d._oC.mp_objR);
}

//���X�g�̒��g����ʂɕ\��
void printList(DataList* draw) {
	Print(draw);
}

//���t���[���AxBased��process(�Ȃ�炩�̏���)�����Ƃ�result���쐬
void optimizeObjList_getResult(DataList* compat, DataList* xBased,DataList* result, bool process(ObjStr* a, ObjStr* b)) {

	//compat�Ƃ́H�c�^�C�v�֌W�B�]�T����������^�C�v�֌W�ɂ��������������ł������������Ǘ]�T�͂Ȃ�����

	DataList checkList; Initialize(&checkList);// �`�F�b�N���X�g(xBased������Ԃ����K�v�ȃ��X�g)�쐬

	xBased->crnt = xBased->head;// x�����X�g�̒��ڃm�[�h�����Z�b�g
	while (Next(xBased)) {
		if (xBased->crnt->d._oE.mp_L == NULL) {// ���ׂ��I�u�W�F�N�g�[���I�u�W�F�N�g�̍��[������
			InsertRear(&checkList, xBased->crnt->d);//���̃I�u�W�F�N�g���`�F�b�N���X�g�ɓo�^(�E�[�͓o�^���Ȃ�)

			//�`�F�b�N���X�g�ɐV�����I�u�W�F�N�g�[���ǉ�����Ă��Ȃ��Ȃ��
			//���U���g���X�g�ɐV�������̂��������͂Ȃ��̂Œ��ג����K�v�͂Ȃ�
			DataNode *sub_crnt; checkList.crnt = checkList.head;
			while (Next(&checkList)) {//���X�g���_�~�[�݂̂������茩�I�������E�o
				sub_crnt = checkList.crnt;
				while (Next(&checkList)) {
					//�J�����g�ȑO�̃m�[�h�͈�傫�����[�v�Œ��׏I����Ă��锤�Ȃ̂Ŕ�ׂ�̂�crnt�̎�����ł悢
					if (SearchObjCon(result, sub_crnt->d._oE.mp_obj, checkList.crnt->d._oE.mp_obj) == NULL)
						InsertRearCon(result, sub_crnt->d._oE.mp_obj, checkList.crnt->d._oE.mp_obj,
								// �܂����ʃ��X�g�ɂȂ����̂������猋�ʃ��X�g�ɓo�^
							process(sub_crnt->d._oE.mp_obj, checkList.crnt->d._oE.mp_obj));
								// ��������֐��œ�������(bool�^)���o�^
				}
				checkList.crnt = sub_crnt;//�J�����g�܂Ŗ߂�
			}
		}
		if (xBased->crnt->d._oE.mp_L != NULL) {// ���ׂ��I�u�W�F�N�g�[���I�u�W�F�N�g�̉E�[������
			checkList.crnt = SearchObjEdge(&checkList, xBased->crnt->d._oE.mp_L->mp_obj);
			RemoveCurrent(&checkList);
				// �E�[�܂ŗ����̂ŁA�Ή����鍶�[�m�[�h���`�F�b�N���X�g����T���ď���
				// NULL�ł��邱�Ƃ͂Ȃ���
		}
	}

	Terminate(&checkList);//�`�F�b�N���X�g�o��
}
