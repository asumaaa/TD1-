#pragma once
#include "WorldTransform.h"
#include "Matrix.h"
#include "ViewProjection.h"

class RailCamera
{
public:
	void Initialize();
	void Update(WorldTransform worldTransform);
	//�Q�b�^�[
	ViewProjection GetViewProjection() { return viewProjection_; }
private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	//���@�ƃJ�����̋���
	float length = 20.0f;
};

