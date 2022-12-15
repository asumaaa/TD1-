#include "Player.h"
#include <cmath>
#include "math.h"
#define PI 3.141592653589

void Player::Initialize(Model* model, uint32_t textureHandle)
{
	// NULL�|�C���^�`�F�b�N
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;

	//�V���O���C���X�^���X���擾����
	input_ = Input::GetInstance();

	//�������W���Z�b�g
	worldTransform_.Initialize();
	worldTransform_.translation_ = { 0,0,-5 };
	worldTransform_.scale_ = { 1,1,1 };
	worldTransform_.rotation_ = { 0,0,0 };

}

void Player::Update(Vector3 pos)
{

	worldTransformUpdate(&worldTransform_);
}

void Player::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

Vector3 Player::GetWorldPosition()
{
	return Vector3();
}

void Player::OnCollision(bool isBreak)
{
}
