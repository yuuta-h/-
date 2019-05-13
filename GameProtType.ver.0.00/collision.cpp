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

// ��]���Ă����`�̒��_���v�Z
D3DXVECTOR2 computeRotatedBox(ObjStr* p_obj)
{
	// ����A�I�u�W�F�N�g��m_pos�͍���̍��W�Ȃ̂ŁA���S���o��
	D3DXVECTOR2 center = { (p_obj->m_pos.x + p_obj->m_rect.x / 2),(p_obj->m_pos.y + p_obj->m_rect.y / 2) };

	// center�𒆐S�Ƃ������[�J�����W��p���āA��]��̍��W�����߂�
	p_obj->m_corner[0].x = center.x + ((p_obj->m_pos.x - center.x) * cos(p_obj->m_rot) - (p_obj->m_pos.y - center.y) * sin(p_obj->m_rot));
	p_obj->m_corner[0].y = center.y + ((p_obj->m_pos.x - center.x) * sin(p_obj->m_rot) + (p_obj->m_pos.y - center.y) * cos(p_obj->m_rot));

	p_obj->m_corner[1].x = center.x + ((p_obj->m_pos.x + p_obj->m_rect.x - center.x) * cos(p_obj->m_rot) - (p_obj->m_pos.y - center.y) * sin(p_obj->m_rot));
	p_obj->m_corner[1].y = center.y + ((p_obj->m_pos.x + p_obj->m_rect.x - center.x) * sin(p_obj->m_rot) + (p_obj->m_pos.y - center.y) * cos(p_obj->m_rot));

	p_obj->m_corner[2].x = center.x + ((p_obj->m_pos.x - center.x) * cos(p_obj->m_rot) - (p_obj->m_pos.y + p_obj->m_rect.y - center.y) * sin(p_obj->m_rot));
	p_obj->m_corner[2].y = center.y + ((p_obj->m_pos.x - center.x) * sin(p_obj->m_rot) + (p_obj->m_pos.y + p_obj->m_rect.y - center.y) * cos(p_obj->m_rot));

	p_obj->m_corner[3].x = center.x + ((p_obj->m_pos.x + p_obj->m_rect.x - center.x) * cos(p_obj->m_rot) - (p_obj->m_pos.y + p_obj->m_rect.y - center.y) * sin(p_obj->m_rot));
	p_obj->m_corner[3].y = center.y + ((p_obj->m_pos.x + p_obj->m_rect.x - center.x) * sin(p_obj->m_rot) + (p_obj->m_pos.y + p_obj->m_rect.y - center.y) * cos(p_obj->m_rot));

	return center;
}

//computeRotateBox�����ɉ�]���Ă����̋�`�̓����蔻������
/**
bool checkHitRotateObjRR(ObjStr* p_obj1, ObjStr* p_obj2) {
	//2�̃I�u�W�F�N�g��m_corner���X�V����
	computeRotatedBox(p_obj1);
	computeRotatedBox(p_obj2);


}
**/