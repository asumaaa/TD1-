#include "RailCamera.h"
#include "math.h"
#include <cassert>
#define PI 3.141592653589

void RailCamera::Initialize()
{
	//����������W�Ɖ�]�p���󂯎��
	/*worldTransform_.translation_ = worldTransform.translation_;
	worldTransform_.rotation_ = worldTransform.rotation_;*/
	/*worldTransform_.translation_.x = worldTransform.translation_.x;
	worldTransform_.translation_.y = worldTransform.translation_.y;
	worldTransform_.translation_.z = worldTransform.translation_.z;
	worldTransform_.rotation_ = worldTransform.rotation_;*/
	//�r���[�v���W�F�N�V�����̏�����
	
	viewProjection_.eye = { 0,7,-50 };
	viewProjection_.target = { 0,0,-32 };
	viewProjection_.Initialize();

}

void RailCamera::Update(WorldTransform worldTransform)
{
	//////����������W�Ɖ�]�p���󂯎��
	////worldTransform_.scale_ = {1,1,1};
	//////���[���h�g�����X�t�H�[���̍X�V
	////worldTransformUpdate(&worldTransform_);

	////�I�u�W�F�N�g�ɒǏ]������W�̏���
	////���[���h���W�����_���W�ɑ��
	///*viewProjection_.eye = worldTransform_.translation_;*/
	////���[���h�O���x�N�g��
	//Vector3 forward(0, 0, 1);
	////���[���J�����̔��]���e��
	///*forward = vector3Normalize(worldTransform_.translation_);*/
	////���_����O���ɓK���ȋ����i�񂾈ʒu�������_
	//viewProjection_.target = { viewProjection_.eye.x + forward.x ,viewProjection_.eye.y + forward.y ,viewProjection_.eye.z + forward.z };
	////���[���h����x�N�g��
	//Vector3 up(0, 1, 0);
	////���[���J�����̉�]�𔽉f
	///*up = vector3Normalize(worldTransform_.rotation_);*/
	////�r���[�v���W�F�N�V�������X�V
	//viewProjection_.Initialize();

	/*float x = worldTransform.translation_.x - (sin(worldTransform.rotation_.y) * length);
	float y = worldTransform.translation_.y - (worldTransform.rotation_.x * length);
	float z = worldTransform.translation_.z - (cos(worldTransform.rotation_.y) * length);*/
	/*float x = worldTransform.translation_.x - (sin(worldTransform.rotation_.y) * length);
	float y = worldTransform.translation_.y - (worldTransform.rotation_.x * length);
	float z = worldTransform.translation_.z + (cos(worldTransform.rotation_.x) * length);*/

	/*float x = worldTransform.translation_.x - (sin(worldTransform.rotation_.y) * length * 2);
	float y = worldTransform.translation_.y + (sin(worldTransform.rotation_.x) * length * 2);
	float z = worldTransform.translation_.z - (cos(worldTransform.rotation_.y) * length) - (cos(worldTransform.rotation_.x) * length );*/

	/*float x, y, z;

	x = worldTransform.translation_.x + (sin(-worldTransform.rotation_.x + (PI / 2)) * cos(-worldTransform.rotation_.y - (PI / 2)) * length);
	y = worldTransform.translation_.y + (cos(-worldTransform.rotation_.x + (PI / 2)) * length);
	z = worldTransform.translation_.z + (sin(-worldTransform.rotation_.x + (PI / 2)) * sin(-worldTransform.rotation_.y - (PI / 2)) * length);

	if (sin(-worldTransform.rotation_.x + (PI / 2)) <= 0)
	{
		viewProjection_.up = { 0,-1,0 };
	}
	else
	{
		viewProjection_.up = { 0,1,0 };
	}
	viewProjection_.eye = { x,y,z };
	viewProjection_.target = { worldTransform.translation_.x, worldTransform.translation_.y, worldTransform.translation_.z };
	viewProjection_.Initialize();*/
}
