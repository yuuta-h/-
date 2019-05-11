//西川
#include "listUse.h"

//ローカル関数
bool stubProcess(ObjStr* obj1, ObjStr* obj2);//なんらかの処理
static int compareCurrentNextByX(Dl_obj* list);
static int compareByX(const Dl_obj* list, const Dn_obj* p1, const  Dn_obj* p2);

Dl_typeCmp compatList;				// タイプ相性表
Dl_obj xBasedList;					// x座標順・オブジェクト・リスト(ゲーム中通用)
Dl_objCon resultList;				// 確かめ結果・オブジェクト関係・リスト(毎フレーム使い捨て)

void initializeObjList(StageObj *p_stageobj) {
	Initialize(&xBasedList);
	for (int i = 0; i < p_stageobj->m_OBJNUM; i++)
		InsertAfter(&xBasedList, xBasedList.crnt, &p_stageobj->m_Obj[i]);
			//オブジェクト全てを{リストのカレントの次}に順次挿入
			//できればここで、タイプ関係的に能動でも受動でも当たり判定が起こりえないもの(UIとか)は排除
}
void uninitializeObjList(void) {
	Terminate(&xBasedList);
}

void updateObjList(void){//仮
	sortObjListByX(&xBasedList);

//	optimizeObjList(&compatList,&xBasedList, &resultList);

	Terminate(&resultList);
}


// オブジェクトリストをx昇順に並び替え
void sortObjListByX(Dl_obj* list) {
	list->crnt = list->head;//着目ノードをリセット
	while (Next(list)) {//最後までx座標順になったら0になって終了

		if (compareCurrentNextByX(list) == 0) {//(先頭ノードでなく)x座標順になっていないものを見つけていたら
			if (compareByX(list, list->crnt->prev, list->crnt->next) == 1) {
					// カレントの次がカレントの前と順序立っていれば==おかしいのがカレントノードならば、カレント自身を右方向へ
				Dn_obj *crnt_prev = list->crnt->prev, *crnt = list->crnt;
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
				Dn_obj *crnt = list->crnt, *crnt_next = list->crnt->next;
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


void optimizeObjList(Dl_typeCmp* compat,Dl_obj* xBased, Dl_objCon* result) {
	xBased->crnt = xBased->head;//着目ノードをリセット
	while (Next(xBased)) {
		
	}

}




////////ローカル関数
bool stubProcess(ObjStr* obj1, ObjStr* obj2){//なんらかの処理
	return true;
}


// 着目ノードと着目の次ノードを、x座標について比べる
static int compareCurrentNextByX(Dl_obj* list) {
	if (list->crnt == list->head || list->crnt->next == list->head)
		return -1;// どちらかがダミーノードで比べられない、という時は-1
	if (list->crnt->mp_obj->m_pos.x <= list->crnt->next->mp_obj->m_pos.x) return 1;//x昇順になっていれば
	return 0;//NOT x昇順ならば
}

// ノード1とノード2を、x座標について比べる
static int compareByX(const Dl_obj* list, const Dn_obj* p1, const  Dn_obj* p2) {
	if (p1 == list->head || p2 == list->head)
		return -1;// どちらかがダミーノードで比べられない、という時は-1
	if (p1->mp_obj->m_pos.x <= p2->mp_obj->m_pos.x) return 1;//x昇順になっていれば
	return 0;//NOT x昇順ならば
}
