#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Model.h"

class Goal
{
public:
	/// <summary>
	/// 初期化,更新,描画
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection viewProjection);

	Vector3 GetWorldPosition();	//ワールド座標取得
	
	void OnCollision();	//触れたとき
	void MaterDown(bool isMaterDown);
	
	int bulletHit_[3] = {};
private:
	WorldTransform worldTransform_[4];
	Model* model_ = nullptr;

	float modelVelocityAngle_ = 0; //digrees

	uint32_t textureHandle_ = 0;

	int materDownTime_ = 0;//メーターダウンのディレイカウント
	
};


