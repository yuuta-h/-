//西川
#include "object.h"
#include "stdlib.h"//malloc用
#include"textureLoader.h"

#define STUB_OBJNUM (100)	//ステージのデータ内にあるオブジェクトの総数/実際には外からもらう値
#define PLUS_OBJNUM (5)		//ステージ側で保存する必要のないオブジェクト情報(UIなど)があればそれの数

int OBJNUM;
ObjStr *Obj = NULL;

//オブジェクトをセットする系ローカル関数
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
}StubObj[STUB_OBJNUM];//実際には外からもらう値

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
}StubTex[TYPE_MAX];//実際には外からもらう値

/*コリジョンリストに必要なもの
obID/obType/pos/rot/scl/coltype

アクションリスト

エフェクトリスト
*/



bool initializeObject(int stage){

	OBJNUM = STUB_OBJNUM + PLUS_OBJNUM;
	objTypes k;//あまり意味はない

	//↓ステージのオブジェクトたちの初期値＝ステージデータ/実際には外からもらう値
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
		else {//ステージデータの中で空になっているもの(実際にはないかも)
			StubObj[i].m_type = NO_TYPE;
		}
	}
	//↑ステージのオブジェクトたちの初期値＝ステージデータ/実際には外からもらう値


	//↓ステージのテクスチャたちの初期値＝テクスチャリスト/実際には外からもらう値
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
		else {//テクスチャリストの中で空になっているもの(実際にはないかも)
			//現状FROMFILE_TYPE_MAXだったとき
			StubTex[j].m_type = NO_TYPE;
		}
	}
	//↑ステージのテクスチャたちの初期値＝テクスチャリスト/実際には外からもらう値


	Obj = (ObjStr*)malloc(sizeof(ObjStr) * OBJNUM);
	if (Obj == NULL) return false;//mallocは確保に失敗することもあるらしく、以降がぜんぶおかしくなると思うのでfalseを返す(返された側で終了するなり無視するなりしてほしい)

	for (int i = 0; i < OBJNUM; i++) {
		if (i < STUB_OBJNUM) {//オブジェクトにオブジェクトデータからもらった値をセット
			setObjFromFile(i);
		}
		else {//オブジェクトにオブジェクトデータからもらっていない値をセット
			setObjNotFrom(i);
		}

		//オブジェクトにテクスチャデータからもらった値をセット
		setObjTex(i);

		switch (Obj[i].m_type) {//タイプごとの、わざわざファイルに書く必要はないが、ゲーム向けにする必要はある初期化
		case CHARA_PLAYER:
			//星
			break;
		case CHARA_BLACKHOLE:
			//ブラックホール
			break;
		case CHARA_KEY:
			//鍵
			break;
		case CHARA_COIN:
			//収集アイテム
			break;
		case STAGE_HURDLE:
			//動かせる障害物
			break;
		case STAGE_WALL:
			//動かせない壁　地面とか
			break;
		case STAGE_LOCK:
			//鍵で開けられる扉
			break;
		case EVENT_GOAL:
			//ゴール
			break;

		case UI_CURSOR:
			//ブラックホール置くカーソル
			break;
		case UI_EFFECT:
			//エフェクト
			break;
		case UI_HP:
			//残機表示
			break;
		}
	}

	return true;
}

void uninitializeObject(void) {
	if (Obj != NULL) {
		free(Obj);
		Obj = NULL;//誤ってfreeを２連続でやるとヤバい かつ NULLぽがfreeされる分には平気 らしいのでこうした
	}
}

void updateObject(void) {
}

void drawObject(void){
	//全てのオブジェクトを描画　※これだと描画順をタイプごとに揃えたりできないので、描画用のリストを作ることになるのかも
	for (int i = 0; i < OBJNUM; i++) {
//		if (Obj[i].m_use == false) continue;
		setPosition(&(Obj[i].m_image),Obj[i].m_pos.x, Obj[i].m_pos.y);
		DrawImage(&(Obj[i].m_image));
	}
}


/////以下ステージセット系ローカル関数

ObjStr cleanObj(int i) {//Objをリセット
	return {
		NO_TYPE,short(i),false,
		0,short(0),
		{0.0f,0.0f},0.0f,{0.0f,0.0f},
		0.0f,{0.0f,0.0f},
//		cleanTex()
	};
}

Image cleanTex() {//Texをリセット
	Image nullTex;
	InitImage(&nullTex, getTexture(textureLoaderNS::TEXTURE_NUMBER(0)), 0, 0, 1, 1);
	return nullTex;
}


void setObjFromFile(int i) {
	//もらったステージデータの中からオブジェクトをセット

	if (StubObj[i].m_type != NO_TYPE) {//ステージデータから中身を直接もらえばいいもの
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
	else {//ステージデータが空のタイプになっていたら
		Obj[i] = cleanObj(i);
	}
}
void setObjNotFrom(int i) {
	//UIなど、ステージごとに変わらないのでファイルに保存する必要もなく、毎回こちらで設定すればいいオブジェクトをセット

	Obj[i].m_id = i;
	Obj[i].m_use = true;
	switch (i - STUB_OBJNUM) {
	case 0:
		Obj[i].m_type = UI_CURSOR;
		Obj[i].m_pos = { (float)WINDOW_CENTER_X,(float)WINDOW_CENTER_Y };//マウスカーソルの移動ってどうやるんだろ
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



void setObjTex(int i) {//ObjにStubTexの中身をセット
	if (Obj[i].m_type != NO_TYPE) {
		StubTexture *p_tex = &(StubTex[int(Obj[i].m_type)]);
		if (p_tex->m_type != NO_TYPE) {
			if (Obj[i].m_image.playAnime == false) {//静止画だったら
				InitImage(&(Obj[i].m_image), getTexture(StubTex[int(Obj[i].m_type)].texture), Obj[i].m_pos.x, Obj[i].m_pos.y,
					p_tex->width, p_tex->height);
			}
			else {//アニメだったら
				InitAnimeImage(&(Obj[i].m_image), getTexture(textureLoaderNS::BACK_GROUND), Obj[i].m_pos.x, Obj[i].m_pos.y,
					p_tex->width, p_tex->height,
					p_tex->ANIME_TIME, p_tex->ANIME_PATTERN, p_tex->DIVIDE_U, p_tex->DIVIDE_V);
			}
		}
		else {//テクスチャデータが空のタイプになっていたら
			Obj[i].m_image = cleanTex();
		}
	}
	else {//オブジェクトデータが空のタイプになっていたら
		Obj[i].m_image = cleanTex();
	}
}
