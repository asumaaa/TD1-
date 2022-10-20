#include "Field.h"
#include <cassert>

void Field::Initialize(Model* model, uint32_t textureHandle, Lane lane)
{
	assert(model);

	model_ = model;

	//�V���O���g���C���X�^���X���擾
	input_ = Input::GetInstance();

	//�e�N�X�`���ǂݍ���
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();

	worldTransform_.scale_ = { 0.3f,0.2f,length };

	//x���W�ɉ����Č��݂̃��[���𔻒�
	lane_ = lane;
	if (lane == Left)
	{
		worldTransform_.translation_ = { -laneWidth,0.0f,25.0f };
	}
	else if (lane == Center)
	{
		worldTransform_.translation_ = { 0.0f,0.0f,25.0f };
	}
	else if (lane == Right)
	{
		worldTransform_.translation_ = { laneWidth,0.0f,25.0f };
	}
	worldTransformUpdate(&worldTransform_);
}

void Field::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Field::Update()
{
	//�L�[���͂ɉ�����Lane��ύX
	if (input_->PushKey(DIK_LEFT) && input_->TriggerKey(DIK_SPACE))
	{
		if (lane_ == Left)lane_ = Center;
		else if (lane_ == Center)lane_ = Left;
	}
	if (input_->PushKey(DIK_RIGHT) && input_->TriggerKey(DIK_SPACE))
	{
		if (lane_ == Right)lane_ = Center;
		else if (lane_ == Center)lane_ = Right;
	}

	//Lane�ɉ�����X��ύX
	if (lane_ == Left)
	{
		worldTransform_.translation_ = { -laneWidth,0.0f,25.0f };
	}
	else if (lane_ == Center)
	{
		worldTransform_.translation_ = { 0.0f,0.0f,25.0f };
	}
	else if (lane_ == Right)
	{
		worldTransform_.translation_ = { laneWidth,0.0f,25.0f };
	}
	worldTransformUpdate(&worldTransform_);
}
