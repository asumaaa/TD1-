#pragma once
#include "DebugText.h"
#include "Input.h"
#include "ViewProjection.h"
#include <Model.h>
#include <WorldTransform.h>
#include <list>
#include <cassert>

class GameScene;

class Bullet
{
public:
	void Initialize(Model* model, uint32_t textureHandle, Vector3 vector3);
	void Update();
	void Draw(ViewProjection viewProjection);
	
	bool IsDead() const { return isDead_; }	//���S��
	int GetId() { return bulletId_; }	
	void SetID(int ID) { bulletId_ = ID; }	

private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	//���f��
	Model* model_ = nullptr;

	//���̑�
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	
	//�ŗLID
	int bulletId_ = 0;

	//�f�X�t���O
	bool isDead_ = false;


};

