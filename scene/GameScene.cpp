#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include<fstream>

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
	//モデル生成
	model_ = Model::Create();
	for (int i = 0; i < 3; i++)
	{
		worldTransform_[i].Initialize();
		worldTransformUpdate(&worldTransform_[i]);
	}

	//テスト用のテクスチャ
	testTexture_ = TextureManager::Load("white.png");
	BulletReset();
}

void GameScene::Update(){
	debugCamera_->Update();
	worldTransform_[0].scale_ = { 0.5f,0.5f,40.0f };
	worldTransform_[0].translation_ = { -10.0f,0.0f,0.0f };
	worldTransform_[1].scale_ = { 0.5f,0.5f,40.0f };
	worldTransform_[1].translation_ = { 0.0f,0.0f,0.0f };
	worldTransform_[2].scale_ = { 0.5f,0.5f,40.0f };
	worldTransform_[2].translation_ = { 10.0f,0.0f,0.0f };
	for (int i = 0; i < 3; i++)
	{
		worldTransformUpdate(&worldTransform_[i]);
	}
	
	//弾発生
	UpdateBulletPopCommands();

	for (std::unique_ptr<Bullet>& bullet_ : bullets_) {	

		bullet_->Update();

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
		model_->Draw(worldTransform_[i], debugCamera_->GetViewProjection());
	}

	for (std::unique_ptr<Bullet>& bullet_ : bullets_) {
		bullet_->Draw(debugCamera_->GetViewProjection());
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

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::AddBullet(std::unique_ptr<Bullet>& Bullet)
{
	bullets_.push_back(std::move(Bullet));
}

void GameScene::GenerBullet(Vector3 BulletPos, int ID)
{
	//生成
	std::unique_ptr<Bullet> newBullet = std::make_unique<Bullet>();
	//敵キャラの初期化
	newBullet->Initialize(model_, testTexture_, BulletPos);

	newBullet->SetID(ID);

	//リストに登録する
	bullets_.push_back(std::move(newBullet));

}

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
			//// X座標
			//std::getline(line_stream, word, ',');
			//float x = static_cast<float>(std::atof(word.c_str()));

			//// Y座標
			//std::getline(line_stream, word, ',');
			//float y = static_cast<float>(std::atof(word.c_str()));

			//// Z座標
			//std::getline(line_stream, word, ',');
			//float z = static_cast<float>(std::atof(word.c_str()));

			//レーン
			std::getline(line_stream, word, ',');
			int lane = static_cast<int>(std::atof(word.c_str()));

			// ID
			std::getline(line_stream, word, ',');
			int ID = static_cast<int>(std::atof(word.c_str()));

			float depth = 10.0f;	//奥行
			float xDifference = 10.0f;	//左右差
			if (lane == 1) {
				GenerBullet(Vector3(-xDifference, 0, depth), ID);
			}else if (lane == 2) {
				GenerBullet(Vector3(0, 0, depth), ID);
			}else if (lane == 3) {
				GenerBullet(Vector3(xDifference, 0, depth), ID);
			}else {
				GenerBullet(Vector3(0, 3.0f, depth), ID);
			}
		}
		// WAITコマンド
		else if (word.find("WAIT") == 0) {
			std::getline(line_stream, word, ',');

			//待ち時間
			int32_t waitTime = std::atoi(word.c_str());

			//待機開始
			isStand_ = true;
			standTime_ = waitTime;

			//抜ける
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


