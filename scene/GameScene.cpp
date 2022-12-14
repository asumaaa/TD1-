#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include<fstream>

GameScene::GameScene() {}


GameScene::~GameScene()
{
	/*delete model_;
	for (int i = 0; i < 3; i++)
	{
		delete field_;
	}
	delete debugCamera_;
	delete goal_;*/

}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	//モデル生成
	model_ = Model::Create();

	//レールカメラの生成
	RailCamera* newRailCamera = new RailCamera();
	newRailCamera->Initialize();
	railCamera_.reset(newRailCamera);


	testTexture2_ = TextureManager::Load("white.png");
	goal_->Initialize(model_, testTexture2_);

	//テスト用のテクスチャ
	testTexture_ = TextureManager::Load("green.png");
	BulletReset();

	//レーン
	laneTexture_[0] = TextureManager::Load("purple.png");
	laneTexture_[1] = TextureManager::Load("orange.png");
	laneTexture_[2] = TextureManager::Load("yellow.png");
	field_[0].Initialize(model_, laneTexture_[0], Left);
	field_[1].Initialize(model_, laneTexture_[1], Center);
	field_[2].Initialize(model_, laneTexture_[2], Right);

	//スプライト
	uint32_t backTexture = TextureManager::Load("backGround.png");
	spriteBackGround_.reset(
		Sprite::Create(backTexture, Vector2(640, 360), Vector4(1, 1, 1, 1), Vector2(0.5, 0.5)));

	uint32_t startTexture = TextureManager::Load("title.png");
	spriteStart_.reset(
		Sprite::Create(startTexture, Vector2(640, 360), Vector4(1, 1, 1, 1), Vector2(0.5, 0.5)));

	uint32_t setumeiTexture = TextureManager::Load("setumei.png");
	spriteSetumei_.reset(
		Sprite::Create(setumeiTexture, Vector2(640, 360), Vector4(1, 1, 1, 1), Vector2(0.5, 0.5)));

	uint32_t scoreTexture = TextureManager::Load("score.png");
	spriteScore_.reset(
		Sprite::Create(scoreTexture, Vector2(640, 360), Vector4(1, 1, 1, 1), Vector2(0.5, 0.5)));

	for (int i = 0; i < 10; i++) {
		spritePurpleMater_[i].reset(Sprite::Create(laneTexture_[0], Vector2(63 + (22 * i), 71), Vector4(1, 1, 1, 1), Vector2(0.5, 0.5)));
		spriteOrangeMater_[i].reset(Sprite::Create(laneTexture_[1], Vector2(63 + (22 * i), 101), Vector4(1, 1, 1, 1), Vector2(0.5, 0.5)));
		spriteYellowMater_[i].reset(Sprite::Create(laneTexture_[2], Vector2(63 + (22 * i), 131), Vector4(1, 1, 1, 1), Vector2(0.5, 0.5)));
	}

	uint32_t materTexture = TextureManager::Load("mater.png");
	spriteMaterBack_.reset(Sprite::Create(materTexture, Vector2(640, 360), Vector4(1, 1, 1, 1), Vector2(0.5, 0.5)));


	//必殺技用
	deathblowTransform_ = new WorldTransform;
	deathblowTransform_->Initialize();
	deathblowTransform_->scale_ = { 2,0.5,2 };
	isDeathblow_ = false;
	//circle_ = Model::CreateFromOBJ("Skydome", true);
	//ファイルの読み込み
	if (sceneNo_ == SceneNo::Game) {
		LoadBulletPopData();
	}
}

