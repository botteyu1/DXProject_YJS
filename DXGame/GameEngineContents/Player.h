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
	ComboMove_Rest,
	ComboAerial,
	ComboAerial_Rest,
	JumpingAttack,
	AerialDownAttack,
	Dash,
	Max, // 일반적으로 사용하지 않는 값.
};

class AnimationData
{
public:
	float DashDistance; // 애니메이션에서 이동할 대쉬 거리 
	bool ComboEnd = false; //마지막 콤보인지 여부

	//int NextComboFrame;  //콤보가 계속 될떄 애니메이션이 바뀌는 프레임
	//bool HaveToIdle;
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
	

	float Speed = 700.0f;
	float DashSpeed = 2000.0f;
	float JumpingAttackSpeed = 1500.0f;

	PlayerState State = PlayerState::Max;
	std::map<std::string, AnimationData> PlayerAnimationDataMap;

	int ComboCount = 1;
	int AerialComboCount = 1;
	float CurDash = 0.0f; //현재까지 움직인 대쉬 거리
	AnimationData* CurAnimationData; //현재 애니메이션 Data

	bool Flip = false;
	bool NextCombo = false; // 다음 콤보 입력했느지 확인 
	bool AerialComboEnd = false; //공콤 끝났는지 여부;
	bool JumpingAttackEnd = false; //점핑어택 끝났는지 여부;




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

	void ComboMove_RestStart();
	void ComboMove_RestUpdate(float _Delta);
	
	void ComboAerialStart();
	void ComboAerialUpdate(float _Delta);

	void ComboAerial_RestStart();
	void ComboAerial_RestUpdate(float _Delta);

	void JumpingAttackStart();
	void JumpingAttackUpdate(float _Delta);

	void AerialDownAttackStart();
	void AerialDownAttackUpdate(float _Delta);

	void DashStart();
	void DashUpdate(float _Delta);

	void InputMoveUpdate(float _Delta);
	void InputJumpUpdate(float _Delta);
	void InputAttackUpdate(float _Delta);
	void InputDashUpdate(float _Delta);

	void FlipCheck();


	void StateUpdate(float _Delta);
	void ChangeState(PlayerState _State);
};

