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
	ForceWait, //���̳� UI�����϶� ���۱�������

	Max, // �Ϲ������� ������� �ʴ� ��.
};


// ���� :
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

	float DamagedDelayTimer = 0.0f; // �ǰ��� �����ð� Ÿ�̸�
	float DamagedDelay = 0.5f; // �ǰ��� �����ð�

	PlayerState State = PlayerState::Max;

	int ComboCount = 0;
	int AerialComboCount = 0;

	int DamageComobo = 10; // �⺻���� ������
	float DamageComoboScale = 1.0f; // �⺻ ���� ������
	float DamagedTickTime = 0.5f; // �ǰ��� �����ð�
	

	bool NextCombo = false; // ���� �޺� �Է��ߴ��� Ȯ�� 
	bool AerialComboEnd = false; //���� �������� ����;
	bool JumpingAttackEnd = false; //���ξ��� �������� ����;
	bool DustLandingValue = false; // ���� �ٿ���� ���� �����ߴ��� Ȯ���ϴ� ��
	bool AttackCollisionValue = false; //�� ������ �̹� �����ߴ��� Ȯ���ϴ� ��
	


	//============================
	// ����
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


	float4 TargetPos = float4::ZERO; // ���� �̵� ��ǥ �����
	float4 TargetPlayerPos = float4::ZERO; // �̵��� �÷��̾� ��ǥ �����


	void StateUpdate(float _Delta);
};

