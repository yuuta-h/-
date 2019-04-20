#pragma once

#include <algorithm>
//============================================================
//	�g�p��
//	Timer timer_(limitTime); // �������Ԃ�ݒ�
//	timer_.update(deltaTime); // �o�ߎ��Ԃ�ǉ����čX�V
//	if (timer_.isTimeout()) { // �^�C���A�E�g���������m�F����
//		// ��莞�Ԃ��Ƃ̏���
//		�c�ȗ�
//		timer_.reset(); // �^�C�}�[�����Z�b�g����
//	}
//============================================================

class Timer
{
public:
	// �R���X�g���N�^
	Timer() {};
	Timer(float limitTime) : time_(0), limitTime_(limitTime) {}

	// �X�V
	void update(float deltaTime);

	// ���Z�b�g
	void reset();

	// �^�C���A�E�g���H
	bool isTimeout() const;

	// ���݂̌o�ߎ��Ԃ��擾
	float getTime() { return time_; };

	// ���~�b�g���Ԃ��擾
	float getLimitTime() { return limitTime_; };

	// ���~�b�g���Ԃɑ΂���o�ߎ��Ԃ̊���
	float getRatioTime() { return time_ / limitTime_; };

private:
	float time_;		// ���݂̎���
	float limitTime_;	// ��������
};