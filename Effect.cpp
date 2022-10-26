#include "Effect.h"
#include "stdlib.h"
#include "Matrix.h"

void Effect::Initialize(Model* model, uint32_t textureHandle, Vector3 vec3)
{
	// NULLポインタチェック
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;

	//シングルインスタンスを取得する
	input_ = Input::GetInstance();

	float kMoveSpeed = 0.2f;	//スピード調整
	float kRotSpeed = 0.2f;

 	//初期値をセット
	for (int i = 0; i < EFFECT_NUM; i++) {
		worldTransform_[i].Initialize();
		worldTransform_[i].translation_ = vec3;
		worldTransform_[i].scale_ = { 0.7,0.7,0.3 };
		worldTransform_[i].rotation_ = { 0,0,0 };
		worldTransformUpdate(&worldTransform_[i]);

		rotVector_[i] = {static_cast<float> (rand() % 20 - 10),
			static_cast<float> (rand() % 20 - 10) ,
			static_cast<float> (rand() % 20 - 10) };	//回転用
		rotVector_[i] = vector3Normalize(rotVector_[i]);

		velocity_[i] = { static_cast<float>(rand() % 20 - 10),
			static_cast<float>(rand() % 20 - 10) ,
			static_cast<float>(rand() % 20 - 10) };	//散布の方向
		velocity_[i] = vector3Normalize(velocity_[i]);
		
		rotVector_[i] *= kRotSpeed;
		velocity_[i] *= kMoveSpeed; 
		
		
	}


}

void Effect::Update()
{
	for (int i = 0; i < EFFECT_NUM; i++) {

		

		worldTransform_[i].translation_ += velocity_[i];	//移動
		worldTransform_[i].rotation_ += rotVector_[i];	//回転
		float kMinusScale = 0.04f;
		worldTransform_[i].scale_ += {-kMinusScale, -kMinusScale, -kMinusScale };
		worldTransformUpdate(&worldTransform_[i]);

		float limitScale = 0.0f;
		if (worldTransform_[i].scale_.x <= limitScale &&
			worldTransform_[i].scale_.y <= limitScale &&
			worldTransform_[i].scale_.z <= limitScale) {
			isDead_ = true;
		}
	}
}

void Effect::Draw(ViewProjection viewProjection)
{
	for (int i = 0; i < EFFECT_NUM; i++) {
		model_->Draw(worldTransform_[i], viewProjection,textureHandle_);
	}
}


