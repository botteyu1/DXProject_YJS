#include "PreCompile.h"
#include "Ghost_Woman.h"
#include "Bullet.h"
#include "Player.h"

Ghost_Woman::Ghost_Woman()
{
}

Ghost_Woman::~Ghost_Woman()
{
}

void Ghost_Woman::Start()
{

	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("GameEngineResources");
	Dir.MoveChild("ContentsResources\\Sprite\\Enemy\\Ghost_Woman");
	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	for (size_t i = 0; i < Directorys.size(); i++)
	{
		GameEngineDirectory& Dir = Directorys[i];

		GameEngineSprite::CreateFolder(Dir.GetStringPath());

	}

	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Enemy);
	MainSpriteRenderer->CreateAnimation("GhostWoman_Attack", "GhostWoman_Attack", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("GhostWoman_Attack", { 0.0f , 30.0f, false,
		{260.0f, 70.0f}, {130.0f, 50.0f},16 }));
	MainSpriteRenderer->CreateAnimation("GhostWoman_Appear", "GhostWoman_Appear", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("GhostWoman_Appear", { 0.0f }));
	MainSpriteRenderer->CreateAnimation("GhostWoman_idle", "GhostWoman_idle", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("GhostWoman_idle", { 0.0f }));
	MainSpriteRenderer->CreateAnimation("GhostWoman_Death", "GhostWoman_Death", 0.0666f, -1, -1, false);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("GhostWoman_Death", { 0.0f }));
	MainSpriteRenderer->CreateAnimation("GhostWoman_Hit", "GhostWoman_Hit", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("GhostWoman_Hit", { 0.0f }));
	MainSpriteRenderer->CreateAnimation("GhostWoman_Run", "GhostWoman_idle", 0.0366f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("GhostWoman_Run", { 0.0f }));
	MainSpriteRenderer->CreateAnimation("GhostWoman_Surprised", "GhostWoman_Surprised", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("GhostWoman_Surprised", { 0.0f }));
	MainSpriteRenderer->CreateAnimation("GhostWoman_Uturn", "GhostWoman_Uturn", 0.0666f, -1, -1, false);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("GhostWoman_Uturn", { 0.0f }));


	//MainSpriteRenderer->SetSamplerState(SamplerOption::LINEAR);
	MainSpriteRenderer->AutoSpriteSizeOn();
	MainSpriteRenderer->Transform.AddLocalPosition({ 30.0f });
	MainSpriteRenderer->SetPivotValue({ 0.0f, 1.0f });

	//AttackfxRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Enemy_Attack);
	//AttackfxRenderer->CreateAnimation("GhostWoman_Attack_FX", "GhostWoman_Attack_FX", 0.0666f, -1, -1, false);
	//AttackfxRenderer->AutoSpriteSizeOn();
	//AttackfxRenderer->Transform.SetLocalPosition({ 50.0f, 50.0f });
	//AttackfxRenderer->Off();


	MainCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Enemy);
	MainCollision->Transform.SetLocalScale({ 50.0f, 100.0f });
	MainCollision->Transform.SetLocalPosition({ 0.0f, 80.0f, 1.0f });

	AttackCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Enemy_Attack);

	DetectCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Enemy_Detect);
	DetectCollision->Transform.SetLocalScale({ 1000.0f, 1000.0f });
	DetectCollision->Transform.SetLocalPosition({ -0.0f, 80.0f, 1.0f });
	DetectCollision->SetCollisionType(ColType::AABBBOX2D);


	DetectAttackCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Enemy_Detect);
	DetectAttackCollision->Transform.SetLocalScale({ 300.0f, 100.0f });
	DetectAttackCollision->Transform.SetLocalPosition({ 0.0f, 80.0f, 1.0f });
	DetectAttackCollision->SetCollisionType(ColType::AABBBOX2D);


	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X + 1000.0f, -HalfWindowScale.Y, -500.0f });
	ChangeState(EnemyState::Idle);
	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("Enemy_Ghost_Woman_IDLE_0001.png");

	DefaultScale = Tex.get()->GetScale();

	Enemy::Start();
}

void Ghost_Woman::Update(float _Delta)
{
	Enemy::Update(_Delta);
	StateUpdate(_Delta);
}

