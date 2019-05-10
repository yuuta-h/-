#include "objectList.h"
#include "textDX.h"

// 一つのノードを動的に生成
static Dn_obj* AllocDnode(void)
{
	return (Dn_obj*)calloc(1, sizeof(Dn_obj));
}
static Dn_objCon* AllocDnode_(void)
{
	return (Dn_objCon*)calloc(1, sizeof(Dn_objCon));
}

// ノードの各メンバに値を設定
static void SetDnode(Dn_obj* n,const ObjStr* x, Dn_obj* prev, Dn_obj* next)
{
	n->mp_obj = x;		// データ
	n->prev = prev;		// 先行ノードへのポインタ
	n->next = next;		// 後続ノードへのポインタ
}
static void SetDnode_(Dn_objCon* n, const ObjStr* x1, const ObjStr* x2, Dn_objCon* prev, Dn_objCon* next)
{
	n->mp_objL = x1;	// データ1(左)
	n->mp_objR = x2;	// データ2(右)
	n->prev = prev;		// 先行ノードへのポインタ
	n->next = next;		// 後続ノードへのポインタ
}

// リストは空か
static int IsEmpty(const Dl_obj* list)
{
	return list->head->next == list->head;
}
static int IsEmpty(const Dl_objCon* list)
{
	return list->head->next == list->head;
}

// pが指すノードを削除
void Remove(Dl_obj* list, Dn_obj* p)
{
	p->prev->next = p->next;
	p->next->prev = p->prev;
	list->crnt = p->prev;	// 削除したノードの先行ノードに着目
	free(p);
	if (list->crnt == list->head)
		list->crnt = list->head->next;
};
void Remove(Dl_objCon* list, Dn_objCon* p)
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
void Initialize(Dl_obj* list)
{
	Dn_obj* dummyNode = AllocDnode(); // ダミーノードを生成
	list->head = list->crnt = dummyNode;
	dummyNode->prev = dummyNode->next = dummyNode;
}
void Initialize(Dl_objCon* list)
{
	Dn_objCon* dummyNode = AllocDnode_(); // ダミーノードを生成
	list->head = list->crnt = dummyNode;
	dummyNode->prev = dummyNode->next = dummyNode;
}

// 着目ノードのデータを表示
void PrintCurrent(const Dl_obj* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "着目ノードがありません。", 0, txtLineBreak());
	else {
		PrintObjStr(list->crnt->mp_obj);
	}
}
void PrintCurrent(const Dl_objCon* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "着目ノードがありません。", 0, txtLineBreak());
	else {
		PrintObjStr(list->crnt->mp_objL);
		PrintObjStr(list->crnt->mp_objR);
	}
}

// 着目ノードのデータを表示（改行付き）
void PrintLnCurrent(const Dl_obj* list)
{
	PrintCurrent(list);
	//	putchar('\n');
	printTextDX(getDebugFont(), "", 0, txtLineBreak());
}
void PrintLnCurrent(const Dl_objCon* list)
{
	PrintCurrent(list);
	//	putchar('\n');
	printTextDX(getDebugFont(), "", 0, txtLineBreak());
}

// 関数compareによって(x)/(x1,x2)と一致すると判定されるノードを探索
Dn_obj* Search(Dl_obj *list, const ObjStr* x, int compare(const ObjStr* x, const ObjStr* y))
{
	Dn_obj* ptr = list->head->next;
	while (ptr != list->head)
	{
		if (compare(ptr->mp_obj, x) == 0)
		{
			list->crnt = ptr;
			return ptr;			// 探索成功
		}
		ptr = ptr->next;
	}
	return NULL;				// 探索失敗
};
Dn_objCon* Search(Dl_objCon *list, const ObjStr* x1, const ObjStr* x2,
	int compare1(const ObjStr* x1, const ObjStr* y1), int compare2(const ObjStr* x2, const ObjStr* y2))
{
	Dn_objCon* ptr = list->head->next;
	while (ptr != list->head)
	{
		if (compare1(ptr->mp_objL, x1) == 0 && compare2(ptr->mp_objR, x2) == 0)
		{
			list->crnt = ptr;
			return ptr;			// 探索成功
		}
		ptr = ptr->next;
	}
	return NULL;				// 探索失敗
};


// 全ノードのデータをリスト順に表示
void Print(const Dl_obj* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "ノードがありません。", 0, txtLineBreak());
	else {
		Dn_obj* ptr = list->head->next;
		printTextDX(getDebugFont(), "【一覧表】", 0, txtLineBreak());
		while (ptr != list->head) {
			PrintObjStr(list->crnt->mp_obj);
			ptr = ptr->next;		// 後続ノードに着目	
		}
	}
};
void Print(const Dl_objCon* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "ノードがありません。", 0, txtLineBreak());
	else {
		Dn_objCon* ptr = list->head->next;
		printTextDX(getDebugFont(), "【一覧表】", 0, txtLineBreak());
		while (ptr != list->head) {
			PrintObjStr(list->crnt->mp_objL);
			PrintObjStr(list->crnt->mp_objR);
			ptr = ptr->next;		// 後続ノードに着目	
		}
	}
};


