#pragma once

#include "main.h"

namespace textureLoaderNS
{
	enum TEXTURE_NUMBER {
		BACK_GROUND,
		// ���
		TITLE_LOGO, 
		TITLE_PRESS_ENTER,
		TITLE_NEW_GAME,
		TITLE_SELECT_STAGE,
		TITLE_CURSOR,
		THUM_STAGE01,
		THUM_STAGE02,
		THUM_STAGE03,
		THUM_STAGE04,
		THUM_STAGE05,
		THUM_STAGE06,
		THUM_STAGE07,
		THUM_STAGE08,
		THUM_STAGE09,
		PAUSE,
		//�����܂�
		MAX_TEXTURE,
	};
}

class TextureLoader
{
private:
	const char* textureName[textureLoaderNS::MAX_TEXTURE];
	LPDIRECT3DTEXTURE9 g_pD3DTexture[textureLoaderNS::MAX_TEXTURE];

public:
	TextureLoader();
	~TextureLoader();

	void load(LPDIRECT3DDEVICE9 pDevice);
	void release();

	LPDIRECT3DTEXTURE9* getTexture(int i) { return &g_pD3DTexture[i]; }
};

TextureLoader* getTextureLoader();
LPDIRECT3DTEXTURE9* getTexture(int i);
