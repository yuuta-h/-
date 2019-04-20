#pragma once
#include "main.h"
#include <string>

struct TextDX
{
	COLOR_ARGB color; // �t�H���g�J���[(a,r,g,b)
	LPD3DXFONT dxFont; // �t�H���g�|�C���^
	RECT fontRect; // �e�L�X�g��`
	// �e�L�X�g�̉�]�s��
	D3DXMATRIX matrix;
	float angle; // �e�L�X�g�̉�]�p�x�i���W�A���p�j
	
};

void initializeTextDX();
void unInitializeTextDX();

bool createTextDX(TextDX* text,int height, bool bold,bool italic,const std::string &fontName);
int printTextDX(TextDX* text, const std::string &str, int x, int y);
int printTextDX(TextDX* text, const std::string &str, int x, int y, float value);
int printTextDX(TextDX* text, const std::string &str, int x, int y, int value);
TextDX* getDebugFont();
