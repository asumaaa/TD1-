#include "Player.h"
#include <cmath>
#include "math.h"
#define PI 3.141592653589

void Player::Initialize(Model* model, uint32_t textureHandle)
{
	// NULL�|�C���^�`�F�b�N
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;

	//�V���O���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = debugText_->GetInstance();

	//�������W���Z�b�g
	worldTransform_.Initialize();
	worldTransform_.translation_ = { -5,0,0 };
	worldTransform_.scale_ = { 1,1,1 };
	worldTransform_.rotation_ = { 0,0.5 * PI,0 };
	pVelocity_ = { 0,0,0.4f };	//�v���C���[�̈ړ���
	
	nowLineWorldTransform_.Initialize();	//���@�̈ʒu

	//���@����t���[���J�E���g
	maxFlameCount_ = 70;
	nowFlameCount_ = 0;

	for (int i = 0; i < _countof(line_); i++) {
		line_[i].worldTransform.Initialize();
		line_[i].sLineVec2 = {};
		line_[i].eLineVec2 = {};
		line_[i].isDraw = false;
		line_[i].worldTransform.translation_.x += i * 2;
		worldTransformUpdate(&line_[i].worldTransform);

	}

	nextLine_ = 0;
	worldTransformUpdate(&worldTransform_);

}

void Player::Update()
{
#pragma region	�A�N�Z��
	if (input_->PushKey(DIK_LEFT)) {
		if (maxFlameCount_ > 10) {
			maxFlameCount_--;
		}
	}
	else if (input_->PushKey(DIK_RIGHT)) {
		if (maxFlameCount_ < 100) {
			maxFlameCount_++;
		}
	}
#pragma endregion

#pragma region ���@�ƃ��C���ۑ�
	nowEndPos = worldTransform_.translation_;//���C���p�̏I�_(���t���[���X�V)

	//line�̃g�����X�t�H�[���v�Z
	nowLineWorldTransform_.translation_ =	//�n�_�I�_�̒��S�����W
	{ (nowStartPos.x + nowEndPos.x) / 2,
		(nowStartPos.y + nowEndPos.y) / 2,
		(nowStartPos.z + nowEndPos.z) / 2
	};	//kmtEngine�̃I�y���[�^��lib������Ă��Ă�����Ȃ�

	float len = sqrtf(pow(nowEndPos.x - nowStartPos.x, 2) +
		pow(nowEndPos.y - nowStartPos.y, 2) +
		pow(nowEndPos.z - nowStartPos.z, 2));

	nowLineWorldTransform_.scale_ = { 0.3,0.3,
		len / 2
	};

	nowLineWorldTransform_.rotation_ = worldTransform_.rotation_;


	Vector3 vel = bVelocity(pVelocity_, worldTransform_);

	worldTransform_.translation_ += vel;

	nowFlameCount_++;
	if (nowFlameCount_ > maxFlameCount_) {	//����������90�x��]

		

		nowFlameCount_ = 0;
		worldTransform_.rotation_.x += 0.5 * PI;
		

		for (int i = 0; i < _countof(line_); i++) {	// ���C���ۑ�
			if (line_[i].isDraw == false) {
				line_[i].isDraw = true;
				line_[i].worldTransform.translation_ = nowLineWorldTransform_.translation_;
				line_[i].worldTransform.rotation_ = nowLineWorldTransform_.rotation_;
				line_[i].worldTransform.scale_ = nowLineWorldTransform_.scale_;
				
				line_[i].sLineVec2 = { nowStartPos.x, nowStartPos.x };
				line_[i].eLineVec2 = { nowEndPos.x, nowEndPos.x };

				break;
			}
		}
		nowStartPos = nowEndPos;	// �I�_�����_�ɂȂ�

	}
#pragma endregion ���@�ƃ��C���ۑ�

#pragma region ���C���Ǝ��@�Փ�
	for (int i = 0; i < _countof(line_); i++) {
		if (line_[i].isDraw == true) {
			
		}

		
	}
#pragma endregion
	
#pragma region ���[���h�g�����X�t�H�[���X�V
	for (int i = 0; i < _countof(line_); i++) {
		worldTransformUpdate(&line_[i].worldTransform);
	}
	worldTransformUpdate(&worldTransform_);
	worldTransformUpdate(&nowLineWorldTransform_);
#pragma endregion ���[���h�g�����X�t�H�[���X�V
	
	
}

void Player::Draw(ViewProjection viewProjection)
{

	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	model_->Draw(nowLineWorldTransform_, viewProjection, textureHandle_);
	for (int i = 0; i < _countof(line_); i++) {
		if (line_[i].isDraw == true) {
		model_->Draw(line_[i].worldTransform, viewProjection, textureHandle_);
		}

		//�g�����X���[�V����
		debugText_->SetPos(20, 20 + i*15);
		debugText_->Printf("%f,%f,%f", line_[i].worldTransform.translation_.x
			, line_[i].worldTransform.translation_.y
			, line_[i].worldTransform.translation_.z);

		//�X�P�[��
		debugText_->SetPos(300, 20 + i * 15);
		debugText_->Printf("%f,%f,%f", line_[i].worldTransform.scale_.x
			, line_[i].worldTransform.scale_.y
			, line_[i].worldTransform.scale_.z);

	}


}

Vector3 Player::GetWorldPosition()
{
	return Vector3();
}

void Player::OnCollision(bool isBreak)
{
	//hp--;
}