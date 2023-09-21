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

	MainSpriteRenderer->SetSamplerState(SamplerOption::LINEAR);
	MainSpriteRenderer->AutoSpriteSizeOn();
	MainSpriteRenderer->SetPivotValue({ 0.0f, 1.0f });

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X + 400.0f, -HalfWindowScale.Y, -500.0f });

	ChangeState(EnemyState::Idle);
}

void Ghost_Man::Update(float _Delta)
{
	Actor::Update(_Delta);
	StateUpdate(_Delta);
}

void Ghost_Man::IdleStart()
{
	MainSpriteRenderer->ChangeAnimation("Ghost_idle");
}

void Ghost_Man::IdleUpdate(float _Delta)
{
}

void Ghost_Man::AttackStart()
{
}

void Ghost_Man::AttackUpdate(float _Delta)
{
}

void Ghost_Man::AppearStart()
{
}

void Ghost_Man::AppearUpdate(float _Delta)
{
}

void Ghost_Man::DeathStart()
{
}

void Ghost_Man::DeathUpdate(float _Delta)
{
}

void Ghost_Man::HitStart()
{
}

void Ghost_Man::HitUpdate(float _Delta)
{
}

