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


typedef struct linePos {
	Vector3 startPos;
	Vector3 endPos;
};

class Player
{
public:
	void Initialize(Model* model, uint32_t textureHandle);
	void Update(Vector3 pos);
	void Draw(ViewProjection viewProjection);

	bool IsDead() const { return isDead_; }	//���S��

	////���[���h���W���擾
	Vector3 GetWorldPosition();

	//�Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollision(bool isBreak);

private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	//���f��
	Model* model_ = nullptr;

	//���̑�
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	std::vector<linePos> lineList_;//���C���n�_�I�_�ۑ��p

	Vector3 nowPos = {};

	
	//�f�X�t���O
	bool isDead_ = false;

	


};

