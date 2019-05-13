////////////////////////////////////////// ����ǉ�
#include "textureLoader.h"
#include "Image.h"
#include "Title.h"
#include "textDX.h"
#include "Select_Game.h"
#include "game.h"
#include "input.h"
#include "game.h"
#include "object.h"

using namespace titleNS;
Image title, title_press_enter, new_game, choose_stage, cursor, pause;
Image stage01, stage02, stage03, stage04, stage05, stage06, stage07, stage08, stage09;
int g_cursor = 0;

// Title.cpp�ɑg�ݍ��ޗp�̊֐�
// ��̓I�ȏ�����init�ȊO�Ȃ�ׂ��ʊ֐��ɋL�q
void initSelectTitle() {
	float x;
	float y;
	float width;
	float height;

	//
	x = WINDOW_WIDTH / 4;
	y = WINDOW_HEIGHT / 18;
	width = LOGO_WIDTH;
	height = LOGO_HEIGHT;
	InitImage(&title, getTexture(textureLoaderNS::TITLE_LOGO), x, y, width, height);

	//
	x = WINDOW_WIDTH / 2.5;
	y = WINDOW_HEIGHT / 1.4;
	width = PRESS_ENTER_WIDTH;
	height = PRESS_ENTER_HEIGHT;
	InitImage(&title_press_enter, getTexture(textureLoaderNS::TITLE_PRESS_ENTER), x, y, width, height);

	//
	x = WINDOW_WIDTH / 2;
	y = WINDOW_HEIGHT / 2.8;
	width = NEW_GAME_WIDTH;
	height = NEW_GAME_HEIGHT;
	InitImage(&new_game, getTexture(textureLoaderNS::TITLE_NEW_GAME), x, y, width, height);

	//
	x = WINDOW_WIDTH / 2;
	y = WINDOW_HEIGHT / 1.8;
	width = CHOOSE_STAGE_WIDTH;
	height = CHOOSE_STAGE_HEIGHT;
	InitImage(&choose_stage, getTexture(textureLoaderNS::TITLE_SELECT_STAGE), x, y, width, height);

	//
	x = WINDOW_WIDTH / 3;
	y = WINDOW_HEIGHT / 2.8;
	width = CURSOR_SELECT_WIDTH;
	height = CURSOR_SELECT_HEIGHT;
	InitImage(&cursor, getTexture(textureLoaderNS::TITLE_CURSOR), x, y, width, height);

	//
	x = WINDOW_WIDTH / 9;
	y = WINDOW_HEIGHT / 9;
	width = THUM_STAGE_WIDTH;
	height = THUM_STAGE_HEIGHT;
	InitImage(&stage01, getTexture(textureLoaderNS::THUM_STAGE01), x, y, width, height);

	//
	x = WINDOW_WIDTH / 2.5;
	y = WINDOW_HEIGHT / 9;
	width = THUM_STAGE_WIDTH;
	height = THUM_STAGE_HEIGHT;
	InitImage(&stage02, getTexture(textureLoaderNS::THUM_STAGE02), x, y, width, height);

	//
	x = WINDOW_WIDTH / 1.4;
	y = WINDOW_HEIGHT / 9;
	width = THUM_STAGE_WIDTH;
	height = THUM_STAGE_HEIGHT;
	InitImage(&stage03, getTexture(textureLoaderNS::THUM_STAGE03), x, y, width, height);

	//
	x = WINDOW_WIDTH / 9;
	y = WINDOW_HEIGHT / 2.5;
	width = THUM_STAGE_WIDTH;
	height = THUM_STAGE_HEIGHT;
	InitImage(&stage04, getTexture(textureLoaderNS::THUM_STAGE04), x, y, width, height);

	//
	x = WINDOW_WIDTH / 2.5;
	y = WINDOW_HEIGHT / 2.5;
	width = THUM_STAGE_WIDTH;
	height = THUM_STAGE_HEIGHT;
	InitImage(&stage05, getTexture(textureLoaderNS::THUM_STAGE05), x, y, width, height);

	//
	x = WINDOW_WIDTH / 1.4;
	y = WINDOW_HEIGHT / 2.5;
	width = THUM_STAGE_WIDTH;
	height = THUM_STAGE_HEIGHT;
	InitImage(&stage06, getTexture(textureLoaderNS::THUM_STAGE06), x, y, width, height);

	//
	x = WINDOW_WIDTH / 9;
	y = WINDOW_HEIGHT / 1.4;
	width = THUM_STAGE_WIDTH;
	height = THUM_STAGE_HEIGHT;
	InitImage(&stage07, getTexture(textureLoaderNS::THUM_STAGE07), x, y, width, height);

	//
	x = WINDOW_WIDTH / 2.5;
	y = WINDOW_HEIGHT / 1.4;
	width = THUM_STAGE_WIDTH;
	height = THUM_STAGE_HEIGHT;
	InitImage(&stage08, getTexture(textureLoaderNS::THUM_STAGE08), x, y, width, height);

	//
	x = WINDOW_WIDTH / 1.4;
	y = WINDOW_HEIGHT / 1.4;
	width = THUM_STAGE_WIDTH;
	height = THUM_STAGE_HEIGHT;
	InitImage(&stage09, getTexture(textureLoaderNS::THUM_STAGE09), x, y, width, height);

	
	x = WINDOW_WIDTH / 3;
	y = WINDOW_HEIGHT / 2.8;
	width = PAUSE_WIDTH;
	height = PAUSE_HEIGHT;
	InitImage(&pause, getTexture(textureLoaderNS::PAUSE), x, y, width, height);
}

