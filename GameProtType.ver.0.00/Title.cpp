#include "Title.h"
#include "textDX.h"
#include "Image.h"
#include"textureLoader.h"

// ����ǉ�
#define _CRT_SECURE_NO_WARNINGS
#include <string>
using namespace std;
#include "read_text.h"
// �����܂�

Image back;

void initializeTitle() {
	InitImage(&back, getTexture(textureLoaderNS::BACK_GROUND), 0, 0, 1200, 900);

	// ����ǉ�
	string info_file = "information.txt"; // �ǂݍ��݃t�@�C�������X�e�[�W�ԍ�
	read_Status_File(info_file);
	// uninit_Stage_Struct();
	// �����܂�

};
void updateTitle() {

};
void drawTitle() {
	DrawImage(&back);
};
void printTitle() {
	printTextDX(getDebugFont(), "Title", 0, 0);
};
void unInitializeTitle() {};