﻿#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include "memory"
#include "list"
#include "Skydome.h"
#include "RailCamera.h"
#include "Bullet.h"
#include "sstream"
#include "Field.h"
#include "Goal.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	//弾リストを取得
	std::list<std::unique_ptr<Bullet>> bullets_;
	const std::list<std::unique_ptr<Bullet>>& GetBullets() { return bullets_; }

	//弾を足す
	void AddBullet(std::unique_ptr<Bullet>& Bullet);
	void GenerBullet(Vector3 BulletPos, int ID);
	
	/// <summary>
	/// 敵発生データ読み込み
	/// </summary>
	void LoadBulletPopData();
	void BulletReset();
	void UpdateBulletPopCommands();

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	//デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;

	//3Dモデル
	Model* model_;
	
	//レーン
	Field field_[3];

	//ゴール用
	Goal* goal_ = nullptr;

	ViewProjection viewProjection_;

	//レールカメラ
	std::unique_ptr<RailCamera>railCamera_;

	//csv
	std::stringstream bulletPopCommands_;

	//テクスチャ
	uint32_t testTexture_ = 0;


	//待機中フラグ
	bool isStand_ = false;
	//待機タイマー
	int standTime_ = 0;

	
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
