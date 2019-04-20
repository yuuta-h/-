//����
#include "object.h"
#include "stdlib.h"//malloc�p
#include"textureLoader.h"

#define STUB_OBJNUM (100)	//�X�e�[�W�̃f�[�^���ɂ���I�u�W�F�N�g�̑���/���ۂɂ͊O������炤�l
#define PLUS_OBJNUM (5)		//�X�e�[�W���ŕۑ�����K�v�̂Ȃ��I�u�W�F�N�g���(UI�Ȃ�)������΂���̐�

int OBJNUM;
ObjStr *Obj = NULL;

//�I�u�W�F�N�g���Z�b�g����n���[�J���֐�
ObjStr cleanObj(int i);
Image cleanTex();

void setObjFromFile(int i);
void setObjNotFrom(int i);
void setObjTex(int i);

struct StubObject {
	objTypes m_type;
	short m_id;

	D3DXVECTOR2 m_pos;
	float m_rot;
	D3DXVECTOR2 m_scl;

	float m_rad;
	D3DXVECTOR2 m_rect;
}StubObj[STUB_OBJNUM];//���ۂɂ͊O������炤�l

struct StubTexture {
	objTypes m_type;

	textureLoaderNS::TEXTURE_NUMBER texture;
	float width;
	float height;
	bool playAnime;
	int ANIME_TIME;
	int ANIME_PATTERN;
	int DIVIDE_U;
	int DIVIDE_V;
}StubTex[TYPE_MAX];//���ۂɂ͊O������炤�l

/*�R���W�������X�g�ɕK�v�Ȃ���
obID/obType/pos/rot/scl/coltype

�A�N�V�������X�g

�G�t�F�N�g���X�g
*/



