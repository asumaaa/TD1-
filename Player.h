#pragma once
#pragma once
#include "DebugText.h"
#include "Input.h"
#include "ViewProjection.h"
#include <Model.h>
#include <WorldTransform.h>
#include<cassert>
#include"Matrix.h"
#include"stdlib.h"
#include"list"


typedef struct linePos {
	Vector3 startPos;
	Vector3 endPos;
};

class Player
{
public:
	void Initialize(Model* model, uint32_t textureHandle);
	void Update(Vector3 pos);
	void Draw(ViewProjection viewProjection);

	bool IsDead() const { return isDead_; }	//死亡時

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

	std::vector<linePos> lineList_;//ライン始点終点保存用

	Vector3 nowPos = {};

	
	//デスフラグ
	bool isDead_ = false;

	


};

