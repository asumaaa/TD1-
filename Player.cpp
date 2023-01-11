#include "Player.h"
#include <cmath>
#include "math.h"
#define PI 3.141592653589

void Player::Initialize(Model* model, uint32_t textureHandle)
{
	// NULLポインタチェック
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;

	//シングルインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = debugText_->GetInstance();

	//初期座標をセット
	worldTransform_.Initialize();
	worldTransform_.translation_ = { -5,0,0 };
	worldTransform_.scale_ = { 1,1,1 };
	worldTransform_.rotation_ = { 0,0.5 * PI,0 };
	pVelocity_ = { 0,0,0.4f };	//プレイヤーの移動量
	
	nowLineWorldTransform_.Initialize();	//自機の位置

	//自機旋回フレームカウント
	maxFlameCount_ = 70;
	nowFlameCount_ = 0;

	for (int i = 0; i < _countof(line_); i++) {
		line_[i].worldTransform.Initialize();
		line_[i].sLineVec2 = {};
		line_[i].eLineVec2 = {};
		line_[i].isDraw = false;
		line_[i].worldTransform.translation_.x += i * 2;
		worldTransformUpdate(&line_[i].worldTransform);

	}

	nextLine_ = 0;
	worldTransformUpdate(&worldTransform_);

}

void Player::Update()
{
#pragma region	アクセル
	if (input_->PushKey(DIK_LEFT)) {
		if (maxFlameCount_ > 10) {
			maxFlameCount_--;
		}
	}
	else if (input_->PushKey(DIK_RIGHT)) {
		if (maxFlameCount_ < 100) {
			maxFlameCount_++;
		}
	}
#pragma endregion

#pragma region 自機とライン保存
	nowEndPos = worldTransform_.translation_;//ライン用の終点(毎フレーム更新)

	//lineのトランスフォーム計算
	nowLineWorldTransform_.translation_ =	//始点終点の中心が座標
	{ (nowStartPos.x + nowEndPos.x) / 2,
		(nowStartPos.y + nowEndPos.y) / 2,
		(nowStartPos.z + nowEndPos.z) / 2
	};	//kmtEngineのオペレータがlib化されていていじれない

	float len = sqrtf(pow(nowEndPos.x - nowStartPos.x, 2) +
		pow(nowEndPos.y - nowStartPos.y, 2) +
		pow(nowEndPos.z - nowStartPos.z, 2));

	nowLineWorldTransform_.scale_ = { 0.3,0.3,
		len / 2
	};

	nowLineWorldTransform_.rotation_ = worldTransform_.rotation_;


	Vector3 vel = bVelocity(pVelocity_, worldTransform_);

	worldTransform_.translation_ += vel;

	nowFlameCount_++;
	if (nowFlameCount_ > maxFlameCount_) {	//時が来たら90度回転

		

		nowFlameCount_ = 0;
		worldTransform_.rotation_.x += 0.5 * PI;
		

		for (int i = 0; i < _countof(line_); i++) {	// ライン保存
			if (line_[i].isDraw == false) {
				line_[i].isDraw = true;
				line_[i].worldTransform.translation_ = nowLineWorldTransform_.translation_;
				line_[i].worldTransform.rotation_ = nowLineWorldTransform_.rotation_;
				line_[i].worldTransform.scale_ = nowLineWorldTransform_.scale_;
				
				line_[i].sLineVec2 = { nowStartPos.x, nowStartPos.x };
				line_[i].eLineVec2 = { nowEndPos.x, nowEndPos.x };

				break;
			}
		}
		nowStartPos = nowEndPos;	// 終点が視点になる

	}
#pragma endregion 自機とライン保存

#pragma region ラインと自機衝突
	for (int i = 0; i < _countof(line_); i++) {
		if (line_[i].isDraw == true) {
			
		}

		
	}
#pragma endregion
	
#pragma region ワールドトランスフォーム更新
	for (int i = 0; i < _countof(line_); i++) {
		worldTransformUpdate(&line_[i].worldTransform);
	}
	worldTransformUpdate(&worldTransform_);
	worldTransformUpdate(&nowLineWorldTransform_);
#pragma endregion ワールドトランスフォーム更新
	
	
}

void Player::Draw(ViewProjection viewProjection)
{

	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	model_->Draw(nowLineWorldTransform_, viewProjection, textureHandle_);
	for (int i = 0; i < _countof(line_); i++) {
		if (line_[i].isDraw == true) {
		model_->Draw(line_[i].worldTransform, viewProjection, textureHandle_);
		}

		//トランスレーション
		debugText_->SetPos(20, 20 + i*15);
		debugText_->Printf("%f,%f,%f", line_[i].worldTransform.translation_.x
			, line_[i].worldTransform.translation_.y
			, line_[i].worldTransform.translation_.z);

		//スケール
		debugText_->SetPos(300, 20 + i * 15);
		debugText_->Printf("%f,%f,%f", line_[i].worldTransform.scale_.x
			, line_[i].worldTransform.scale_.y
			, line_[i].worldTransform.scale_.z);

	}


}

Vector3 Player::GetWorldPosition()
{
	return Vector3();
}

void Player::OnCollision(bool isBreak)
{
	//hp--;
}