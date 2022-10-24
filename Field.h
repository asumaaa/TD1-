#pragma once
#include "WorldTransform.h"
#include "Vector3.h"
#include "Matrix.h"
#include "ViewProjection.h"
#include "memory"
#include "Model.h"
#include "Input.h"
#include "Ease.h"

//���[���̗񋓌^
	enum Lane
	{
		Left,
		Center,
		Right
	};

class Field
{
public:
	void Initialize(Model* model, uint32_t textureHandle, Lane lane);	//���[����X���W�����߂ď�����
	void Draw(ViewProjection viewProjection);
	void Update();
	//�Q�b�^�[
	Vector3 GetTransration() { return worldTransform_.translation_; };

	void LaneChange();
private:

	Input* input_ = nullptr;
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;

	float length = 200.0f;	//���[���̒���
	float zLen_ = 165.0f;	//okuyuki
	//���݂̃��[��
	Lane lane_;

	//���[���̕�
	float laneWidth = 10.0f;
	//�C�[�W���O�p
	Ease* ease_ = nullptr;
	bool isChangeRight_ = false;		//���[���`�F���W
	bool isChangeLeft_ = false;
	const int maxTime_ = 10;
	int time_ = 0;


};

