#pragma once
#include "DebugText.h"
#include "Input.h"
#include "ViewProjection.h"
#include <Model.h>
#include <WorldTransform.h>
#include <list>
#include <cassert>

class GameScene;

class Bullet
{
public:
	void Initialize(Model* model, uint32_t textureHandle, Vector3 vector3);
	void Update();
	void Draw(ViewProjection viewProjection);
	
	bool IsDead() const { return isDead_; }	//死亡時
	int GetId() { return bulletId_; }	
	void SetID(int ID) { bulletId_ = ID; }	

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


};

