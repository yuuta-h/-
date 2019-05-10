#include "typeList.h"
#include "textDX.h"

// 一つのノードを動的に生成
static Dn_typeCmp* AllocDnode_(void)
{
	return (Dn_typeCmp*)calloc(1, sizeof(Dn_typeCmp));
}

// ノードの各メンバに値を設定
static void SetDnode_(Dn_typeCmp* n, const objTypes* x1, const objTypes* x2, Dn_typeCmp* prev, Dn_typeCmp* next)
{
	n->mp_type1 = x1;	// データ1(左)
	n->mp_type2 = x2;	// データ2(右)
	n->prev = prev;		// 先行ノードへのポインタ
	n->next = next;		// 後続ノードへのポインタ
}

// リストは空か
static int IsEmpty(const Dl_typeCmp* list)
{
	return list->head->next == list->head;
}

// pが指すノードを削除
void Remove(Dl_typeCmp* list, Dn_typeCmp* p)
{
	p->prev->next = p->next;
	p->next->prev = p->prev;
	list->crnt = p->prev;	// 削除したノードの先行ノードに着目
	free(p);
	if (list->crnt == list->head)
		list->crnt = list->head->next;
};

//↑ローカル関数

// リストを初期化
void Initialize(Dl_typeCmp* list)
{
	Dn_typeCmp* dummyNode = AllocDnode_(); // ダミーノードを生成
	list->head = list->crnt = dummyNode;
	dummyNode->prev = dummyNode->next = dummyNode;
}

// 着目ノードのデータを表示
void PrintCurrent(const Dl_typeCmp* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "着目ノードがありません。", 0, txtLineBreak());
	else {
		PrintobjTypes(list->crnt->mp_type1);
		PrintobjTypes(list->crnt->mp_type2);
	}
}

// 着目ノードのデータを表示（改行付き）
void PrintLnCurrent(const Dl_typeCmp* list)
{
	PrintCurrent(list);
	//	putchar('\n');
	printTextDX(getDebugFont(), "", 0, txtLineBreak());
}

// 関数compareによって(x)/(x1,x2)と一致すると判定されるノードを探索
Dn_typeCmp* Search(Dl_typeCmp *list, const objTypes* x1, const objTypes* x2,
	int compare1(const objTypes* x1, const objTypes* y1), int compare2(const objTypes* x2, const objTypes* y2))
{
	Dn_typeCmp* ptr = list->head->next;
	while (ptr != list->head)
	{
		if (compare1(ptr->mp_type1, x1) == 0 && compare2(ptr->mp_type2, x2) == 0)
		{
			list->crnt = ptr;
			return ptr;			// 探索成功
		}
		ptr = ptr->next;
	}
	return NULL;				// 探索失敗
};


// 全ノードのデータをリスト順に表示
void Print(const Dl_typeCmp* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "ノードがありません。", 0, txtLineBreak());
	else {
		Dn_typeCmp* ptr = list->head->next;
		printTextDX(getDebugFont(), "【一覧表】", 0, txtLineBreak());
		while (ptr != list->head) {
			PrintobjTypes(list->crnt->mp_type1);
			PrintobjTypes(list->crnt->mp_type2);
			ptr = ptr->next;		// 後続ノードに着目	
		}
	}
};


// 全ノードのデータをリストの逆順に表示
void PrintReverse(const Dl_typeCmp* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "ノードがありません。", 0, txtLineBreak());
	else {
		Dn_typeCmp* ptr = list->head->prev;
		printTextDX(getDebugFont(), "【一覧表】", 0, txtLineBreak());
		while (ptr != list->head) {
			PrintobjTypes(list->crnt->mp_type1);
			PrintobjTypes(list->crnt->mp_type2);
			ptr = ptr->prev;		// 先行ノードに着目
		}
	}
};

// 着目ノードを一つ後方に進める
int Next(Dl_typeCmp* list)
{
	if (IsEmpty(list) || list->crnt->next == list->head)
		return 0;	// 進めることはできない
	list->crnt = list->crnt->next;
	return 1;
};

// 着目ノードを一つ前方に戻す
int Prev(Dl_typeCmp* list)
{
	if (IsEmpty(list) || list->crnt->prev == list->head)
		return 0;	// 戻すことはできない
	list->crnt = list->crnt->prev;
	return 1;
};


// pが指すノードの直後にノードを挿入
void InsertAfter(Dl_typeCmp* list, Dn_typeCmp* p, const objTypes* x1, const objTypes* x2)
{
	Dn_typeCmp* ptr = AllocDnode_();
	Dn_typeCmp* nxt = p->next;
	p->next = p->next->prev = ptr;
	SetDnode_(ptr, x1, x2, p, nxt);
	list->crnt = ptr;
};

// 先頭にノードを挿入
void InsertFront(Dl_typeCmp* list, const objTypes* x1, const objTypes* x2)
{
	InsertAfter(list, list->head, x1, x2);
};

// 末尾にノードを挿入
void InsertRear(Dl_typeCmp* list, const objTypes* x1, const objTypes* x2)
{
	InsertAfter(list, list->head->prev, x1, x2);
};

// 先頭ノードを削除
void RemoveFront(Dl_typeCmp* list)
{
	if (!IsEmpty(list))
		Remove(list, list->head->next);
};

// 末尾ノードを削除
void RemoveRear(Dl_typeCmp* list)
{
	if (!IsEmpty(list))
		Remove(list, list->head->prev);
};

// 着目ノードを削除
void RemoveCurrent(Dl_typeCmp* list)
{
	if (list->crnt != list->head)
		Remove(list, list->crnt);
};

// 全ノードを削除
void Clear(Dl_typeCmp* list)
{
	while (!IsEmpty(list))	// 空になるまで
		RemoveFront(list);	// 先頭ノードを削除
};


// 循環・重連結リストの後始末
void Terminate(Dl_typeCmp* list)
{
	Clear(list);			// 全ノードを削除
	free(list->head);		// ダミーノードを削除
};

// データの表示（改行なし）
void PrintobjTypes(const objTypes* d)
{
	printTextDX(getDebugFont(), "type：", 0, txtLineBreak(), int(d));
};