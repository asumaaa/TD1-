#pragma once
#pragma once
#include "DebugText.h"
#include "Input.h"
#include "ViewProjection.h"
#include <Model.h>
#include <WorldTransform.h>
#include<cassert>
#include"Matrix.h"
#include"stdlib.h"
#include"list"

//�O���錾



typedef struct Line {
	WorldTransform worldTransform;
	bool isDraw;
	
};

class Player
{
public:
	void Initialize(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection viewProjection);

	bool IsDead() const { return isDead_; }	//���S��

	////���[���h���W���擾
	Vector3 GetWorldPosition();

	//�Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollision(bool isBreak);

public:
	

private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	//���f��
	Model* model_ = nullptr;

	//���̑�
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	
	//�ߋ��̃��C��
	WorldTransform lineWorldTransform_[10];
	Line line_[10];
	int nextLine_ = 0;

	//���ݒn���C��
	Vector3 nowStartPos = {};	//���݂̃��C���ۑ��p
	Vector3 nowEndPos{};	//
	WorldTransform nowLineWorldTransform_;


	Vector3 pVelocity_ = {};

	
	//�f�X�t���O
	bool isDead_ = false;

	int maxFlameCount_;	//�v���C���[���Ȃ���܂ł̋���
	int nowFlameCount_;

	

};

