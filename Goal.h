#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Model.h"

class Goal
{
public:
	/// <summary>
	/// ������,�X�V,�`��
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection viewProjection);

	Vector3 GetWorldPosition();	//���[���h���W�擾
	
	void OnCollision();	//�G�ꂽ�Ƃ�
	void MaterDown(bool isMaterDown);
	
	int bulletHit_[3] = {};
private:
	WorldTransform worldTransform_[4];
	Model* model_ = nullptr;

	float modelVelocityAngle_ = 0; //digrees

	uint32_t textureHandle_ = 0;

	int materDownTime_ = 0;//���[�^�[�_�E���̃f�B���C�J�E���g
	
};


