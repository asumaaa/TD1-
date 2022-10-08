#include "Filed.h"
#include <cassert>

void Filed::Initialize(Model* model, float posX)
{
	assert(model);

	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("white1x1.png");

	worldTransform_.Initialize();

	worldTransform_.scale_ = { 0.5f,0.5f,length };
	worldTransform_.translation_ = { posX,0.0f,0.0f };
	worldTransformUpdate(&worldTransform_);
}

void Filed::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Filed::Update()
{
}
