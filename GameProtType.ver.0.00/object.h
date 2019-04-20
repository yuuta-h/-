//西川
#pragma once

#include "main.h"
#include "Image.h"

enum objTypes{
	NO_TYPE = -1,
		CHARA_PLAYER,
		CHARA_BLACKHOLE,
		CHARA_KEY,
		CHARA_COIN,
		STAGE_HURDLE,
		STAGE_WALL,
		STAGE_LOCK,
		EVENT_GOAL,
	FROMFILE_TYPE_MAX,
		UI_CURSOR,
		UI_EFFECT,
		UI_HP,
	TYPE_MAX
};

//shortは-0.5±32767.5、intは-0.5±2147483647.5

//オブジェクトの一つ一つ
//敵[0]か、敵[1]か、敵[2]か…etc
typedef struct{
	objTypes m_type;					//オブジェクトタイプ
	short m_id;							//全タイプが入っている配列内の、自分の番号
	bool m_use;							//useフラグ

	int m_time;							//プレイヤーとは独立して勝手に動くオブジェクトがあれば使うかも
	short m_mode;						//同上

	D3DXVECTOR2 m_pos;					//座標
	float m_rot;						//角度
	D3DXVECTOR2 m_scl;					//大きさ

	float m_rad;						//半径(プレイヤーの当たり判定とか)
	D3DXVECTOR2 m_rect;					//矩形の辺長(ステージの当たり判定とか)
	//衝突以外でも使うなら配列になるかも(近寄ると動き出すとか、ブラックホールが吸い寄せ始める範囲とか)

	Image m_image;						//描画情報
}ObjStr;//Structure


bool initializeObject(int stage);
void uninitializeObject(void);
void updateObject(void);
void drawObject(void);

