#include "PreCompile.h"
#include "Enemy.h"

Enemy::Enemy() 
{
}

Enemy::~Enemy()
{
}

void Enemy::FlipCheck()
{
}

void Enemy::ChangeState(EnemyState _State)
{
	switch (_State)
	{
	case EnemyState::Idle:
		IdleStart();
		break;
	case EnemyState::Attack:
		AttackStart();
		break;
	case EnemyState::Appear:
		AppearStart();
		break;
	case EnemyState::Death:
		DeathStart();
		break;
	case EnemyState::Hit:
		HitStart();
		break;
	case EnemyState::Run:
		RunStart();
		break;
	case EnemyState::Surprised:
		SurprisedStart();
		break;
	case EnemyState::Uturn:
		UturnStart();
		break;
	case EnemyState::Waiting:
		WaitingStart();
		break;
	default:
		break;
	}

	State = _State;
}


void Enemy::StateUpdate(float _Delta)
{
	switch (State)
	{
	case EnemyState::Idle:
		IdleUpdate(_Delta);
		break;
	case EnemyState::Attack:
		AttackUpdate(_Delta);
		break;
	case EnemyState::Appear:
		AppearUpdate(_Delta);
		break;
	case EnemyState::Death:
		DeathUpdate(_Delta);
		break;
	case EnemyState::Hit:
		HitUpdate(_Delta);
		break;
	case EnemyState::Run:
		RunUpdate(_Delta);
		break;
	case EnemyState::Surprised:
		SurprisedUpdate(_Delta);
		break;
	case EnemyState::Uturn:
		UturnUpdate(_Delta);
		break;
	case EnemyState::Waiting:
		WaitingUpdate(_Delta);
		break;
	default:
		break;
	}
}

void Enemy::IdleStart()
{

}

void Enemy::IdleUpdate(float _Delta)
{
}

void Enemy::AttackStart()
{
}

void Enemy::AttackUpdate(float _Delta)
{
}

void Enemy::AppearStart()
{
}

void Enemy::AppearUpdate(float _Delta)
{
}

void Enemy::DeathStart()
{
}

void Enemy::DeathUpdate(float _Delta)
{
}

void Enemy::HitStart()
{
}

void Enemy::HitUpdate(float _Delta)
{
}

void Enemy::RunStart()
{
}

void Enemy::RunUpdate(float _Delta)
{
}

void Enemy::SurprisedStart()
{
}

void Enemy::SurprisedUpdate(float _Delta)
{
}

void Enemy::UturnStart()
{
}

void Enemy::UturnUpdate(float _Delta)
{
}

void Enemy::WaitingStart()
{
}

void Enemy::WaitingUpdate(float _Delta)
{
}
