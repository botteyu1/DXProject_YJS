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
			// ���������� �� �����ϰ� �ִ����� �ڽ��� ��Ȯ�ϰ� �����ϱ� ���ؼ�
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());

		}


		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>();
		MainSpriteRenderer->CreateAnimation("LD_Idle", "LD_Idle", 0.0333f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("LD_RunUturn", "LD_RunUturn", 0.0333f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("LD_Run", "LD_Run", 0.0333f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("LD_RunToIdle", "LD_RunToIdle", 0.0333f, -1, -1, true);
		//MainSpriteRenderer->SetEndEvent("LD_RunUturn", std::bind(&Player::EndUturnEvent, this, MainSpriteRenderer.get()));
		MainSpriteRenderer->SetSamplerState(SamplerOption::LINEAR);
		MainSpriteRenderer->AutoSpriteSizeOn();
		

		

		//MainSpriteRenderer->SetEndEvent("Run", std::bind(&Player::TestEvent, this, std::placeholders::_1));
		// MainSpriteRenderer->Transform.SetLocalScale({5, 5});
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

	ChangeState(PlayerState::Idle);

}


void Player::Update(float _Delta)
{
	Actor::Update(_Delta);

	StateUpdate(_Delta);
	

	

	if (GameEngineInput::IsPress('Q'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, 360.0f * _Delta });
	}

	if (GameEngineInput::IsPress('E'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, -360.0f * _Delta });
	}


	// �÷��̾� ī�޶� ��Ŀ��
	GameEngineColor Color = PlayMap::MainMap->GetColor(Transform.GetWorldPosition(), GameEngineColor::RED);
	std::shared_ptr<GameEngineCamera> MainCamara = GetLevel()->GetMainCamera();
	MainCamara->Transform.SetLocalPosition(Transform.GetWorldPosition());
}






void Player::ChangeState(PlayerState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case PlayerState::Idle:	
			IdleStart();
			break;
		case PlayerState::Jump:
			JumpStart();
			break;
		case PlayerState::Run:
			RunStart();
			break;
		case PlayerState::RunUturn:
			RunUturnStart();
			break;
		case PlayerState::RunToIdle:
			RunToIdleStart();
			break;
		case PlayerState::Attack:
			AttackStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}


void Player::StateUpdate(float _Delta)
{
	switch (State)
	{
	case PlayerState::Idle:
		IdleUpdate(_Delta);
		break;
	case PlayerState::Jump:
		JumpUpdate(_Delta);
		break;
	case PlayerState::Run:
		RunUpdate(_Delta);
		break;	
	case PlayerState::RunUturn:
		RunUturnUpdate(_Delta);
		break;
	case PlayerState::RunToIdle:
		RunToIdleUpdate(_Delta);
		break;
	case PlayerState::Attack:
		AttackUpdate(_Delta);
		break;
	default:
		break;
	}
}
