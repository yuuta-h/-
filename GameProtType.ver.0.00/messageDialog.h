#pragma once


#ifndef _MESSAGEDIALOG_H        // ���̃t�@�C���������̉ӏ��ŃC���N���[�h�����ꍇ�ɁA 
#define _MESSAGEDIALOG_H        // ���d�ɒ�`����邱�Ƃ�h���܂��B
#define WIN32_LEAN_AND_MEAN

#include <string>
#include "main.h"
#include "textDX.h"
#include "input.h"

namespace messageDialogNS
{
	const UINT WIDTH = 400;             // �_�C�A���O�̃f�t�H���g�̕�
	const UINT HEIGHT = 100;            // �f�t�H���g�̍���
	const UINT BORDER = 5;
	const UINT MARGIN = 5;              // �g����e�L�X�g�܂ł̗]��
	const char FONT[] = "Arial";        // �t�H���g
	const int FONT_HEIGHT = 18;         // �t�H���g�̍���
	const COLOR_ARGB FONT_COLOR = colorNS::WHITE;        // �e�L�X�g�̐F
	const COLOR_ARGB BORDER_COLOR = D3DCOLOR_ARGB(192, 192, 192, 192); // �g���̐F
	const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(255, 100, 100, 192);   // �w�i�F
	const UINT X = WINDOW_WIDTH / 2 - WIDTH / 2; // �f�t�H���g�̈ʒu
	const UINT Y = WINDOW_HEIGHT / 4 - HEIGHT / 2;
	const UINT BUTTON_WIDTH = (UINT)(FONT_HEIGHT * 4.5);
	const UINT BUTTON_HEIGHT = FONT_HEIGHT + 4;
	const int MAX_TYPE = 2;
	const int OK_CANCEL = 0;            // OK/Cancel �^�C�v�̃{�^��
	const int YES_NO = 1;               // Yes/No �^�C�v�̃{�^��
	static const char* BUTTON1_TEXT[MAX_TYPE] = { "OK", "YES" };
	static const char* BUTTON2_TEXT[MAX_TYPE] = { "CANCEL", "NO" };
	const byte DIALOG_CLOSE_KEY = VK_RETURN;    // Enter�L�[
	const COLOR_ARGB BUTTON_COLOR = colorNS::GRAY;       // button�w�i
	const COLOR_ARGB BUTTON_FONT_COLOR = colorNS::WHITE; // button�e�L�X�g�̐F
}

// ���b�Z�[�W�_�C�A���O
class MessageDialog
{
protected:
	TextDX*      dxFont;                 // DirectX�t�H���g
	float       x, y;                    // ��ʂ̈ʒu
	UINT        height;                 // �_�C�A���O�̍����Aprint()�Ōv�Z
	UINT        width;                  // �_�C�A���O�̕�
	std::string text;                   // �_�C�A���O�e�L�X�g
	RECT        textRect;               // �e�L�X�g�̋�`
	RECT        buttonRect;             // �{�^���̋�`
	RECT        button2Rect;            // �{�^��2�̋�`
	COLOR_ARGB  fontColor;              // �t�H���g�̐F(a,r,g,b)
	COLOR_ARGB  borderColor;            // �g�̐F (a,r,g,b)
	COLOR_ARGB  backColor;              // �w�i�̐F(a,r,g,b)
	COLOR_ARGB  buttonColor;            // �{�^���̐F
	COLOR_ARGB  buttonFontColor;        // �{�^���t�H���g�̐F
	VertexC vtx[4];                     // ���_�f�[�^
	LPDIRECT3DVERTEXBUFFER9 dialogVerts;        // �_�C�A���O�̒��_�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9 borderVerts;        // �g�̒��_�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9 buttonVerts;        // �{�^���̒��_�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9 button2Verts;       // �{�^��2�̒��_�o�b�t�@
	int buttonClicked;                  // �ǂ̃{�^�����N���b�N���ꂽ��(1�܂���2)
	int buttonType;                     // 0 = OK/Cancel, 1 = Yes/No
	bool    initialized;                // ����ɏ��������ꂽ�ꍇ�Atrue
	bool    visible;                    // true�̏ꍇ�͕\������
	HWND    hwnd;                       // �E�B���h�E�ւ̃n���h��
	float   screenRatioX, screenRatioY;

public:
	// �R���X�g���N�^
	MessageDialog();
	// �f�X�g���N�^
	virtual ~MessageDialog();

	// MessageDialog�̏�����
	// ���s�O: *g��Graphics �I�u�W�F�N�g���w��
	//      *in��Input �I�u�W�F�N�g���w��
	//      hwnd = �E�B���h�E�n���h��
	bool initialize(HWND hwnd);

	// ���_�o�b�t�@������
	void prepareVerts();

	// MessageDialog��\��
	const void draw();

	// �N���b�N���ꂽ�{�^����߂�
	// 0 = �{�^���̓N���b�N����Ă��Ȃ�
	// 1�͍��{�^��, 2�͉E�{�^��
	int getButtonClicked() { return buttonClicked; }

	// �\��/��\���̏�Ԃ�߂�
	bool getVisible() { return visible; }

	// �t�H���g�̐F��ݒ�
	void setFontColor(COLOR_ARGB fc) { fontColor = fc; }

	// �g�̐F��ݒ�
	void setBorderColor(COLOR_ARGB bc) { borderColor = bc; }

	// �w�i�̐F��ݒ�
	void setBackColor(COLOR_ARGB bc) { backColor = bc; }

	// �{�^���̐F��ݒ�
	void setButtonColor(COLOR_ARGB bc) { buttonColor = bc; }

	// �{�^���t�H���g�̐F��ݒ�
	void setButtonFontColor(COLOR_ARGB bfc) { buttonFontColor = bfc; }

	// �\��/��\����ݒ�
	void setVisible(bool v) { visible = v; }

	// �{�^���^�C�v��ݒ�(0 = OK/CANCEL, 1 = YES/NO)
	void setButtonType(UINT t)
	{
		if (t < messageDialogNS::MAX_TYPE)
			buttonType = t;
	}

	// �e�L�X�gstr��MessageDialog�ɕ\��
	void print(const std::string &str);

	// �u����v�C�x���g���`�F�b�N
	void update();

	// �O���t�B�b�N�X�f�o�C�X�����������Ƃ��ɌĂяo��
	void onLostDevice();

	// �O���t�B�b�N�X�f�o�C�X�����Z�b�g���ꂽ�Ƃ��ɌĂяo��
	void onResetDevice();
};

#endif