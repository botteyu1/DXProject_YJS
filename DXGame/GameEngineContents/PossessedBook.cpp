#include "PreCompile.h"
#include "PossessedBook.h"
#include "Bullet.h"
#include "Player.h"

PossessedBook::PossessedBook() 
{
}

PossessedBook::~PossessedBook()
{
}

void PossessedBook::Start()
{

	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("GameEngineResources");
	Dir.MoveChild("ContentsResources\\Sprite\\Enemy\\PossessedBook");
	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	for (size_t i = 0; i < Directorys.size(); i++)
	{
		GameEngineDirectory& Dir = Directorys[i];
		GameEngineSprite::CreateFolder(Dir.GetStringPath());
	}

	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Enemy);
	MainSpriteRenderer->CreateAnimation("PossessedBook_Attack", "PossessedBook_Attack", 0.0333f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("PossessedBook_Attack", { 0.5f , 30.0f, false,
		{00.0f, 00.0f}, {130.0f, 50.0f},43 }));
	MainSpriteRenderer->CreateAnimation("PossessedBook_Idle", "PossessedBook_Idle", 0.02666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("PossessedBook_Idle", {  }));
	MainSpriteRenderer->CreateAnimation("PossessedBook_Death", "PossessedBook_Death", 0.0333f, -1, -1, false);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("PossessedBook_Death", { }));
	MainSpriteRenderer->CreateAnimation("PossessedBook_Hit", "PossessedBook_Hit", 0.0333f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("PossessedBook_Hit", { }));
	MainSpriteRenderer->CreateAnimation("PossessedBook_Suprised", "PossessedBook_Hit", 0.0333f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("PossessedBook_Suprised", { }));
	MainSpriteRenderer->CreateAnimation("PossessedBook_Run", "PossessedBook_Idle", 0.02666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("PossessedBook_Run", {  }));
	MainSpriteRenderer->CreateAnimation("PossessedBook_Uturn", "PossessedBook_Uturn", 0.0333f, -1, -1, false);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("PossessedBook_Uturn", {  }));


	//MainSpriteRenderer->SetSamplerState(SamplerOption::LINEAR);
	MainSpriteRenderer->AutoSpriteSizeOn();
	MainSpriteRenderer->Transform.AddLocalPosition({0.0f });
	MainSpriteRenderer->SetPivotValue({ 0.5f, 0.0f });

	//AttackfxRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Enemy_Attack);
	//AttackfxRenderer->CreateAnimation("GhostWoman_Attack_FX", "GhostWoman_Attack_FX", 0.0666f, -1, -1, false);
	//AttackfxRenderer->AutoSpriteSizeOn();
	//AttackfxRenderer->Transform.SetLocalPosition({ 50.0f, 50.0f });
	//AttackfxRenderer->Off();


	MainCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Enemy);
	MainCollision->Transform.SetLocalScale({ 50.0f, 50.0f });
	MainCollision->Transform.SetLocalPosition({ 0.0f, 40.0f, 1.0f });

	AttackCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Enemy_Attack);

	DetectCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Enemy_Detect);
	DetectCollision->Transform.SetLocalScale({ 1000.0f, 1000.0f });
	DetectCollision->Transform.SetLocalPosition({ -0.0f, 80.0f, 1.0f });
	DetectCollision->SetCollisionType(ColType::AABBBOX2D);


	DetectAttackCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Enemy_Detect);
	DetectAttackCollision->Transform.SetLocalScale({ 800.0f, 800.0f });
	DetectAttackCollision->Transform.SetLocalPosition({ 0.0f, 80.0f, 1.0f });
	DetectAttackCollision->SetCollisionType(ColType::AABBBOX2D);


	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X + 700.0f, -(HalfWindowScale.Y+ 2000.0f )});
	ChangeState(EnemyState::Idle);
	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("W1_Enemy_PossessedBook_Idle_0001.png");

	DefaultScale = Tex.get()->GetScale();

	//공중 몬스터
	ForceGrivityOff = true;

	MoveSpeed = 200.0f;

	Enemy::Start();
}

void PossessedBook::Update(float _Delta)
{
	Enemy::Update(_Delta);
	StateUpdate(_Delta);
}

void PossessedBook::IdleStart()
{
	ChangeMainAnimation("PossessedBook_Idle");
	MotionTime = 0.0f;
}

void PossessedBook::IdleUpdate(float _Delta)
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
	if (MotionTime >= 2.0f and CheckStartAttackFrame() == true)
	{
		//패턴끝날때까지 못찾으면 false

		DetectPlayer = false;
		ChangeState(EnemyState::Uturn);
	}
}

void PossessedBook::AttackStart()
{
	ChangeMainAnimation("PossessedBook_Attack");
	MainSpriteRenderer->SetAutoScaleRatio({ 0.5f, 0.5f,0.5f });
}

void PossessedBook::AttackUpdate(float _Delta)
{
	//CheckAttackCollision();
	if (CheckStartAttackFrame() == true)
	{
		std::shared_ptr <Bullet> Object = GetLevel()->CreateActor<Bullet>(ContentsObjectType::Bullet);

		float4 Pos2 = Transform.GetLocalPosition();
		float4 Pos = Transform.GetLocalPosition() + float4{ 50.0f, 50.0f };
		float4 PlayerDir = Player::GetMainPlayer()->Transform.GetLocalPosition() - Transform.GetLocalPosition() + float4{0.0f, 0.0f, 1.0f};

		Object->Init(BulletType::Fire, Pos, AttackDamage, PlayerDir, 500.f);
	}


	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		MainSpriteRenderer->SetAutoScaleRatio({ 1.0f, 1.0f ,1.0f});
		ChangeState(EnemyState::Run);
	}
}

void PossessedBook::AppearStart()
{
	
}

void PossessedBook::AppearUpdate(float _Delta)
{
	
}

void PossessedBook::DeathStart()
{
	ChangeMainAnimation("PossessedBook_Death");

}

void PossessedBook::DeathUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		Off();
	}
}

void PossessedBook::HitStart()
{
	ChangeMainAnimation("PossessedBook_Hit");
}

void PossessedBook::HitUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(EnemyState::Idle);
	}
}

void PossessedBook::RunStart()
{
	ChangeMainAnimation("PossessedBook_Run");
	MotionTime = 0.0f;
}

void PossessedBook::RunUpdate(float _Delta)
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
	if (MotionTime >= 2.0f and CheckStartAttackFrame() == true)
	{

		ChangeState(EnemyState::Idle);
	}
}

void PossessedBook::SurprisedStart()
{
	ChangeMainAnimation("PossessedBook_Suprised");
	
}

void PossessedBook::SurprisedUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd() == true)
	{
		FlipCheck();
		ChangeState(EnemyState::Run);
	}
}

void PossessedBook::UturnStart()
{
	ChangeMainAnimation("PossessedBook_Uturn");
}

void PossessedBook::UturnUpdate(float _Delta)
{

	if (MainSpriteRenderer->IsCurAnimationEnd() == true)
	{
		Flip = !Flip;
		FlipCheck();
		ChangeState(EnemyState::Run);
	}
}

void PossessedBook::WaitingStart()
{
	//ChangeMainAnimation("GhostWoman_Waiting");
}

void PossessedBook::WaitingUpdate(float _Delta)
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
