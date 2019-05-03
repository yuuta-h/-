#include "Stage.h"
#include "textDX.h"
#include "input.h"
#include "messageDialog.h"
#include "inputDialog.h"
#include "object.h"//����
#include "game.h"
#include "Select_Game.h" // ����ǉ�

MessageDialog mDialog;
InputDialog inDialog;

void initializeStage() {
	inDialog.initialize(getHWnd());
	mDialog.initialize(getHWnd());
	mDialog.print("Hello World");
	initializeObject(0);//����
};
void updateStage() {

	// ����ǉ�
	// timer��main�ɂ��邩��A������if�����邩�A������timer�������Ă��邩�ǂ��炪������
	bool p_pause = *getPause();
	updatePause();
	if (p_pause == FALSE)
	// ��̂����܂�
	{
		inDialog.update();
		mDialog.update();
		changeScene();
		if (getMouseMButton())
		{
			inDialog.print("please InputText");
		}
	}
};
void drawStage() {
	inDialog.draw();
	//mDialog.draw();
	drawObject();//����
	drawPause(); // ���
};

void printStage() {
	printTextDX(getDebugFont(), "Stage", 0, 0);
	printTextDX(getDebugFont(), "�}�E�X���{�^���������œ��̓_�C�A���O�{�b�N�X��\������", 500, 30);
	printTextDX(getDebugFont(), "mouseX:", 1000, 0, getMouseX());
	printTextDX(getDebugFont(), "mouseY:", 1000, 30, getMouseY());
};
void unInitializeStage() {
	uninitializeObject();//����
};