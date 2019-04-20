#include "Stage.h"
#include "textDX.h"
#include "input.h"
#include "messageDialog.h"
#include "inputDialog.h"
#include "object.h"//西川

MessageDialog mDialog;
InputDialog inDialog;

void initializeStage() {
	inDialog.initialize(getHWnd());
	mDialog.initialize(getHWnd());
	mDialog.print("Hello World");
	initializeObject(0);//西川
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
	drawObject();//西川
};

void printStage() {
	printTextDX(getDebugFont(), "Stage", 0, 0);
	printTextDX(getDebugFont(), "マウス中ボタンを押下で入力ダイアログボックスを表示する", 500, 30);
	printTextDX(getDebugFont(), "mouseX:", 1000, 0, getMouseX());
	printTextDX(getDebugFont(), "mouseY:", 1000, 30, getMouseY());
};
void unInitializeStage() {
	uninitializeObject();//西川
};