#pragma once
#include "main.h"
#include <string>
#include "textDX.h"
#include "input.h"
#include "messageDialog.h"

namespace inputDialogNS
{
	const COLOR_ARGB TEXT_BACK_COLOR = colorNS::BLACK; // ���̓e�L�X�g�̔w�i
	const COLOR_ARGB TEXT_COLOR = colorNS::WHITE; // ���̓e�L�X�g�̐F
}

class InputDialog:public MessageDialog
{
private:
		
	std::string inText; // ���̓e�L�X�g
	RECT inTextRect;// �e�L�X�g��`
	RECT tempRect;
	COLOR_ARGB textBackColor;//�e�L�X�g�̈�̔w�i�̐F
	COLOR_ARGB textFontColor;//�e�L�X�g�̈�̃t�H���g�̐F
	LPDIRECT3DVERTEXBUFFER9 inTextVerts;//�e�L�X�g�̈�̒��_�o�b�t�@

public:
	InputDialog();
	virtual ~InputDialog();

	// ���_�o�b�t�@������
	void prepareVerts();

	//InputDialog��\��
	const void draw();

	//���̓e�L�X�g��߂�
	std::string getText()
	{
		if (!visible)
		{
			return inText;
		}
		else
		{
			return "";
		}
	}

	// ���̓e�L�X�g�̃t�H���g�̐F��ݒ�
	void setTextFontColor(COLOR_ARGB fc) { textFontColor = fc; }
	// ���̓e�L�X�g�̔w�i�̐F��ݒ�
	void setTextBackColor(COLOR_ARGB bc) { textBackColor = bc; }

	// �e�L�X�gstr��InputDialog�ɕ\��
	void print(const std::string &str);

	// �u����v�C�x���g���`�F�b�N
	void update();

	// �O���t�B�b�N�X�f�o�C�X�����������Ƃ��ɌĂяo��
	void onLostDevice();
};