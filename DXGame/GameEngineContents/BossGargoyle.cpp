#include "PreCompile.h"	
#include "BossGargoyle.h"
#include "Player.h"

BossGargoyle::BossGargoyle() 
{
}

BossGargoyle::~BossGargoyle()
{
}

void BossGargoyle::TakeDamage(GameEngineCollision* _Attacker, float _Damage)
{
	HP -= static_cast<int>(_Damage);
}

void BossGargoyle::Start()
{

	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("GameEngineResources");
	Dir.MoveChild("ContentsResources\\Sprite\\Boss");
	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	for (size_t i = 0; i < Directorys.size(); i++)
	{
		GameEngineDirectory& Dir = Directorys[i];

		GameEngineSprite::CreateFolder(Dir.GetStringPath());

	}

	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Enemy);
	MainSpriteRenderer->CreateAnimation("Gargoyle_Combo1", "Gargoyle_Combo1", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Combo1", { 1.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Combo2", "Gargoyle_Combo2", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Combo2", { 1.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Combo3", "Gargoyle_Combo3", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Combo3", { 1.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Dive_Attack_End", "Gargoyle_Dive_Attack_End", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Dive_Attack_End", { 1.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Dive_Attack_Loop", "Gargoyle_Dive_Attack_Loop", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Dive_Attack_Loop", { 1.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_DiveAttack_Anticipation", "Gargoyle_DiveAttack_Anticipation", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_DiveAttack_Anticipation", { 1.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_End_1", "Gargoyle_End_1", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_End_1", { 1.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_End_2", "Gargoyle_End_2", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_End_2", { 1.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Fly_Stomp_Anticipation", "Gargoyle_Fly_Stomp_Anticipation", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Fly_Stomp_Anticipation", { 1.0f }));

	/*MainSpriteRenderer->CreateAnimation("Gargoyle_Fly_Stomp_Anticipation", "Gargoyle_Fly_Stomp_Anticipation", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Fly_Stomp_Anticipation", { 0.0f }));*/

	MainSpriteRenderer->CreateAnimation("Gargoyle_Hit", "Gargoyle_Hit", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Hit", { 1.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Idle", "Gargoyle_Idle", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Idle", { 1.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Intro", "Gargoyle_Intro", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Intro", { 1.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Posing1", "Gargoyle_Posing1", 0.366f, -1, -1, false);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Posing1", {1.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Posing2", "Gargoyle_Posing2", 0.366f, -1, -1, false);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Posing2", {1.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Posing3", "Gargoyle_Posing3", 0.366f, -1, -1, false);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Posing3", {1.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Posing4", "Gargoyle_Posing4", 0.366f, -1, -1, false);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Posing4", {1.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Posing5", "Gargoyle_Posing5", 0.666f, -1, -1, false);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Posing5", {1.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Posing6", "Gargoyle_Posing6", 0.666f, -1, -1, false);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Posing6", {1.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Posing7", "Gargoyle_Posing7", 0.666f, -1, -1, false);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Posing7", {1.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_SpinAir", "Gargoyle_SpinAir", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_SpinAir", { 1.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_SpinGround", "Gargoyle_SpinGround", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_SpinGround", { 1.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Stun_End", "Gargoyle_Stun_End", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Stun_End", { 1.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Stun_idle", "Gargoyle_Stun_idle", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Stun_idle", { 1.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Stun_Start", "Gargoyle_Stun_Start", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Stun_Start", { 1.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Uturn", "Gargoyle_Uturn", 0.0333f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Uturn", { 1.0f }));

	MainSpriteRenderer->AutoSpriteSizeOn();
	MainSpriteRenderer->SetPivotValue({ 0.0f, 1.0f });

	

	MainCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Enemy);
	MainCollision->Transform.SetLocalScale({ 100.0f, 250.0f });
	MainCollision->Transform.SetLocalPosition({ 0.0f, 120.0f });

	AttackCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Enemy_Attack);

	DetectCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Enemy_Detect);
	DetectCollision->Transform.SetLocalScale({ 3000.0f, 3000.0f });
	DetectCollision->Transform.SetLocalPosition({ -0.0f, 80.0f });
	DetectCollision->SetCollisionType(ColType::AABBBOX2D);


	DetectAttackCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Enemy_Detect);
	DetectAttackCollision->Transform.SetLocalScale({ 500.0f, 100.0f });
	DetectAttackCollision->Transform.SetLocalPosition({ 0.0f, 80.0f });
	DetectAttackCollision->SetCollisionType(ColType::AABBBOX2D);

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X + 700.0f, -HalfWindowScale.Y });
	ChangeState(EnemyState::Idle);
	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("Boss_Gargoyle_Idle_0001.png");

	DefaultScale = Tex.get()->GetScale();
	DashSpeed = 3000.0f;

	Enemy::Start();

	SetName("Gargoyle");
}

void BossGargoyle::Update(float _Delta)
{
	Enemy::Update(_Delta);
}

void BossGargoyle::IdleStart()
{
	ChangeMainAnimation("Gargoyle_Idle");
	MotionTime = 0.0f;
}

void BossGargoyle::IdleUpdate(float _Delta)
{
	
	MotionTime += _Delta;
	if (MotionTime < 2.0f)
	{
		return;
	}
	bool PreFlip = Flip;
	Flip = LookPlayer();
	//플레이어 반대방향에있으면
	if (Flip != PreFlip)
	{
		ChangeState(EnemyState::Uturn);
		return;
	}
	else
	{
		ChangeState(EnemyState::Run);
	}
}


