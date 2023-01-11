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
	Vector2 sLineVec2;	//�n�_
	Vector2 eLineVec2;	//�I�_
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
	void SetAtkColide(Vector2 minVec2);

	//�Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollision(bool isBreak);

public://�v�Z
	bool LineColide(Vector2 line_abStart, Vector2 line_abEnd, Vector2 line_cdStart, Vector2 line_cdEnd);


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
	Line line_[100];

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

	//�U��
	bool isAtk = false;
	Vector2 minVec2;
	Vector2 maxVec2;
	

};