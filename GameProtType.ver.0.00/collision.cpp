#include "collision.h"

//�I�u�W�F�N�g���m�̓����蔻��(�~*�~)
bool checkHitObjCC(ObjStr* p_obj1, ObjStr* p_obj2){
	//����A�I�u�W�F�N�g��m_pos�͍���̍��W�Ȃ̂ŁA�܂����S���o��
	D3DXVECTOR2 pos1 = { (p_obj1->m_pos.x + p_obj1->m_rect.x / 2),(p_obj1->m_pos.y + p_obj1->m_rect.y / 2) };
	D3DXVECTOR2 pos2 = { (p_obj2->m_pos.x + p_obj2->m_rect.x / 2),(p_obj2->m_pos.y + p_obj2->m_rect.y / 2) };

	if (((pos1.x - pos2.x)*(pos1.x - pos2.x)) + ((pos1.y - pos2.y)*(pos1.y - pos2.y))
		<= ((p_obj1->m_rad + p_obj2->m_rad) * (p_obj1->m_rad + p_obj2->m_rad))){
		return true;
	}

	return false;
};

//�I�u�W�F�N�g���m�̓����蔻��(��`*��`)
bool checkHitObjRR(ObjStr* p_obj1, ObjStr* p_obj2) {

	if (((p_obj1->m_pos.x > p_obj2->m_pos.x && p_obj1->m_pos.x < p_obj2->m_pos.x + p_obj2->m_rect.x) ||
		(p_obj2->m_pos.x > p_obj1->m_pos.x && p_obj2->m_pos.x < p_obj1->m_pos.x + p_obj1->m_rect.x)) &&
		((p_obj1->m_pos.y > p_obj2->m_pos.y && p_obj1->m_pos.y < p_obj2->m_pos.y + p_obj2->m_rect.y) ||
		(p_obj2->m_pos.y > p_obj1->m_pos.y && p_obj2->m_pos.y < p_obj1->m_pos.y + p_obj1->m_rect.y))){
		return true;
	}
	else{
		return false;
	}

};

//�I�u�W�F�N�g���m�̓����蔻��(�~*��`)
bool checkHitObjCR(ObjStr* p_obj1, ObjStr* p_obj2) {
	//����A�I�u�W�F�N�g��m_pos�͍���̍��W�Ȃ̂ŁA�܂����S���o��
	D3DXVECTOR2 pos1 = { (p_obj1->m_pos.x + p_obj1->m_rect.x / 2),(p_obj1->m_pos.y + p_obj1->m_rect.y / 2) };

	//�~�̒��S�_�����`�̂P�ԋ߂�X���W
	D3DXVECTOR2 pos;
	if (pos1.x < p_obj1->m_pos.x){
		pos.x = p_obj1->m_pos.x;
	}
	else if (pos1.x > p_obj1->m_pos.x + p_obj1->m_rect.x) {
		pos.x = p_obj1->m_pos.x + p_obj1->m_rect.x;
	}
	else {
		pos.x = pos1.x;
	}
	//�~�̒��S�_�����`�̂P�ԋ߂�Y���W
	if (pos1.y < p_obj1->m_pos.y) {
		pos.y = p_obj1->m_pos.y;
	}
	else if (pos1.y > p_obj1->m_pos.y + p_obj1->m_rect.y) {
		pos.y = p_obj1->m_pos.y + p_obj1->m_rect.y;
	}
	else {
		pos.x = pos1.y;
	}

	//��������ɏՓ˔���
	float distance[2] = {fabsf(pos1.x - pos.x),fabsf(pos1.y - pos.y)};
	float dis = sqrtf((distance[0]* distance[0])+(distance[1]*distance[1]));
	if (dis < p_obj1->m_rad){
		return true;
	}
	return false;

};
