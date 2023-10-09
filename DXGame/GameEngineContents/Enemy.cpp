#include "PreCompile.h"
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy() 
{
}

Enemy::~Enemy()
{
}

void Enemy::TakeDamage(GameEngineCollision* _Player ,int _Damage)
{
	HP -= _Damage;
	ChangeState(EnemyState::Hit);

	//맞을 떄 플레이어 쪽을 바라보도록
	LookPlayer();
	FlipCheck();
}

void Enemy::LookPlayer()
{
	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition();
	float4 EnemyPos = Transform.GetLocalPosition();
	if (PlayerPos.X < EnemyPos.X)
	{
		Flip = true;
	}
	else
	{
		Flip = false;
	}
	
}
bool Enemy::IsDetectPlayer()
{
	if (DetectCollision->Collision<ContentsCollisionType>(ContentsCollisionType::Player))
	{
		float4 PlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition() + (0.0f, -100.0f);
		float4 EnemyPos = Transform.GetLocalPosition()+ (0.0f, -100.0f);
		float4 Distance = PlayerPos - EnemyPos;

		for (int i = 1; i < 10; i++)
		{
			float4 CheckPos = EnemyPos + (Distance * ( static_cast<float>(i)/ 10.0f ));
			GameEngineColor Color = PosCollisionCheck(CheckPos);
			if (Color == GameEngineColor::RED or Color == GameEngineColor::BLUE)
			{
 				return false;
			}
		}
		return true;
	}
	return false;
}


void Enemy::Start()
{
	Actor::Start();
}


void Enemy::FlipCheck()
{
	if (Flip == true)
	{
		
		if (Flip != FlipPrev)
		{
			Dir = float4::LEFT;
			MainSpriteRenderer->SetPivotValue({ 1.0f, 1.0f });
			MainSpriteRenderer->LeftFlip();
			MainSpriteRenderer->Transform.AddLocalPosition({ -DefaultScale.X,0.0f });
		}
		FlipPrev = Flip;
	}
	if (Flip == false)
	{
		
		if (Flip != FlipPrev)
		{
			Dir = float4::RIGHT;
			MainSpriteRenderer->SetPivotValue({ 0.0f, 1.0f });
			MainSpriteRenderer->RightFlip();
			MainSpriteRenderer->Transform.AddLocalPosition({ DefaultScale.X,0.0f });
		}
		FlipPrev = Flip;
	}
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
