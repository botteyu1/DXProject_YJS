#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� : �����ο����̴� ��ü�� ex)���� �÷��̾�  
class Actor : public GameEngineActor
{
public:
	// constrcuter destructer
	Actor();
	~Actor();

	// delete Function
	Actor(const Actor& _Other) = delete;
	Actor(Actor&& _Other) noexcept = delete;
	Actor& operator=(const Actor& _Other) = delete;
	Actor& operator=(Actor&& _Other) noexcept = delete;



protected:

	void Start() override;
	void Update(float _Delta) override;
	float4 Dir = float4::ZERO;
	float4 GrivityForce = { 0.0f, 0.0f, 0.0f, 1.0f }; //�߷���
	bool AerialCheck = true; //���� �پ����� ������ �ȼ��ø��� üũ
	bool ForceGrivityOff = false; 
	std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer;

private:

};

