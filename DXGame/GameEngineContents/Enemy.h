#pragma once
#include "Actor.h"

enum class EnemyState
{
	Idle,
	Attack,
	Appear,
	Death,
	Hit,
	Run,
	Surprised,
	Uturn,
	Waiting,
	Max, // 일반적으로 사용하지 않는 값.
};

// 설명 :
class Enemy : public Actor
{
public:
	// constrcuter destructer
	Enemy();
	~Enemy();

	// delete Function
	Enemy(const Enemy& _Other) = delete;
	Enemy(Enemy&& _Other) noexcept = delete;
	Enemy& operator=(const Enemy& _Other) = delete;
	Enemy& operator=(Enemy&& _Other) noexcept = delete;

	virtual void TakeDamage(class GameEngineCollision* _Attacker ,float _Damage) override;

	void static ComboHit(GameEngineCollision* _Left, GameEngineCollision* _Right);

	float inline GetAttackDamage()
	{
		return AttackDamage;
	}

protected:
	
	float MoveSpeed = 400.0f;
	float AttackDamage = 10.0f;
	float AttackCoolTime = 3.0f;
	float AttackCoolTimeCheck = 0.0f;

	float DamagedDelayTimer = 0.0f; // 피격후 무적시간 타이머
	float DamagedDelay = 0.5f; // 피격후 무적시간

	std::shared_ptr<GameEngineCollision> DetectCollision;
	std::shared_ptr<GameEngineCollision> DetectAttackCollision;

	void Start() override;
	void Update(float _Delta) override;
	bool LookPlayer();
	bool IsDetectPlayer();

	bool  DetectPlayer = false;

	void CheckAttackCollision();

private:
	
	EnemyState State = EnemyState::Max;



protected:
	//============================
	// 상태
	//============================

	virtual void IdleStart();
	virtual void IdleUpdate(float _Delta);
	
	virtual void AttackStart();
	virtual void AttackUpdate(float _Delta);

	virtual void AppearStart();
	virtual void AppearUpdate(float _Delta);

	virtual void DeathStart();
	virtual void DeathUpdate(float _Delta);
	
	virtual void HitStart();
	virtual void HitUpdate(float _Delta);

	virtual void RunStart();
	virtual void RunUpdate(float _Delta);

	virtual void SurprisedStart();
	virtual void SurprisedUpdate(float _Delta);

	virtual void UturnStart();
	virtual void UturnUpdate(float _Delta);

	virtual void WaitingStart();
	virtual void WaitingUpdate(float _Delta);

	

	void StateUpdate(float _Delta);
	void ChangeState(EnemyState _State);
};