bool initializeObject(int stage){

	OBJNUM = STUB_OBJNUM + PLUS_OBJNUM;
	objTypes k;//���܂�Ӗ��͂Ȃ�

	//���X�e�[�W�̃I�u�W�F�N�g�����̏����l���X�e�[�W�f�[�^/���ۂɂ͊O������炤�l
	for (int i = 0; i < STUB_OBJNUM; i++) {
		k = (objTypes)(i);
		if (k != NO_TYPE && k < FROMFILE_TYPE_MAX) {
			StubObj[i].m_type = k;
			StubObj[i].m_id = i;
			StubObj[i].m_pos = { WINDOW_WIDTH * float(StubObj[i].m_type) / float(FROMFILE_TYPE_MAX),0.0f };
			StubObj[i].m_rot = D3DX_PI * 0.5f;
			StubObj[i].m_scl = { 10.0f,10.0f };
			StubObj[i].m_rad = 12.0f;
			StubObj[i].m_rect = { 10.0f,10.0f };
		}
		else {//�X�e�[�W�f�[�^�̒��ŋ�ɂȂ��Ă������(���ۂɂ͂Ȃ�����)
			StubObj[i].m_type = NO_TYPE;
		}
	}
	//���X�e�[�W�̃I�u�W�F�N�g�����̏����l���X�e�[�W�f�[�^/���ۂɂ͊O������炤�l


	//���X�e�[�W�̃e�N�X�`�������̏����l���e�N�X�`�����X�g/���ۂɂ͊O������炤�l
	for (int j = 0; j < TYPE_MAX; j++) {
		k = (objTypes)(j);
		if (k != NO_TYPE && k != FROMFILE_TYPE_MAX){
			StubTex[j].m_type = k;
			if (k != UI_EFFECT && k != UI_CURSOR) {
				StubTex[j].texture = (textureLoaderNS::BACK_GROUND);
				StubTex[j].width = 640.0f;
				StubTex[j].height = 320.0f * float(StubTex[j].m_type) / float(TYPE_MAX);
				StubTex[j].playAnime = false;
				StubTex[j].ANIME_TIME = 1;
				StubTex[j].ANIME_PATTERN = 1;
				StubTex[j].DIVIDE_U = 1;
				StubTex[j].DIVIDE_V = 1;
			}
			else {
				if (k == UI_EFFECT) {
					StubTex[j].texture = (textureLoaderNS::BACK_GROUND);
					StubTex[j].width = 160.0f;
					StubTex[j].height = 80.0f;
					StubTex[j].playAnime = true;
					StubTex[j].ANIME_TIME = 3;
					StubTex[j].ANIME_PATTERN = 5;
					StubTex[j].DIVIDE_U = 10;
					StubTex[j].DIVIDE_V = 5;
				}
				else if (k == UI_CURSOR) {
					StubTex[j].texture = (textureLoaderNS::BACK_GROUND);
					StubTex[j].width = 240.0f;
					StubTex[j].height = 120.0f;
					StubTex[j].playAnime = true;
					StubTex[j].ANIME_TIME = 10;
					StubTex[j].ANIME_PATTERN = 50;
					StubTex[j].DIVIDE_U = 20;
					StubTex[j].DIVIDE_V = 10;
				}
			}
		}
		else {//�e�N�X�`�����X�g�̒��ŋ�ɂȂ��Ă������(���ۂɂ͂Ȃ�����)
			//����FROMFILE_TYPE_MAX�������Ƃ�
			StubTex[j].m_type = NO_TYPE;
		}
	}
	//���X�e�[�W�̃e�N�X�`�������̏����l���e�N�X�`�����X�g/���ۂɂ͊O������炤�l


	Obj = (ObjStr*)malloc(sizeof(ObjStr) * OBJNUM);
	if (Obj == NULL) return false;//malloc�͊m�ۂɎ��s���邱�Ƃ�����炵���A�ȍ~������Ԃ��������Ȃ�Ǝv���̂�false��Ԃ�(�Ԃ��ꂽ���ŏI������Ȃ薳������Ȃ肵�Ăق���)

	for (int i = 0; i < OBJNUM; i++) {
		if (i < STUB_OBJNUM) {//�I�u�W�F�N�g�ɃI�u�W�F�N�g�f�[�^�����������l���Z�b�g
			setObjFromFile(i);
		}
		else {//�I�u�W�F�N�g�ɃI�u�W�F�N�g�f�[�^���������Ă��Ȃ��l���Z�b�g
			setObjNotFrom(i);
		}

		//�I�u�W�F�N�g�Ƀe�N�X�`���f�[�^�����������l���Z�b�g
		setObjTex(i);

		switch (Obj[i].m_type) {//�^�C�v���Ƃ́A�킴�킴�t�@�C���ɏ����K�v�͂Ȃ����A�Q�[�������ɂ���K�v�͂��鏉����
		case CHARA_PLAYER:
			//��
			break;
		case CHARA_BLACKHOLE:
			//�u���b�N�z�[��
			break;
		case CHARA_KEY:
			//��
			break;
		case CHARA_COIN:
			//���W�A�C�e��
			break;
		case STAGE_HURDLE:
			//���������Q��
			break;
		case STAGE_WALL:
			//�������Ȃ��ǁ@�n�ʂƂ�
			break;
		case STAGE_LOCK:
			//���ŊJ�������
			break;
		case EVENT_GOAL:
			//�S�[��
			break;

		case UI_CURSOR:
			//�u���b�N�z�[���u���J�[�\��
			break;
		case UI_EFFECT:
			//�G�t�F�N�g
			break;
		case UI_HP:
			//�c�@�\��
			break;
		}
	}

	return true;
}

void uninitializeObject(void) {
	if (Obj != NULL) {
		free(Obj);
		Obj = NULL;//�����free���Q�A���ł��ƃ��o�� ���� NULL�ۂ�free����镪�ɂ͕��C �炵���̂ł�������
	}
}

void updateObject(void) {
}

void drawObject(void){
	//�S�ẴI�u�W�F�N�g��`��@�����ꂾ�ƕ`�揇���^�C�v���Ƃɑ�������ł��Ȃ��̂ŁA�`��p�̃��X�g����邱�ƂɂȂ�̂���
	for (int i = 0; i < OBJNUM; i++) {
//		if (Obj[i].m_use == false) continue;
		setPosition(&(Obj[i].m_image),Obj[i].m_pos.x, Obj[i].m_pos.y);
		DrawImage(&(Obj[i].m_image));
	}
}


