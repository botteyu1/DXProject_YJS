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
	
	ForceWait, //씬이나 UI상태일때 조작금지상태

	Max, // 일반적으로 사용하지 않는 값.
};

class PlayerData
{

public:
	int HP = 80;
	int MaxHP = 80;
	float MaxMP = 50;
	float MP = 50;
	int Soulary = 0;
	float DamageComobo = 0.0f; // 기본 공격 추가 데미지
	float DamageComoboScale = 1.0f; // 기본 공격 스케일

	int DamageCape= 0; // 망토 추가 데미지
	float DamageCapeScale = 1.0f; // 망토 추가 스케일

	int DamageMagic= 0; // 마법 추가 데미지
	float DamageMagicScale = 1.0f; // 마법 추가 스케일

	float DebugScale = 1.0f;

	float MPScale = 1.0f;

	int DashCount = 1;
	int AnimaSocket = 3;


	int MaxAnima = 4;
	int Anima = 1;

	float UltGauge = 0.0f;
	float MaxUltGauge = 100.0f;


	CapeType CurCapeType = CapeType::EvilBirds; // 현재 착용중인 망토 타입
	CapeType CurCapeType2 = CapeType::Katana; // 현재 착용중인 서브 망토 타입

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


// 설명 :
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
	

	float DamagedDelayTimer = 0.0f; // 피격후 무적시간 타이머
	float DamagedDelay = 0.8f; // 피격후 무적시간

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

	
	
	float DamagedTickTime = 0.5f; // 피격후 무적시간
	

	bool NextCombo = false; // 다음 콤보 입력했느지 확인 
	bool AerialComboEnd = false; //공콤 끝났는지 여부;
	bool JumpingAttackEnd = false; //점핑어택 끝났는지 여부;
	bool DustLandingValue = false; // 점프 다운어택 땅에 도달했는지 확인하는 용
	bool AttackCollisionValue = false; //한 공격이 이미 적중했는지 확인하는 용

	void CapeStart();
	void CapeUpdate(float _Delta);

	
	std::shared_ptr<class GameEngineSpriteRenderer> UltSpriteRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> UltmateSpriteRenderer;


	//Cape CapeData;

	GameEngineState CapeState;
	CapeType CurCapeType = CapeType::EvilBirds; // 현재 착용중인 망토 타입
	CapeType CurCapeType2 = CapeType::Tornado; // 현재 착용중인 서브 망토 타입
	float CurCapeCoolTime = 0.0f;
	float CurCapeCoolTime2 = 0.0f;


	CapeType CurCapeType3 = CapeType::Katana; // 디버그용 서브 망토 타입
	CapeType CurCapeType4 = CapeType::EvilHands; // 디버그용 서브 망토 타입
	


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


	float4 TargetPos = float4::ZERO; // 고정 이동 좌표 저장용
	float4 TargetPlayerPos = float4::ZERO; // 이동전 플레이어 좌표 저장용


	void StateUpdate(float _Delta);
};

