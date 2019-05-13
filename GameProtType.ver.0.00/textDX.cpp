#include "textDX.h"

TextDX debugFont;

struct {
	const int m_TOP = 100, m_SIZE = 25;//�J�n�ʒu/�s�Ԋu
	int m_y = m_TOP;
}TxtLine;//���� 0.02

void initializeTextDX()
{
	createTextDX(&debugFont, 24, false, false, "Arial");
}
void unInitializeTextDX() 
{
	safeRelease(debugFont.dxFont);
};

bool createTextDX(TextDX* text,int height,bool bold,bool italic,const std::string &fontName ) {
	text->color = SETCOLOR_ARGB(255, 255, 255, 255); // ���F�Ńf�t�H���g

	// �t�H���g�ʒu��ݒ肷��
	text->fontRect.top = 0;
	text->fontRect.left = 0;
	text->fontRect.right = WINDOW_WIDTH;
	text->fontRect.bottom= WINDOW_HEIGHT;
	text->dxFont = NULL;
	text->angle = 0;

	UINT weight = FW_NORMAL;
	if (bold)
	{
		weight = FW_BOLD;
	}

	// DirectX�t�H���g�쐬
	if (FAILED(D3DXCreateFont(getDevice(), height, 0, weight, 1, italic,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, fontName.c_str(), &text->dxFont)))
	{
		return false;
	}

	// �ϊ��s����쐬����
	D3DXMatrixTransformation2D(&text->matrix, NULL, 0.0f, NULL, NULL, 0.0f, NULL);
	return true;
};

int printTextDX(TextDX* text,const std::string &str, int x,int y) {
	if (text->dxFont == NULL)
	{
		return 0;
	}

	// �t�H���g�ʒu��ݒ�
	text->fontRect.top = y;
	text->fontRect.left = x;
	
	// ��]���S
	D3DXVECTOR2 rCenter = D3DXVECTOR2((float)x, (float)y);

	// �e�L�X�g�����̊p�x�ŉ�]����s�������
	D3DXMatrixTransformation2D(&text->matrix, NULL, 0.0f, NULL, &rCenter, text->angle, NULL);

	// �s����X�v���C�g�ɓK�p
	getSprite()->SetTransform(&text->matrix);
	return text->dxFont->DrawTextA(getSprite(), str.c_str(), -1, &text->fontRect, DT_LEFT, text->color);
};


int printTextDX(TextDX* text,const std::string &str, int x, int y, float value)
{
	const int BUF_SIZE = 255;
	static char buffer[BUF_SIZE];
	// ����float��Cstring�ɕϊ�����
	_snprintf_s(buffer, BUF_SIZE, "%f", value);
	return printTextDX(text,str + buffer, x, y);
}
int printTextDX(TextDX* text,const std::string &str, int x, int y, int value)
{
	const int BUF_SIZE = 255;
	static char buffer[BUF_SIZE];
	// ����float��Cstring�ɕϊ�����
	_snprintf_s(buffer, BUF_SIZE, "%d", value);
	return printTextDX(text,str + buffer, x, y);
}

TextDX* getDebugFont()
{
	return &debugFont;
}

int txtLineReset(int newtop) {//���� 0.02
	TxtLine.m_y = newtop;//�s�ʒu���Z�b�g(���t���[���ŏ�)

	return TxtLine.m_TOP;//����̏����l���擾
//	txtLineReset(txtLineReset(0));//�Ə����Ə����l�Ń��Z�b�g�����
}

int txtLineBreak() {//���� 0.02
	TxtLine.m_y += TxtLine.m_SIZE;//���s
	return TxtLine.m_y - TxtLine.m_SIZE;
}