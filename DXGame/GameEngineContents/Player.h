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
	Hit,
	EnterElavator,
	ExitElavator,
	ForceWait, //씬이나 UI상태일때 조작금지상태

	Max, // 일반적으로 사용하지 않는 값.
};


// 설명 :
class Player : public Actor
{
	friend class BookOfTheDead;

private:
	static Player* MainPlayer;

public:
	static Player* GetMainPlayer()
	{
		return MainPlayer;
	}
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;
	void static ComboHit(class GameEngineCollision* _Left, GameEngineCollision* _Right);
	void CheckAttackCollision();

	int GetDamageComobo()
	{
		return DamageComobo;
	}

	float GetDamageComoboScale()
	{
		return DamageComoboScale;
	}

	void TakeDamage(GameEngineCollision* _Attacker, float _Damage) override;
	void SetTargetPos(const float4& _Pos)
	{
		TargetPos = _Pos;
	}


	void ChangeState(PlayerState _State);
	void LevelStart(class GameEngineLevel* _NextLevel) override;

	void LevelEnd(class GameEngineLevel* _NextLevel) override;
protected:
	void Start() override;
	void Update(float _Delta) override;
	std::shared_ptr<GameEngineCollision> DetectCollision;
	std::shared_ptr<class BookOfTheDead> PlayerBook;
	
	//std::shared_ptr<class SecondaryRenderer> ShadowRenderer;


	//void LevelStart() override;

	//std::shared_ptr<class FX> FXJumpActor;

private:
	

	float MoveSpeed = 700.0f;
	float JumpingSpeed = 1500.0f;
	float JumpingAttackSpeed = 1500.0f;

	float DamagedDelayTimer = 0.0f; // 피격후 무적시간 타이머
	float DamagedDelay = 0.5f; // 피격후 무적시간

	PlayerState State = PlayerState::Max;

	int ComboCount = 0;
	int AerialComboCount = 0;

	int DamageComobo = 10; // 기본공격 데미지
	float DamageComoboScale = 1.0f; // 기본 공격 스케일
	float DamagedTickTime = 0.5f; // 피격후 무적시간
	

	bool NextCombo = false; // 다음 콤보 입력했느지 확인 
	bool AerialComboEnd = false; //공콤 끝났는지 여부;
	bool JumpingAttackEnd = false; //점핑어택 끝났는지 여부;
	bool DustLandingValue = false; // 점프 다운어택 땅에 도달했는지 확인하는 용
	bool AttackCollisionValue = false; //한 공격이 이미 적중했는지 확인하는 용
	


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

	void HitStart();
	void HitUpdate(float _Delta);

	void EnterElavatorStart();
	void EnterElavatorUpdate(float _Delta);

	void ExitElavatorStart();
	void ExitElavatorUpdate(float _Delta);

	void ForceWaitStart();
	void ForceWaitUpdate(float _Delta);


	bool InputMoveUpdate(float _Delta);
	bool InputJumpUpdate(float _Delta);
	bool InputAttackUpdate(float _Delta);
	bool InputDashUpdate(float _Delta);


	float4 TargetPos = float4::ZERO; // 고정 이동 좌표 저장용
	float4 TargetPlayerPos = float4::ZERO; // 이동전 플레이어 좌표 저장용


	void StateUpdate(float _Delta);
};

