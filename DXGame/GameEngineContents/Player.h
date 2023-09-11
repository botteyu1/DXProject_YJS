#pragma once
#include "Actor.h"

enum class PlayerState
{
	Idle,
	Jump_Falling,
	Jump_Start,
	Jump_Landing,
	Run,
	RunUturn,
	RunToIdle,
	ComboMove,
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




	


private:
	std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer;

	float Speed = 700.0f;

	PlayerState State = PlayerState::Max;
	
	
	int ComboCount = 1;

	bool Flip = false;
	bool NextCombo = false; // 다음 콤보 입력했느지 확인 




	//============================
	// 상태
	//============================

	void IdleStart();
	void IdleUpdate(float _Delta);

	void RunStart();
	void RunUpdate(float _Delta);

	void RunUturnStart();
	void RunUturnUpdate(float _Delta);

	void RunToIdleStart();
	void RunToIdleUpdate(float _Delta);

	void Jump_FallingStart();
	void Jump_FallingUpdate(float _Delta);

	void Jump_LandingStart();
	void Jump_LandingUpdate(float _Delta);

	void Jump_StartStart();
	void Jump_StartUpdate(float _Delta);

	void ComboMoveStart();
	void ComboMoveUpdate(float _Delta);

	void InputMoveUpdate(float _Delta);
	void InputJumpUpdate(float _Delta);
	void InputAttackUpdate(float _Delta);
	void FlipCheck();


	void StateUpdate(float _Delta);
	void ChangeState(PlayerState _State);
};

