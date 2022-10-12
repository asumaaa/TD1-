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
	worldTransform_.Initialize();
	worldTransform_.translation_ = vector3;
	worldTransform_.scale_ = { 1,1,1 };
	worldTransform_.rotation_ = { 0,0,0 };

	//現在のXによってレーンを変更
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
	//キー入力に応じてLaneを変更
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

	//Laneに応じてXを変更
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


