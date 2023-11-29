#include "PreCompile.h"
#include "Ghost_Med.h"
#include "FX.h"
#include "Level.h"

Ghost_Med::Ghost_Med() 
{
}

Ghost_Med::~Ghost_Med()
{
}


void Ghost_Med::Start()
{

	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("GameEngineResources");
	Dir.MoveChild("ContentsResources\\Sprite\\Enemy\\Ghost_Med");
	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	for (size_t i = 0; i < Directorys.size(); i++)
	{
		GameEngineDirectory& Dir = Directorys[i];

		GameEngineSprite::CreateFolder(Dir.GetStringPath());

	}

	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Enemy);
	MainSpriteRenderer->CreateAnimation("GhostMed_Attack1", "GhostMed_Attack1", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("GhostMed_Attack1", { 0.5f , 300.0f, false,
		{230.0f, 150.0f}, {130.0f, 80.0f},5}));
	MainSpriteRenderer->CreateAnimation("GhostMed_Attack2", "GhostMed_Attack2", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("GhostMed_Attack2", { 0.5f , 120.0f, false,
		{250.0f, 450.0f}, {40.0f, 200.0f},5}));
	MainSpriteRenderer->CreateAnimation("GhostMed_Attack3", "GhostMed_Attack3", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("GhostMed_Attack3", { 0.5f , 150.0f, false,
		{250.0f, 450.0f}, {40.0f, 200.0f},5 }));
	MainSpriteRenderer->CreateAnimation("GhostMed_Attack4", "GhostMed_Attack4", 0.06666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("GhostMed_Attack4", { 0.5f , 30.0f, false,
		{550.0f, 150.0f}, {0.0f, 80.0f},6}));
	MainSpriteRenderer->CreateAnimation("GhostMed_Appear", "GhostMed_Appear", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("GhostMed_Appear", { 0.5f }));
	MainSpriteRenderer->CreateAnimation("GhostMed_Idle", "GhostMed_Idle", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("GhostMed_Idle", { 0.5f }));
	MainSpriteRenderer->CreateAnimation("GhostMed_Death", "GhostMed_Death", 0.0666f, -1, -1, false);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("GhostMed_Death", { 0.5f }));
	MainSpriteRenderer->CreateAnimation("GhostMed_Hit", "GhostMed_Hit", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("GhostMed_Hit", { 0.5f }));
	MainSpriteRenderer->CreateAnimation("GhostMed_Run", "GhostMed_Idle", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("GhostMed_Run", { 0.5f }));
	MainSpriteRenderer->CreateAnimation("GhostMed_Surprised", "GhostMed_Surprised", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("GhostMed_Surprised", { 0.5f }));
	MainSpriteRenderer->CreateAnimation("GhostMed_Uturn", "GhostMed_Uturn", 0.0666f, -1, -1, false);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("GhostMed_Uturn", { 0.5f }));
	/*MainSpriteRenderer->CreateAnimation("Ghost_Waiting", "Ghost_Waiting", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Ghost_Waiting", { 0.5f }));*/


	//MainSpriteRenderer->SetSamplerState(SamplerOption::LINEAR);
	MainSpriteRenderer->AutoSpriteSizeOn();
	MainSpriteRenderer->SetPivotValue({ 0.0f, 1.0f });

	

	MainCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Enemy);
	MainCollision->Transform.SetLocalScale({ 100.0f, 250.0f });
	MainCollision->Transform.SetLocalPosition({ 0.0f, 120.0f });

	AttackCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Enemy_Attack);

	DetectCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Enemy_Detect);
	DetectCollision->Transform.SetLocalScale({ 1000.0f, 1000.0f });
	DetectCollision->Transform.SetLocalPosition({ -0.0f, 80.0f });
	DetectCollision->SetCollisionType(ColType::AABBBOX2D);


	DetectAttackCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Enemy_Detect);
	DetectAttackCollision->Transform.SetLocalScale({ 500.0f, 100.0f });
	DetectAttackCollision->Transform.SetLocalPosition({ 0.0f, 80.0f });
	DetectAttackCollision->SetCollisionType(ColType::AABBBOX2D);


	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X + 700.0f, -HalfWindowScale.Y });
	ChangeState(EnemyState::Idle);
	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("Ghost_Med_Idle_0001.png");

	DefaultScale = Tex.get()->GetScale();
	DashSpeed = 3000.0f;

	Enemy::Start();
	static int Num = 0;
	Num++;

	//SetName("Ghost_Med_" + std::to_string(Num));
	SetName("Ghost_Me");

	HP = 200;
}

