#pragma once
#include "DebugText.h"
#include "Input.h"
#include "ViewProjection.h"
#include <Model.h>
#include <WorldTransform.h>
#include <list>
#include <cassert>
#include"Matrix.h"
#include"Field.h"

class GameScene;

class Bullet
{
public:
	void Initialize(Model* model, uint32_t textureHandle, Vector3 vector3, float kBulSpeed);
	void Update(Vector3 pos);
	void Draw(ViewProjection viewProjection);

	bool IsDead() const { return isDead_; }	//死亡時
	int GetId() { return bulletId_; }
	void SetID(int ID) { bulletId_ = ID; }
	void SetFieldLane(int lane) { fieldLane_ = lane; };
	int GetFieldLane() { return fieldLane_; }
	//弾のイージング
	float easeIn(float x);

	////ワールド座標を取得
	Vector3 GetWorldPosition();

	//衝突を検出したら呼び出されるコールバック関数
	void OnCollision(bool isBreak);

private:
	//ワールド変換データ
	WorldTransform worldTransform_;

	//モデル
	Model* model_ = nullptr;

	//その他
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	//固有ID
	int bulletId_ = 0;

	//デスフラグ
	bool isDead_ = false;

	float depth = 40.0f;	//奥行
	float xDifference = 10.0f;	//左右差

	//ノーツの速度
	float kBulletSpeedZ = 0.4;
	//ノーツの加速度
	float kBulletSpeedAcc = 0.003;

	//現在のレーン
	Lane lane_;

	//フィールド取得用
	int fieldLane_ = 0;

	float kBulSpeed_ = 0;
};