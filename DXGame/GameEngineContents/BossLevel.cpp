#include "PreCompile.h"
#include "BossLevel.h"

#include "BossGargoyle.h"
#include "PlayMap.h"
#include "Player.h"
#include "FX.h"
#include "BossGargoyle.h"
#include "PlayUI.h"
#include "BossUI.h"
#include "MovieBar.h"

BossLevel::BossLevel() 
{
}

BossLevel::~BossLevel()
{
}

void BossLevel::Start()
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -1000.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);

	{
		 PlayerPtr = CreateActor<Player>(ContentsObjectType::Player);
		 PlayerPtr->Transform.SetLocalPosition({ 1076.0f, -3574.0f, 5.0f });
	}

	{
		std::shared_ptr<PlayMap> Object = CreateActor<PlayMap>(ContentsObjectType::BackGround);
		Object->Init("StageBoss.dds", "StagePixelBoss.png");
		SetMap(Object);
	}
	BossPtr = CreateActor<BossGargoyle>(ContentsObjectType::BackGround);
	PlayUIPtr = CreateActor<PlayUI>(ContentsObjectType::UI);
	BossUIPtr = CreateActor<BossUI>(ContentsObjectType::UI);
	BossUIPtr->SetBoss(BossPtr);
	

	FXActor = CreateActor<FX>(ContentsObjectType::FX);


	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("GameEngineResources");
	Dir.MoveChild("ContentsResources\\Data\\StageBoss.GameData");

	GameEngineSerializer BinSer;

	GameEngineFile File = Dir.GetStringPath();
	File.Open(FileOpenType::Read, FileDataType::Binary);
	File.DataAllRead(BinSer);

	DeSerializer(BinSer, false);


	Level::Start();

	{
		CreateStateParameter NewPara;

		// 한번만 실행되는 겁니다.
		NewPara.Init = [=](class GameEngineState* _Parent)
			{
				// MainSpriteRenderer->ChangeAnimation("Idle");
			};


		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				BossUIPtr->Off();
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				std::shared_ptr<GameEngineCamera> MainCamara = GetMainCamera();
				float4 PlayePos = PlayerPtr->Transform.GetWorldPosition();
				float4 MainCamaraPos = MainCamara->Transform.GetWorldPosition();
				float4 Pos = { PlayePos.X, -3150.0f,-1000.0f };

				if (Pos.X >= 3450.0f and BossIntroOver == false)
				{
					_Parent->ChangeState(BossLevelState::IntroCamera);
				}

				MainCamara->Transform.SetWorldPosition(Pos);
			};

		State.CreateState(BossLevelState::Normal, NewPara);
	}	

	{
		CreateStateParameter NewPara;

		// 한번만 실행되는 겁니다.
		NewPara.Init = [=](class GameEngineState* _Parent)
			{
				// MainSpriteRenderer->ChangeAnimation("Idle");
			};


		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				BossIntroOver = true;
				MovieBarPtr->MovieBarStart();
				PlayUIPtr->Off();
				PlayerPtr->ChangeState(PlayerState::ForceWait);

			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				std::shared_ptr<GameEngineCamera> MainCamara = GetMainCamera();
				//float4 PlayePos = PlayerPtr->Transform.GetWorldPosition();
				float4 MainCamaraPos = MainCamara->Transform.GetWorldPosition();
				float4 Pos = { MainCamaraPos.X + 500.0f * _DeltaTime, -3150.0f,-1000.0f };
				if (Pos.X >= 4175.0f)
				{
					Pos.X = 4175.0f;
					_Parent->ChangeState(BossLevelState::Intro);
				}
				MainCamara->Transform.SetWorldPosition(Pos);


				/*if (Pos.X <= 3250.0f and BossIntroOver == false)
				{
					_Parent->ChangeState(BossLevelState::Intro);
				}*/
				
			};

		State.CreateState(BossLevelState::IntroCamera, NewPara);
	}

	{
		CreateStateParameter NewPara;

		// 한번만 실행되는 겁니다.
		NewPara.Init = [=](class GameEngineState* _Parent)
			{
				

			};


		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				BossIntroOver = true;

				BossPtr->ChangeState(EnemyState::Intro);
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (BossPtr->GetState() == EnemyState::Idle)
				{
					_Parent->ChangeState(BossLevelState::Boss);
					
				}
				
			};

		State.CreateState(BossLevelState::Intro, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Init = [=](class GameEngineState* _Parent)
			{
				
			};


		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				PlayerPtr->ChangeState(PlayerState::Idle);
				MovieBarPtr->MovieBarEnd();
				PlayUIPtr->On();
				BossUIPtr->On();
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				
			};

		State.CreateState(BossLevelState::Boss, NewPara);
	}



	State.ChangeState(BossLevelState::Normal);

	//MovieBarPtr->On();

	//std::shared_ptr<GameEngineCamera> MainCamara = GetMainCamera();
	//float4 PlayePos = PlayerPtr->Transform.GetWorldPosition();
	////float4 Pos = PlayePos

	//MainCamara->Transform.SetWorldPosition(PlayePos + float4{ 0.0f,0.0f,-1000.0f });

	GameEngineInput::AddInputObject(this);
}

void BossLevel::Update(float _Delta)
{
	State.Update(_Delta);

	if (GameEngineInput::IsDown('3', this))
	{
		MovieBarPtr->MovieBarStart();
	}
	if (GameEngineInput::IsDown('4', this))
	{
		MovieBarPtr->MovieBarEnd();
	}
}

void BossLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
}

void BossLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
}
