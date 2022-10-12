#include "Field.h"
#include <cassert>

void Field::Initialize(Model* model, float posX)
{
	assert(model);

	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("white1x1.png");

	worldTransform_.Initialize();

	worldTransform_.scale_ = { 0.3f,0.2f,length };
	worldTransform_.translation_ = { posX,0.0f,25.0f };
	worldTransformUpdate(&worldTransform_);
}

void Field::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Field::Update()
{
}