void BossGargoyle::AttackStart()
{
	MotionTime = 0.0f;
	std::string AnimationName;
	switch (AttackPatern)
	{
	case GargoyleAttackPatern::Combo:
	{
		if (ComboStart == true)
		{
			ComboCount = 0;
			ComboStart = false;
		}
		ComboCount++;
		AnimationName = "Gargoyle_Combo" + std::to_string(ComboCount);
		break;
	}
	case GargoyleAttackPatern::Posing:
	{
		PosingCount++;
		AnimationName = "Gargoyle_Posing" + std::to_string(PosingCount);
		if (PosingCount >= 7)
		{
			PosingCount = 0;
		}
		break;
	}
	case GargoyleAttackPatern::Dive:
		break;
	case GargoyleAttackPatern::Spin:
		break;
	case GargoyleAttackPatern::Max:
		break;
	default:
		break;
	}

	ChangeMainAnimation(AnimationName);

	
	////ChangeMainAnimation("GhostMed_Attack");
	//switch (AttackPatern)
	//{
	//case MedAttackPatern::Combo:
	//	ComboCount++;
	//	break;
	//case MedAttackPatern::Power:
	//	ComboCount = 4;
	//	break;
	//default:
	//	break;
	//}

	//AnimationName = "GhostMed_Attack" + std::to_string(ComboCount);
	
}

void BossGargoyle::AttackUpdate(float _Delta)
{
	MotionTime += _Delta;

	if (true == CheckStartAttackFrame())
	{
		DashStartCheck = true;
	}
	CheckAttackCollision();
	DashProcessUpdate(_Delta, float4::RIGHT, DashSpeed);

	switch (AttackPatern)
	{
	case GargoyleAttackPatern::Combo:
	{
		if (true == MainSpriteRenderer->IsCurAnimationEnd())
		{
			if (ComboCount < 3)
			{
				ChangeState(EnemyState::Attack);
			}
			else
			{
				ComboCount = 0;
				ComboStart = true;
				AttackPatern = static_cast<GargoyleAttackPatern>(static_cast<int>(AttackPatern) + 1);
				ChangeState(EnemyState::Idle);
			}
		}
		break;
	}
	case GargoyleAttackPatern::Posing:
	{
		if (MotionTime >= 0.5f)
		{
			ForceGrivityOff = false;
		}

		if (AerialCheck == false)
		{
			ChangeState(EnemyState::Idle);
		}
	}
		break;
	case GargoyleAttackPatern::Dive:
		break;
	case GargoyleAttackPatern::Spin:
		break;
	case GargoyleAttackPatern::Max:
		break;
	default:
		break;
	}


	
}

void BossGargoyle::AppearStart()
{
}

void BossGargoyle::AppearUpdate(float _Delta)
{
}

void BossGargoyle::DeathStart()
{
}

void BossGargoyle::DeathUpdate(float _Delta)
{
}

void BossGargoyle::HitStart()
{
	ChangeMainAnimation("Gargoyle_Hit");
}

void BossGargoyle::HitUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(EnemyState::Idle);
	}
}

void BossGargoyle::RunStart()
{

	MotionTime = 0.0f;
	switch (AttackPatern)
	{
	case GargoyleAttackPatern::Combo:
	{
		ChangeMainAnimation("Gargoyle_Idle");
		break;
	}
	case GargoyleAttackPatern::Posing:
	{
		TargetPlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition() + float4{ 0.0f,400.0f,0.0f };
		TargetPos = Transform.GetLocalPosition() + float4{ 0.0f, 50.0f };
		ForceGrivityOff = true;
		ChangeMainAnimation("Gargoyle_SpinAir");
		break;
	}
	case GargoyleAttackPatern::Dive:
	{

	}
	case GargoyleAttackPatern::Spin:
		break;
	case GargoyleAttackPatern::Max:
		break;
	default:
		break;
	}
}

void BossGargoyle::RunUpdate(float _Delta)
{
	//MotionTime += _Delta;

	switch (AttackPatern)
	{
	case GargoyleAttackPatern::Combo:
	{
		Transform.AddLocalPosition(Dir * _Delta * MoveSpeed);

		if (DetectAttackCollision->Collision<ContentsCollisionType>(ContentsCollisionType::Player))
		{
			ChangeState(EnemyState::Attack);
			return;
		}
		else if (Flip != LookPlayer())
		{
			Flip = LookPlayer();
			ChangeState(EnemyState::Uturn);
			return;
		}
		break;
	}
	case GargoyleAttackPatern::Posing:
	{
		MotionTime += _Delta * 2.0f;
		float4 Pos = float4::LerpClamp(TargetPos, TargetPlayerPos, MotionTime);
		Transform.SetLocalPosition(Pos);
		if (1.0f <= MotionTime)
		{
			
			ChangeState(EnemyState::Attack);
			return;
		}
		break;
	}
	case GargoyleAttackPatern::Dive:
		break;
	case GargoyleAttackPatern::Spin:
		break;
	case GargoyleAttackPatern::Max:
		break;
	default:
		break;
	}
	
	


	
}

void BossGargoyle::SurprisedStart()
{
}

void BossGargoyle::SurprisedUpdate(float _Delta)
{
}

void BossGargoyle::UturnStart()
{
	Flip = !Flip;
	ChangeMainAnimation("Gargoyle_Uturn");
}

void BossGargoyle::UturnUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd() == true)
	{
		Flip = !Flip;
		ChangeState(EnemyState::Run);
	}
}

void BossGargoyle::WaitingStart()
{
}

void BossGargoyle::WaitingUpdate(float _Delta)
{
}

