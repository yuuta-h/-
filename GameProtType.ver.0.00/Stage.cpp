#include "Stage.h"
#include "textDX.h"
#include "input.h"
#include "messageDialog.h"
#include "inputDialog.h"
#include "object.h"//����

MessageDialog mDialog;
InputDialog inDialog;

void initializeStage() {
	inDialog.initialize(getHWnd());
	mDialog.initialize(getHWnd());
	mDialog.print("Hello World");
	initializeObject(0);//����
};
void updateStage() {
	inDialog.update();
	mDialog.update();
	if (getMouseMButton())
	{
		inDialog.print("please InputText");
	}
};
void drawStage() {
	inDialog.draw();
	//mDialog.draw();
	drawObject();//����
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