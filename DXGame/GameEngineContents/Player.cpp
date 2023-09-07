#include "PreCompile.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include "PlayMap.h"

Player::Player() 
{
	
}

Player::~Player() 
{
}

void Player::Start()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\Sprite\\Player");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			// 구조적으로 잘 이해하고 있는지를 자신이 명확하게 인지하기 위해서
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());

			// GameEngineTexture::Load(File.GetStringPath());
		}

		//GameEngineSprite::CreateSingle("TestMap.png");


		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>();
		MainSpriteRenderer->CreateAnimation("Run", "LD_Idle", 0.0333f, -1, -1, true);
		MainSpriteRenderer->ChangeAnimation("Run");
		MainSpriteRenderer->SetSamplerState(SamplerOption::LINEAR);
		MainSpriteRenderer->Transform.SetLocalPosition({ 100.0f, 0.0f, 0.0f });

		//MainSpriteRenderer->SetEndEvent("Run", std::bind(&Player::TestEvent, this, std::placeholders::_1));

		// MainSpriteRenderer->Transform.SetLocalScale({5, 5});
		MainSpriteRenderer->AutoSpriteSizeOn();
		MainSpriteRenderer->SetAutoScaleRatio(1.0f);
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

}


void Player::Update(float _Delta)
{
	Actor::Update(_Delta);
	float Speed = 100.0f;

	if (GameEngineInput::IsPress('A'))
	{
		Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('D'))
	{
		Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('W'))
	{
		Transform.AddLocalPosition(float4::UP * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('S'))
	{
		Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('Q'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, 360.0f * _Delta });
	}

	if (GameEngineInput::IsPress('E'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, -360.0f * _Delta });
	}


	// 플레이어 카메라 포커스
	GameEngineColor Color = PlayMap::MainMap->GetColor(Transform.GetWorldPosition(), GameEngineColor::RED);
	std::shared_ptr<GameEngineCamera> MainCamara = GetLevel()->GetMainCamera();
	MainCamara->Transform.SetLocalPosition(Transform.GetWorldPosition());
}