void GameScene::Update() {

	switch (sceneNo_) {
	case SceneNo::Title: //タイトル
		if (input_->TriggerKey(DIK_SPACE) && sceneNo_ == SceneNo::Title) {
			sceneNo_ = SceneNo::Operate;

		}
		break;
	case SceneNo::Operate: //操作説明(チュートリアル)
		if (input_->TriggerKey(DIK_SPACE) && sceneNo_ == SceneNo::Operate) {
			sceneNo_ = SceneNo::Game;
			for (std::unique_ptr<Bullet>& bullet_ : bullets_) {
				bullet_->OnCollision(false);
			}
			BulletReset();
			hit_ = 0;
			gameLevel_ = 0;
			gameTimer_ = 0;
			goal_->bulletHit_[Left] = 0;
			goal_->bulletHit_[Center] = 0;
			goal_->bulletHit_[Right] = 0;
			
		}
		break;

	case SceneNo::Game: //ゲーム
		gameTimer_++;
		if (gameTimer_ > 200) {
			if (gameLevel_ < levelMax_) {
				gameTimer_ = 0;
				gameLevel_++;
			}
			else {
				gameTimer_ = 0;
			}

		}

		//デリート
		bullets_.remove_if([](std::unique_ptr<Bullet>& bullet_) { return bullet_->IsDead(); });
		

		//デバッグカメラアップデート
		debugCamera_->Update();


		//弾発生
		UpdateBulletPopCommands();


		/*for (std::unique_ptr<Bullet>& bullet_ : bullets_) {
			bullet_->Update(field_[bullet_->GetFieldLane()].GetTransration());
		}*/

		

		

#pragma region 必殺技
		if (goal_->bulletHit_[0] >= 7 &&
			goal_->bulletHit_[1] >= 7 &&
			goal_->bulletHit_[2] >= 7) {
			isDeathblow_ = true;
		}
		else if (goal_->bulletHit_[0] <= 0 &&
			goal_->bulletHit_[1] <= 0 &&
			goal_->bulletHit_[2] <= 0) {
			isDeathblow_ = false;
		}
		goal_->MaterDown(isDeathblow_);

		if (isDeathblow_ == true) {
			float powerRadius = 5.0f;
			deathblowRadius += powerRadius;
		}
		else if (isDeathblow_ == false) {
			deathblowRadius = 0;
		}
#pragma endregion 必殺技

		CheckAllCollisions();

		break;

	case SceneNo::Over: //クリア
		if (input_->TriggerKey(DIK_SPACE)&& sceneNo_ == SceneNo::Over) {

			sceneNo_ = SceneNo::Title;
		}
		break;


	}


}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	spriteBackGround_->Draw();
	spriteMaterBack_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	for (int i = 0; i < 3; i++)
	{
		field_[i].Draw(railCamera_->GetViewProjection());
	}

	for (std::unique_ptr<Bullet>& bullet_ : bullets_) {
		bullet_->Draw(railCamera_->GetViewProjection());
	}



	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>


	for (int i = 0; i < 10; i++) {
		if (i + 1 <= goal_->bulletHit_[0]) {
			spritePurpleMater_[i]->Draw();
		}
		if (i + 1 <= goal_->bulletHit_[1]) {
			spriteOrangeMater_[i]->Draw();
		}
		if (i + 1 <= goal_->bulletHit_[2]) {
			spriteYellowMater_[i]->Draw();
		}
	}

	if (sceneNo_ == SceneNo::Title) {
		spriteStart_->Draw();
	}
	else if (sceneNo_ == SceneNo::Operate) {
		spriteSetumei_->Draw();
	}
	else if (sceneNo_ == SceneNo::Over) {
		spriteScore_->Draw();
		debugText_->SetPos(630.0f, 340.0f);
		debugText_->SetScale(5.0f);
		debugText_->Printf("%d/200", hit_);

		if (hit_ > 179) {
			debugText_->SetPos(420.0f, 100.0f);
			debugText_->SetScale(5.0f);
			debugText_->Printf("rank S");
		}
		else if (hit_ > 135) {
			debugText_->SetPos(420.0f, 100.0f);
			debugText_->SetScale(5.0f);
			debugText_->Printf("rank A");
		}
		else if (hit_ > 80) {
			debugText_->SetPos(420.0f, 100.0f);
			debugText_->SetScale(5.0f);
			debugText_->Printf("rank B");
		}
		else if(hit_ > 40) {
			debugText_->SetPos(420.0f, 100.0f);
			debugText_->SetScale(5.0f);
			debugText_->Printf("rank C");
		}
		else {
			debugText_->SetPos(420.0f, 100.0f);
			debugText_->SetScale(5.0f);
			debugText_->Printf("rank D");
		}



	}

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::AddBullet(std::unique_ptr<Bullet>& Bullet)
{
}

void GameScene::GenerBullet(Vector3 BulletPos, int ID, int lane)
{
	//生成
	std::unique_ptr<Bullet> newBullet = std::make_unique<Bullet>();
	//敵キャラの初期化
	float kBulSpeed = 0.4f;
	if (gameLevel_ > 0) {
		kBulSpeed += gameLevel_ * 0.1f + 1.0f;	//レベルが上がると弾が加速
	}

	if (lane == 0) {
		newBullet->Initialize(model_, laneTexture_[0], BulletPos, kBulSpeed);
	}
	else if (lane == 1) {
		newBullet->Initialize(model_, laneTexture_[1], BulletPos, kBulSpeed);
	}
	else if (lane == 2) {
		newBullet->Initialize(model_, laneTexture_[2], BulletPos, kBulSpeed);
	}

	newBullet->SetID(ID);
	//newBullet->SetFieldLane(lane);

	//リストに登録する
	bullets_.push_back(std::move(newBullet));

}

//void GameScene::GenerEffect(Vector3 pos, int lane)
//{
//	//生成
//	std::unique_ptr<Effect> newEffect = std::make_unique<Effect>();
//	//敵キャラの初期化
//	int maxHitCount = 14;
//	if (lane == Left) {
//		newEffect->Initialize(model_, laneTexture_[Left], pos);
//		if (goal_->bulletHit_[Left] <= maxHitCount && isDeathblow_ == false) {
//			goal_->bulletHit_[Left]++;	//グローバル変数です。ごめんなさい。by細井
//		}
//	}
//	else if (lane == Center) {
//		newEffect->Initialize(model_, laneTexture_[Center], pos);
//		if (goal_->bulletHit_[Center] <= maxHitCount && isDeathblow_ == false) {
//			goal_->bulletHit_[Center]++;
//		}
//	}
//	else if (lane == Right) {
//		newEffect->Initialize(model_, laneTexture_[Right], pos);
//		if (goal_->bulletHit_[Right] <= maxHitCount && isDeathblow_ == false) {
//			goal_->bulletHit_[Right]++;
//		}
//	}
//
//	//リストに登録する
//	effects_.push_back(std::move(newEffect));
//
//}



