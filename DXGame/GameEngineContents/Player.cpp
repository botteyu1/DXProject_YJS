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
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());

		}
		 

		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Player);
		MainSpriteRenderer->CreateAnimation("LD_Idle", "LD_Idle", 0.0333f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("LD_RunUturn", "LD_RunUturn", 0.0333f, -1, -1, false);
		MainSpriteRenderer->CreateAnimation("LD_Run", "LD_Run", 0.0333f, -1, -1, true);
		MainSpriteRenderer->CreateAnimation("LD_RunToIdle", "LD_RunToIdle", 0.0333f, -1, -1, false);
		MainSpriteRenderer->CreateAnimation("LD_Jump_Start", "LD_Jump_Start", 0.0533f, -1, -1, false);
		MainSpriteRenderer->CreateAnimation("LD_Jump_Landing", "LD_Jump_Landing", 0.0533f, -1, -1, false);
		MainSpriteRenderer->CreateAnimation("LD_Jump_Falling", "LD_Jump_Falling", 0.3333f, -1, -1, true);

		MainSpriteRenderer->CreateAnimation("LD_ComboMove_01", "LD_ComboMove_01", 0.0233f, -1, -1, false);
		PlayerAnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_ComboMove_01", {0.0f}));
		MainSpriteRenderer->CreateAnimation("LD_ComboMove_02", "LD_ComboMove_02", 0.0333f, -1, -1, false);
		PlayerAnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_ComboMove_02", {100.0f}));
		MainSpriteRenderer->CreateAnimation("LD_ComboMove_03", "LD_ComboMove_03", 0.0333f, -1, -1, false);
		PlayerAnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_ComboMove_03", {100.0f}));
		MainSpriteRenderer->CreateAnimation("LD_ComboMove_04", "LD_ComboMove_04", 0.0333f, -1, -1, false);
		PlayerAnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_ComboMove_04", {50.0f, true }));
		
		MainSpriteRenderer->CreateAnimation("LD_ComboAerial_01", "LD_ComboAerial_01", 0.0333f, -1, -1, false);
		PlayerAnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_ComboAerial_01", {0.0f}));
		MainSpriteRenderer->CreateAnimation("LD_ComboAerial_02", "LD_ComboAerial_02", 0.0233f, -1, -1, false);
		PlayerAnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_ComboAerial_02", {30.0f}));
		MainSpriteRenderer->CreateAnimation("LD_ComboAerial_03", "LD_ComboAerial_03", 0.0333f, -1, -1, false);
		PlayerAnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_ComboAerial_03", {100.0f , true}));
		MainSpriteRenderer->CreateAnimation("LD_JumpingAttack", "LD_JumpingAttack", 0.0333f, -1, -1, false);
		PlayerAnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_JumpingAttack", {500.0f , true}));
		MainSpriteRenderer->CreateAnimation("LD_AerialDownAttack", "LD_AerialDownAttack", 0.0333f, -1, -1, false);

		MainSpriteRenderer->CreateAnimation("LD_ComboMove_01_Rest", "LD_ComboMove_01_Rest", 0.0333f, -1, -1, false);
		MainSpriteRenderer->CreateAnimation("LD_ComboMove_02_Rest", "LD_ComboMove_02_Rest", 0.0333f, -1, -1, false);
		MainSpriteRenderer->CreateAnimation("LD_ComboMove_03_Rest", "LD_ComboMove_03_Rest", 0.0333f, -1, -1, false);
		MainSpriteRenderer->CreateAnimation("LD_ComboMove_04_Rest", "LD_ComboMove_04_Rest", 0.0333f, -1, -1, false);

		MainSpriteRenderer->CreateAnimation("LD_ComboAerial_01_Rest", "LD_ComboAerial_01_Rest", 0.0333f, -1, -1, false);
		MainSpriteRenderer->CreateAnimation("LD_ComboAerial_02_Rest", "LD_ComboAerial_02_Rest", 0.0333f, -1, -1, false);
		MainSpriteRenderer->CreateAnimation("LD_ComboAerial_03_Rest", "LD_ComboAerial_03_Rest", 0.0333f, -1, -1, false);
		MainSpriteRenderer->CreateAnimation("LD_Dash", "LD_Dash", 0.0333f, -1, -1, false);
		//MainSpriteRenderer->SetEndEvent("LD_RunUturn", std::bind(&Player::EndUturnEvent, this, MainSpriteRenderer.get()));
		MainSpriteRenderer->SetSamplerState(SamplerOption::LINEAR);
		MainSpriteRenderer->AutoSpriteSizeOn();
		//MainSpriteRenderer->SetPivotType(PivotType::Bottom);
		
		const SpriteData& Sprite = MainSpriteRenderer->GetCurSprite();
		//Sprite.GetScale();

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
	
	if (AerialCheck == false)
	{
		JumpingAttackEnd = false;
		AerialComboCount = 0;
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
	//GameEngineColor Color = PlayMap::MainMap->GetColor(Transform.GetWorldPosition(), GameEngineColor::RED);
	//std::shared_ptr<GameEngineCamera> MainCamara = GetLevel()->GetMainCamera();
	//MainCamara->Transform.SetLocalPosition(Transform.GetWorldPosition());
}






void Player::ChangeState(PlayerState _State)
{
	
	switch (_State)
	{
	case PlayerState::Idle:	
		IdleStart();
		break;
	case PlayerState::Jump_Falling:
		Jump_FallingStart();
		break;
	case PlayerState::Jump_Landing:
		Jump_LandingStart();
		break;
	case PlayerState::Jump_Start:
		Jump_StartStart();
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
	case PlayerState::ComboMove:
		ComboMoveStart();
		break;
	case PlayerState::ComboMove_Rest:
		ComboMove_RestStart();
		break;
	case PlayerState::ComboAerial:
		ComboAerialStart();
		break;
	case PlayerState::ComboAerial_Rest:
		ComboAerial_RestStart();
		break;
	case PlayerState::JumpingAttack:
		JumpingAttackStart();
		break;
	case PlayerState::AerialDownAttack:
		AerialDownAttackStart();
		break;
	case PlayerState::Dash:
		DashStart();
		break;
	default:
		break;
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
	case PlayerState::Jump_Falling:
		Jump_FallingUpdate(_Delta);
		break;
	case PlayerState::Jump_Landing:
		Jump_LandingUpdate(_Delta);
		break;
	case PlayerState::Jump_Start:
		Jump_StartUpdate(_Delta);
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
	case PlayerState::ComboMove:
		ComboMoveUpdate(_Delta);
		break;
	case PlayerState::ComboMove_Rest:
		ComboMove_RestUpdate(_Delta);
		break;
	case PlayerState::ComboAerial:
		ComboAerialUpdate(_Delta);
		break;
	case PlayerState::ComboAerial_Rest:
		ComboAerial_RestUpdate(_Delta);
		break;
	case PlayerState::JumpingAttack:
		JumpingAttackUpdate(_Delta);
		break;
	case PlayerState::AerialDownAttack:
		AerialDownAttackUpdate(_Delta);
		break;
	case PlayerState::Dash:
		DashUpdate(_Delta);
		break;
	default:
		break;
	}
}
