#include "Bullet.h"
#include <cmath>
#include "math.h"
#define PI 3.141592653589

void Bullet::Initialize(Model* model, uint32_t textureHandle, Vector3 vector3, float kBulSpeed)
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

void Bullet::Update(Vector3 pos)
{
	
	////�L�[���͂ɉ�����Lane��ύX
	//if (input_->PushKey(DIK_LEFT) && input_->TriggerKey(DIK_SPACE))
	//{
	//	if (lane_ == Left)lane_ = Center;
	//	else if (lane_ == Center)lane_ = Left;
	//}
	//if (input_->PushKey(DIK_RIGHT) && input_->TriggerKey(DIK_SPACE))
	//{
	//	if (lane_ == Right)lane_ = Center;
	//	else if (lane_ == Center)lane_ = Right;
	//}

	////Lane�ɉ�����X��ύX
	//if (lane_ == Left)
	//{
	//	worldTransform_.translation_.x = -xDifference;
	//}
	//else if (lane_ == Center)
	//{
	//	worldTransform_.translation_.x = 0;
	//}
	//else if (lane_ == Right)
	//{
	//	worldTransform_.translation_.x = xDifference;
	//}
	worldTransform_.translation_.x = pos.x;
	worldTransform_.translation_.y = pos.y;

	worldTransformUpdate(&worldTransform_);

	//�m�[�c�̑��x�̏���
	kBulletSpeedZ += kBulletSpeedAcc;
	Vector3 kBulletSpeed = { 0.0f,0.0f,-easeIn(kBulletSpeedZ)};
	worldTransform_.translation_ += kBulletSpeed;
	worldTransformUpdate(&worldTransform_);

}

void Bullet::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

float Bullet::easeIn(float x)
{
	return 1 - cos((x * PI) / 2);
}

Vector3 Bullet::GetWorldPosition()
{
	//���[���h���W������ϐ�
	Vector3 worldPos;
	//���[���h�s��̕��s�ړ�����
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Bullet::OnCollision()
{
	isDead_ = true;
}