void updateSelectTitle() {

	int *scene = getScene();

	switch (*scene)
	{
	case TITLE: 
		changeScene(); break;

	// MODE�I���̂Ƃ������A����image�����W�ړ�����
	// �X�ɁA�I�񂾂��̂ɂ��V�[���J�ڐ悪�ς��
	case SELECT_MODE:
		changeCursorSize();
		moveSelectModeCursor(); break;

	case CHOOSE_STAGE:
		changeCursorSize();
		moveChooseStageCursor(); break;
	}
}

void drawSelectTitle()
{
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	int *scene = getScene();
	switch (*scene)
	{
	case TITLE:			drawTitleStart();	break;
	case SELECT_MODE:	drawSelectMode();	break;
	case CHOOSE_STAGE:	drawChooseStage();	break;
	}
}

void printSelectTitle() {

	int *scene = getScene();
	switch (*scene )
	{
	case TITLE: 	printTextDX(getDebugFont(), "Title", 0, 0); break;
	case SELECT_MODE: printTextDX(getDebugFont(), "SelectGame", 0, 0); break;
	case CHOOSE_STAGE: printTextDX(getDebugFont(), "ChooseStage", 0, 0); break;
	}	
};

// ���[�h�I��
void moveSelectModeCursor()
{
	int *scene = getScene();
	float x, y;
	g_cursor += moveTitleCursor(*scene);
	returnBeforeScene();

	switch (g_cursor % MOVE_MAX)
	{
	case MOVE_NEW_GAME:
		moveCursorPos(&new_game);
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			// �X�e�[�W01�ɔ��
			g_cursor = 0;
			*scene = STAGE;
		}
		break;

	case MOVE_CHOOSE_STAGE:
		moveCursorPos(&choose_stage);
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			// �X�e�[�W�I���ɔ��
			g_cursor = 0;
			*scene = CHOOSE_STAGE;
		}
		break;
	}
}

int moveTitleCursor(int scene)
{
	if (scene == SELECT_MODE)
	{
		if (GetKeyboardTrigger(DIK_UP) || GetKeyboardTrigger(DIK_DOWN))
		{
			return 1;
		}
	}
}


