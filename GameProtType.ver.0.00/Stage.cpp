#include "Stage.h"
#include "textDX.h"
#include "input.h"
#include "Image.h"
#include"textureLoader.h"
#include "messageDialog.h"
#include "inputDialog.h"
#include "object.h"
#include "useList.h"
#include "collision.h"//����0515/git0.02 �R���W�������̊֐������X�g�ɓn������

MessageDialog mDialog;
InputDialog inDialog;

StageObj stageObj;//���� 0.02
Image gameBG;
DataList xBasedList;//����0515/git0.02 x���W���E�I�u�W�F�N�g�E���X�g(�Q�[�����ʗp)
DataList resultList;//����0515/git0.02 �m���ߌ��ʁE�I�u�W�F�N�g�֌W�E���X�g(���t���[���g���̂�)

void initializeStage() {
	inDialog.initialize(getHWnd());
	mDialog.initialize(getHWnd());
	mDialog.print("Hello World");
	InitImage(&gameBG, getTexture(textureLoaderNS::BACK_GROUND), 0, 0, 1200, 900);
};
void startStage() {//����0515/git0.02 �V�����X�e�[�W�ɓ���O�ɌĂԊ֐�
	initializeObject(&stageObj, 0);//���� 0.02 �ЂƂ܂�0�X�e�[�W��
	initializeObjList(&stageObj, &xBasedList, &resultList);
};
void updateStage() {
	inDialog.update();
	mDialog.update();
	updateObject(&stageObj);
	updateObjList(&xBasedList, &resultList,checkHitObjRR);//����0516/git0.02 x�����X�g���X�V�A�֐���n���Ă��̌��ʃ��X�g���擾
//	checkResultList(&resultList,);//����0515/git0.02
	if (getMouseMButton())
	{
		inDialog.print("please InputText");
	}

};
void drawStage() {
	inDialog.draw();
	DrawImage(&gameBG);
	//mDialog.draw();
	drawObject(&stageObj);
};

void printStage() {
	printTextDX(getDebugFont(), "Stage", 0, 0);
	printTextDX(getDebugFont(), "�}�E�X���{�^���������œ��̓_�C�A���O�{�b�N�X��\������", 500, 30);
	printTextDX(getDebugFont(), "mouseX:", 1000, 0, getMouseX());
	printTextDX(getDebugFont(), "mouseY:", 1000, 30, getMouseY());

//	printObject(&stageObj);//���� 0.22
	printList(&resultList);//����0515/git0.02
};
void unInitializeStage() {
	finishStage();//����0515/git0.02
};
void finishStage() {//����0515/git0.02 ���̃X�e�[�W����߂���ɌĂԊ֐�
	uninitializeObject(&stageObj);
	uninitializeObjList(&xBasedList, &resultList);
};