void Ghost_Med::Update(float _Delta)
{
	Enemy::Update(_Delta);
}

void Ghost_Med::IdleStart()
{
	ChangeMainAnimation("GhostMed_Idle");
	MotionTime = 0.0f;
}

void Ghost_Med::IdleUpdate(float _Delta)
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
			return;
		}
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
		//패턴끝날때까지 못찾으면 false

		DetectPlayer = false;
		ChangeState(EnemyState::Uturn);
	}

}
	

void Ghost_Med::AttackStart()
{
	if (ComboStart == true)
	{
		GameEngineSound::SoundPlay("MedAttackInit");
		if (AttackPatern == MedAttackPatern::Combo)
		{
			AttackPatern = MedAttackPatern::Power;
		}
		else if (AttackPatern == MedAttackPatern::Power)
		{
			AttackPatern = MedAttackPatern::Combo;
		}
		ComboCount = 0;
		ComboStart = false;
	}

	std::string AnimationName;
	//ChangeMainAnimation("GhostMed_Attack");


	switch (AttackPatern)
	{
	case MedAttackPatern::Combo:

		ComboCount++;
		break;
	case MedAttackPatern::Power:
		ComboCount = 4;
		break;
	default:
		break;
	}
	 
	AnimationName = "GhostMed_Attack" + std::to_string(ComboCount);
	ChangeMainAnimation(AnimationName);

	// 공격의 시작일때미리 다음 공격 세팅
	
}

void Ghost_Med::AttackUpdate(float _Delta)
{
	switch (AttackPatern)
	{
	case MedAttackPatern::Combo:
		if (CheckStartAttackFrame(-1, 10.0f))
		{
			DashStartCheck = true;
			GameEngineSound::SoundPlay("MedAttackCombo" + std::to_string(ComboCount));
		}
		break;
	case MedAttackPatern::Power:
		if (CheckStartAttackFrame(-1, 13.0f) == true)
		{
			DashStartCheck = true;
			GameEngineSound::SoundPlay("MedAttackPower");
		}

		break;
	default:
		break;
	}
	
	/*if (true == CheckStartAttackFrame())
	{
		DashStartCheck = true;
	}*/
	CheckAttackCollision();
	DashProcessUpdate(_Delta, float4::RIGHT, DashSpeed);

	if (true == MainSpriteRenderer->IsCurAnimationEnd() )
	{
		if (ComboCount < 3 and AttackPatern == MedAttackPatern::Combo)
		{
			ChangeState(EnemyState::Attack);
		}

		else
		{
			ComboCount = 0;
			ChangeState(EnemyState::Run);
		}
	
	}
	
}

void Ghost_Med::AppearStart()
{
	ChangeMainAnimation("GhostMed_Appear");
}

void Ghost_Med::AppearUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(EnemyState::Run);
	}
}

void Ghost_Med::DeathStart()
{
	ChangeMainAnimation("GhostMed_Death");

}

void Ghost_Med::DeathUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		DeathEnd();
	}
}

void Ghost_Med::HitStart()
{
	ChangeMainAnimation("GhostMed_Hit");
}

void Ghost_Med::HitUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(EnemyState::Idle);
	}
}

void Ghost_Med::RunStart()
{
	ChangeMainAnimation("GhostMed_Run");
	MotionTime = 0.0f;
}

void Ghost_Med::RunUpdate(float _Delta)
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
				ComboStart = true;
				if (AttackCoolTimeCheck() == true)
				{
					ChangeState(EnemyState::Attack);
				}
				else
				{
					Transform.AddLocalPosition(-Dir * _Delta * MoveSpeed);
				}
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

void Ghost_Med::SurprisedStart()
{
	ChangeMainAnimation("GhostMed_Surprised");
	float4 Pos = Transform.GetLocalPosition() + float4(0.0f,100.0f,0.0f,0.0f);
	
	GetContentsLevel()->GetFXActor()->FXStart(FXType::Surprised, Flip, Pos);
}

void Ghost_Med::SurprisedUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd() == true)
	{
		FlipCheck();
		ChangeState(EnemyState::Run);
	}
}

void Ghost_Med::UturnStart()
{
	ChangeMainAnimation("GhostMed_Uturn");
}

void Ghost_Med::UturnUpdate(float _Delta)
{

	if (MainSpriteRenderer->IsCurAnimationEnd() == true)
	{
		Flip = !Flip;
		//FlipCheck();
		ChangeState(EnemyState::Run);
	}
}

void Ghost_Med::WaitingStart()
{
	//ChangeMainAnimation("Ghost_Waiting");
}

void Ghost_Med::WaitingUpdate(float _Delta)
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

