#include "messageDialog.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
MessageDialog::MessageDialog()
{
	initialized = false;                // ����ɏ��������ꂽ�ꍇ�Atrue��ݒ�
	visible = false;                    // ��\���ɂ���
	fontColor = messageDialogNS::FONT_COLOR;
	borderColor = messageDialogNS::BORDER_COLOR;
	backColor = messageDialogNS::BACK_COLOR;
	buttonColor = messageDialogNS::BUTTON_COLOR;
	buttonFontColor = messageDialogNS::BUTTON_FONT_COLOR;
	x = messageDialogNS::X;                // �J�n�ʒu
	y = messageDialogNS::Y;
	height = messageDialogNS::HEIGHT;
	width = messageDialogNS::WIDTH;
	textRect.bottom = messageDialogNS::Y + messageDialogNS::HEIGHT - messageDialogNS::MARGIN;
	textRect.left = messageDialogNS::X + messageDialogNS::MARGIN;
	textRect.right = messageDialogNS::X + messageDialogNS::WIDTH - messageDialogNS::MARGIN;
	textRect.top = messageDialogNS::Y + messageDialogNS::MARGIN;
	dialogVerts = NULL;
	borderVerts = NULL;
	buttonVerts = NULL;
	button2Verts = NULL;
	buttonType = 0;     // OK/Cancel
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
MessageDialog::~MessageDialog()
{
	onLostDevice();            // ���ׂẴO���t�B�b�N�X�A�C�e���ɂ���onLostDevice()���Ăяo��
}

//=============================================================================
// MessageDialog��������
//=============================================================================
bool MessageDialog::initialize(HWND h)
{
	hwnd = h;

	// DirectX�t�H���g��������
	dxFont = getDebugFont();
	initialized = true;
	return true;
}

//=============================================================================
// �_�C�A���O�̔w�i�ƃ{�^����`�悷�邽�߂ɒ��_�o�b�t�@������
//=============================================================================
void MessageDialog::prepareVerts()
{
	safeRelease(dialogVerts);
	safeRelease(borderVerts);
	safeRelease(buttonVerts);
	safeRelease(button2Verts);

	// �g�̍���
	vtx[0].x = x;
	vtx[0].y = y;
	vtx[0].z = 0.0f;
	vtx[0].rhw = 1.0f;
	vtx[0].color = borderColor;

	// �g�̉E��
	vtx[1].x = x + width;
	vtx[1].y = y;
	vtx[1].z = 0.0f;
	vtx[1].rhw = 1.0f;
	vtx[1].color = borderColor;

	// �g�̉E��
	vtx[2].x = x + width;
	vtx[2].y = y + height;
	vtx[2].z = 0.0f;
	vtx[2].rhw = 1.0f;
	vtx[2].color = borderColor;

	// �g�̍���
	vtx[3].x = x;
	vtx[3].y = y + height;
	vtx[3].z = 0.0f;
	vtx[3].rhw = 1.0f;
	vtx[3].color = borderColor;

	createVertexBuffer(vtx, sizeof vtx, borderVerts);

	// �w�i�̍���
	vtx[0].x = x + messageDialogNS::BORDER;
	vtx[0].y = y + messageDialogNS::BORDER;
	vtx[0].z = 0.0f;
	vtx[0].rhw = 1.0f;
	vtx[0].color = backColor;

	// �w�i�̉E��
	vtx[1].x = x + width - messageDialogNS::BORDER;
	vtx[1].y = y + messageDialogNS::BORDER;
	vtx[1].z = 0.0f;
	vtx[1].rhw = 1.0f;
	vtx[1].color = backColor;

	// �w�i�̉E��
	vtx[2].x = x + width - messageDialogNS::BORDER;
	vtx[2].y = y + height - messageDialogNS::BORDER;
	vtx[2].z = 0.0f;
	vtx[2].rhw = 1.0f;
	vtx[2].color = backColor;

	// �w�i�̍���
	vtx[3].x = x + messageDialogNS::BORDER;
	vtx[3].y = y + height - messageDialogNS::BORDER;
	vtx[3].z = 0.0f;
	vtx[3].rhw = 1.0f;
	vtx[3].color = backColor;

	createVertexBuffer(vtx, sizeof vtx, dialogVerts);

	// �{�^���̍���
	vtx[0].x = x + width / 2.0f - messageDialogNS::BUTTON_WIDTH / 2.0f;
	vtx[0].y = y + height - messageDialogNS::BORDER - messageDialogNS::MARGIN - messageDialogNS::BUTTON_HEIGHT;
	vtx[0].z = 0.0f;
	vtx[0].rhw = 1.0f;
	vtx[0].color = buttonColor;

	// �{�^���̉E��
	vtx[1].x = x + width / 2.0f + messageDialogNS::BUTTON_WIDTH / 2.0f;
	vtx[1].y = vtx[0].y;
	vtx[1].z = 0.0f;
	vtx[1].rhw = 1.0f;
	vtx[1].color = buttonColor;

	// �{�^���̉E��
	vtx[2].x = vtx[1].x;
	vtx[2].y = vtx[0].y + messageDialogNS::BUTTON_HEIGHT;
	vtx[2].z = 0.0f;
	vtx[2].rhw = 1.0f;
	vtx[2].color = buttonColor;

	// �{�^���̍���
	vtx[3].x = vtx[0].x;
	vtx[3].y = vtx[2].y;
	vtx[3].z = 0.0f;
	vtx[3].rhw = 1.0f;
	vtx[3].color = buttonColor;

	createVertexBuffer(vtx, sizeof vtx, buttonVerts);

	// �{�^����`�̃Z�b�g
	buttonRect.left = (long)vtx[0].x;
	buttonRect.right = (long)vtx[1].x;
	buttonRect.top = (long)vtx[0].y;
	buttonRect.bottom = (long)vtx[2].y;

	// �{�^��2�̍���
	vtx[0].x = x + width - messageDialogNS::BUTTON_WIDTH*1.2f;
	vtx[0].y = y + height - messageDialogNS::BORDER - messageDialogNS::MARGIN - messageDialogNS::BUTTON_HEIGHT;
	vtx[0].z = 0.0f;
	vtx[0].rhw = 1.0f;
	vtx[0].color = buttonColor;
	// �{�^��2�̉E��
	vtx[1].x = vtx[0].x + messageDialogNS::BUTTON_WIDTH;
	vtx[1].y = vtx[0].y;
	vtx[1].z = 0.0f;
	vtx[1].rhw = 1.0f;
	vtx[1].color = buttonColor;
	// �{�^��2�̉E��
	vtx[2].x = vtx[1].x;
	vtx[2].y = vtx[0].y + messageDialogNS::BUTTON_HEIGHT;
	vtx[2].z = 0.0f;
	vtx[2].rhw = 1.0f;
	vtx[2].color = buttonColor;
	// �{�^��2�̍���
	vtx[3].x = vtx[0].x;
	vtx[3].y = vtx[2].y;
	vtx[3].z = 0.0f;
	vtx[3].rhw = 1.0f;
	vtx[3].color = buttonColor;
	createVertexBuffer(vtx, sizeof vtx, button2Verts);

	// �{�^��2�̋�`���Z�b�g
	button2Rect.left = (long)vtx[0].x;
	button2Rect.right = (long)vtx[1].x;
	button2Rect.top = (long)vtx[0].y;
	button2Rect.bottom = (long)vtx[2].y;
}

//=============================================================================
// MessageDialog��`��
//=============================================================================
const void MessageDialog::draw()
{
	if (!visible || !initialized)
	{
		return;
	}

	drawQuad(borderVerts);        // �g��`��
	drawQuad(dialogVerts);        // �w�i��`��
	drawQuad(buttonVerts);        // �{�^����`��
	drawQuad(button2Verts);       // �{�^��2��`��

	// �X�v���C�g�̕`����J�n
	getSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	if (text.size() == 0)
	{
		return;
	}
	// �e�L�X�g��MessageDialog�ɕ\��
	dxFont->color = fontColor;
	printTextDX(dxFont,text, textRect.left,textRect.top);

	// �e�L�X�g���{�^���ɕ\��
	dxFont->color = buttonFontColor;
	printTextDX(dxFont, messageDialogNS::BUTTON1_TEXT[buttonType], buttonRect.left, buttonRect.top);
	printTextDX(dxFont, messageDialogNS::BUTTON2_TEXT[buttonType], button2Rect.left, button2Rect.top);

	// �X�v���C�g�̕`����I��
	getSprite()->End();
}

//=============================================================================
// DIALOG_CLOSE_KEY��OK�{�^���̃N���b�N���`�F�b�N
//=============================================================================
void MessageDialog::update()
{
	if (!initialized || !visible)
	{
		return;
	}

	if (GetKeyboardTrigger(messageDialogNS::DIALOG_CLOSE_KEY))
	{
		visible = false;
		buttonClicked = 1;              // �{�^��1���N���b�N���ꂽ
		return;
	}

	// �E�B���h�E���T�C�Y�ύX����Ă���ꍇ���l�����āA��ʂ̔䗦���v�Z
	RECT clientRect;
	GetClientRect(hwnd, &clientRect);
	screenRatioX = (float)WINDOW_WIDTH / clientRect.right;
	screenRatioY = (float)WINDOW_HEIGHT / clientRect.bottom;

	if (getMouseLButton())       // �}�E�X�̍��{�^���̏ꍇ
	{
		// �}�E�X�N���b�N���{�^��1(OK)�̓����Ŕ��������ꍇ
		if (getMouseX()*screenRatioX >= buttonRect.left &&
			getMouseX()*screenRatioX <= buttonRect.right &&
			getMouseY()*screenRatioY >= buttonRect.top &&
			getMouseY()*screenRatioY <= buttonRect.bottom)
		{
			visible = false;            // ���b�Z�[�W�_�C�A���O���\��
			buttonClicked = 1;          // �{�^��1���N���b�N���ꂽ
			return;
		}

		// �}�E�X�N���b�N���{�^��2(cancel)�̓����Ŕ��������ꍇ
		if (getMouseX()*screenRatioX >= button2Rect.left &&
			getMouseX()*screenRatioX <= button2Rect.right &&
			getMouseY()*screenRatioY >= button2Rect.top &&
			getMouseY()*screenRatioY <= button2Rect.bottom)
		{
			visible = false;            // ���b�Z�[�W�_�C�A���O���\��
			buttonClicked = 2;          // �{�^��2���N���b�N���ꂽ
		}
	}
}

//=============================================================================
// �e�L�X�g�������ݒ�A�_�C�A���O�̉��[���e�L�X�g�����܂�T�C�Y�ɕύX�A
// visible = true��ݒ�
//=============================================================================
void MessageDialog::print(const std::string &str)
{
	// ����������Ă��Ȃ��A���͊��Ɏg�p���̏ꍇ
	if (!initialized || visible)
	{
		return;
	}
	text = str + "\n\n\n\n"; // �{�^���p�ɋ�Ԃ��󂯂�

	// textRect���_�C�A���O�̃e�L�X�g�̈�Ƃ��Đݒ�
	textRect.left = (long)(x + messageDialogNS::MARGIN);
	textRect.right = (long)(x + messageDialogNS::WIDTH - messageDialogNS::MARGIN);
	textRect.top = (long)(y + messageDialogNS::MARGIN);
	textRect.bottom = (long)(y + messageDialogNS::HEIGHT - messageDialogNS::MARGIN);

	// textRect.bottom���e�L�X�g�ɕK�v�Ȑ��m�ȍ����ɐݒ�
	// DT_CALDRECT�I�v�V�����̏ꍇ�A�e�L�X�g�͏o�͂���Ȃ�
	printTextDX(dxFont, text, textRect.left, textRect.top);
	height = textRect.bottom - (int)y + messageDialogNS::BORDER + messageDialogNS::MARGIN;

	prepareVerts();    // ���_�o�b�t�@������
	buttonClicked = 0; // buttonClicked���N���A
	visible = true;
}

//=============================================================================
// �O���t�B�b�N�X�f�o�C�X�����������Ƃ��ɌĂяo�����
//=============================================================================
void MessageDialog::onLostDevice()
{
	if (!initialized)
	{
		return;
	}
	safeRelease(dxFont->dxFont);
	safeRelease(dialogVerts);
	safeRelease(borderVerts);
	safeRelease(buttonVerts);
	safeRelease(button2Verts);
}

//=============================================================================
// �O���t�B�b�N�X�f�o�C�X�����Z�b�g�����Ƃ��ɌĂяo�����
//=============================================================================
void MessageDialog::onResetDevice()
{
	if (!initialized)
	{
		return;
	}
	prepareVerts();
}
