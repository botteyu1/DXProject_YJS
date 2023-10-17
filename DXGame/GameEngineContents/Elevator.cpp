#include "PreCompile.h"
#include "Elevator.h"

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

	MainSpriteRenderer->CreateAnimation("Elevator", "Elevator", 0.0333f, -1, -1, true);
	MainSpriteRenderer->AutoSpriteSizeOn();
	MainSpriteRenderer->SetPivotValue({ 0.5f, 1.0f });
	MainSpriteRenderer->SetAutoScaleRatio({ 1.5f, 1.5f });

	MainSpriteRenderer->ChangeAnimation("Elevator");

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X - 700.0f, -HalfWindowScale.Y * 4 });

	MainCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::StageObject);
	MainCollision->Transform.SetLocalScale({ 50.0f, 100.0f });
	MainCollision->Transform.SetLocalPosition({ 0.0f, 80.0f });
	MainCollision->SetCollisionType(ColType::AABBBOX2D);

	GameEngineInput::AddInputObject(this);
	DebugValue = true;
}

void Elevator::Update(float _Delta)
{

	StageObject::Update(_Delta);

	if (DebugValue == true)
	{
		return;
	}
	 

	
	

	/*EventParameter Parameter;

	Parameter.Enter = CollisionUpdate;

	MainCollision->CollisionEvent<ContentsCollisionType>(ContentsCollisionType::Player, Parameter);*/


}

void Elevator::CollisionUpdate(GameEngineCollision* _Left, GameEngineCollision* _Right)
{

}

void Elevator::NextStageAnimationStart()
{

}

