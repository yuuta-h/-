// ����ǉ�

#ifndef _SELECT_GAME_H_
#define _SELECT_GAME_H_

#include "main.h"

namespace titleNS
{
	const float LOGO_WIDTH = 500;
	const float LOGO_HEIGHT = 500;
	const float PRESS_ENTER_WIDTH = 1368 / 4;
	const float PRESS_ENTER_HEIGHT = 201 / 4;
	const float NEW_GAME_WIDTH = 1336 / 5;
	const float NEW_GAME_HEIGHT = 331 / 5;
	const float CHOOSE_STAGE_WIDTH = 2247 / 5;
	const float CHOOSE_STAGE_HEIGHT = 331 / 5;
	const float CURSOR_SELECT_WIDTH = 1140 / 15;
	const float CURSOR_SELECT_HEIGHT = 1317 / 15;
	const float CURSOR_CHOOSE_WIDTH = 1140 / 30;
	const float CURSOR_CHOOSE_HEIGHT = 1317 / 30;
	const float THUM_STAGE_WIDTH = 200;
	const float THUM_STAGE_HEIGHT = 100;
	const float PAUSE_WIDTH = 1600 / 30;
	const float PAUSE_HEIGHT = 573 / 30;

	// Cursor�ʒu�̒���
	const float CURSOR_SELECT_FIX_X = 200;
	const float CURSOR_SELECT_FIX_Y = 0;
	const float CURSOR_CHOOSE_FIX_X = 50;
	const float CURSOR_CHOOSE_FIX_Y = 30;
}

enum MOVE_CURSOR_SELECT
{
	MOVE_NEW_GAME = 0,
	MOVE_CHOOSE_STAGE,
	MOVE_MAX
};

enum MOVE_CURSOR_CHOOSE
{
	STAGE01 = 0,
	STAGE02,
	STAGE03,
	STAGE04,
	STAGE05,
	STAGE06,
	STAGE07,
	STAGE08,
	STAGE09,
	MOVE_CHOOSE_MAX
};


// Title.cpp�ɒ��ڑg�ݍ��ޗp�̊֐� 
// update��draw��Switch�̏�������
void initSelectTitle();
void updateSelectTitle();
void drawSelectTitle();
void printSelectTitle();

// ���[�h�I��
// draw or update SelectTitle();���ɑg�ݍ��ފ֐��i��̓I�ȏ����j
void moveSelectModeCursor();
int moveTitleCursor(int scene);

// �X�e�[�W�I��
// draw or update SelectTitle();���ɑg�ݍ��ފ֐��i��̓I�ȏ����j
void moveChooseStageCursor();
int moveStageCursor(int scene);
void fixCursorNum(); // Cursor�̐�����0�ȉ��̂Ƃ��͍ő�l�ɂ���

// ���̑��i���[�h�E�X�e�[�W�I�����p�̊֐��j
void returnBeforeScene(); // �O�̍��ڂɖ߂�
void unInitializeSelectTitle(); // �I������
void changeCursorSize(); // Cursor�̃T�C�Y���V�[�����Ƃɕς���
void moveCursorPos(Image* image); // Cursor�̈ʒu��ς���

// draw�֐��܂Ƃ�
void drawTitleStart();
void drawSelectMode();
void drawChooseStage();

// �|�[�Y�����@�ꎞ�I�ɂ����ɋL�q
void updatePause();
void drawPause();



// �����܂�
#endif