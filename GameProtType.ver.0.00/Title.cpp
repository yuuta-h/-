#include "Title.h"
#include "textDX.h"
#include "Image.h"
#include "textureLoader.h"

// 樋沼追加
#include "Select_Game.h"
#define _CRT_SECURE_NO_WARNINGS
#include <string>
using namespace std;
#include "read_text.h"
// ここまで

Image back;


void initializeTitle() {
	InitImage(&back, getTexture(textureLoaderNS::BACK_GROUND), 0, 0, 1536, 1152);

	// 樋沼追加
	string info_file = "information.txt"; // 読み込みファイル名＝ステージ番号
	read_Status_File(info_file);
	// uninit_Stage_Struct();

	initSelectTitle();
	// ここまで

};
void updateTitle() {
	updateSelectTitle();	// 樋沼追加
};


void drawTitle() {
	DrawImage(&back);
	
	drawSelectTitle();	// 樋沼追加
};
void printTitle() {

	// printTextDX(getDebugFont(), "Title", 0, 0);

	printSelectTitle();	// 樋沼追加
};
void unInitializeTitle() {};