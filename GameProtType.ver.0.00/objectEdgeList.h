#pragma once
// 循環・重連結リスト(ヘッダ部)

#include "object.h"


//オブジェクトの端 版
	// ノード
	typedef struct __node_obj {
		const ObjStr* mp_obj;				// データ
		float m_dst;						// オブジェクトの座標からその端までの距離
		struct __node_obj *prev;			// 前ノードへのポインタ
		struct __node_obj *next;			// 後ノードへのポインタ
		struct __node_obj *mp_L;			// オブジェクトの左端を覚えたノードへのポインタ(自分が左端だった場合はNULL)
	}Dn_objEdge;

	// 循環・重連結リスト
	typedef struct {
		Dn_objEdge *head;						// 先頭(左端)ダミーノードへのポインタ
		Dn_objEdge *crnt;						// 着目ノードへのポインタ
	}Dl_objEdge;

// リストを初期化
void Initialize(Dl_objEdge *list);

// 着目ノードのデータを表示
void PrintCurrent(const Dl_objEdge *list);

// 着目ノードのデータを表示（改行付き）
void PrintLnCurrent(const Dl_objEdge *list);

// 関数compareによってxとデータ内容が一致しているノードを探索
Dn_objEdge* Search(Dl_objEdge *list, const ObjStr* x,int compare(const ObjStr* x, const ObjStr* y));

// 全ノードのデータをリスト順に表示
void Print(const Dl_objEdge* list);

// 全ノードのデータをリストの逆順に表示
void PrintReverse(const Dl_objEdge* list);

// 着目ノードを一つ後方に進める
int Next(Dl_objEdge* list);

// 着目ノードを一つ前方に戻す
int Prev(Dl_objEdge* list);

// pが指すノードの直後にノードを挿入
void InsertAfter(Dl_objEdge* list, Dn_objEdge* p, const ObjStr* x);

// 先頭にノードを挿入
void InsertFront(Dl_objEdge* list, const ObjStr* x);

// 末尾にノードを挿入
void InsertRear(Dl_objEdge* list, const ObjStr* x);

// 末尾にオブジェクトの両端を挿入し、距離を設定
void InsertAfterEdges(Dl_objEdge* list, const ObjStr* x, float eL, float eR);

// 末尾にcopyedのコピーを挿入
void CopyRear(Dl_objEdge* list, Dn_objEdge* copied);

// 先頭ノードを削除
void RemoveFront(Dl_objEdge* list);

// 末尾ノードを削除
void RemoveRear(Dl_objEdge* list);

// 着目ノードを削除
void RemoveCurrent(Dl_objEdge* list);

// 全ノードを削除
void Clear(Dl_objEdge* list);

// ノード1をノード2の直後に移動
void MoveDnode(Dn_objEdge* p_is, Dn_objEdge* p_to);

// 循環・重連結リストの後始末
void Terminate(Dl_objEdge* list);

// データの表示
void PrintObjEdge(const Dn_objEdge* n);

// リストに登録されているオブジェクトの端を全てx順にソート
void sortObjListByX(Dl_objEdge* list);

