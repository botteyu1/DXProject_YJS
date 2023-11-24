#include "PreCompile.h"	
#include "BossGargoyle.h"
#include "Player.h"
#include "ContentsCore.h"
#include "Bullet.h"
#include "FX.h"

BossGargoyle::BossGargoyle() 
{
}

BossGargoyle::~BossGargoyle()
{
}

void BossGargoyle::TakeDamage(GameEngineCollision* _Attacker, float _Damage)
{
	if (State == EnemyState::Death)
	{
		return;
	}

	HP -= static_cast<int>(_Damage);


	GetContentsLevel()->StartScreenShake(0.5f, 8.0f, 10.0f);

	// 데미지 표기
	GetContentsLevel()->GetFXActor()->FXTextStart(FXType::DamageText, std::to_string(static_cast<int>(_Damage)), Transform.GetLocalPosition() + float4(0.0f, 60.0f), 30.0f);

	
	GetContentsLevel()->GetFXActor()->FXStart(FXType::Splash_Water, Flip, Transform.GetLocalPosition() + float4(0.0f, 50.0f));
	GetContentsLevel()->GetFXActor()->FXStart(FXType::Slash, Flip, Transform.GetLocalPosition() + float4(0.0f, 50.0f));

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
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Combo1", { 1.0f, 300.0f, false,
		{230.0f, 150.0f}, {130.0f, 80.0f},10 }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Combo2", "Gargoyle_Combo2", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Combo2", { 1.0f,120.0f, false,
	{250.0f, 350.0f}, {100.0f, 200.0f},6 }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Combo3", "Gargoyle_Combo3", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Combo3", { 1.0f ,250.0f, false,
		{350.0f, 350.0f}, {40.0f, 200.0f},10 }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Dive_Attack_End", "Gargoyle_Dive_Attack_End", 0.0666f, -1, -1, false);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Dive_Attack_End", { 0.8f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Dive_Attack_Turn", "Gargoyle_Dive_Attack_Turn", 0.0666f, -1, -1, false);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Dive_Attack_Turn", { 0.8f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Dive_Attack_Loop", "Gargoyle_Dive_Attack_Loop", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Dive_Attack_Loop", { 0.8f, 0.0f, false,
		{200.0f, 150.0f}, {0.0f, 80.0f},0 }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_DiveAttack_Anticipation", "Gargoyle_DiveAttack_Anticipation", 0.0666f, -1, -1, false);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_DiveAttack_Anticipation", { 1.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_End_1", "Gargoyle_End_1", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_End_1", { 1.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_End_2", "Gargoyle_End_2", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_End_2", { 1.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Fly_Stomp_Anticipation", "Gargoyle_Fly_Stomp_Anticipation", 0.0266f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Fly_Stomp_Anticipation", { 1.0f }));

	/*MainSpriteRenderer->CreateAnimation("Gargoyle_Fly_Stomp_Anticipation", "Gargoyle_Fly_Stomp_Anticipation", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Fly_Stomp_Anticipation", { 0.0f }));*/

	MainSpriteRenderer->CreateAnimation("Gargoyle_Hit", "Gargoyle_Hit", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Hit", { 1.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Idle", "Gargoyle_Idle", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Idle", { 1.0f }));


	MainSpriteRenderer->CreateAnimation("Gargoyle_Posing1", "Gargoyle_Posing1", 0.366f, -1, -1, false);
	
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Posing1", { 0.8f , 0.0f, false,
		{200.0f, 150.0f}, {0.0f, 100.0f},0 }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Posing2", "Gargoyle_Posing2", 0.366f, -1, -1, false);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Posing2", { 0.8f , 0.0f, false,
		{200.0f, 150.0f}, {0.0f, 100.0f},0 }));


	MainSpriteRenderer->CreateAnimation("Gargoyle_Posing3", "Gargoyle_Posing3", 0.366f, -1, -1, false);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Posing3", { 0.8f , 0.0f, false,
		{200.0f, 150.0f}, {0.0f, 100.0f},0 }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Posing4", "Gargoyle_Posing4", 0.366f, -1, -1, false);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Posing4", { 0.8f , 0.0f, false,
		{200.0f, 150.0f}, {0.0f, 100.0f},0 }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Posing5", "Gargoyle_Posing5", 0.666f, -1, -1, false);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Posing5", { 0.8f , 0.0f, false,
		{200.0f, 150.0f}, {0.0f, 100.0f},0 }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Posing6", "Gargoyle_Posing6", 0.666f, -1, -1, false);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Posing6", { 0.8f , 0.0f, false,
		{200.0f, 150.0f}, {0.0f, 100.0f},0 }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Posing7", "Gargoyle_Posing7", 0.666f, -1, -1, false);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Posing7", { 0.8f , 0.0f, false,
		{200.0f, 150.0f}, {0.0f, 100.0f},0 }));

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

	MainSpriteRenderer->CreateAnimation("Gargoyle_Uturn", "Gargoyle_Uturn", 0.03666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Uturn", { 1.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Intro", "Gargoyle_Intro", 0.04666f, -1, -1, false);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Intro", { 0.8f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Intro_Idle", "Gargoyle_Intro_Idle", 0.0466f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Intro_Idle", { 0.8f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_End", "Gargoyle_End_1", 0.0633f, -1, -1, false);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_End", { 0.5f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Outro", "Gargoyle_End_2", 0.0633f, -1, -1, false);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Outro", { 0.8f }));

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
	Transform.SetLocalPosition({ 5000.0f, -3000.0f , -1.0f});
	ChangeState(EnemyState::IntroIdle);
	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("Boss_Gargoyle_Idle_0001.png");

	DefaultScale = Tex.get()->GetScale() + float4 { 50.0f, 0.0f };
	DashSpeed = 3000.0f;
	MoveSpeed = 600.0f;

	Enemy::Start();

	SetName("Gargoyle");

	HP = 1000;
}

