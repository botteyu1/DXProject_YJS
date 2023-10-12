#include "PreCompile.h"
#include "Ghost_Man.h"
Ghost_Man::Ghost_Man() 
{
}

Ghost_Man::~Ghost_Man()
{
}


void Ghost_Man::Start()
{

	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("GameEngineResources");
	Dir.MoveChild("ContentsResources\\Sprite\\Enemy\\Ghost_Man");
	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	for (size_t i = 0; i < Directorys.size(); i++)
	{
		GameEngineDirectory& Dir = Directorys[i];

		GameEngineSprite::CreateFolder(Dir.GetStringPath());

	}

	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Enemy);
	MainSpriteRenderer->CreateAnimation("Ghost_Attack", "Ghost_Attack", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Ghost_Attack", { 0.0f , 30.0f, false,
		{260.0f, 70.0f}, {130.0f, 50.0f},16, "Ghost_Attack_FX",{0.0f,0.5f} ,{ 55.0f, 50.0f } }));
	MainSpriteRenderer->CreateAnimation("Ghost_Appear", "Ghost_Appear", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Ghost_Appear", {0.0f}));
	MainSpriteRenderer->CreateAnimation("Ghost_idle", "Ghost_idle", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Ghost_idle", {0.0f}));
	MainSpriteRenderer->CreateAnimation("Ghost_Death", "Ghost_Death", 0.0666f, -1, -1, false);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Ghost_Death", {0.0f}));
	MainSpriteRenderer->CreateAnimation("Ghost_Hit", "Ghost_Hit", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Ghost_Hit", {0.0f}));
	MainSpriteRenderer->CreateAnimation("Ghost_Run", "Ghost_Run", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Ghost_Run", {0.0f}));
	MainSpriteRenderer->CreateAnimation("Ghost_Surprised", "Ghost_Surprised", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Ghost_Surprised", {0.0f}));
	MainSpriteRenderer->CreateAnimation("Ghost_Uturn", "Ghost_Uturn", 0.0666f, -1, -1, false);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Ghost_Uturn", {0.0f}));
	MainSpriteRenderer->CreateAnimation("Ghost_Waiting", "Ghost_Waiting", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Ghost_Waiting", {0.5f}));
	

	//MainSpriteRenderer->SetSamplerState(SamplerOption::LINEAR);
	MainSpriteRenderer->AutoSpriteSizeOn();
	MainSpriteRenderer->SetPivotValue({ 0.0f, 1.0f });

	AttackfxRenderer= CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Enemy_Attack);
	AttackfxRenderer->CreateAnimation("Ghost_Attack_FX", "Ghost_Attack_FX", 0.0666f, -1, -1, false);
	AttackfxRenderer->AutoSpriteSizeOn();
	AttackfxRenderer->Transform.SetLocalPosition({ 50.0f, 50.0f });
	AttackfxRenderer->Off();
	

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
	Transform.SetLocalPosition({ HalfWindowScale.X + 700.0f, -HalfWindowScale.Y, -500.0f });
	ChangeState(EnemyState::Waiting);
	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("Ghost_Idle_0001.png");

	DefaultScale = Tex.get()->GetScale();

	Enemy::Start();
}

void Ghost_Man::Update(float _Delta)
{
	Enemy::Update(_Delta);
	StateUpdate(_Delta);
}

void Ghost_Man::IdleStart()
{
	ChangeMainAnimation("Ghost_idle");
	MotionTime = 0.0f;
}

void Ghost_Man::IdleUpdate(float _Delta)
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

void Ghost_Man::AttackStart()
{
	ChangeMainAnimation("Ghost_Attack");
}

void Ghost_Man::AttackUpdate(float _Delta)
{
	CheckStartAttackFrame();
	CheckAttackCollision();

	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(EnemyState::Run);
	}
}

void Ghost_Man::AppearStart()
{
	ChangeMainAnimation("Ghost_Appear");
}

void Ghost_Man::AppearUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(EnemyState::Run);
	}
}

void Ghost_Man::DeathStart()
{
	ChangeMainAnimation("Ghost_Death");

}

void Ghost_Man::DeathUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		Off();
	}
}

void Ghost_Man::HitStart()
{
	ChangeMainAnimation("Ghost_Hit");
}

void Ghost_Man::HitUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(EnemyState::Idle);
	}
}

void Ghost_Man::RunStart()
{
	ChangeMainAnimation("Ghost_Run");
	MotionTime = 0.0f;
}

void Ghost_Man::RunUpdate(float _Delta)
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

void Ghost_Man::SurprisedStart()
{
	ChangeMainAnimation("Ghost_Surprised");
}

void Ghost_Man::SurprisedUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd() == true)
	{
		FlipCheck();
		ChangeState(EnemyState::Run);
	}
}

void Ghost_Man::UturnStart()
{
	ChangeMainAnimation("Ghost_Uturn");
}

void Ghost_Man::UturnUpdate(float _Delta)
{
	
	if (MainSpriteRenderer->IsCurAnimationEnd() == true)
	{
		Flip = !Flip;
		FlipCheck();
		ChangeState(EnemyState::Run);
	}
}

void Ghost_Man::WaitingStart()
{
	ChangeMainAnimation("Ghost_Waiting");
}

void Ghost_Man::WaitingUpdate(float _Delta)
{
	if (IsDetectPlayer())
	{
		if (LookPlayer() != Flip)
		{
			Flip = !Flip;
		}
		DetectPlayer = true;
		ChangeState(EnemyState::Appear);
	}
}

