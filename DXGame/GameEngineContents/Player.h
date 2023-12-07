#pragma once
#include "Actor.h"
#include <GameEngineCore/GameEngineState.h>
#include "Cape.h"


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
	CapeAttack,
	Dash,
	Hit,
	EnterElavator,
	ExitElavator,
	Acquisition,
	PowerUp,
	UltAttack,
	UltAttack_Rest,
	
	ForceWait, //���̳� UI�����϶� ���۱�������

	Max, // �Ϲ������� ������� �ʴ� ��.
};

class PlayerData
{

public:
	int HP = 80;
	int MaxHP = 80;
	float MaxMP = 50;
	float MP = 50;
	int Soulary = 0;
	float DamageComobo = 0.0f; // �⺻ ���� �߰� ������
	float DamageComoboScale = 1.0f; // �⺻ ���� ������

	int DamageCape= 0; // ���� �߰� ������
	float DamageCapeScale = 1.0f; // ���� �߰� ������

	int DamageMagic= 0; // ���� �߰� ������
	float DamageMagicScale = 1.0f; // ���� �߰� ������

	float DebugScale = 1.0f;

	float MPScale = 1.0f;

	int DashCount = 1;
	int AnimaSocket = 3;


	int MaxAnima = 4;
	int Anima = 1;

	float UltGauge = 0.0f;
	float MaxUltGauge = 100.0f;


	CapeType CurCapeType = CapeType::EvilBirds; // ���� �������� ���� Ÿ��
	CapeType CurCapeType2 = CapeType::Katana; // ���� �������� ���� ���� Ÿ��

	void AddAnima(int _Num = 1)
	{
		if (Anima + _Num <= MaxAnima)
		{
			Anima += _Num;
		}
		else
		{
			Anima = MaxAnima;
		}
	}
	

};


// ���� :
class Player : public Actor
{
	friend class BookOfTheDead;
	friend class PlayUI;
	friend class CurseUI;

private:
	static Player* MainPlayer;
	static PlayerData MainPlayerData;

public:
	static Player* GetMainPlayer()
	{
		return MainPlayer;
	}
	static PlayerData& GetMainPlayerData()
	{
		return MainPlayerData;
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


	/*int GetDamageComobo()
	{
		return DamageComobo;
	}

	float GetDamageComoboScale()
	{
		return DamageComoboScale;
	}*/

	CapeType GetCurCapeType()
	{
		return CurCapeType;
	}
	CapeType GetCurCapeType2()
	{
		return CurCapeType2;
	}
	void SetCurCapeType(CapeType _Type)
	{
		CurCapeType = _Type;
	}

	void SetCurCapeType2(CapeType _Type)
	{
		CurCapeType2 = _Type;
	}

	void TakeDamage(GameEngineCollision* _Attacker, float _Damage) override;
	void SetTargetPos(const float4& _Pos)
	{
		TargetPos = _Pos;
	}


	void ChangeState(PlayerState _State);
	void LevelStart(class GameEngineLevel* _NextLevel) override;

	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	void AddSoulary(int _Soulary)
	{
		Soulary += _Soulary;
	}

	PlayerState GetState()
	{
		return State;
	}

	void AddUltGauge(float _UltGauge = 7.0f)
	{
		if (Player::GetMainPlayerData().UltGauge < Player::GetMainPlayerData().MaxUltGauge)
		{
			Player::GetMainPlayerData().UltGauge += _UltGauge;

		}
		else
		{
			Player::GetMainPlayerData().UltGauge = Player::GetMainPlayerData().MaxUltGauge;
		}
	}

protected:
	void Start() override;
	void Update(float _Delta) override;
	std::shared_ptr<GameEngineCollision> DetectCollision;
	std::shared_ptr<class BookOfTheDead> PlayerBook;


	
	//std::shared_ptr<class SecondaryRenderer> ShadowRenderer;


	//void LevelStart() override;

	//std::shared_ptr<class FX> FXJumpActor;

private:
	void DataUpdate();

	float MoveSpeed = 700.0f;
	float JumpingSpeed = 1500.0f;
	float JumpingAttackSpeed = 1500.0f;
	

	float DamagedDelayTimer = 0.0f; // �ǰ��� �����ð� Ÿ�̸�
	float DamagedDelay = 0.8f; // �ǰ��� �����ð�

	float DashDelay = 1.0f;
	float DashDelayTimer = 0.0f;

	int DashCountCur= 0;

	int JumpingAttackCount = 0;


	PlayerState State = PlayerState::Max;

	float MP = 50;
	float MaxMP = 50;
	int MaxHP = 80;
	int Soulary = 0;

	int ComboCount = 0;
	int AerialComboCount = 0;

	
	
	float DamagedTickTime = 0.5f; // �ǰ��� �����ð�
	

	bool NextCombo = false; // ���� �޺� �Է��ߴ��� Ȯ�� 
	bool AerialComboEnd = false; //���� �������� ����;
	bool JumpingAttackEnd = false; //���ξ��� �������� ����;
	bool DustLandingValue = false; // ���� �ٿ���� ���� �����ߴ��� Ȯ���ϴ� ��
	bool AttackCollisionValue = false; //�� ������ �̹� �����ߴ��� Ȯ���ϴ� ��

	void CapeStart();
	void CapeUpdate(float _Delta);

	
	std::shared_ptr<class GameEngineSpriteRenderer> UltSpriteRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> UltmateSpriteRenderer;


	//Cape CapeData;

	GameEngineState CapeState;
	CapeType CurCapeType = CapeType::EvilBirds; // ���� �������� ���� Ÿ��
	CapeType CurCapeType2 = CapeType::Tornado; // ���� �������� ���� ���� Ÿ��
	float CurCapeCoolTime = 0.0f;
	float CurCapeCoolTime2 = 0.0f;


	CapeType CurCapeType3 = CapeType::Katana; // ����׿� ���� ���� Ÿ��
	CapeType CurCapeType4 = CapeType::EvilHands; // ����׿� ���� ���� Ÿ��
	


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

	void CapeAttackStart();
	void CapeAttackUpdate(float _Delta);
	void CapeAttackEnd();

	void AcquisitionStart();
	void AcquisitionUpdate(float _Delta);

	void PowerUpStart();
	void PowerUpUpdate(float _Delta);

	void UltAttackStart();
	void UltAttackUpdate(float _Delta);

	void UltAttack_RestStart();
	void UltAttack_RestUpdate(float _Delta);

	bool InputMoveUpdate(float _Delta);
	bool InputJumpUpdate(float _Delta);
	bool InputAttackUpdate(float _Delta);
	bool InputDashUpdate(float _Delta);


	float4 TargetPos = float4::ZERO; // ���� �̵� ��ǥ �����
	float4 TargetPlayerPos = float4::ZERO; // �̵��� �÷��̾� ��ǥ �����


	void StateUpdate(float _Delta);
};