void GameScene::LoadBulletPopData()
{
	//ファイルを開く
	std::ifstream file;
	file.open("Resources/enemyPop2.csv");

	assert(file.is_open());

	//ファイルの内容を文字列ストリームにコピー
	bulletPopCommands_ << file.rdbuf();

	//ファイルを閉じる
	file.close();
}

void GameScene::UpdateBulletPopCommands()
{
	//待機処理
	if (isStand_) {
		standTime_--;
		if (standTime_ <= 0) {
			//待機完了
			isStand_ = false;
		}
		return;
	}
	// 1行分の文字列を入れる変数
	std::string line;

	//コマンド実行ループ
	while (getline(bulletPopCommands_, line)) {
		// 1行分の文字数をストリームに変換して解折しやすくなる
		std::istringstream line_stream(line);

		std::string word;
		//,区切りで行の先頭文字を取得
		getline(line_stream, word, ',');

		//"//"から始まる行はコメント
		if (word.find("//") == 0) {
			//コメント行を飛ばす
			continue;
		}
		// POPコマンド
		if (word.find("POP") == 0) {

			//レーン
			std::getline(line_stream, word, ',');
			int lane = static_cast<int>(std::atof(word.c_str()));

			// ID
			std::getline(line_stream, word, ',');
			int ID = static_cast<int>(std::atof(word.c_str()));

			float depth = 200.0f;	//奥行
			float xDifference = 10.0f;	//左右差



			if (lane == 1) {
				for (int i = 0; i < 3; i++) {
					if (field_[i].GetLane() == 0) {
						popLane_ = i;
						break;
					}
				}
				GenerBullet(Vector3(-xDifference, 0, depth), ID, popLane_);

			}
			else if (lane == 2) {
				for (int i = 0; i < 3; i++) {
					if (field_[i].GetLane() == 1) {
						popLane_ = i;
						break;
					}
				}
				GenerBullet(Vector3(0, 0, depth), ID, popLane_);
			}
			else if (lane == 3) {
				for (int i = 0; i < 3; i++) {
					if (field_[i].GetLane() == 2) {
						popLane_ = i;
						break;
					}
				}
				GenerBullet(Vector3(xDifference, 0, depth), ID, popLane_);
			}
			else {


			}
		}
		// WAITコマンド
		else if (word.find("WAIT") == 0) {
			std::getline(line_stream, word, ',');

			//待ち時間
			int32_t waitTime = std::atoi(word.c_str());

			//待機開始
			isStand_ = true;
			int maxTimeDiv = 10;
			if (gameLevel_ <= 0) {
				standTime_ = waitTime * (maxTimeDiv - gameLevel_) / maxTimeDiv;
			}
			else {

				standTime_ = waitTime * (maxTimeDiv - gameLevel_) / maxTimeDiv;
			}

			//抜ける
			break;
		}
		else if (word.find("OVER") == 0) {
			sceneNo_ = SceneNo::Over;
			break;
			
		}
	}
}

void GameScene::BulletReset()
{
	bulletPopCommands_.str("");
	bulletPopCommands_.clear(std::stringstream::goodbit);
	LoadBulletPopData();
}


void GameScene::CheckAllCollisions() {

	//判定対象AとBの座標
	Vector3 posA, posB;



#pragma region 自弾と敵キャラの当たり判定
	//敵キャラの座標
	for (std::unique_ptr<Bullet>& bullet_ : bullets_) {
		posA = bullet_->GetWorldPosition();


		//自弾の座標
		posB = goal_->GetWorldPosition();

		float x = posB.x - posA.x;
		float y = posB.y - posA.y;
		float z = posB.z - posA.z;

		float cd = sqrt(x * x + y * y + z * z);

		if (cd <= 4.0f) {
			//敵キャラの衝突時コールバックを呼び出す
			bullet_->OnCollision(true);
			//GenerEffect(bullet_->GetWorldPosition(), bullet_->GetFieldLane());

			//衝突時コールバックを呼び出す
			//goal_->OnCollision();
			hit_++;
		}


		if (cd <= deathblowRadius) {
			//敵キャラの衝突時コールバックを呼び出す
			bullet_->OnCollision(true);
			//GenerEffect(bullet_->GetWorldPosition(), bullet_->GetFieldLane());
			hit_++;
			//衝突時コールバックを呼び出す
			//goal_->OnCollision();
		}

		if (posA.z < -50/*画面外*/) {
			bullet_->OnCollision(false);
			
		}



	}
}
