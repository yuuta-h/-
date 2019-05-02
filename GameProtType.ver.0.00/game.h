#pragma once
#ifndef _GAME_H_
#define _GAME_H_


#include "main.h"

enum SceneList {
	TITLE,
	//////////////// ����ǉ�
	SELECT_MODE,
	CHOOSE_STAGE,
	//////////////// �����܂�
	STAGE,
	RESULT,
	SCENE_NUM,
};

//�@����ǉ�
int *getScene();
//�@�����܂�

void initializeGame();
void updateGame();
void drawGame();
void printGame();
void unInitializeGame();
void changeScene();

#endif