#include "objectEdgeList.h"
#include "textDX.h"

// 一つのノードを動的に生成
static Dn_objEdge* AllocDnode(void)
{
	return (Dn_objEdge*)calloc(1, sizeof(Dn_objEdge));
}

// ノードの各メンバに値を設定
static void SetDnode(Dn_objEdge* n,const ObjStr* x, Dn_objEdge* prev, Dn_objEdge* next)
{
	n->mp_obj = x;		// データ
	n->prev = prev;		// 先行ノードへのポインタ
	n->next = next;		// 後続ノードへのポインタ
}

// リストは空か
static int IsEmpty(const Dl_objEdge* list)
{
	return list->head->next == list->head;
}

// pが指すノードを削除
void Remove(Dl_objEdge* list, Dn_objEdge* p)
{
	p->prev->next = p->next;
	p->next->prev = p->prev;
	list->crnt = p->prev;	// 削除したノードの先行ノードに着目
	free(p);
	if (list->crnt == list->head)
		list->crnt = list->head->next;
};

// 着目ノードと着目の次ノードを、x座標について比べる
static int compareCurrentNextByX(Dl_objEdge* list) {
	if (list->crnt == list->head || list->crnt->next == list->head)
		return -1;// どちらかがダミーノードで比べられない、という時は-1
	if (list->crnt->mp_obj->m_pos.x + list->crnt->m_dst <= 
		list->crnt->next->mp_obj->m_pos.x + list->crnt->next->m_dst) return 1;//x昇順になっていれば
	return 0;//NOT x昇順ならば
}

// ノード1とノード2を、x座標について比べる
static int compareByX(const Dl_objEdge* list, const Dn_objEdge* p1, const  Dn_objEdge* p2) {
	if (p1 == list->head || p2 == list->head)
		return -1;// どちらかがダミーノードで比べられない、という時は-1
	if (p1->mp_obj->m_pos.x + p1->m_dst <= p2->mp_obj->m_pos.x + p2->m_dst) return 1;//x昇順になっていれば
	return 0;//NOT x昇順ならば
}

// データの番号の比較関数
int objPntrCmp(const ObjStr* x, const ObjStr* y)
{
	// xの番号がyの番号より小さい時→-1を戻す
	// xの番号がyの番号より大きい時→1を戻す
	// xの番号とyの番号が等しい時→0を戻す
	return x < y ? -1 : x > y ? 1 : 0;
};

//↑ローカル関数

// リストを初期化
void Initialize(Dl_objEdge* list)
{
	Dn_objEdge* dummyNode = AllocDnode(); // ダミーノードを生成
	list->head = list->crnt = dummyNode;
	dummyNode->prev = dummyNode->next = dummyNode;
}

// 着目ノードのデータを表示
void PrintCurrent(const Dl_objEdge* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "着目ノードがありません。", 0, txtLineBreak());
	else {
		PrintObjEdge(list->crnt);
	}
}

// 着目ノードのデータを表示（改行付き）
void PrintLnCurrent(const Dl_objEdge* list)
{
	PrintCurrent(list);
	//	putchar('\n');
	printTextDX(getDebugFont(), "", 0, txtLineBreak());
}

// 関数compareによってxとデータ内容が一致しているノードを探索
Dn_objEdge* Search(Dl_objEdge *list, const ObjStr* x)
{
	Dn_objEdge* ptr = list->head->next;
	while (ptr != list->head)
	{
		if (objPntrCmp(ptr->mp_obj, x) == 0)
		{
			list->crnt = ptr;
			return ptr;			// 探索成功
		}
		ptr = ptr->next;
	}
	return NULL;				// 探索失敗
};

// 全ノードのデータをリスト順に表示
void Print(const Dl_objEdge* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "ノードがありません。", 0, txtLineBreak());
	else {
		Dn_objEdge* ptr = list->head->next;
		printTextDX(getDebugFont(), "【一覧表】", 0, txtLineBreak());
		while (ptr != list->head) {
			PrintObjEdge(list->crnt);
			ptr = ptr->next;		// 後続ノードに着目	
		}
	}
};

// 全ノードのデータをリストの逆順に表示
void PrintReverse(const Dl_objEdge* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "ノードがありません。", 0, txtLineBreak());
	else {
		Dn_objEdge* ptr = list->head->prev;
		printTextDX(getDebugFont(), "【一覧表】", 0, txtLineBreak());
		while (ptr != list->head) {
			PrintObjEdge(list->crnt);
			ptr = ptr->prev;		// 先行ノードに着目
		}
	}
};

// 着目ノードを一つ後方に進める
int Next(Dl_objEdge* list)
{
	if (IsEmpty(list) || list->crnt->next == list->head)
		return 0;	// 進めることはできない
	list->crnt = list->crnt->next;
	return 1;
};

// 着目ノードを一つ前方に戻す
int Prev(Dl_objEdge* list)
{
	if (IsEmpty(list) || list->crnt->prev == list->head)
		return 0;	// 戻すことはできない
	list->crnt = list->crnt->prev;
	return 1;
};


