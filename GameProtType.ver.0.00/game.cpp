#include "game.h"
#include "input.h"
#include "Title.h"
#include "Stage.h"
#include "Result.h"
#include "textureLoader.h"

int scene;
void changeScene();

void initializeGame() {
	getTextureLoader()->load(getDevice());//�e�N�X�`���̓Ǎ�
	scene = TITLE;
	initializeTitle();
	initializeStage();
	initializeResult();
};

void updateGame() {
	
	switch (scene)
	{
	case TITLE:		updateTitle();		break;
	case SELECT_MODE: updateTitle(); break;	// ����ǉ�
	case CHOOSE_STAGE: updateTitle(); break;	// ����ǉ�
	case STAGE:		updateStage();	break;
	case RESULT:		updateResult();	break;
	default:	break;
	}
};

void drawGame() {
	switch (scene)
	{
	case TITLE:		drawTitle();break;
	case SELECT_MODE: drawTitle(); break;	// ����ǉ�
	case CHOOSE_STAGE: drawTitle(); break;	// ����ǉ�
	case STAGE:		drawStage(); break;
	case RESULT:		drawResult(); break;
	default:	break;
	}
};

void printGame()
{
	switch (scene)
	{
	case TITLE:		printTitle(); break;
	case SELECT_MODE: printTitle(); break;	// ����ǉ�
	case CHOOSE_STAGE: printTitle(); break;	// ����ǉ�
	case STAGE:		printStage(); break;
	case RESULT:		printResult(); break;
	default:	break;
	}
}

void unInitializeGame() {
	getTextureLoader()->release();//�e�N�X�`���̉��
	unInitializeTitle();
	unInitializeStage();
	unInitializeResult();
};

void changeScene()
{
	if(GetKeyboardTrigger(DIK_RETURN))
	{
		scene++;
		if (scene >= SCENE_NUM)
		{
			scene = 0;
		}
	}
}

// ����ǉ�
int *getScene() { return (&scene); }
// �����܂