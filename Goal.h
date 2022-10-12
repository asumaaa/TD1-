#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Model.h"

class Goal
{
public:
	void Initialize(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection viewProjection);
private:
	WorldTransform worldTransform_[4];
	Model* model_ = nullptr;

	float modelVelocityAngle_ = 0; //digrees

	uint32_t textureHandle_ = 0;
};

