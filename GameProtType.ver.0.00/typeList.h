#pragma once
#include "object.h"

// あるタイプのオブジェクトについて、ある処理が、全タイプそれぞれと行われるかどうかの表

	// ノード
	typedef struct __node_type {
		const objTypes* mp_type1;				// データ1
		const objTypes* mp_type2;				// データ2

		bool m_act;								// 1が2に干渉するか
		bool m_pas;								// 2が1に干渉するか

		struct __node_type *prev;				// 左ノードへのポインタ
		struct __node_type *next;				// 右ノードへのポインタ
	}Dn_typeCmp;

	// 循環・重連結リスト
	typedef struct {
		Dn_typeCmp *head;						// 先頭(左端)ダミーノードへのポインタ
		Dn_typeCmp *crnt;						// 着目ノードへのポインタ
	}Dl_typeCmp;

// リストを初期化
void Initialize(Dl_typeCmp *list);

// 着目ノードのデータを表示
void PrintCurrent(const Dl_typeCmp *list);

// 着目ノードのデータを表示（改行付き）
void PrintLnCurrent(const Dl_typeCmp *list);

// 関数compareによって(x)/(x1,x2)と一致すると判定されるノードを探索
Dn_typeCmp* Search(Dl_typeCmp *list, const objTypes* x1, const objTypes* x2,
	int compare1(const objTypes* x1, const objTypes* y1), int compare2(const objTypes* x2, const objTypes* y2));

// 全ノードのデータをリスト順に表示
void Print(const Dl_typeCmp* list);

// 全ノードのデータをリストの逆順に表示
void PrintReverse(const Dl_typeCmp* list);

// 着目ノードを一つ後方に進める
int Next(Dl_typeCmp* list);

// 着目ノードを一つ前方に戻す
int Prev(Dl_typeCmp* list);

// pが指すノードの直後にノードを挿入
void InsertAfter(Dl_typeCmp* list, Dn_typeCmp* p, const objTypes* x1, const objTypes* x2);

// 先頭にノードを挿入
void InsertFront(Dl_typeCmp* list, const objTypes* x1, const objTypes* x2);

// 末尾にノードを挿入
void InsertRear(Dl_typeCmp* list, const objTypes* x1, const objTypes* x2);

// 先頭ノードを削除
void RemoveFront(Dl_typeCmp* list);

// 末尾ノードを削除
void RemoveRear(Dl_typeCmp* list);

// 着目ノードを削除
void RemoveCurrent(Dl_typeCmp* list);

// 全ノードを削除
void Clear(Dl_typeCmp* list);

// 循環・重連結リストの後始末
void Terminate(Dl_typeCmp* list);

// データの表示（改行なし）
void PrintobjTypes(const objTypes* d);
