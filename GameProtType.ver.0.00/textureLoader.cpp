#include "TextureLoader.h"

TextureLoader textureLoader;
TextureLoader* getTextureLoader()
{
	return &textureLoader;
}
LPDIRECT3DTEXTURE9* getTexture(int i)
{
	return textureLoader.getTexture(i);
}

TextureLoader::TextureLoader()
{
	textureName[textureLoaderNS::BACK_GROUND] = { "TEXTURE/backGround.png" };

	// ����ǉ�
	textureName[textureLoaderNS::TITLE_LOGO] = { "TEXTURE/title_logo.png" };
	textureName[textureLoaderNS::TITLE_PRESS_ENTER] = { "TEXTURE/press_enter.png" };
	textureName[textureLoaderNS::TITLE_NEW_GAME] = { "TEXTURE/new_game.png" };
	textureName[textureLoaderNS::TITLE_SELECT_STAGE] = { "TEXTURE/stage_select.png" };
	textureName[textureLoaderNS::TITLE_CURSOR] = { "TEXTURE/cursor.png" };
	textureName[textureLoaderNS::PAUSE] = { "TEXTURE/pause.png" };
	textureName[textureLoaderNS::THUM_STAGE01] = { "TEXTURE/stage01.png" };
	
	// �ꎞ�I�ɃX�e�[�W2�ȍ~�����摜�z�u
	textureName[textureLoaderNS::THUM_STAGE02] = { "TEXTURE/stage01.png" };
	textureName[textureLoaderNS::THUM_STAGE03] = { "TEXTURE/stage01.png" };
	textureName[textureLoaderNS::THUM_STAGE04] = { "TEXTURE/stage01.png" };
	textureName[textureLoaderNS::THUM_STAGE05] = { "TEXTURE/stage01.png" };
	textureName[textureLoaderNS::THUM_STAGE06] = { "TEXTURE/stage01.png" };
	textureName[textureLoaderNS::THUM_STAGE07] = { "TEXTURE/stage01.png" };
	textureName[textureLoaderNS::THUM_STAGE08] = { "TEXTURE/stage01.png" };
	textureName[textureLoaderNS::THUM_STAGE09] = { "TEXTURE/stage01.png" };

	//textureName[textureLoaderNS::THUM_STAGE02] = { "TEXTURE/stage02.png" };
	//textureName[textureLoaderNS::THUM_STAGE03] = { "TEXTURE/stage03.png" };
	//textureName[textureLoaderNS::THUM_STAGE04] = { "TEXTURE/stage04.png" };
	//textureName[textureLoaderNS::THUM_STAGE05] = { "TEXTURE/stage05.png" };
	//textureName[textureLoaderNS::THUM_STAGE06] = { "TEXTURE/stage06.png" };
	//textureName[textureLoaderNS::THUM_STAGE07] = { "TEXTURE/stage07.png" };
	//textureName[textureLoaderNS::THUM_STAGE08] = { "TEXTURE/stage08.png" };
	// �����܂�
}//aaaa


TextureLoader::~TextureLoader()
{
	release();
}


void TextureLoader::load(LPDIRECT3DDEVICE9 pDevice)
{
	for (int i = 0; i < textureLoaderNS::MAX_TEXTURE; i++)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
			textureName[i],		// �t�@�C���̖��O
			&g_pD3DTexture[i]);	// �ǂݍ��ރ������[
	}
}

void TextureLoader::release()
{
	for (int i = 0; i < textureLoaderNS::MAX_TEXTURE; i++) {
		if (g_pD3DTexture[i] != NULL)
		{// �e�N�X�`���̊J��
			g_pD3DTexture[i]->Release();
			g_pD3DTexture[i] = NULL;
		}
	}
}
