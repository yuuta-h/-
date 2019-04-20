#include "inputDialog.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
InputDialog::InputDialog()
{
	textBackColor = inputDialogNS::TEXT_BACK_COLOR;
	textFontColor = inputDialogNS::TEXT_COLOR;
	inTextVerts = NULL;
	inText = "";
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
InputDialog::~InputDialog()
{
	onLostDevice();            // �����ׂẴO���t�B�b�N�X�A�C�e���ɂ���onLostDevice()���Ăяo��
}

//=============================================================================
// �_�C�A���O�̔w�i�ƃ{�^����`�悷�邽�߂ɒ��_�o�b�t�@������
//=============================================================================
void InputDialog::prepareVerts()
{
	MessageDialog::prepareVerts(); // ��{�N���X��prepareVerts���Ăяo��
	safeRelease(inTextVerts);

	// inText����
	vtx[0].x = x + messageDialogNS::BORDER * 2;
	vtx[0].y = y + height - messageDialogNS::BORDER - messageDialogNS::MARGIN - messageDialogNS::BUTTON_HEIGHT*2.5f;
	vtx[0].z = 0.0f;
	vtx[0].rhw = 1.0f;
	vtx[0].color = textBackColor;
	// inText�E��
	vtx[1].x = x + width - messageDialogNS::BORDER * 2;
	vtx[1].y = vtx[0].y;
	vtx[1].z = 0.0f;
	vtx[1].rhw = 1.0f;
	vtx[1].color = textBackColor;
	// inText�E��
	vtx[2].x = vtx[1].x;
	vtx[2].y = vtx[0].y + messageDialogNS::BUTTON_HEIGHT;
	vtx[2].z = 0.0f;
	vtx[2].rhw = 1.0f;
	vtx[2].color = textBackColor;
	// inText����
	vtx[3].x = vtx[0].x;
	vtx[3].y = vtx[2].y;
	vtx[3].z = 0.0f;
	vtx[3].rhw = 1.0f;
	vtx[3].color = textBackColor;
	createVertexBuffer(vtx, sizeof vtx, inTextVerts);

	// inText��`��ݒ�
	inTextRect.left = (long)vtx[0].x;
	inTextRect.right = (long)vtx[1].x;
	inTextRect.top = (long)vtx[0].y;
	inTextRect.bottom = (long)vtx[2].y;
}


//=============================================================================
// InputDialog��`��
//=============================================================================
const void InputDialog::draw()
{
	if (!visible || !initialized)
		return;

	drawQuad(borderVerts);        // �g��`��
	drawQuad(dialogVerts);        // �w�i��`��
	drawQuad(buttonVerts);        // �{�^����`��
	drawQuad(button2Verts);       // �{�^��2��`��
	drawQuad(inTextVerts);        // �e�L�X�g���͗̈��`��

	getSprite()->Begin(D3DXSPRITE_ALPHABLEND);                // �X�v���C�g�̕`����J�n

	if (text.size() == 0)
	{
		return;
	}
	// MessageDialog�Ńe�L�X�g��\��
	dxFont->color = fontColor;
	printTextDX(dxFont, text, textRect.left, textRect.top);

	// �{�^���̃e�L�X�g��\��
	dxFont->color = buttonFontColor;
	printTextDX(dxFont, messageDialogNS::BUTTON1_TEXT[buttonType], buttonRect.left, buttonRect.top);
	printTextDX(dxFont, messageDialogNS::BUTTON2_TEXT[buttonType], button2Rect.left, button2Rect.top);

	// ���̓e�L�X�g��\��
	dxFont->color=textFontColor;
	tempRect = inTextRect;      // �ۑ�
	
	// DT_CALDRECT�I�v�V�����̏ꍇ�A�e�L�X�g�͏o�͂���Ȃ��B��`���E�ֈړ�
	printTextDX(dxFont,inText, tempRect.left, tempRect.top);

	// �X�v���C�g�̕`����I��
	getSprite()->End();
}

//=============================================================================
// DIALOG_CLOSE_KEY�ƃ}�E�X�N���b�N�{�^�����`�F�b�N
//=============================================================================
void InputDialog::update()
{
	MessageDialog::update();        // ��{�N���X��update���Ăяo��
	if (!initialized || !visible)
	{
		if (buttonClicked == 2)      // Cancel�{�^���̏ꍇ
		{
			inText = "";            // ���̓e�L�X�g���N���A
		}
		return;
	}
	inText = getTextIn();    // ���̓e�L�X�g�擾
}

//=============================================================================
// Set text string, size dialog bottom to fit text and set visible = true
//=============================================================================
void InputDialog::print(const std::string &str)
{
	// ����������Ă��Ȃ��A���͊��Ɏg�p���̏ꍇ
	if (!initialized || visible)
	{
		return;
	}
	text = str + "\n\n\n\n\n";   // �{�^���p�ɋ�Ԃ��󂯂�

								 // textRect���_�C�A���O�̃e�L�X�g�̈�Ƃ��Đݒ�
	textRect.left = (long)(x + messageDialogNS::MARGIN);
	textRect.right = (long)(x + messageDialogNS::WIDTH - messageDialogNS::MARGIN);
	textRect.top = (long)(y + messageDialogNS::MARGIN);
	textRect.bottom = (long)(y + messageDialogNS::HEIGHT - messageDialogNS::MARGIN);

	// textRect.bottom���e�L�X�g�ɕK�v�Ȑ��m�ȍ����ɐݒ�
	// No text is printed with DT_CALDRECT�I�v�V�����̏ꍇ�A�e�L�X�g�͏o�͂���Ȃ�.
	printTextDX(dxFont, text, textRect.left, textRect.top);
	height = textRect.bottom - (int)y + messageDialogNS::BORDER + messageDialogNS::MARGIN;

	prepareVerts();                 // ���_�o�b�t�@������
	inText = "";                    // �Â����͂��N���A
	clearTextIn();
	buttonClicked = 0;              // buttonClicked���N���A
	visible = true;
}

//=============================================================================
// �O���t�B�b�N�X�f�o�C�X�����������Ƃ��ɌĂяo�����
//=============================================================================
void InputDialog::onLostDevice()
{
	if (!initialized)
		return;
	MessageDialog::onLostDevice();
	SAFE_RELEASE(inTextVerts);
}



