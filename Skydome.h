#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Model.h"

class Skydome
{
public:
	//引数で天球のサイズを指定
	void Initialize(Model* model, float r);
	void Update();
	void Draw(ViewProjection viewProjection);
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	//天球の大きさ
	float r_;
};

