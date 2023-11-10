#pragma once
#include "ContentObject.h"
//����


class StageObject : public ContentObject
{
public:
	// constrcuter destructer
	StageObject();
	~StageObject();

	// delete Function
	StageObject(const StageObject& _Other) = delete;
	StageObject(StageObject&& _Other) noexcept = delete;
	StageObject& operator=(const StageObject& _Other) = delete;
	StageObject& operator=(StageObject&& _Other) noexcept = delete;


	

protected:
	void Start() override;
	void Update(float _Delta) override;

	//std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer; //�⺻ ������
	std::shared_ptr<GameEngineCollision> MainCollision;

	float GravityTimer = 0.0f;
	bool BouncingValue = true; //�ٿ������ true;
	bool AerialCheck = false; // �������� üũ �����̸� Ʈ��
	bool ForceGrivityOff = true; //���߿� �ְų� �߷��� �ȹ����� Ʈ��
	float4 GrivityForce = { 0.0f, 0.0f, 0.0f, 1.0f }; //�߷���
	float GrivityPower = 2000.0f; //�߷°���;

private:
	GameEngineColor PixelCollisionCheck(float4 _Pixel, GameEngineColor _DefaultColor = GameEngineColor::RED);
	GameEngineColor PosCollisionCheck(float4 _Pos, GameEngineColor _DefaultColor = GameEngineColor::RED);


	

};