void BossGargoyle::Update(float _Delta)
{
	Enemy::Update(_Delta);
}

void BossGargoyle::DeathCheck()
{
	if (HP <= 0 and DeathValue == false)
	{
		ForceGrivityOff = false;
		DeathValue = true;
		ChangeState(EnemyState::Death);
	}
}

void BossGargoyle::IdleStart()
{
	AttackPatern = GargoyleAttackPatern::Spin;
	ChangeMainAnimation("Gargoyle_Idle");
	MotionTime = 0.0f;
}

void BossGargoyle::IdleUpdate(float _Delta)
{
	
	MotionTime += _Delta;
	if (MotionTime < 1.2f)
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
	//AttackPatern = GargoyleAttackPatern::Posing;
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
		//AnimationName = "Gargoyle_Posing1" ;
		if (PosingCount >= 7)
		{
			PosingCount = 0;
		}
		break;
	}
	case GargoyleAttackPatern::Dive:
	{
		
		ForceGrivityOff = true;
		float4 TargetPos;
		if (Flip == true)
		{
			TargetPos = { 3385.0f, -3500.0f, -1.0f };
		}
		else
		{
			TargetPos = { 5000.0f, -3500.0f, -1.0f };
		}
		AnimationName = "Gargoyle_Dive_Attack_Loop";
		float4 StartPos = Transform.GetLocalPosition();
		float4 Nor = (TargetPos - StartPos).NormalizeReturn();
		MoveVec = Nor * 1700.0f;
	}
		break;

	case GargoyleAttackPatern::Dive_Anti:
	{
		ForceGrivityOff = true;
		float4 TargetPos;
		if (Flip == true)
		{
			TargetPos = { 3385.0f, -3500.0f, -1.0f };
		}
		else
		{
			TargetPos = { 5000.0f, -3500.0f, -1.0f };
		}
		AnimationName = "Gargoyle_Dive_Attack_Loop";
		float4 StartPos = Transform.GetLocalPosition();
		float4 Nor = (TargetPos - StartPos).NormalizeReturn();
		MoveVec = Nor * 1700.0f;
		break;
	}
	case GargoyleAttackPatern::Spin:
	{
		ForceGrivityOff = true;
		AnimationName = "Gargoyle_SpinGround";
		break;
	}
	case GargoyleAttackPatern::Max:
		break;
	default:
		break;
	}

	ChangeMainAnimation(AnimationName);
}

