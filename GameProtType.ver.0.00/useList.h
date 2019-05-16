//����
#pragma once

#include "main.h"
#include "dataList.h"

//�X�e�[�W�J�n���AxBased/result�Ƀ_�~�[�m�[�h��o�^�AxBased�ɃI�u�W�F�N�g�̒[��S�ēo�^
void initializeObjList(StageObj* p_stageobj, DataList* xBased, DataList* result);
//�X�e�[�W�I�����AxBased��result�𖕏�
void uninitializeObjList(DataList* xBased, DataList* result);

//���t���[���AxBased���X�g�̏�Ԃ��ێ��Aresult���X�g���쐬�A�y��process(�悻��������������)�����s
void updateObjList(DataList* xBased, DataList* result, bool process(ObjStr* a, ObjStr* b));
//���t���[���A���ɍ�������ʃ��X�g��S������鏈��(�s�s�����o�����Ȃ̂ŏo���Ƃ��͕ς��܂�)
void checkResultList(DataList* result, void process(ObjStr* a, ObjStr* b));

//���t���[���A���X�g�̒��g��S�ĕ`��
void printList(DataList* draw);
