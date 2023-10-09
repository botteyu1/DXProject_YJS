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
	Max, // �Ϲ������� ������� �ʴ� ��.
};

// ���� :
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

	void TakeDamage(class GameEngineCollision* _Player ,int _Damage);

protected:
	float MotionTime = 0.0f; // �⺻������ ���� �ൿ�ϴ�  �ð�
	float MoveSpeed = 400.0f;

	std::shared_ptr<GameEngineCollision> DetectCollision;
	std::shared_ptr<GameEngineCollision> DetectAttackCollision;
	void Start() override;
	void LookPlayer();
	bool IsDetectPlayer();

	bool  DetectPlayer = false;

private:
	
	EnemyState State = EnemyState::Max;



protected:
	//============================
	// ����
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

	
	void FlipCheck();

	void StateUpdate(float _Delta);
	void ChangeState(EnemyState _State);
};