void BossGargoyle::AttackUpdate(float _Delta)
{
	MotionTime += _Delta;

	if (true == CheckStartAttackFrame())
	{
		DashStartCheck = true;
	}
	

	switch (AttackPatern)
	{
	case GargoyleAttackPatern::Combo:
	{
		CurDamage = 10.0f;
		if (true == MainSpriteRenderer->IsCurAnimationEnd())
		{
			if (ComboCount < 3)
			{
				CurDamage = 10.0f;
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
		CurDamage = 20.0f;
		if (MotionTime >= 0.5f)
		{
			ForceGrivityOff = false;
		}

		if (!AerialPixelCheck() and ForceGrivityOff == false)
		{
			
			ChangeState(EnemyState::Attack_End);
		}
	}
		break;
	case GargoyleAttackPatern::Dive:
	{
		CurDamage = 15.0f;
		float4 NextPos = Transform.GetLocalPosition() + (MoveVec * _Delta);

		if (Flip == true)
		{
			if (NextPos.X <= 3385.0f)
			{
				NextPos = { 3385.0f, -3500.0f, -1.0f };
				AttackPatern = GargoyleAttackPatern::Dive_Anti;
				ChangeState(EnemyState::Attack_Init);
			}
		}
		else
		{
			if (NextPos.X >= 5000.0f)
			{
				NextPos = { 5000.0f, -3500.0f, -1.0f };
				AttackPatern = GargoyleAttackPatern::Dive_Anti;
				ChangeState(EnemyState::Attack_Init);
			}

		}
		Transform.SetLocalPosition(NextPos);
		
		break;
	}
	case GargoyleAttackPatern::Dive_Anti:
	{
		CurDamage = 15.0f;
		float4 NextPos = Transform.GetLocalPosition() + (MoveVec * _Delta);

		if (Flip == true)
		{
			if (NextPos.X <= 3385.0f)
			{
				NextPos = { 3385.0f, -3500.0f, -1.0f };
				//AttackPatern = GargoyleAttackPatern::Dive_Anti;
				ChangeState(EnemyState::Attack_End);
				Dir == float4::LEFT;
			}
		}
		else
		{
			if (NextPos.X >= 5000.0f)
			{
				NextPos = { 5000.0f, -3500.0f, -1.0f };
				//AttackPatern = GargoyleAttackPatern::Dive_Anti;
				ChangeState(EnemyState::Attack_End);
				Dir == float4::RIGHT;
			}

		}
		Transform.SetLocalPosition(NextPos);
		
		break;
	}
	case GargoyleAttackPatern::Spin:
	{
		float4 NextPos = Transform.GetLocalPosition() + Dir * _Delta * 1500.0f;
		
		//BulletDelay = ContentsCore::MainRandom->RandomFloat(0.2f, 0.5f);
		BulletDelayCheck += _Delta;

		if (Flip == true)
		{
			if (NextPos.X <= 3385.0f)
			{
				NextPos.X = 3385.0f;
				Flip = false;
				Dir = float4::RIGHT;
			}
			
		}
		else
		{
			if (NextPos.X >= 5100.0f)
			{
				NextPos.X = 5100.0f;
				Flip = true;
				Dir = float4::LEFT;
			}
		}
		Transform.SetLocalPosition(NextPos);

		// 바위 발사
		if (BulletDelay <= BulletDelayCheck)
		{
			BulletDelayCheck = 0.0f;
			BulletDelay = ContentsCore::MainRandom->RandomFloat(0.1f, 0.3f);

			//중력 적용
			std::shared_ptr <Bullet> Object = GetLevel()->CreateActor<Bullet>(ContentsObjectType::Bullet);

			float4 Pos2 = Transform.GetLocalPosition() + float4(0.0f,100.0f);
			//float4 Pos = Transform.GetLocalPosition() + float4{ 50.0f, 50.0f };
			//float4 PlayerDir = Player::GetMainPlayer()->Transform.GetLocalPosition() - Transform.GetLocalPosition() + float4{ 0.0f, 0.0f, 1.0f };

			Object->Init(BulletType::Rock, Pos2, 10.0f, float4::UP, 0.0f);
		}

		if (MotionTime >= 4.0f)
		{
			ChangeState(EnemyState::Attack_End);
		}
	}

		break;
	case GargoyleAttackPatern::Max:
		break;
	default:
		break;
	}

	CheckAttackCollision();
	DashProcessUpdate(_Delta, float4::RIGHT, DashSpeed);


	
}

void BossGargoyle::Attack_InitStart()
{
	switch (AttackPatern)
	{
	case GargoyleAttackPatern::Combo:
		break;
	case GargoyleAttackPatern::Posing:
		break;
	case GargoyleAttackPatern::Dive:
		Flip = !Flip;
		ChangeMainAnimation("Gargoyle_DiveAttack_Anticipation");
		break;
	case GargoyleAttackPatern::Dive_Anti:
		Flip = !Flip;
		ChangeMainAnimation("Gargoyle_Dive_Attack_Turn");
		break;
	case GargoyleAttackPatern::Spin:
		break;
	case GargoyleAttackPatern::Max:
		break;
	default:
		break;
	}
}

void BossGargoyle::Attack_InitUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd() == true)
	{
		ChangeState(EnemyState::Attack);
	}
}

