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
	worldTransform_.translation_ = vector3;
	worldTransform_.scale_ = { 2,2,2 };


}

void Bullet::Update()
{

}

void Bullet::Draw(ViewProjection viewProjection)
{

}


