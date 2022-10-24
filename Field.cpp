#include "Field.h"
#include <cassert>


void Field::Initialize(Model* model, uint32_t textureHandle, Lane lane)
{

	assert(model);

	model_ = model;

	//�V���O���g���C���X�^���X���擾
	input_ = Input::GetInstance();

	//�e�N�X�`���ǂݍ���
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();

	worldTransform_.scale_ = { 0.3f,0.2f,length };

	//x���W�ɉ����Č��݂̃��[���𔻒�
	lane_ = lane;
	
	if (lane == Left)
	{
		worldTransform_.translation_ = { -laneWidth,0.0f,zLen_ };
	}
	else if (lane == Center)
	{
		worldTransform_.translation_ = { 0.0f,0.0f,zLen_ };
	}
	else if (lane == Right)
	{
		worldTransform_.translation_ = { laneWidth,0.0f,zLen_ };
	}
	worldTransformUpdate(&worldTransform_);

	//�C�[�W���O
	ease_ = new Ease;
	
}

void Field::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Field::Update()
{
	//�L�[���͂ɉ�����Lane��ύX
	if (input_->PushKey(DIK_LEFT) && input_->TriggerKey(DIK_SPACE)
		&& isChangeLeft_ == false&& isChangeRight_ == false)
	{
		/*if (lane_ == Left)lane_ = Center;
		else if (lane_ == Center)lane_ = Left;*/
		isChangeLeft_ = true;

	}else if (input_->PushKey(DIK_RIGHT) && input_->TriggerKey(DIK_SPACE)
		&& isChangeLeft_ == false && isChangeRight_ == false)
	{
		/*if (lane_ == Right)lane_ = Center;
		else if (lane_ == Center)lane_ = Right;*/
		isChangeRight_ = true;
	}

	if (time_ >= maxTime_) {	//�^�C�����Z�b�g
		time_ = 0;
		if (isChangeLeft_ == true) {
			isChangeLeft_ = false;
			if (lane_ == Left) {
				lane_ = Center;
			}
			else if (lane_ == Center) {
				lane_ = Left;
			}
		}
		if (isChangeRight_ == true) {
			isChangeRight_ = false;
			if (lane_ == Right) {
				lane_ = Center;
			}
			else if (lane_ == Center) {
				lane_ = Right;
			}
		}

		if (lane_ == Left)
		{
			worldTransform_.translation_ = { -laneWidth,0.0f,zLen_ };
		}
		else if (lane_ == Center)
		{
			worldTransform_.translation_ = { 0.0f,0.0f,zLen_ };
		}
		else if (lane_ == Right)
		{
			worldTransform_.translation_ = { laneWidth,0.0f,zLen_ };
		}
	}


	if (isChangeLeft_ == true) {
		time_++;
		if (lane_ == Left) {
			worldTransform_.translation_.x = ease_->InOutQuad(laneWidth, -laneWidth,maxTime_,time_);
		}
		if (lane_ == Center) {
			worldTransform_.translation_.x = ease_->InOutQuad(-laneWidth, 0.0f, maxTime_, time_);
		}
		
	}
	else if (isChangeRight_ == true) {
		time_++;
		if (lane_ == Right) {
			worldTransform_.translation_.x = ease_->InOutQuad(-laneWidth, laneWidth, maxTime_, time_);
		}
		if (lane_ == Center) {
			worldTransform_.translation_.x = ease_->InOutQuad(laneWidth, 0.0f, maxTime_, time_);
		}
	}
	
		
	

	

	//Lane�ɉ�����X��ύX
	/*if (lane_ == Left)
	{
		worldTransform_.translation_ = { -laneWidth,0.0f,zLen_ };
	}
	else if (lane_ == Center)
	{
		worldTransform_.translation_ = { 0.0f,0.0f,zLen_ };
	}
	else if (lane_ == Right)
	{
		worldTransform_.translation_ = { laneWidth,0.0f,zLen_ };
	}*/
	worldTransformUpdate(&worldTransform_);
}

void Field::LaneChange()
{

}