void BossGargoyle::Attack_EndStart()
{
	switch (AttackPatern)
	{
	case GargoyleAttackPatern::Combo:
		break;
	case GargoyleAttackPatern::Posing:
		ChangeMainAnimation("Gargoyle_Fly_Stomp_Anticipation");
		GetContentsLevel()->GetFXActor()->FXStart(FXType::Gargoyle_Fly_Stomp, Flip, Transform.GetLocalPosition() + float4(-20.0f, 0.0f,-5.0f),{1.2f,1.2f,1.0f}, {0.5f,1.0f});
		break;
	case GargoyleAttackPatern::Dive:
		Flip = !Flip;
		ChangeMainAnimation("Gargoyle_Dive_Attack_End");
		break;
	case GargoyleAttackPatern::Dive_Anti:
		Flip = !Flip;
		ChangeMainAnimation("Gargoyle_Dive_Attack_End");
		break;
	case GargoyleAttackPatern::Spin:
		ChangeMainAnimation("Gargoyle_Dive_Attack_End");
		break;
	case GargoyleAttackPatern::Max:
		break;
	default:
		break;
	}
}

void BossGargoyle::Attack_EndUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd() == true)
	{
		ForceGrivityOff = false;

		switch (AttackPatern)
		{
		case GargoyleAttackPatern::Combo:
			break;
		case GargoyleAttackPatern::Posing:
			AttackPatern = GargoyleAttackPatern::Dive;
			break;
		case GargoyleAttackPatern::Dive:
			AttackPatern = GargoyleAttackPatern::Spin;
			break;
		case GargoyleAttackPatern::Dive_Anti:
			AttackPatern = GargoyleAttackPatern::Spin;
			break;
		case GargoyleAttackPatern::Spin:
			AttackPatern = GargoyleAttackPatern::Combo;
			break;
		case GargoyleAttackPatern::Max:
			break;
		default:
			break;
		}
		
		ChangeState(EnemyState::Idle);
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
	ForceGrivityOff = false;
	Flip = true;
	ChangeMainAnimation("Gargoyle_End");
}

