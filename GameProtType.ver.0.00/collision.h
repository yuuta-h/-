
#pragma once
#include "main.h"
#include "object.h"


//�I�u�W�F�N�g���m�̓����蔻��(�~*�~)
bool checkHitObjCC(ObjStr* p_obj1, ObjStr* p_obj2);
//�I�u�W�F�N�g���m�̓����蔻��(��`*��`)
bool checkHitObjRR(ObjStr* p_obj1, ObjStr* p_obj2);
//�I�u�W�F�N�g���m�̓����蔻��(�~*��`)
bool checkHitObjCR(ObjStr* p_obj1, ObjStr* p_obj2);

// ��]���Ă����`�̒��_���v�Z
D3DXVECTOR2 computeRotatedBox(ObjStr* p_obj);
