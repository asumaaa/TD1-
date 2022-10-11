#include "Bullet.h"
#include <cmath>

void Bullet::Initialize(Model* model, uint32_t textureHandle, Vector3 vector3)
{
	// NULLポインタチェック
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;

	//シングルインスタンスを取得する
	input_ = Input::GetInstance();

	//初期座標をセット
	worldTransform_.translation_ = vector3;
	worldTransform_.scale_ = { 2,2,2 };


}

void Bullet::Update()
{

}

void Bullet::Draw(ViewProjection viewProjection)
{

}


