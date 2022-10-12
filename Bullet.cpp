#include "Bullet.h"
#include <cmath>

void Bullet::Initialize(Model* model, uint32_t textureHandle, Vector3 vector3)
{
	// NULL�|�C���^�`�F�b�N
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;

	//�V���O���C���X�^���X���擾����
	input_ = Input::GetInstance();

	//�������W���Z�b�g
	worldTransform_.Initialize();
	worldTransform_.translation_ = vector3;
	worldTransform_.scale_ = { 1,1,1 };
	worldTransform_.rotation_ = { 0,0,0 };

	//���݂�X�ɂ���ă��[����ύX
	if (worldTransform_.translation_.x < 0)
	{
		lane_ = Left;
	}
	else if (worldTransform_.translation_.x == 0)
	{
		lane_ = Center;
	}
	else if (worldTransform_.translation_.x > 0)
	{
		lane_ = Right;
	}

}

void Bullet::Update()
{
	//�L�[���͂ɉ�����Lane��ύX
	if (input_->TriggerKey(DIK_LEFT))
	{
		if (lane_ == Left)lane_ = Center;
		else if (lane_ == Center)lane_ = Left;
	}
	if (input_->TriggerKey(DIK_RIGHT))
	{
		if (lane_ == Right)lane_ = Center;
		else if (lane_ == Center)lane_ = Right;
	}

	//Lane�ɉ�����X��ύX
	if (lane_ == Left)
	{
		worldTransform_.translation_.x = -xDifference;
	}
	else if (lane_ == Center)
	{
		worldTransform_.translation_.x = 0;
	}
	else if (lane_ == Right)
	{
		worldTransform_.translation_.x = xDifference;
	}
	worldTransformUpdate(&worldTransform_);

	worldTransform_.translation_ += kBulletSpeed;
	worldTransformUpdate(&worldTransform_);

}

void Bullet::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}


