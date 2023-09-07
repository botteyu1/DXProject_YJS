#pragma once
#include "Actor.h"

enum class PlayerState
{
	Idle,
	Jump,
	Run,
	RunUturn,
	RunToIdle,
	Attack,
	Max, // 일반적으로 사용하지 않는 값.
};

// 설명 :
class Player : public Actor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _Delta) override;




	void IdleStart();
	void IdleUpdate(float _Delta);
	
	void RunStart();
	void RunUpdate(float _Delta);
	
	void RunUturnStart();
	void RunUturnUpdate(float _Delta);
	
	void RunToIdleStart();
	void RunToIdleUpdate(float _Delta);
	
	void JumpStart();
	void JumpUpdate(float _Delta);

	void AttackStart();
	void AttackUpdate(float _Delta);

	void StateUpdate(float _Delta);
	void ChangeState(PlayerState _State);


	void EndUturnEvent(GameEngineRenderer* _Renderer);
private:
	std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer;

	float Speed = 700.0f;

	PlayerState State = PlayerState::Max;
	float4 Dir = float4::ZERO;
	bool Flip = false;
};

