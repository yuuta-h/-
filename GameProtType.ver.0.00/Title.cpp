#include "Title.h"
#include "textDX.h"
#include "Image.h"
#include "textureLoader.h"

// ����ǉ�
#include "Select_Game.h"
#define _CRT_SECURE_NO_WARNINGS
#include <string>
using namespace std;
#include "read_text.h"
// �����܂�

Image back;


void initializeTitle() {
	InitImage(&back, getTexture(textureLoaderNS::BACK_GROUND), 0, 0, 1536, 1152);

	// ����ǉ�
	string info_file = "information.txt"; // �ǂݍ��݃t�@�C�������X�e�[�W�ԍ�
	read_Status_File(info_file);
	// uninit_Stage_Struct();

	initSelectTitle();
	// �����܂�

};
void updateTitle() {
	updateSelectTitle();	// ����ǉ�
};


void drawTitle() {
	DrawImage(&back);
	
	drawSelectTitle();	// ����ǉ�
};
void printTitle() {

	// printTextDX(getDebugFont(), "Title", 0, 0);

	printSelectTitle();	// ����ǉ�
};
void unInitializeTitle() {};