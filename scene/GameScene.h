#pragma once
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
#include "Enemy.h"
#include "sstream"
#include"Player.h"


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

	//敵リストを取得
	std::list<std::unique_ptr<Enemy>> enemys_;
	const std::list<std::unique_ptr<Enemy>>& GetEnemys() { return enemys_; }

	

	//敵を足す
	void AddEnemy(std::unique_ptr<Enemy>& Enemy);
	void GenerEnemy(Vector3 EnemyPos, int ID, int lane);



	/// <summary>
	/// 敵発生データ読み込み
	/// </summary>
	void LoadEnemyPopData();
	void EnemyReset();
	void UpdateEnemyPopCommands();

	//当たり判定
	void CheckAllCollisions();

	int gameLevel_ = 0;
	const int levelMax_ = 8;

	//シーン切り替え
	enum class SceneNo {
		Title, //タイトル
		Operate, //操作説明(チュートリアル)
		Game,  //射撃
		Over   //ゲメオーバー
	};

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
	int popLane_ = 0;



	ViewProjection viewProjection_;



	//レールカメラ
	std::unique_ptr<RailCamera>railCamera_;

	//csv
	std::stringstream enemyPopCommands_;

	//テクスチャ
	uint32_t testTexture_ = 0;
	uint32_t testTexture2_ = 0;
	//スプライト
	std::unique_ptr<Sprite> spriteBackGround_;	//背景
	std::unique_ptr<Sprite> spriteOrangeMater_[10];//メーター
	std::unique_ptr<Sprite> spritePurpleMater_[10];//
	std::unique_ptr<Sprite> spriteYellowMater_[10];//
	std::unique_ptr<Sprite> spriteMaterBack_;
	std::unique_ptr<Sprite> spriteStart_;
	std::unique_ptr<Sprite> spriteSetumei_;
	std::unique_ptr<Sprite> spriteScore_;

	//レーンデバッグ用のテクスチャ
	uint32_t laneTexture_[3];

	//待機中フラグ
	bool isStand_ = false;
	//待機タイマー
	int standTime_ = 0;
	int gameTimer_ = 0;

	//必殺技モデル用<-必殺技全般はゲームシーン直下です。ごめんなさい。
	WorldTransform* deathblowTransform_ = nullptr;
	bool isDeathblow_ = false;
	Model* circle_ = nullptr;
	float deathblowRadius = 0.0f;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	SceneNo sceneNo_ = SceneNo::Title;

	//スコア
	int hit_ = 0;
};