void Ghost_Woman::IdleStart()
{
	ChangeMainAnimation("GhostWoman_idle");
	MotionTime = 0.0f;
}

void Ghost_Woman::IdleUpdate(float _Delta)
{

	bool PreFlip = Flip;
	if (IsDetectPlayer())
	{
		//플레이어 반대방향에있으면
		if (LookPlayer() != Flip)
		{
			ChangeState(EnemyState::Uturn);

			return;
		}
		//발견중이였다면
		if (DetectPlayer = true)
		{
			ChangeState(EnemyState::Run);
		}
		else
		{
			DetectPlayer = true;
			ChangeState(EnemyState::Surprised);
		}
	}


	MotionTime += _Delta;
	if (MotionTime >= 2.0f)
	{
		//패턴끝날때까지 못찾으면 false

		DetectPlayer = false;
		ChangeState(EnemyState::Uturn);
	}
}

void Ghost_Woman::AttackStart()
{
	ChangeMainAnimation("GhostWoman_Attack");
	
	std::shared_ptr <Bullet> Object = GetLevel()->CreateActor<Bullet>(ContentsObjectType::Bullet);

	float4 Pos = Transform.GetLocalPosition();
	float4 PlayerDir = Player::GetMainPlayer()->Transform.GetLocalPosition() - Pos;

	Object->Init(BulletType::Fire, Pos, AttackDamage, PlayerDir, 200.f);
}

void Ghost_Woman::AttackUpdate(float _Delta)
{
	CheckStartAttackFrame();
	CheckAttackCollision();

	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(EnemyState::Run);
	}
}

void Ghost_Woman::AppearStart()
{
	ChangeMainAnimation("GhostWoman_Appear");
}

void Ghost_Woman::AppearUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(EnemyState::Run);
	}
}

void Ghost_Woman::DeathStart()
{
	ChangeMainAnimation("GhostWoman_Death");

}

void Ghost_Woman::DeathUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		Off();
	}
}

void Ghost_Woman::HitStart()
{
	ChangeMainAnimation("GhostWoman_Hit");
}

void Ghost_Woman::HitUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(EnemyState::Idle);
	}
}

void Ghost_Woman::RunStart()
{
	ChangeMainAnimation("GhostWoman_Run");
	MotionTime = 0.0f;
}

void Ghost_Woman::RunUpdate(float _Delta)
{
	Transform.AddLocalPosition(Dir * _Delta * MoveSpeed);

	// 플레이어 발견시
	bool PreFlip = Flip;

	if (IsDetectPlayer())
	{
		//발견중이였다면
		if (DetectPlayer == true)
		{
			if (LookPlayer() != Flip)
			{
				ChangeState(EnemyState::Uturn);
				return;
			}
			if (DetectAttackCollision->Collision<ContentsCollisionType>(ContentsCollisionType::Player))
			{
				ChangeState(EnemyState::Attack);
			}
			return;
		}
		// 새로 발견하면
		else
		{
			DetectPlayer = true;
			ChangeState(EnemyState::Surprised);
			return;
		}
	}

	MotionTime += _Delta;
	if (MotionTime >= 2.0f)
	{

		ChangeState(EnemyState::Idle);
	}
}

void Ghost_Woman::SurprisedStart()
{
	ChangeMainAnimation("GhostWoman_Surprised");
}

void Ghost_Woman::SurprisedUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd() == true)
	{
		FlipCheck();
		ChangeState(EnemyState::Run);
	}
}

void Ghost_Woman::UturnStart()
{
	ChangeMainAnimation("GhostWoman_Uturn");
}

void Ghost_Woman::UturnUpdate(float _Delta)
{

	if (MainSpriteRenderer->IsCurAnimationEnd() == true)
	{
		Flip = !Flip;
		FlipCheck();
		ChangeState(EnemyState::Run);
	}
}

void Ghost_Woman::WaitingStart()
{
	//ChangeMainAnimation("GhostWoman_Waiting");
}

void Ghost_Woman::WaitingUpdate(float _Delta)
{
	/*if (IsDetectPlayer())
	{
		if (LookPlayer() != Flip)
		{
			Flip = !Flip;
		}
		DetectPlayer = true;
		ChangeState(EnemyState::Appear);
	}*/
}