// pが指すノードの直後にノードを挿入
void InsertAfter(Dl_objEdge* list, Dn_objEdge* p, const ObjStr* x)
{
	Dn_objEdge* ptr = AllocDnode();
	Dn_objEdge* nxt = p->next;
	p->next = p->next->prev = ptr;
	SetDnode(ptr, x, p, nxt);
	list->crnt = ptr;
};

// 先頭にノードを挿入
void InsertFront(Dl_objEdge* list, const ObjStr* x)
{
	InsertAfter(list, list->head, x);
};

// 末尾にノードを挿入
void InsertRear(Dl_objEdge* list, const ObjStr* x)
{
	InsertAfter(list, list->head->prev, x);
};

// 末尾にオブジェクトの両端を挿入し、距離を設定
void InsertAfterEdges(Dl_objEdge* list, const ObjStr* x, float eL, float eR)
{
	InsertAfter(list, list->head->prev, x);
	list->crnt->m_dst = eL;// 左端の距離を設定
	list->crnt->mp_L = NULL;// 右端でない

	Dn_objEdge* p_L = list->crnt;//左端
	InsertAfter(list, list->head->prev, x);
	list->crnt->m_dst = eR;// 右端の距離を設定
	list->crnt->mp_L = p_L;// 自分は右端であり、左端のノードはmp_L
};

// 末尾にcopyedのコピーを挿入
void CopyRear(Dl_objEdge* list, Dn_objEdge* copied)
{
	InsertAfter(list, list->head->prev, copied->mp_obj);
	list->crnt->m_dst = copied->m_dst; list->crnt->mp_L = copied->mp_L;//prev,next,mp_obj以外も転写
};

// 先頭ノードを削除
void RemoveFront(Dl_objEdge* list)
{
	if (!IsEmpty(list))
		Remove(list, list->head->next);
};

// 末尾ノードを削除
void RemoveRear(Dl_objEdge* list)
{
	if (!IsEmpty(list))
		Remove(list, list->head->prev);
};

// 着目ノードを削除
void RemoveCurrent(Dl_objEdge* list)
{
	if (list->crnt != list->head)
		Remove(list, list->crnt);
};

// 全ノードを削除
void Clear(Dl_objEdge* list)
{
	while (!IsEmpty(list))	// 空になるまで
		RemoveFront(list);	// 先頭ノードを削除
};

// ノード1をノード2の直後に移動
void MoveDnode(Dn_objEdge* p_is, Dn_objEdge* p_to) {
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
void Terminate(Dl_objEdge* list)
{
	Clear(list);			// 全ノードを削除
	free(list->head);		// ダミーノードを削除
};

// データの表示（改行なし）
void PrintObjEdge(const Dn_objEdge* n)
{
	printTextDX(getDebugFont(), "id：", 0, txtLineBreak(), int(n->mp_obj->m_id));
	printTextDX(getDebugFont(), "type：", 0, txtLineBreak(), int(n->mp_obj->m_type));
	printTextDX(getDebugFont(), "distance：", 0, txtLineBreak(), int(n->m_dst));
};

// オブジェクトリストをx昇順に並び替え
void sortObjListByX(Dl_objEdge* list) {
	list->crnt = list->head;//着目ノードをリセット
	while (Next(list)) {//最後までx座標順になったら0になって終了

		if (compareCurrentNextByX(list) == 0) {//(先頭ノードでなく)x座標順になっていないものを見つけていたら
			if (compareByX(list, list->crnt->prev, list->crnt->next) == 1) {
				// カレントの次がカレントの前と順序立っていれば==おかしいのがカレントノードならば、カレント自身を右方向へ
				Dn_objEdge *crnt_prev = list->crnt->prev, *crnt = list->crnt;
				while (Next(list)) {
					if (compareByX(list, crnt, list->crnt) != 1) {
						if (compareByX(list, crnt, list->crnt) == 0)
							Prev(list);//末尾でなければ進み過ぎてるので一つ戻る
						MoveDnode(crnt, list->crnt);
						break;
					}
				}
				list->crnt = crnt_prev;
			}
			else if (compareByX(list, list->crnt->prev, list->crnt->next) == 0) {//でなければ
					// でなければ==おかしいのがカレントの次ノードならば、カレントの次を左方向へ移動
				Dn_objEdge *crnt = list->crnt, *crnt_next = list->crnt->next;
				while (Prev(list)) {
					if (compareByX(list, crnt_next, list->crnt) != 1) {
						if (compareByX(list, crnt, list->crnt) == 0)
							Next(list);//先頭でなければ戻り過ぎてるので一つ進む
						MoveDnode(crnt_next, list->crnt);
						break;
					}
				}
				list->crnt = crnt;
			}
		}
	}
}
//ifやwhileなどの条件式内で関数を呼んだ場合にも値は書き変わる。
