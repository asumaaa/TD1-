#include "Bullet.h"
#include <cmath>
#include "math.h"
#define PI 3.141592653589

void Bullet::Initialize(Model* model, uint32_t textureHandle, Vector3 vector3, float kBulSpeed)
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

void Bullet::Update(Vector3 pos)
{
	
	////キー入力に応じてLaneを変更
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

	////Laneに応じてXを変更
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

	//ノーツの速度の処理
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
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//ワールド行列の平行移動成分
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Bullet::OnCollision()
{
	isDead_ = true;
}

