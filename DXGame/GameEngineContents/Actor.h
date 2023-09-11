#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 실제로움직이는 객체들 ex)몬스터 플레이어  
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
	float4 GrivityForce = { 0.0f, 0.0f, 0.0f, 1.0f }; //중력힘
	bool GrivityCheck = true; //중력힘

private:

};