/////�ȉ��X�e�[�W�Z�b�g�n���[�J���֐�

ObjStr cleanObj(int i) {//Obj�����Z�b�g
	return {
		NO_TYPE,short(i),false,
		0,short(0),
		{0.0f,0.0f},0.0f,{0.0f,0.0f},
		0.0f,{0.0f,0.0f},
//		cleanTex()
	};
}

Image cleanTex() {//Tex�����Z�b�g
	Image nullTex;
	InitImage(&nullTex, getTexture(textureLoaderNS::TEXTURE_NUMBER(0)), 0, 0, 1, 1);
	return nullTex;
}


void setObjFromFile(int i) {
	//��������X�e�[�W�f�[�^�̒�����I�u�W�F�N�g���Z�b�g

	if (StubObj[i].m_type != NO_TYPE) {//�X�e�[�W�f�[�^���璆�g�𒼐ڂ��炦�΂�������
		Obj[i].m_type = StubObj[i].m_type;
		Obj[i].m_id = StubObj[i].m_id;
		Obj[i].m_use = true;

		Obj[i].m_time = 0;
		Obj[i].m_mode = 0;

		Obj[i].m_pos = StubObj[i].m_pos;
		Obj[i].m_rot = StubObj[i].m_rot;
		Obj[i].m_scl = StubObj[i].m_scl;

		Obj[i].m_rad = StubObj[i].m_rad;
		Obj[i].m_rect = StubObj[i].m_rect;
	}
	else {//�X�e�[�W�f�[�^����̃^�C�v�ɂȂ��Ă�����
		Obj[i] = cleanObj(i);
	}
}
void setObjNotFrom(int i) {
	//UI�ȂǁA�X�e�[�W���Ƃɕς��Ȃ��̂Ńt�@�C���ɕۑ�����K�v���Ȃ��A���񂱂���Őݒ肷��΂����I�u�W�F�N�g���Z�b�g

	Obj[i].m_id = i;
	Obj[i].m_use = true;
	switch (i - STUB_OBJNUM) {
	case 0:
		Obj[i].m_type = UI_CURSOR;
		Obj[i].m_pos = { (float)WINDOW_CENTER_X,(float)WINDOW_CENTER_Y };//�}�E�X�J�[�\���̈ړ����Ăǂ����񂾂�
		break;
	case 1:
		Obj[i].m_type = UI_EFFECT;
		Obj[i].m_pos = { 720.0f,480.0f };
		break;
	default:
		Obj[i].m_type = UI_HP;
		Obj[i].m_pos = { 0.0f,0.0f };
		break;
	}
}



void setObjTex(int i) {//Obj��StubTex�̒��g���Z�b�g
	if (Obj[i].m_type != NO_TYPE) {
		StubTexture *p_tex = &(StubTex[int(Obj[i].m_type)]);
		if (p_tex->m_type != NO_TYPE) {
			if (Obj[i].m_image.playAnime == false) {//�Î~�悾������
				InitImage(&(Obj[i].m_image), getTexture(StubTex[int(Obj[i].m_type)].texture), Obj[i].m_pos.x, Obj[i].m_pos.y,
					p_tex->width, p_tex->height);
			}
			else {//�A�j����������
				InitAnimeImage(&(Obj[i].m_image), getTexture(textureLoaderNS::BACK_GROUND), Obj[i].m_pos.x, Obj[i].m_pos.y,
					p_tex->width, p_tex->height,
					p_tex->ANIME_TIME, p_tex->ANIME_PATTERN, p_tex->DIVIDE_U, p_tex->DIVIDE_V);
			}
		}
		else {//�e�N�X�`���f�[�^����̃^�C�v�ɂȂ��Ă�����
			Obj[i].m_image = cleanTex();
		}
	}
	else {//�I�u�W�F�N�g�f�[�^����̃^�C�v�ɂȂ��Ă�����
		Obj[i].m_image = cleanTex();
	}
}
