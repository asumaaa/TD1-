#include "Enemy.h"
#include <cmath>
#include "math.h"
#define PI 3.141592653589

void Enemy::Initialize(Model* model, uint32_t textureHandle, Vector3 vector3, float kBulSpeed)
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



	kEnemySpeedZ = kBulSpeed;
}

void Enemy::Update()
{

	worldTransformUpdate(&worldTransform_);

	//ノーツの速度の処理
	kEnemySpeedZ += kEnemySpeedAcc;
	Vector3 kEnemySpeed = { 0.0f,0.0f,-1.0f };
	worldTransform_.translation_ += kEnemySpeed;
	worldTransformUpdate(&worldTransform_);

}

void Enemy::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

float Enemy::easeIn(float x)
{
	return 1 - cos((x * PI) / 2);
}

Vector3 Enemy::GetWorldPosition()
{
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//ワールド行列の平行移動成分
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Enemy::OnCollision(bool isBreak)
{
	isDead_ = true;
}

void Enemy::SetPlayer(Player* player) {
	player_ = player;
}