// �X�e�[�W�I��
void moveChooseStageCursor()
{
	int *scene = getScene();
	g_cursor += moveStageCursor(*scene); 
	fixCursorNum();
	returnBeforeScene();

	if (GetKeyboardTrigger(DIK_RETURN))
	{
		// void �� int �ɂ��ĕԂ�l��n���悤�ɂ���H
		initializeObject(g_cursor % MOVE_CHOOSE_MAX);
		g_cursor = 0;

		// STAGE�𐳂����J�ڐ�ɕς���K�v����
		// �����@STAGE + (g_cursor % MOVE_CHOOSE_MAX)
		// game.h���Ƒ��k
		*scene = STAGE;
	}

	switch (g_cursor % MOVE_CHOOSE_MAX)
	{
	case STAGE01:
		moveCursorPos(&stage01);
		break;
	case STAGE02:
		moveCursorPos(&stage02);
		break;
	case STAGE03:
		moveCursorPos(&stage03);
		break;
	case STAGE04:
		moveCursorPos(&stage04);
		break;
	case STAGE05:
		moveCursorPos(&stage05);
		break;
	case STAGE06:
		moveCursorPos(&stage06);
		break;
	case STAGE07:
		moveCursorPos(&stage07);
		break;
	case STAGE08:
		moveCursorPos(&stage08);
		break;
	case STAGE09:
		moveCursorPos(&stage09);
		break;
	}
}

int moveStageCursor(int scene)
{
	if (scene == CHOOSE_STAGE)
	{
		if (GetKeyboardTrigger(DIK_RIGHT))
		{
			return 1;
		}
		if (GetKeyboardTrigger(DIK_LEFT))
		{
			return -1;
		}
		if (GetKeyboardTrigger(DIK_UP))
		{
			return -3;
		}
		if (GetKeyboardTrigger(DIK_DOWN))
		{
			return 3;
		}
	}
}

void fixCursorNum()
{
	if (g_cursor < 0)
	{
		g_cursor = MOVE_CHOOSE_MAX;
	}
}

// ���̑�
void returnBeforeScene()
{
	int *scene = getScene();
	if (GetKeyboardTrigger(DIK_BACK))
	{
		g_cursor = 0;
		*scene -= 1;
	}
}

void unInitializeSelectTitle()
{
}

void changeCursorSize()
{
	int *scene = getScene();
	float width, height;
	switch (*scene)
	{
	case SELECT_MODE:
		width = CURSOR_SELECT_WIDTH;
		height = CURSOR_SELECT_HEIGHT;
		setSize(&cursor, width, height);
		break;

	case CHOOSE_STAGE:
		width = CURSOR_CHOOSE_WIDTH;
		height = CURSOR_CHOOSE_HEIGHT;
		setSize(&cursor, width, height);
		break;
	}
}

void moveCursorPos(Image* image)
{
	int *scene = getScene();
	float x, y;
	switch (*scene)
	{
	case SELECT_MODE:
		x = image->position.x - CURSOR_SELECT_FIX_X;
		y = image->position.y + CURSOR_SELECT_FIX_Y;
		setPosition(&cursor, x, y);
		break;

	case CHOOSE_STAGE:
		x = image->position.x - CURSOR_CHOOSE_FIX_X;
		y = image->position.y + CURSOR_CHOOSE_FIX_Y;
		setPosition(&cursor, x, y);
		break;
	}
}

// draw�֐��܂Ƃ�
void drawTitleStart()
{
	DrawImage(&title);
	DrawImage(&title_press_enter);
}
void drawSelectMode()
{
	DrawImage(&new_game);
	DrawImage(&choose_stage);
	DrawImage(&cursor);
}
void drawChooseStage()
{
	DrawImage(&cursor);
	DrawImage(&stage01);
	DrawImage(&stage02);
	DrawImage(&stage03);
	DrawImage(&stage04);
	DrawImage(&stage05);
	DrawImage(&stage06);
	DrawImage(&stage07);
	DrawImage(&stage08);
	DrawImage(&stage09);
}

// �|�[�Y����

// �b��̕ϐ�
bool g_pause = FALSE;

void updatePause()
{
	if (GetKeyboardTrigger(DIK_P))
	{
		g_pause = TRUE;
	}
	// updateStage()����
	// if(g_pause == FALSE) {����}�̕��������� 
}

void drawPause()
{
	if (g_pause == TRUE)
	{
		DrawImage(&pause);
	}
}

// �����܂