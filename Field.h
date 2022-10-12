#pragma once
#include "WorldTransform.h"
#include "Vector3.h"
#include "Matrix.h"
#include "ViewProjection.h"
#include "memory"
#include "Model.h"
#include "Input.h"

//レーンの列挙型
	enum Lane
	{
		Left,
		Center,
		Right
	};

class Field
{
public:
	void Initialize(Model* model, uint32_t textureHandle, Lane lane);	//レーンのX座標を決めて初期化
	void Draw(ViewProjection viewProjection);
	void Update();
	//ゲッター
	Vector3 GetTransration() { return worldTransform_.translation_; };
private:

	Input* input_ = nullptr;
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	float length = 60.0f;	//レーンの長さ

	//現在のレーン
	Lane lane_;

	//レーンの幅
	float laneWidth = 10.0f;
};

