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

//前方宣言



typedef struct Line {
	Vector2 sLineVec2;	//始点
	Vector2 eLineVec2;	//終点
	WorldTransform worldTransform;
	bool isDraw;

};

class Player
{
public:
	void Initialize(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection viewProjection);

	bool IsDead() const { return isDead_; }	//死亡時

	////ワールド座標を取得
	Vector3 GetWorldPosition();
	void SetAtkColide(Vector2 minVec2);

	//衝突を検出したら呼び出されるコールバック関数
	void OnCollision(bool isBreak);

public://計算
	bool LineColide(Vector2 line_abStart, Vector2 line_abEnd, Vector2 line_cdStart, Vector2 line_cdEnd);


private:
	//ワールド変換データ
	WorldTransform worldTransform_;

	//モデル
	Model* model_ = nullptr;

	//その他
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	//過去のライン
	WorldTransform lineWorldTransform_[10];
	Line line_[100];

	int nextLine_ = 0;

	//現在地ライン
	Vector3 nowStartPos = {};	//現在のライン保存用
	Vector3 nowEndPos{};	//
	WorldTransform nowLineWorldTransform_;

	Vector3 pVelocity_ = {};


	//デスフラグ
	bool isDead_ = false;

	int maxFlameCount_;	//プレイヤーが曲がるまでの挙動
	int nowFlameCount_;

	//攻撃
	bool isAtk = false;
	Vector2 minVec2;
	Vector2 maxVec2;
	

};