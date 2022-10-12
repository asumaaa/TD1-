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

	worldTransformUpdate(&worldTransform_);




}

void Bullet::Update()
{
	Vector3 kBulletSpeed = { 0.0f,0.0f,-0.2f };
	worldTransform_.translation_ += kBulletSpeed;
	worldTransformUpdate(&worldTransform_);

}

void Bullet::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}


