#include "RailCamera.h"
#include "math.h"
#include <cassert>
#define PI 3.141592653589

void RailCamera::Initialize()
{
	
	//�r���[�v���W�F�N�V�����̏�����
	
	viewProjection_.eye = { 0,7,-50 };
	viewProjection_.target = { 0,0,-32 };
	viewProjection_.Initialize();

}

void RailCamera::Update(WorldTransform worldTransform)
{
	
}
