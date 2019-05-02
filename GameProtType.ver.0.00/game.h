#pragma once
#ifndef _GAME_H_
#define _GAME_H_


#include "main.h"

enum SceneList {
	TITLE,
	//////////////// îÛè¿í«â¡
	SELECT_MODE,
	CHOOSE_STAGE,
	//////////////// Ç±Ç±Ç‹Ç≈
	STAGE,
	RESULT,
	SCENE_NUM,
};

//Å@îÛè¿í«â¡
int *getScene();
//Å@Ç±Ç±Ç‹Ç≈

void initializeGame();
void updateGame();
void drawGame();
void printGame();
void unInitializeGame();
void changeScene();

#endif