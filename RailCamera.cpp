#include "RailCamera.h"
#include "math.h"
#include <cassert>
#define PI 3.141592653589

void RailCamera::Initialize()
{
	
	//ビュープロジェクションの初期化
	
	viewProjection_.eye = { 0,7,-50 };
	viewProjection_.target = { 0,0,-32 };
	viewProjection_.Initialize();

}

void RailCamera::Update(WorldTransform worldTransform)
{
	
}
