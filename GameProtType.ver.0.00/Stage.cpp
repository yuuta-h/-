#include "Stage.h"
#include "textDX.h"
#include "input.h"
#include "Image.h"
#include"textureLoader.h"
#include "messageDialog.h"
#include "inputDialog.h"
#include "object.h"
#include "useList.h"
#include "collision.h"//西川0515/git0.02 コリジョン内の関数をリストに渡すため

MessageDialog mDialog;
InputDialog inDialog;

StageObj stageObj;//西川 0.02
Image gameBG;
DataList xBasedList;//西川0515/git0.02 x座標順・オブジェクト・リスト(ゲーム中通用)
DataList resultList;//西川0515/git0.02 確かめ結果・オブジェクト関係・リスト(毎フレーム使い捨て)

void initializeStage() {
	inDialog.initialize(getHWnd());
	mDialog.initialize(getHWnd());
	mDialog.print("Hello World");
	InitImage(&gameBG, getTexture(textureLoaderNS::BACK_GROUND), 0, 0, 1200, 900);
};
void startStage() {//西川0515/git0.02 新しいステージに入る前に呼ぶ関数
	initializeObject(&stageObj, 0);//西川 0.02 ひとまず0ステージで
	initializeObjList(&stageObj, &xBasedList, &resultList);
};
void updateStage() {
	inDialog.update();
	mDialog.update();
	updateObject(&stageObj);
	updateObjList(&xBasedList, &resultList,checkHitObjRR);//西川0516/git0.02 x順リストを更新、関数を渡してその結果リストを取得
//	checkResultList(&resultList,);//西川0515/git0.02
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
	printTextDX(getDebugFont(), "マウス中ボタンを押下で入力ダイアログボックスを表示する", 500, 30);
	printTextDX(getDebugFont(), "mouseX:", 1000, 0, getMouseX());
	printTextDX(getDebugFont(), "mouseY:", 1000, 30, getMouseY());

//	printObject(&stageObj);//西川 0.22
	printList(&resultList);//西川0515/git0.02
};
void unInitializeStage() {
	finishStage();//西川0515/git0.02
};
void finishStage() {//西川0515/git0.02 今のステージをやめた後に呼ぶ関数
	uninitializeObject(&stageObj);
	uninitializeObjList(&xBasedList, &resultList);
};
