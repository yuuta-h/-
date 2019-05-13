//����
#include "object.h"
#include "collision.h"
//#include "stdlib.h"//malloc�p
#include"textureLoader.h"
#include "read_text.h"
#include "textDX.h"

//���u���\���̂���
struct StubObject {
	objTypes m_type;					//�I�u�W�F�N�g�^�C�v
	short	 m_id;						//�S�^�C�v�������Ă���z����́A�����̔ԍ�
	bool	 m_use;						//use�t���O

	D3DXVECTOR2	m_pos;					//���W
	float		m_rot;					//�p�x
	D3DXVECTOR2 m_scl;					//�傫��

	D3DXVECTOR2 m_speed;				//���x
	D3DXVECTOR2 m_accel;				//�����x(���̃I�u�W�F�N�g����y�ڂ����́A�����Ƃ�)
	D3DXVECTOR2 m_attract;				//���́@(�����ȊO�̃I�u�W�F�N�g�ɋy�ڂ��͂Ƃ�)

	int		m_time;						//�v���C���[�Ƃ͓Ɨ����ď���ɓ����I�u�W�F�N�g������Ύg��(�X�e�[�W�M�~�b�N�n)
	short	m_mode;						//����A�s���p�^�[���Ƃ��͂�����


	float m_rad;						//���a(�v���C���[�̓����蔻��Ƃ�)
	D3DXVECTOR2 m_rect;					//��`�̕Ӓ�(�X�e�[�W�̓����蔻��Ƃ�)
	//�ՓˈȊO�ł��g���Ȃ�z��ɂȂ邩��(�ߊ��Ɠ����o���Ƃ��A�u���b�N�z�[�����z���񂹎n�߂�͈͂Ƃ�)

	Image m_image;						//�`����
}StubObj[STUB_OBJNUM];//���ۂɂ͊O������炤�l

//���u���̕ϐ�
int plID;
int bhID;
int whID;

const float VALUE_ATTRACTION = 0.02f; // ���͂̋���
const float RANGE_ATTRACTION = 800.0f;	// ���͂̓����͈�

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

//�I�u�W�F�N�g���Z�b�g����n���[�J���֐�
ObjStr cleanObj(int i);
Image cleanTex(void);

//�I�u�W�F�N�g������������֐�
void setObjFromFile(ObjStr* p_obj, int i, Stage* p_fromstage);
void setObjNotFrom(ObjStr* p_obj, int i, int objnum);
void setObjTex(ObjStr* p_obj, int i);

//�I�u�W�F�N�g���ʏ�������֐�
void updatePlayer(ObjStr* p_obj);
void setBlackHole(ObjStr* p_obj);
void updateBlackHole(ObjStr* p_obj);
void setWhiteHole(ObjStr* p_obj);
void updateWhiteHole(ObjStr* p_obj);
void resetStar(ObjStr* p_obj);
//���낢�뉞�p�ł������Ȍv�Z�����I�֐�
float objectLength(ObjStr* p_obj1, ObjStr* p_obj2);				//2�̃I�u�W�F�N�g�Ԃ̋������v�Z
D3DXVECTOR2 objectDirection(ObjStr* p_obj1, ObjStr* p_obj2);	// �I�u�W�F�N�g1�ɑ΂���I�u�W�F�N�g2�̕����x�N�g����߂�


/*�R���W�������X�g�ɕK�v�����Ȃ���
obID/obType/pos/rot/scl/coltype

�A�N�V�������X�g

�G�t�F�N�g���X�g
*/



