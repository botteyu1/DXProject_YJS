#include "PreCompile.h"
#include "Elevator.h"
#include "Player.h"

Elevator::Elevator() 
{
}

Elevator::~Elevator()
{
}



void Elevator::Start()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("GameEngineResources");
	Dir.MoveChild("ContentsResources\\Sprite\\StageObject\\Elevator");

	GameEngineSprite::CreateFolder(Dir.GetStringPath());
	//std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	/*for (size_t i = 0; i < Directorys.size(); i++)
	{
		GameEngineDirectory& Dir = Directorys[i];
		GameEngineSprite::CreateFolder(Dir.GetStringPath());
	}*/

	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::StageObject);

	MainSpriteRenderer->CreateAnimation("Elevator", "Elevator", 0.0333f, -1, -1, false);
	MainSpriteRenderer->AutoSpriteSizeOn();
	MainSpriteRenderer->SetPivotValue({ 0.5f, 1.0f });
	MainSpriteRenderer->SetAutoScaleRatio({ 1.5f, 1.5f });

	MainSpriteRenderer->ChangeAnimation("Elevator");

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ 953.0f, -2534.0f,0.0f });

	MainCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::StageObject);
	MainCollision->Transform.SetLocalScale({ 150.0f, 300.0f });
	MainCollision->Transform.SetLocalPosition({30.0f, 220.0f });
	MainCollision->SetCollisionType(ColType::AABBBOX2D);

	GameEngineInput::AddInputObject(this);
	//DebugValue = true;

	static int Num = 0;
	Num++;

	SetName("Elavator_" + std::to_string(Num));
}

void Elevator::Update(float _Delta)
{
	StageObject::Update(_Delta);

	if (DebugValue == true)
	{
		return;
	}

	

	switch (State)
	{
	case ElevatorState::Static:
		break;
	case ElevatorState::Start:
		if (MainSpriteRenderer->IsCurAnimationEnd() == true)
		{
			State = ElevatorState::Static;
			Player::GetMainPlayer()->Transform.SetLocalPosition(Transform.GetLocalPosition() + float4(30.0f, 0.0f, -5.0f));
			Player::GetMainPlayer()->ChangeState(PlayerState::ExitElavator);
		}
		break;
	case ElevatorState::End:
		if (MainCollision->Collision<ContentsCollisionType>(ContentsCollisionType::Player))
		{
			if (GameEngineInput::IsDown('F', this))
			{
				
				Player::GetMainPlayer()->ChangeState(PlayerState::EnterElavator);
			}
		}
		break;
	default:
		break;
	}

	
	 
	
}

void Elevator::Init(ElevatorState _State)
{
	State = _State;
	switch (_State)
	{
	case ElevatorState::Static:
		MainSpriteRenderer->ChangeAnimation("Elevator");
		break;
	case ElevatorState::Start:
	{
		MainSpriteRenderer->ChangeAnimation("Elevator");
		float4 TargetPos = Transform.GetLocalPosition() + float4(30.f, 50.f);
		//Player::GetMainPlayer()->Transform.SetLocalPosition(TargetPos);
		//Player::GetMainPlayer()->SetTargetPos(TargetPos);
		break;
	}
	case ElevatorState::End:
		MainSpriteRenderer->ChangeAnimation("Elevator");
		break;
	default:
		break;
	}

	
}

void Elevator::CollisionUpdate(GameEngineCollision* _Left, GameEngineCollision* _Right)
{

}

void Elevator::NextStageAnimationStart()
{

}



