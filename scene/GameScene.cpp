#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

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
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
