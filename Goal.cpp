#include "Goal.h"
#include "Matrix.h"
#include <cassert>
#define PI 3.141592653589

void Goal::Initialize(Model* model, uint32_t textureHandle)
{
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	for (int i = 0; i < 4; i++) {
		worldTransform_[i].Initialize();
		worldTransform_[i].translation_ = {0,0,0};
		worldTransform_[i].scale_ = {0.5,0.2,0.2};
	}
	worldTransform_[0].rotation_ = { 0,0,0 };
	worldTransform_[1].rotation_ = { 0,0,PI* 3/2 };
	worldTransform_[2].rotation_ = { 0,0,PI };
	worldTransform_[3].rotation_ = { 0,0,PI / 2 };
	
	


	for (int i = 0; i < 4; i++) {
		worldTransformUpdate(&worldTransform_[i]);
		
	}

	

}

void Goal::Update()
{
	modelVelocityAngle_++;
	if (modelVelocityAngle_ > 360) {
		modelVelocityAngle_ = 0;
	}

	for (int i = 0; i < 4; i++) {
		
		Vector3 kVec = { 0,sinf(modelVelocityAngle_*PI /180.0f)+2.4f,0};
		kVec = bVelocity(kVec, worldTransform_[i]);
		worldTransform_[i].translation_ = { kVec.x,kVec.y,-38 };
		worldTransformUpdate(&worldTransform_[i]);

	}
}

void Goal::Draw(ViewProjection viewProjection)
{
	for (int i = 0; i < 4; i++) {
		model_->Draw(worldTransform_[i], viewProjection,textureHandle_);
	}

}
