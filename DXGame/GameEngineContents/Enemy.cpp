#include "PreCompile.h"
#include "Enemy.h"
#include "Player.h"
#include "FX.h"
#include "FxSpriteRenderer.h"
#include "AnimaDrop.h"
#include "SoularyDrop.h"

Enemy::Enemy() 
{
}

Enemy::~Enemy()
{
}

void Enemy::TakeDamage(GameEngineCollision* _Attacker,float _Damage)
{
	if (State == EnemyState::Death)
	{
		return;
	}

	static bool HitSound = false;
	HitSound = !HitSound;

	if (HitSound == true)
	{

		GameEngineSound::SoundPlay("EnemyHit1");
	}
	else
	{

		GameEngineSound::SoundPlay("EnemyHit2");
	}

	HP -= static_cast<int>(_Damage);


	GetContentsLevel()->StartScreenShake(0.5f, 8.0f, 10.0f);

	// 데미지 표기
	GetContentsLevel()->GetFXActor()->FXTextStart(FXType::DamageText, std::to_string(static_cast<int>(_Damage)), Transform.GetLocalPosition() + float4(0.0f, 60.0f),30.0f);

	ChangeState(EnemyState::Hit);


	//맞을 떄 플레이어 쪽을 바라보도록
	Flip = LookPlayer();
	FlipCheck();

	HitPushBackTimeCheck = 0.0f;
	//이펙트
	GetContentsLevel()->GetFXActor()->FXStart(FXType::Splash_Water, Flip, Transform.GetLocalPosition() + float4(0.0f, 50.0f));
	GetContentsLevel()->GetFXActor()->FXStart(FXType::Slash, Flip, Transform.GetLocalPosition() + float4(0.0f, 50.0f));
}


void Enemy::HitPushBackUpdate(float _Delta)
{
	if (HitPushBackTimeCheck < HitPushBackTime)
	{
		HitPushBackTimeCheck += _Delta;
		if (Flip == false)
		{
			Transform.AddLocalPosition(float4(-500.0f * _Delta));
		}
		else
		{
			Transform.AddLocalPosition(float4(500.0f * _Delta));
		}
	}
}

bool Enemy::AttackCoolTimeCheck()
{
	if (AttackCoolDownTimer < AttackCoolDown)
	{
		AttackCoolDownTimer = 0.0f;
		return true;
	}
	return false;
}

void Enemy::CheckAttackCollision()
{
	EventParameter Parameter;

	Parameter.Enter = ComboHit;

	AttackCollision->CollisionEvent<ContentsCollisionType>(ContentsCollisionType::Player, { ComboHit,nullptr,nullptr });
}

void Enemy::DeathCheck()
{
	if (HP <= 0 and DeathValue == false)
	{

		static bool DeathSound = false;
		DeathSound = !DeathSound;

		if (DeathSound == true)
		{
			GameEngineSound::SoundPlay("EnemyDeath1");
		}
		else
		{

			GameEngineSound::SoundPlay("EnemyDeath2");
		}

		DeathValue = true;
		ChangeState(EnemyState::Death);
		GetContentsLevel()->StartScreenShake(0.5f, 12.0f, 10.0f);
		std::shared_ptr<AnimaDrop> Object2 =  GetContentsLevel()->CreateActor<AnimaDrop>(ContentsObjectType::BackGroundobject);
		Object2->Spawn(Transform.GetLocalPosition());
		std::shared_ptr<SoularyDrop> Object =  GetContentsLevel()->CreateActor<SoularyDrop>(ContentsObjectType::BackGroundobject);
		Object->Spawn(Transform.GetLocalPosition());
		Object =  GetContentsLevel()->CreateActor<SoularyDrop>(ContentsObjectType::BackGroundobject);
		Object->Spawn(Transform.GetLocalPosition());
		Object =  GetContentsLevel()->CreateActor<SoularyDrop>(ContentsObjectType::BackGroundobject);
		Object->Spawn(Transform.GetLocalPosition());
		Object =  GetContentsLevel()->CreateActor<SoularyDrop>(ContentsObjectType::BackGroundobject);
		Object->Spawn(Transform.GetLocalPosition());
		Object =  GetContentsLevel()->CreateActor<SoularyDrop>(ContentsObjectType::BackGroundobject);
		Object->Spawn(Transform.GetLocalPosition());
		Object =  GetContentsLevel()->CreateActor<SoularyDrop>(ContentsObjectType::BackGroundobject);
		Object->Spawn(Transform.GetLocalPosition());
	}
}

void Enemy::DeathEnd()
{
	Off();
	
}



void Enemy::ComboHit(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
	float Damagef = _Left->GetParent<Enemy>()->GetCurDamage();
	_Right->GetParent<Player>()->TakeDamage(_Left, Damagef);
}



bool Enemy::LookPlayer()  //왼쪽이면 false 오른쪽이며 트루
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

	HitPushBackUpdate(_Delta);
	DeathCheck();
	AttackCoolDownTimer += _Delta;
	

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
		if (AttackCoolTimeCheck() == true)
		{
			AttackStart();
		}
		else
		{
			return;
		}
		
		
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


void Enemy::Spawn()
{

	std::shared_ptr<FxSpriteRenderer> Renderer = GetContentsLevel()->GetFXActor()->FXStart(FXType::SpawnEnemy, false, Transform.GetLocalPosition() + float4(0.0f, 20.0f));
	Renderer->SetSpawnObject(this);
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
