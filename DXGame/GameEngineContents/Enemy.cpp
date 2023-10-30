#include "PreCompile.h"
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy() 
{
}

Enemy::~Enemy()
{
}

void Enemy::TakeDamage(GameEngineCollision* _Attacker,float _Damage)
{
	HP -= static_cast<int>(_Damage);
	ChangeState(EnemyState::Hit);

	//���� �� �÷��̾� ���� �ٶ󺸵���
	LookPlayer();
	FlipCheck();
}

void Enemy::CheckAttackCollision()
{
	EventParameter Parameter;

	Parameter.Enter = ComboHit;

	AttackCollision->CollisionEvent<ContentsCollisionType>(ContentsCollisionType::Player, { ComboHit,nullptr,nullptr });
}

void Enemy::ComboHit(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
	float Damagef = _Left->GetParent<Enemy>()->GetAttackDamage();
	_Right->GetParent<Player>()->TakeDamage(_Left, Damagef);
}



bool Enemy::LookPlayer()  //�����̸� false �������̸� Ʈ��
{
	float4 PlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition();
	float4 EnemyPos = Transform.GetLocalPosition();
	if (PlayerPos.X < EnemyPos.X)
	{
		return true;
	}
	else
	{
		return false;
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

void Enemy::Update(float _Delta)
{	
	Actor::Update(_Delta);
	if (DebugValue == true)
	{
		return;
	}
	StateUpdate(_Delta);

	

	if (HP <= 0 and DeathValue == false)
	{ 
		DeathValue = true;
		ChangeState(EnemyState::Death);
	}

	//if (AttackCoolTimeCheck <= AttackCoolTime)
	//{
	//	return;
	//}

	//AttackCoolTimeCheck += _Delta;
}




void Enemy::ChangeState(EnemyState _State)
{
	switch (_State)
	{
	case EnemyState::Idle:
		IdleStart();
		break;
	case EnemyState::Attack:
		
		AttackCoolTimeCheck = 0.0f;
		AttackStart();
		break;
	case EnemyState::Attack_Init:
		Attack_InitStart();
		break;
	case EnemyState::Attack_End:
		Attack_EndStart();
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
	case EnemyState::Intro:
		IntroStart();
		break;
	case EnemyState::IntroIdle:
		IntroIdleStart();
		break;
	case EnemyState::End:
		EndStart();
		break;
	case EnemyState::Outro:
		OutroStart();
		break;
	default:
		break;
	}
	FrameCheck = false;
	DashStartCheck = false;
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
	case EnemyState::Attack_Init:
		Attack_InitUpdate(_Delta);
		break;
	case EnemyState::Attack_End:
		Attack_EndUpdate(_Delta);
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
	case EnemyState::Intro:
		IntroUpdate(_Delta);
		break;
	case EnemyState::IntroIdle:
		IntroIdleUpdate(_Delta);
		break;
	case EnemyState::End:
		EndUpdate(_Delta);
		break;
	case EnemyState::Outro:
		OutroUpdate(_Delta);
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

void Enemy::Attack_InitStart()
{
}

void Enemy::Attack_InitUpdate(float _Delta)
{
}

void Enemy::Attack_EndStart()
{
}

void Enemy::Attack_EndUpdate(float _Delta)
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

void Enemy::IntroStart()
{
}

void Enemy::IntroIdleStart()
{
}

void Enemy::EndStart()
{
}

void Enemy::OutroStart()
{
}

void Enemy::IntroUpdate(float _Delta)
{
}

void Enemy::IntroIdleUpdate(float _Delta)
{
}

void Enemy::EndUpdate(float _Delta)
{
}

void Enemy::OutroUpdate(float _Delta)
{
}