void BossGargoyle::DeathUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(EnemyState::Outro);
	}
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
		ForceGrivityOff = true;
		TargetPlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition() + float4{ 0.0f,400.0f,0.0f };
		TargetPos = Transform.GetLocalPosition() + float4{ 0.0f, 50.0f };
		ChangeMainAnimation("Gargoyle_SpinAir");
		break;
	}
	case GargoyleAttackPatern::Dive:
	{
		ForceGrivityOff = true;
		float4 TargetPos;
		if (Flip == true)
		{
			TargetPos = { 3385.0f, -2900.0f, -1.0f };
		}
		else
		{
			TargetPos = { 5000.0f, -2900.0f, -1.0f };
		}
		ChangeMainAnimation("Gargoyle_Idle");
		float4 StartPos = Transform.GetLocalPosition();
		float4 Nor = (TargetPos - StartPos).NormalizeReturn();
		MoveVec = Nor * 1000.0f;
		break;
	}
	case GargoyleAttackPatern::Dive_Anti:
	{
		break;
	}
	case GargoyleAttackPatern::Spin:
	{
		ForceGrivityOff = true;
		TargetPos = { 4200.0f, -2900.0f, -1.0f };
		float4 StartPos = Transform.GetLocalPosition();
		if (StartPos.X <= TargetPos.X)
		{
			Flip = false;
		}
		else
		{
			Flip = true;
		}

		float4 Nor = (TargetPos - StartPos).NormalizeReturn();
		MoveVec = Nor * 1000.0f;

		ChangeMainAnimation("Gargoyle_Idle");
		break;
	}
		
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
	{
		float4 NextPos = Transform.GetLocalPosition() + (MoveVec * _Delta);

		if (Flip == true)
		{
			if (NextPos.X <= 3385.0f)
			{
				NextPos = { 3385.0f, -2900.0f, -1.0f };
				//AttackPatern = GargoyleAttackPatern::Dive_Anti;
				ChangeState(EnemyState::Attack_Init);
			}
		}
		else
		{
			if (NextPos.X >= 5000.0f)
			{
				NextPos = { 5000.0f, -2900.0f, -1.0f };
				
				ChangeState(EnemyState::Attack_Init);
			}
			
		}
		Transform.SetLocalPosition(NextPos);
		break;
	}
	case GargoyleAttackPatern::Spin:
	{
		float4 NextPos = Transform.GetLocalPosition() + (MoveVec * _Delta);

		if (Flip == true)
		{
			if (NextPos.X <= TargetPos.X)
			{
				NextPos = TargetPos;
				//AttackPatern = GargoyleAttackPatern::Dive_Anti;
				ChangeState(EnemyState::Attack);
			}
		}
		else
		{
			if (NextPos.X >= TargetPos.X)
			{
				NextPos = TargetPos;
				ChangeState(EnemyState::Attack);
			}
			
		}
		Transform.SetLocalPosition(NextPos);
		break;
	}
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

void BossGargoyle::IntroStart()
{
	Flip = true;
	ChangeMainAnimation("Gargoyle_Intro");
}

void BossGargoyle::IntroUpdate(float _Delta)
{
	if (MainSpriteRenderer->GetCurIndex() >= 54)
	{
		Transform.AddLocalPosition(-1000.0f * _Delta);
	}

	if (MainSpriteRenderer->IsCurAnimationEnd() == true)
	{
		ChangeState(EnemyState::Idle);
	}
}

void BossGargoyle::IntroIdleStart()
{
	Flip = true;
	ChangeMainAnimation("Gargoyle_Intro_Idle");
}

void BossGargoyle::IntroIdleUpdate(float _Delta)
{
	
}

void BossGargoyle::EndStart()
{
	ChangeMainAnimation("Gargoyle_End");
}


void BossGargoyle::EndUpdate(float _Delta)
{
}

void BossGargoyle::OutroStart()
{
	MotionTime = 0.0f;
	ChangeMainAnimation("Gargoyle_Outro");
}

void BossGargoyle::OutroUpdate(float _Delta)
{
	MotionTime += _Delta;
	if (MainSpriteRenderer->GetCurIndex() > 14)
	{
		Transform.AddLocalPosition(float4::RIGHT * 1500.0f * _Delta);
	}

	if (MotionTime >= 4.0f)
	{
		Death();
	}
}

