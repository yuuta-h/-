#pragma once
// 循環・重連結リスト(ヘッダ部)

#include "object.h"


//オブジェクト版
	// ノード
	typedef struct __node_obj {
		const ObjStr* mp_obj;				// データ
		struct __node_obj *prev;			// 前ノードへのポインタ
		struct __node_obj *next;			// 後ノードへのポインタ
	}Dn_obj;

	// 循環・重連結リスト
	typedef struct {
		Dn_obj *head;						// 先頭(左端)ダミーノードへのポインタ
		Dn_obj *crnt;						// 着目ノードへのポインタ
	}Dl_obj;

//オブジェクト関係版
	// ノード
	typedef struct __node_objCon {
		const ObjStr* mp_objL;				// データ1(左にいる)
		const ObjStr* mp_objR;				// データ2(右にいる)
		bool use_objCon;					// そのオブジェクト関係の当たり判定がどうだったか
		struct __node_objCon *prev;			// 先行ノードへのポインタ
		struct __node_objCon *next;			// 後続ノードへのポインタ
	}Dn_objCon;

	// 循環・重連結リスト
	typedef struct {
		Dn_objCon *head;					// 先頭ダミーノードへのポインタ
		Dn_objCon *crnt;					// 着目ノードへのポインタ
	}Dl_objCon;

// リストを初期化
void Initialize(Dl_obj *list);
void Initialize(Dl_objCon *list);

// 着目ノードのデータを表示
void PrintCurrent(const Dl_obj *list);
void PrintCurrent(const Dl_objCon *list);

// 着目ノードのデータを表示（改行付き）
void PrintLnCurrent(const Dl_obj *list);
void PrintLnCurrent(const Dl_objCon *list);

// 関数compareによって(x)/(x1,x2)と一致すると判定されるノードを探索
Dn_obj* Search(Dl_obj *list, const ObjStr* x,int compare(const ObjStr* x, const ObjStr* y));
Dn_objCon* Search(Dl_objCon *list, const ObjStr* x1, const ObjStr* x2,
	int compare1(const ObjStr* x1, const ObjStr* y1), int compare2(const ObjStr* x2, const ObjStr* y2));

// 全ノードのデータをリスト順に表示
void Print(const Dl_obj* list);
void Print(const Dl_objCon* list);

// 全ノードのデータをリストの逆順に表示
void PrintReverse(const Dl_obj* list);
void PrintReverse(const Dl_objCon* list);

// 着目ノードを一つ後方に進める
int Next(Dl_obj* list);
int Next(Dl_objCon* list);

// 着目ノードを一つ前方に戻す
int Prev(Dl_obj* list);
int Prev(Dl_objCon* list);

// pが指すノードの直後にノードを挿入
void InsertAfter(Dl_obj* list, Dn_obj* p, const ObjStr* x);
void InsertAfter(Dl_objCon* list, Dn_objCon* p, const ObjStr* x1, const ObjStr* x2);

// 先頭にノードを挿入
void InsertFront(Dl_obj* list, const ObjStr* x);
void InsertFront(Dl_objCon* list, const ObjStr* x1, const ObjStr* x2);

// 末尾にノードを挿入
void InsertRear(Dl_obj* list, const ObjStr* x);
void InsertRear(Dl_objCon* list, const ObjStr* x1, const ObjStr* x2);

// 先頭ノードを削除
void RemoveFront(Dl_obj* list);
void RemoveFront(Dl_objCon* list);

// 末尾ノードを削除
void RemoveRear(Dl_obj* list);
void RemoveRear(Dl_objCon* list);

// 着目ノードを削除
void RemoveCurrent(Dl_obj* list);
void RemoveCurrent(Dl_objCon* list);

// 全ノードを削除
void Clear(Dl_obj* list);
void Clear(Dl_objCon* list);

// ノード1をノード2の直後に移動
void MoveDnode(Dn_obj* p_is, Dn_obj* p_to);

// 循環・重連結リストの後始末
void Terminate(Dl_obj* list);
void Terminate(Dl_objCon* list);

// データの表示（改行なし）
void PrintObjStr(const ObjStr* d);
