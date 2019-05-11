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
//���� 0.22
	textureName[textureLoaderNS::STAR] = { "TEXTURE/star.png" };
	textureName[textureLoaderNS::BLACK_HOLE] = { "TEXTURE/blackHole.png" };
	textureName[textureLoaderNS::WHITE_HOLE] = { "TEXTURE/whiteHole.png" };
	textureName[textureLoaderNS::COMET] = { "TEXTURE/comet.jpg" };
	textureName[textureLoaderNS::PLANET] = { "TEXTURE/planet.jpg" };

	textureName[textureLoaderNS::BACK_GROUND] = { "TEXTURE/gameBG.png" };
}


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
