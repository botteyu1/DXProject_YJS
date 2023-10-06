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
	MainSpriteRenderer->CreateAnimation("Ghost_Appear", "Ghost_Appear", 0.0666f, -1, -1, true);
	MainSpriteRenderer->CreateAnimation("Ghost_idle", "Ghost_idle", 0.0666f, -1, -1, true);
	MainSpriteRenderer->CreateAnimation("Ghost_Death", "Ghost_Death", 0.0666f, -1, -1, true);
	MainSpriteRenderer->CreateAnimation("Ghost_Hit", "Ghost_Hit", 0.0666f, -1, -1, true);
	MainSpriteRenderer->CreateAnimation("Ghost_Run", "Ghost_Run", 0.0666f, -1, -1, true);
	MainSpriteRenderer->CreateAnimation("Ghost_Surprised", "Ghost_Surprised", 0.0666f, -1, -1, true);
	MainSpriteRenderer->CreateAnimation("Ghost_Uturn", "Ghost_Uturn", 0.0666f, -1, -1, false);
	MainSpriteRenderer->CreateAnimation("Ghost_Waiting", "Ghost_Waiting", 0.0666f, -1, -1, true);

	//MainSpriteRenderer->SetSamplerState(SamplerOption::LINEAR);
	MainSpriteRenderer->AutoSpriteSizeOn();
	MainSpriteRenderer->SetPivotValue({ 0.0f, 1.0f });

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X + 700.0f, -HalfWindowScale.Y, -500.0f });
	ChangeState(EnemyState::Idle);

	DefaultScale = MainSpriteRenderer->GetCurSprite().Texture.get()->GetScale();

	MainCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Enemy);
	MainCollision->Transform.SetLocalScale({ 50.0f, 100.0f });
	MainCollision->Transform.SetLocalPosition({ -80.0f, 80.0f, 1.0f });

	AttackCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Enemy_Attack);

	Actor::Start();
}

void Ghost_Man::Update(float _Delta)
{
	Actor::Update(_Delta);
	StateUpdate(_Delta);
}

void Ghost_Man::IdleStart()
{
	MainSpriteRenderer->ChangeAnimation("Ghost_idle");
	MotionTime = 0.0f;
}

void Ghost_Man::IdleUpdate(float _Delta)
{
	MotionTime += _Delta;
	if (MotionTime >= 2.0f)
	{
		ChangeState(EnemyState::Uturn);
	}
}

void Ghost_Man::AttackStart()
{
	MainSpriteRenderer->ChangeAnimation("Ghost_Attack");
}

void Ghost_Man::AttackUpdate(float _Delta)
{
}

void Ghost_Man::AppearStart()
{
	MainSpriteRenderer->ChangeAnimation("Ghost_Attack");
}

void Ghost_Man::AppearUpdate(float _Delta)
{

}

void Ghost_Man::DeathStart()
{
	MainSpriteRenderer->ChangeAnimation("Ghost_Death");
}

void Ghost_Man::DeathUpdate(float _Delta)
{
}

void Ghost_Man::HitStart()
{
	MainSpriteRenderer->ChangeAnimation("Ghost_Hit");
}

void Ghost_Man::HitUpdate(float _Delta)
{
}

void Ghost_Man::RunStart()
{
	MainSpriteRenderer->ChangeAnimation("Ghost_Run");
	MotionTime = 0.0f;
}

void Ghost_Man::RunUpdate(float _Delta)
{
	Transform.AddLocalPosition(Dir * _Delta * MoveSpeed);

	MotionTime += _Delta;
	if (MotionTime >= 2.0f)
	{
		ChangeState(EnemyState::Idle);
	}

}

void Ghost_Man::SurprisedStart()
{
	MainSpriteRenderer->ChangeAnimation("Ghost_Surprised");
}

void Ghost_Man::SurprisedUpdate(float _Delta)
{
}

void Ghost_Man::UturnStart()
{
	MainSpriteRenderer->ChangeAnimation("Ghost_Uturn");
}

void Ghost_Man::UturnUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd() == true)
	{
		Flip = !Flip;
		ChangeState(EnemyState::Run);
	}
}

void Ghost_Man::WaitingStart()
{
	MainSpriteRenderer->ChangeAnimation("Ghost_Waiting");
}

void Ghost_Man::WaitingUpdate(float _Delta)
{

}

