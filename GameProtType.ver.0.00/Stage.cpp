#include "Stage.h"
#include "textDX.h"
#include "input.h"
#include "messageDialog.h"
#include "inputDialog.h"
#include "object.h"//西川
#include "game.h"
#include "Select_Game.h" // 樋沼追加

MessageDialog mDialog;
InputDialog inDialog;

void initializeStage() {
	inDialog.initialize(getHWnd());
	mDialog.initialize(getHWnd());
	mDialog.print("Hello World");
	initializeObject(0);//西川
};
void updateStage() {

	// 樋沼追加
	// timerはmainにあるから、そこでif文するか、ここにtimerを持ってくるかどちらがいいか
	bool p_pause = *getPause();
	updatePause();
	if (p_pause == FALSE)
	// 大体ここまで
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
	drawObject();//西川
	drawPause(); // 樋沼
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