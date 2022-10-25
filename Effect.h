#pragma once
#include "DebugText.h"
#include "Input.h"
#include "ViewProjection.h"
#include <Model.h>
#include <WorldTransform.h>
#include <list>
#include <cassert>
#include"Matrix.h"

const int EFFECT_NUM = 40;

class Effect
{
public:
	void Initialize(Model* model, uint32_t textureHandle, Vector3 vec);
	void Update();
	void Draw(ViewProjection viewProjection);

	bool IsDead() const { return isDead_; }	//死亡時




private:
	//ワールド変換データ

	WorldTransform worldTransform_[EFFECT_NUM];

	//モデル
	Model* model_ = nullptr;

	//その他
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	Vector3 velocity_[EFFECT_NUM] = {};
	Vector3 rotVector_[EFFECT_NUM] = {};

	//デスフラグ
	bool isDead_ = false;
	int daedFlame_ = 0;

};