void initializeObject(StageObj *p_stgobj,int stage){
	p_stgobj->m_STAGE = stage;
	Stage *p_fromstage = get_g_pStage(stage);//������擾����X�e�[�W

	p_stgobj->m_OBJNUM = p_fromstage->num_m_pObj + PLUS_OBJNUM;
	objTypes k;//���܂�Ӗ��͂Ȃ�

	//���X�e�[�W�̃I�u�W�F�N�g�����̏����l���X�e�[�W�f�[�^/���ۂɂ͊O������炤�l
	//���͉��Ƃ���StugObj��������
	for (int i = 0; i < p_stgobj->m_OBJNUM; i++) {
		k = (objTypes)(i);
		if (NO_TYPE < k && k < FROMFILE_TYPE_MAX) {
			StubObj[i].m_type = k;
			StubObj[i].m_id = i;
			StubObj[i].m_pos = { WINDOW_WIDTH * float(StubObj[i].m_type) / float(FROMFILE_TYPE_MAX),0.0f };
			if (k == CHARA_PLAYER)
				StubObj[i].m_pos = { 0.0f,(float)WINDOW_CENTER_Y };
			StubObj[i].m_rot = 0.0f;
			StubObj[i].m_scl = { 10.0f,10.0f };
			StubObj[i].m_speed = { 0.0f,0.0f };
			StubObj[i].m_accel = { 0.0f,0.0f };
			StubObj[i].m_attract = { 0.0f,0.0f };
			StubObj[i].m_time = -1;
			StubObj[i].m_mode = -1;
			StubObj[i].m_rad = 50.0f;
			StubObj[i].m_rect = { 100.0f,100.0f };
		}
		else {//�X�e�[�W�f�[�^�̒��ŋ�ɂȂ��Ă������(���ۂɂ͂Ȃ�����)
			StubObj[i].m_type = NO_TYPE;
		}
	}
	//���X�e�[�W�̃I�u�W�F�N�g�����̏����l���X�e�[�W�f�[�^/���ۂɂ͊O������炤�l



	//���X�e�[�W�̃e�N�X�`�������̏����l���e�N�X�`�����X�g/���ۂɂ͊O������炤�l
	for (int j = 0; j < TYPE_MAX; j++) {
		k = (objTypes)(j);
		if (NO_TYPE < k && k < TYPE_MAX && k != FROMFILE_TYPE_MAX) {
			StubTex[j].m_type = k;
			switch (k) {
			case CHARA_PLAYER:
				StubTex[j].texture = (textureLoaderNS::STAR);
				StubTex[j].width = 50.0f;
				StubTex[j].height = 50.0f;
				StubTex[j].playAnime = false;
				StubTex[j].ANIME_TIME = 1;
				StubTex[j].ANIME_PATTERN = 1;
				StubTex[j].DIVIDE_U = 1;
				StubTex[j].DIVIDE_V = 1;
				break;
			case CHARA_BLACKHOLE:
				StubTex[j].texture = (textureLoaderNS::BLACK_HOLE);
				StubTex[j].width = 80.0f;
				StubTex[j].height = 80.0f;
				StubTex[j].playAnime = false;
				StubTex[j].ANIME_TIME = 1;
				StubTex[j].ANIME_PATTERN = 1;
				StubTex[j].DIVIDE_U = 1;
				StubTex[j].DIVIDE_V = 1;
				break;
			case CHARA_WHITEHOLE:
				StubTex[j].texture = (textureLoaderNS::WHITE_HOLE);
				StubTex[j].width = 80.0f;
				StubTex[j].height = 80.0f;
				StubTex[j].playAnime = false;
				StubTex[j].ANIME_TIME = 1;
				StubTex[j].ANIME_PATTERN = 1;
				StubTex[j].DIVIDE_U = 1;
				StubTex[j].DIVIDE_V = 1;
				break;
			case CHARA_COMET:
				StubTex[j].texture = (textureLoaderNS::COMET);
				StubTex[j].width = 100.0f;
				StubTex[j].height = 100.0f;
				StubTex[j].playAnime = false;
				StubTex[j].ANIME_TIME = 1;
				StubTex[j].ANIME_PATTERN = 1;
				StubTex[j].DIVIDE_U = 1;
				StubTex[j].DIVIDE_V = 1;
				break;
			case STAGE_WALL:
				StubTex[j].texture = (textureLoaderNS::WALL);
				StubTex[j].width = 40.0f;
				StubTex[j].height = 300.0f;
				StubTex[j].playAnime = false;
				StubTex[j].ANIME_TIME = 1;
				StubTex[j].ANIME_PATTERN = 1;
				StubTex[j].DIVIDE_U = 1;
				StubTex[j].DIVIDE_V = 1;
				break;
			case UI_EFFECT:
				StubTex[j].texture = (textureLoaderNS::BACK_GROUND);
				StubTex[j].width = 160.0f;
				StubTex[j].height = 80.0f;
				StubTex[j].playAnime = true;
				StubTex[j].ANIME_TIME = 3;
				StubTex[j].ANIME_PATTERN = 5;
				StubTex[j].DIVIDE_U = 10;
				StubTex[j].DIVIDE_V = 5;
				break;
			case UI_CURSOR:
				StubTex[j].texture = (textureLoaderNS::PLANET);
				StubTex[j].width = 240.0f;
				StubTex[j].height = 120.0f;
				StubTex[j].playAnime = true;
				StubTex[j].ANIME_TIME = 10;
				StubTex[j].ANIME_PATTERN = 4;
				StubTex[j].DIVIDE_U = 2;
				StubTex[j].DIVIDE_V = 2;
				break;
			default:
				StubTex[j].texture = (textureLoaderNS::BACK_GROUND);
				StubTex[j].width = 100.0f;
				StubTex[j].height = 100.0f;
				StubTex[j].playAnime = false;
				StubTex[j].ANIME_TIME = 1;
				StubTex[j].ANIME_PATTERN = 1;
				StubTex[j].DIVIDE_U = 1;
				StubTex[j].DIVIDE_V = 1;
				break;
			}
		}
		else {//�e�N�X�`�����X�g�̒��ŋ�ɂȂ��Ă������(���ۂɂ͂Ȃ�����)
			//����FROMFILE_TYPE_MAX�������Ƃ�
			StubTex[j].m_type = NO_TYPE;
		}
	}
	//���X�e�[�W�̃e�N�X�`�������̏����l���e�N�X�`�����X�g/���ۂɂ͊O������炤�l

//	if (p_stgobj->m_Obj != NULL) uninitializeObject(p_stgobj);//��łȂ���������

//	Obj = (ObjStr*)malloc(sizeof(ObjStr) * OBJNUM);
	p_stgobj->m_Obj = new ObjStr[p_stgobj->m_OBJNUM];

	if (p_stgobj->m_Obj == NULL) return;//malloc/new�͊m�ۂɎ��s���邱�Ƃ�����炵���A�ȍ~������Ԃ��������Ȃ�Ǝv���̂�false��Ԃ�(�Ԃ��ꂽ���ŏI������Ȃ薳������Ȃ肵�Ăق���)

	for (int i = 0; i < p_stgobj->m_OBJNUM; i++) {
		if (i < p_stgobj->m_OBJNUM) {//�I�u�W�F�N�g�ɃI�u�W�F�N�g�f�[�^�����������l���Z�b�g
			setObjFromFile(&(p_stgobj->m_Obj[i]),i, p_fromstage);
		}
		else {//�I�u�W�F�N�g�ɃI�u�W�F�N�g�f�[�^���������Ă��Ȃ��l���Z�b�g
			setObjNotFrom(&(p_stgobj->m_Obj[i]),i, p_stgobj->m_OBJNUM);
		}

		//�I�u�W�F�N�g�Ƀe�N�X�`���f�[�^�����������l���Z�b�g
		setObjTex(&(p_stgobj->m_Obj[i]),i);

		switch (p_stgobj->m_Obj[i].m_type) {//�^�C�v���Ƃ́A�킴�킴�t�@�C���ɏ����K�v�͂Ȃ����A�Q�[�������ɂ���K�v�͂��鏉����
		case CHARA_PLAYER:
			//��
			p_stgobj->m_Obj[i].m_use = true;
			p_stgobj->m_Obj[i].m_pos = D3DXVECTOR2{ 200.0f , 450.0f};
			p_stgobj->m_Obj[i].m_speed.x = -1.0f;
			plID = p_stgobj->m_Obj[i].m_id;
			break;
		case CHARA_BLACKHOLE:
			//�u���b�N�z�[��
			p_stgobj->m_Obj[i].m_use = true;
			bhID = p_stgobj->m_Obj[i].m_id;
			break;
		case CHARA_WHITEHOLE:
			//�z���C�g�z�[��
			p_stgobj->m_Obj[i].m_use = true;
			break;
		case CHARA_COMET:
			//覐�
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
			p_stgobj->m_Obj[i].m_use = true;
			p_stgobj->m_Obj[i].m_pos = D3DXVECTOR2{ 400.0f , 250.0f };
			p_stgobj->m_Obj[i].m_rect = { StubTex[i].width,StubTex[i].height };
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

	for (int i = 0; i < p_stgobj->m_OBJNUM; i++) {
		p_stgobj->m_Obj[i].m_tar = p_stgobj->m_Obj[plID].m_ptr;
	}

}

void uninitializeObject(StageObj* p_stgobj) {
	if (p_stgobj->m_Obj != NULL) {
//		free(Obj);
		delete[]p_stgobj->m_Obj;
		p_stgobj->m_Obj = NULL;
		//�����free/delete���Q�A���ł��ƃ��o�� ���� NULL�ۂ�free/delete����镪�ɂ͕��C �炵���̂ł�������
	}
}

void updateObject(StageObj* p_stgobj) {
	objTypes k;//���܂�Ӗ��͂Ȃ�
	for (int i = 0; i < p_stgobj->m_OBJNUM; i++) {
		if (p_stgobj->m_Obj[i].m_use == false) continue;
		k = (objTypes)(i);
		switch (p_stgobj->m_Obj[i].m_type) {//�^�C�v���Ƃɏ�������
		case CHARA_PLAYER:
			//��
			updatePlayer(p_stgobj->m_Obj[i].m_ptr);
			break;
		case CHARA_BLACKHOLE:
			//�u���b�N�z�[��
			if (getMouseLButtonTrigger()) // �E�N���b�N�ŃZ�b�g
				setBlackHole(p_stgobj->m_Obj[i].m_ptr);

			updateBlackHole(p_stgobj->m_Obj[i].m_ptr);
			break;
		case CHARA_WHITEHOLE:
			//�z���C�g�z�[��
			if (getMouseRButtonTrigger()) // �E�N���b�N�ŃZ�b�g
				setWhiteHole(p_stgobj->m_Obj[i].m_ptr);

			updateWhiteHole(p_stgobj->m_Obj[i].m_ptr);
			break;
		case CHARA_COMET:
			//覐�
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
			if (checkHitObjRR(p_stgobj->m_Obj[i].m_ptr, p_stgobj->m_Obj[i].m_ptr->m_tar))
			{
				resetStar(p_stgobj->m_Obj[i].m_ptr->m_tar);
			};
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
}

void drawObject(StageObj* p_stgobj){
	//�S�ẴI�u�W�F�N�g��`��@�����ꂾ�ƕ`�揇���^�C�v���Ƃɑ�������ł��Ȃ��̂ŁA�`��p�̃��X�g����邱�ƂɂȂ�̂���
	for (int i = 0; i < p_stgobj->m_OBJNUM; i++) {
//		p_stgobj->m_Obj[i].m_pos.y += 0.01f;
		if (p_stgobj->m_Obj[i].m_use == false) continue;
		setPosition(&(p_stgobj->m_Obj[i].m_image), p_stgobj->m_Obj[i].m_pos.x , p_stgobj->m_Obj[i].m_pos.y);
		setAngle(&(p_stgobj->m_Obj[i].m_image), p_stgobj->m_Obj[i].m_image.angle + 1);
		DrawImage(&(p_stgobj->m_Obj[i].m_image));
	}
}

void printObject(StageObj* p_stgobj) {
	for (int i = 0; i < p_stgobj->m_OBJNUM; i++) {
		txtLineReset(int(p_stgobj->m_Obj[i].m_pos.y + p_stgobj->m_Obj[i].m_image.height));//�������s�ʒu���Z�b�g
		printTextDX(getDebugFont(), "type", int(p_stgobj->m_Obj[i].m_pos.x), txtLineBreak(), int(p_stgobj->m_Obj[i].m_type));
		printTextDX(getDebugFont(), "id", int(p_stgobj->m_Obj[i].m_pos.x), txtLineBreak(), p_stgobj->m_Obj[i].m_id);
		printTextDX(getDebugFont(), "x", int(p_stgobj->m_Obj[i].m_pos.x), txtLineBreak(), p_stgobj->m_Obj[i].m_pos.x);
		printTextDX(getDebugFont(), "y", int(p_stgobj->m_Obj[i].m_pos.x), txtLineBreak(), p_stgobj->m_Obj[i].m_pos.y);
	}

	/*************************************************
	printTextDX(getDebugFont(), "Length",0, 90, objectLength(&p_stgobj->m_Obj[plID],&p_stgobj->m_Obj[bhID]));
	printTextDX(getDebugFont(), "BH_att.x", 0, 120, p_stgobj->m_Obj[bhID].m_attract.x);
	printTextDX(getDebugFont(), "BH_att.y", 0, 150, p_stgobj->m_Obj[bhID].m_attract.y);
	printTextDX(getDebugFont(), "PL_speed.x", 0, 180, p_stgobj->m_Obj[plID].m_speed.x);
	printTextDX(getDebugFont(), "PL_speed.y", 0, 210, p_stgobj->m_Obj[plID].m_speed.y);
	printTextDX(getDebugFont(), "PL_accel.x", 0, 240, p_stgobj->m_Obj[plID].m_accel.x);
	printTextDX(getDebugFont(), "PL_accel.y", 0, 270, p_stgobj->m_Obj[plID].m_accel.y);
	****************************************************/

	D3DXVECTOR2 center = computeRotatedBox(&p_stgobj->m_Obj[plID]);
	printTextDX(getDebugFont(), "PL_corner.����x", 0, 90, p_stgobj->m_Obj[plID].m_corner[0].x);
	printTextDX(getDebugFont(), "PL_corner.����y", 0, 120, p_stgobj->m_Obj[plID].m_corner[0].y);
	printTextDX(getDebugFont(), "PL_corner.�E��x", 0, 150, p_stgobj->m_Obj[plID].m_corner[1].x);
	printTextDX(getDebugFont(), "PL_corner.�E��y", 0, 180, p_stgobj->m_Obj[plID].m_corner[1].y);
	printTextDX(getDebugFont(), "PL_corner.����x", 0, 210, p_stgobj->m_Obj[plID].m_corner[2].x);
	printTextDX(getDebugFont(), "PL_corner.����y", 0, 240, p_stgobj->m_Obj[plID].m_corner[2].y);
	printTextDX(getDebugFont(), "PL_corner.�E��x", 0, 270, p_stgobj->m_Obj[plID].m_corner[3].x);
	printTextDX(getDebugFont(), "PL_corner.�E��y", 0, 300, p_stgobj->m_Obj[plID].m_corner[3].y);

	printTextDX(getDebugFont(), "PL_center.x", 0, 330, center.x);
	printTextDX(getDebugFont(), "PL_center.y", 0, 360, center.y);

}


/////�ȉ��I�u�W�F�N�g�Z�b�g�n���[�J���֐�

ObjStr cleanObj(int i) {//Obj�����Z�b�g
	return {
		NO_TYPE,
		short(i),
		false,
		NULL,
		NULL,
		{0.0f,0.0f},
		0.0f,
		{0.0f,0.0f},
		{0.0f,0.0f},
		{0.0f,0.0f},
		{0.0f,0.0f},
		int(0),
		short(0),
		0.0f,
		{0.0f,0.0f}
//		cleanTex()
	};
}

Image cleanTex(void) {//Tex�����Z�b�g
	Image nullTex;
	InitImage(&nullTex, getTexture(textureLoaderNS::TEXTURE_NUMBER(0)), 0, 0, 1, 1);
	return nullTex;
}

void setObjFromFile(ObjStr *obj, int i, Stage* p_fromstage){
	//��������X�e�[�W�f�[�^�̒�����I�u�W�F�N�g���Z�b�g

	if (StubObj[i].m_type != NO_TYPE) {//�X�e�[�W�f�[�^���璆�g�𒼐ڂ��炦�΂�������
		obj->m_type = StubObj[i].m_type;
		obj->m_id = StubObj[i].m_id;
		obj->m_use = false;
		obj->m_ptr = obj;
		obj->m_tar = NULL;

		obj->m_pos = StubObj[i].m_pos;
		obj->m_rot = StubObj[i].m_rot;
		obj->m_scl = StubObj[i].m_scl;

		obj->m_speed = D3DXVECTOR2{0.0f,0.0f};
		obj->m_accel = StubObj[i].m_accel;
		obj->m_attract = StubObj[i].m_attract;

		obj->m_time = StubObj[i].m_time;
		obj->m_mode = StubObj[i].m_mode;

		obj->m_rad = StubObj[i].m_rad;
		obj->m_rect = StubObj[i].m_rect;
		obj->m_rect = { StubTex[i].width,StubTex[i].height };
	}
	else {//�X�e�[�W�f�[�^����̃^�C�v�ɂȂ��Ă�����
		*obj = cleanObj(i);
	}
}

void setObjNotFrom(ObjStr *obj, int i, int objnum) {
	//UI�ȂǁA�X�e�[�W���Ƃɕς��Ȃ��̂Ńt�@�C���ɕۑ�����K�v���Ȃ��A���񂱂���Őݒ肷��΂����I�u�W�F�N�g���Z�b�g

	obj->m_id = i;
	obj->m_use = true;
	switch (i - objnum) {
	case 0:
		obj->m_type = UI_CURSOR;
		obj->m_pos = { (float)WINDOW_CENTER_X,(float)WINDOW_CENTER_Y };//�}�E�X�J�[�\���̈ړ����Ăǂ����񂾂�
		break;
	case 1:
		obj->m_type = UI_EFFECT;
		obj->m_pos = { 720.0f,480.0f };
		break;
	default:
		obj->m_type = UI_HP;
		obj->m_pos = { 0.0f,0.0f };
		break;
	}
}



void setObjTex(ObjStr* obj, int i) {//Obj��StubTex�̒��g���Z�b�g
	if (obj->m_type != NO_TYPE) {
		StubTexture *p_tex = &(StubTex[int(obj->m_type)]);
		if (p_tex->m_type != NO_TYPE) {
			if (obj->m_image.playAnime == false) {//�Î~�悾������
				InitImage(&(obj->m_image), getTexture(StubTex[int(obj->m_type)].texture), obj->m_pos.x, obj->m_pos.y,
					p_tex->width, p_tex->height);
			}
			else {//�A�j����������
				InitAnimeImage(&(obj->m_image), getTexture(StubTex[int(obj->m_type)].texture), obj->m_pos.x, obj->m_pos.y,
					p_tex->width, p_tex->height,
					p_tex->ANIME_TIME, p_tex->ANIME_PATTERN, p_tex->DIVIDE_U, p_tex->DIVIDE_V);
			}
		}
		else {//�e�N�X�`���f�[�^����̃^�C�v�ɂȂ��Ă�����
			obj->m_image = cleanTex();
		}
	}
	else {//�I�u�W�F�N�g�f�[�^����̃^�C�v�ɂȂ��Ă�����
		obj->m_image = cleanTex();
	}
}

void updatePlayer(ObjStr* p_obj) {
	//p_obj->m_rot = D3DX_PI / 4;
	p_obj->m_speed.x += p_obj->m_accel.x;	// �����x�𑬓x�։��Z����
	p_obj->m_speed.y += p_obj->m_accel.y;	// �����x�𑬓x�։��Z����

	if (p_obj->m_speed.x > 2.0f)
	{
		p_obj->m_speed.x = 2.0f;
	}
	if (p_obj->m_speed.y > 2.0f)
	{
		p_obj->m_speed.y = 2.0f;
	}

	if (p_obj->m_speed.x < -2.0f)
	{
		p_obj->m_speed.x = -2.0f;
	}
	if (p_obj->m_speed.y < -2.0f)
	{
		p_obj->m_speed.y = -2.0f;
	}

	//p_obj->m_pos.x += p_obj->m_speed.x;			// �ʒu���𑬓x�ōX�V
	//p_obj->m_pos.y += p_obj->m_speed.y;			// �ʒu���𑬓x�ōX�V

};
void updateBlackHole(ObjStr* p_obj) {
	// ���͂��v�Z����
	p_obj->m_attract = objectDirection(p_obj, p_obj->m_tar) * VALUE_ATTRACTION;
	if (p_obj->m_use == true)// �u���b�N�z�[�����L���Ȃ��
	{
		if (objectLength(p_obj, p_obj->m_tar) <= RANGE_ATTRACTION) // �v���C���[�̋��������͂̓����͈͓��Ȃ��
			p_obj->m_tar->m_accel =
			p_obj->m_attract * (1-(objectLength(p_obj, p_obj->m_tar) / RANGE_ATTRACTION));	// �v���C���[�̉����x�ֈ��͂����Z����
			// (����) * (1 - �v���C���[����/���͔͈�)
	}

};
void updateWhiteHole(ObjStr* p_obj) {

};

void  setBlackHole(ObjStr* p_obj) {
	p_obj->m_use = true;
	p_obj->m_pos = D3DXVECTOR2{ (float)getMouseX(),(float)getMouseY() };
};

void  setWhiteHole(ObjStr* p_obj) {
	p_obj->m_pos = D3DXVECTOR2{ (float)getMouseX(),(float)getMouseY() };
};

// 2�̃I�u�W�F�N�g�Ԃ̋�����(�Z�o����/�߂�/�Ԃ�)
float objectLength(ObjStr* p_obj1, ObjStr* p_obj2)
{
	D3DXVECTOR2 toTarget;
	toTarget.x = p_obj1->m_pos.x - p_obj2->m_pos.x;
	toTarget.y = p_obj1->m_pos.y - p_obj2->m_pos.y;
	float length = D3DXVec2Length(&toTarget);
	return length;
};

// �I�u�W�F�N�g1�ɑ΂���I�u�W�F�N�g2�̕����x�N�g����߂�
D3DXVECTOR2 objectDirection(ObjStr* p_obj1, ObjStr* p_obj2)
{
	D3DXVECTOR2 dir;
	dir.x = p_obj1->m_pos.x - p_obj2->m_pos.x;
	dir.y = p_obj1->m_pos.y - p_obj2->m_pos.y;
	// ���K�����đ傫����1�ɂ���
	D3DXVec2Normalize(&dir, &dir);
	return dir;
}

void resetStar(ObjStr* p_obj)
{
	p_obj->m_pos = D3DXVECTOR2{ WINDOW_WIDTH , 450.0f };
	p_obj->m_speed = D3DXVECTOR2{ -1.0f,0.0f };
	p_obj->m_accel = D3DXVECTOR2{ 0.0f,0.0f };
}