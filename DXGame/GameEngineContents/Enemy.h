#pragma once
#include "Actor.h"

enum class EnemyState
{
	Idle,
	Attack,
	Appear,
	Death,
	Hit,
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

protected:

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

	
	void FlipCheck();

	void StateUpdate(float _Delta);
	void ChangeState(EnemyState _State);
};

