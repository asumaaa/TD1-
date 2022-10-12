#pragma once
#include "WorldTransform.h"
#include "Vector3.h"
#include "Matrix.h"
#include "ViewProjection.h"
#include "memory"
#include "Model.h"

class Field
{
public:
	void Initialize(Model* model, float posX);	//���[����X���W�����߂ď�����
	void Draw(ViewProjection viewProjection);
	void Update();
	//�Q�b�^�[
	Vector3 GetTransration() { return worldTransform_.translation_; };
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	float length = 60.0f;	//���[���̒���
};

