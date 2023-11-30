#include "PreCompile.h"
#include "Contractor.h"
#include <GameEngineCore/GameEngineState.h>
#include "Level.h"
#include "CurseUI.h"
#include "Player.h"

Contractor::Contractor() 
{
}

Contractor::~Contractor()
{
}

void Contractor::Start()
{
	if (nullptr == GameEngineTexture::Find("NPC_Contractor_Appear_0001.png"))
	{
		GameEngineDirectory Dir2;
		Dir2.MoveParentToExistsChild("GameEngineResources");
		Dir2.MoveChild("ContentsResources\\Sprite\\StageObject\\Contractor");
		std::vector<GameEngineDirectory> Directorys = Dir2.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& File = Directorys[i];

			GameEngineSprite::CreateFolder(File.GetStringPath());
		}
	}

	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::BackGroundobject);
	MainSpriteRenderer->CreateAnimation("Contractor_ON", "Contractor_ON", 0.0633f, -1, -1, false);
	MainSpriteRenderer->CreateAnimation("Contractor_OFF", "Contractor_OFF", 0.0633f, -1, -1, false);
	MainSpriteRenderer->CreateAnimation("Contractor_Appear", "Contractor_Appear", 0.0633f, -1, -1, false);
	MainSpriteRenderer->CreateAnimation("Contractor_Disappear", "Contractor_Disappear", 0.0633f, -1, -1, false);
	MainSpriteRenderer->CreateAnimation("Contractor_Reading", "Contractor_Reading", 0.1033f, -1, -1, true);
	//MainSpriteRenderer->CreateAnimation("Contractor_Appear", "Contractor_Appear", 0.0333f, -1, -1, false);
	MainSpriteRenderer->AutoSpriteSizeOn();
	MainSpriteRenderer->SetPivotValue({ 0.5f, 1.0f,1.0f});
	MainSpriteRenderer->SetAutoScaleRatio({ 1.0f, 1.0f });
	MainSpriteRenderer->ChangeAnimation("Contractor_Appear");
	//MainSpriteRenderer->Off();

	MainCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::StageObject);
	MainCollision->Transform.SetLocalScale({ 150.0f, 300.0f });
	MainCollision->Transform.SetLocalPosition({ 30.0f, 220.0f });
	MainCollision->SetCollisionType(ColType::AABBBOX2D);

	DetectCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Enemy_Detect);
	DetectCollision->Transform.SetLocalScale({ 1300.0f, 1300.0f });
	DetectCollision->Transform.SetLocalPosition({ -0.0f, 80.0f, 1.0f });
	DetectCollision->SetCollisionType(ColType::AABBBOX2D);

	{
		CreateStateParameter NewPara;


		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainSpriteRenderer->Off();
				MainSpriteRenderer->SetAutoScaleRatio({ 1.0f, 1.0f,1.0f });
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (DetectCollision->Collision(ContentsCollisionType::Player))
				{
					MainSpriteRenderer->On();
					State.ChangeState(ContractorState::ON);
				}
			};

		State.CreateState(ContractorState::Hide, NewPara);
	} 
	{
		CreateStateParameter NewPara;


		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainSpriteRenderer->On();
				MainSpriteRenderer->ChangeAnimation("Contractor_ON");
				MainSpriteRenderer->SetAutoScaleRatio({ 1.0f, 1.0f,1.0f });
				GameEngineSound::SoundPlay("ContractorOn");
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainSpriteRenderer->IsCurAnimationEnd() == true)
				{
					State.ChangeState(ContractorState::Appear);
				}
			};

		State.CreateState(ContractorState::ON, NewPara);
	}
	{
		CreateStateParameter NewPara;


		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainSpriteRenderer->On();
				MainSpriteRenderer->SetAutoScaleRatio({ 1.5f, 1.5f,1.5f });
				MainSpriteRenderer->ChangeAnimation("Contractor_Appear");
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainSpriteRenderer->IsCurAnimationEnd() == true)
				{
					State.ChangeState(ContractorState::Idle);
				}
			};

		State.CreateState(ContractorState::Appear, NewPara);
	}
	{
		CreateStateParameter NewPara;


		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				
				MainSpriteRenderer->SetAutoScaleRatio({ 1.0f, 1.0f ,1.0f});
				MainSpriteRenderer->ChangeAnimation("Contractor_Reading");
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainCollision->Collision(ContentsCollisionType::Player))
				{
					if (GameEngineInput::IsDown('F', this) and GetContentsLevel()->GetCurseUI()->IsUpdate() == false)
					{
						static bool Type = false;
						if(Type == false)
						{
							Type = true;
							GetContentsLevel()->GetCurseUI()->CurseUIStart(1);
						}
						else
						{
							Type = false;
							GetContentsLevel()->GetCurseUI()->CurseUIStart(2);
						}
						
						
					}
				}

				if (Player::GetMainPlayer()->GetState() == PlayerState::PowerUp)
				{
					State.ChangeState(ContractorState::DisAppear);
				}
			};

		State.CreateState(ContractorState::Idle, NewPara);
	}

	{
		CreateStateParameter NewPara;


		NewPara.Start = [=](class GameEngineState* _Parent)
			{

				MainSpriteRenderer->SetAutoScaleRatio({ 1.5f, 1.5f ,1.5f});
				MainSpriteRenderer->ChangeAnimation("Contractor_DisAppear");
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainSpriteRenderer->IsCurAnimationEnd() == true)
				{
					State.ChangeState(ContractorState::OFF);
				}
			};

		State.CreateState(ContractorState::DisAppear, NewPara);
	}
	{
		CreateStateParameter NewPara;


		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainSpriteRenderer->ChangeAnimation("Contractor_OFF");
				MainSpriteRenderer->SetAutoScaleRatio({ 1.0f, 1.0f,1.0f });
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainSpriteRenderer->IsCurAnimationEnd() == true)
				{


					MainSpriteRenderer->Off();
				}
			};

		State.CreateState(ContractorState::OFF, NewPara);
	}

	State.ChangeState(ContractorState::Hide);
	GameEngineInput::AddInputObject(this);

	static int Num = 0;
	Num++;

	SetName("Contractor_" + std::to_string(Num));

	ForceGrivityOff = false;

}

void Contractor::Update(float _Delta)
{
	StageObject::Update(_Delta);

	if (DebugValue == true)
	{
		return;
	}

	State.Update(_Delta);
}

