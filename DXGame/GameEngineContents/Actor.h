#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
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

private:
	float4 GrivityForce = { 0.0f, 0.0f, 0.0f, 1.0f }; //중력힘
};