// 全ノードのデータをリストの逆順に表示
void PrintReverse(const Dl_obj* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "ノードがありません。", 0, txtLineBreak());
	else {
		Dn_obj* ptr = list->head->prev;
		printTextDX(getDebugFont(), "【一覧表】", 0, txtLineBreak());
		while (ptr != list->head) {
			PrintObjStr(list->crnt->mp_obj);
			ptr = ptr->prev;		// 先行ノードに着目
		}
	}
};
void PrintReverse(const Dl_objCon* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "ノードがありません。", 0, txtLineBreak());
	else {
		Dn_objCon* ptr = list->head->prev;
		printTextDX(getDebugFont(), "【一覧表】", 0, txtLineBreak());
		while (ptr != list->head) {
			PrintObjStr(list->crnt->mp_objL);
			PrintObjStr(list->crnt->mp_objR);
			ptr = ptr->prev;		// 先行ノードに着目
		}
	}
};

// 着目ノードを一つ後方に進める
int Next(Dl_obj* list)
{
	if (IsEmpty(list) || list->crnt->next == list->head)
		return 0;	// 進めることはできない
	list->crnt = list->crnt->next;
	return 1;
};
int Next(Dl_objCon* list)
{
	if (IsEmpty(list) || list->crnt->next == list->head)
		return 0;	// 進めることはできない
	list->crnt = list->crnt->next;
	return 1;
};

// 着目ノードを一つ前方に戻す
int Prev(Dl_obj* list)
{
	if (IsEmpty(list) || list->crnt->prev == list->head)
		return 0;	// 戻すことはできない
	list->crnt = list->crnt->prev;
	return 1;
};
int Prev(Dl_objCon* list)
{
	if (IsEmpty(list) || list->crnt->prev == list->head)
		return 0;	// 戻すことはできない
	list->crnt = list->crnt->prev;
	return 1;
};


// pが指すノードの直後にノードを挿入
void InsertAfter(Dl_obj* list, Dn_obj* p, const ObjStr* x)
{
	Dn_obj* ptr = AllocDnode();
	Dn_obj* nxt = p->next;
	p->next = p->next->prev = ptr;
	SetDnode(ptr, x, p, nxt);
	list->crnt = ptr;
};
void InsertAfter(Dl_objCon* list, Dn_objCon* p, const ObjStr* x1, const ObjStr* x2)
{
	Dn_objCon* ptr = AllocDnode_();
	Dn_objCon* nxt = p->next;
	p->next = p->next->prev = ptr;
	SetDnode_(ptr, x1, x2, p, nxt);
	list->crnt = ptr;
};

// 先頭にノードを挿入
void InsertFront(Dl_obj* list, const ObjStr* x)
{
	InsertAfter(list, list->head, x);
};
void InsertFront(Dl_objCon* list, const ObjStr* x1, const ObjStr* x2)
{
	InsertAfter(list, list->head, x1,x2);
};

// 末尾にノードを挿入
void InsertRear(Dl_obj* list, const ObjStr* x)
{
	InsertAfter(list, list->head->prev, x);
};
void InsertRear(Dl_objCon* list, const ObjStr* x1, const ObjStr* x2)
{
	InsertAfter(list, list->head->prev, x1, x2);
};

// 先頭ノードを削除
void RemoveFront(Dl_obj* list)
{
	if (!IsEmpty(list))
		Remove(list, list->head->next);
};
void RemoveFront(Dl_objCon* list)
{
	if (!IsEmpty(list))
		Remove(list, list->head->next);
};

// 末尾ノードを削除
void RemoveRear(Dl_obj* list)
{
	if (!IsEmpty(list))
		Remove(list, list->head->prev);
};
void RemoveRear(Dl_objCon* list)
{
	if (!IsEmpty(list))
		Remove(list, list->head->prev);
};

// 着目ノードを削除
void RemoveCurrent(Dl_obj* list)
{
	if (list->crnt != list->head)
		Remove(list, list->crnt);
};
void RemoveCurrent(Dl_objCon* list)
{
	if (list->crnt != list->head)
		Remove(list, list->crnt);
};

// 全ノードを削除
void Clear(Dl_obj* list)
{
	while (!IsEmpty(list))	// 空になるまで
		RemoveFront(list);	// 先頭ノードを削除
};
void Clear(Dl_objCon* list)
{
	while (!IsEmpty(list))	// 空になるまで
		RemoveFront(list);	// 先頭ノードを削除
};

// ノード1をノード2の直後に移動
void MoveDnode(Dn_obj* p_is, Dn_obj* p_to) {
	if (p_is != p_to) {
		//(どちらもダミーノードではないものとする)

		//p_isの前後にp_isを忘れさせる
		p_is->prev->next = p_is->next;
		p_is->next->prev = p_is->prev;

		//p_isに新しい前後ノードを覚えさせる
		p_is->prev = p_to;
		p_is->next = p_to->next;

		//p_toと次のノードにp_isを覚えさせる
		p_to->next->prev = p_is;
		p_to->next = p_is;
	}
};

// 循環・重連結リストの後始末
void Terminate(Dl_obj* list)
{
	Clear(list);			// 全ノードを削除
	free(list->head);		// ダミーノードを削除
};
void Terminate(Dl_objCon* list)
{
	Clear(list);			// 全ノードを削除
	free(list->head);		// ダミーノードを削除
};

// データの表示（改行なし）
void PrintObjStr(const ObjStr* d)
{
	printTextDX(getDebugFont(), "id：", 0, txtLineBreak(), int(d->m_id));
	printTextDX(getDebugFont(), "type：", 0, txtLineBreak(), int(d->m_type));
};