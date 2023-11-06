#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"
#include "PlayMap.h"
#include "Ghost_Man.h"
#include "Ghost_Woman.h"
#include "PossessedBook.h"
#include "Ghost_Med.h" 
#include "Elevator.h"
#include "GUI.h"
#include "BGObject.h"
#include "FX.h"
#include "BossGargoyle.h"
#include "Map.h"
#include "PlayUI.h"
#include "PaperWall.h"
#include "WeaponDrop.h"


PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Start()
{
	

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -5000.0f});
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);

	{
		PlayerPtr = CreateActor<Player>(ContentsObjectType::Player);
		PlayerPtr->Transform.SetLocalPosition({ 432.0f, -2475.0f, 5.0f });
	}
	{
		std::shared_ptr<PlayMap> Object = CreateActor<PlayMap>(ContentsObjectType::BackGround);
		Object->Init("Stage1.dds", "StagePixel1.png", "Stage2.dds", "StagePixel2.png");
		SetMap(Object);
	}
	FXActor = CreateActor<FX>(ContentsObjectType::FX);
	PlayUIPtr = CreateActor<PlayUI>(ContentsObjectType::UI);

	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("GameEngineResources");
	Dir.MoveChild("ContentsResources\\Data\\Stage1.GameData");

	GameEngineSerializer BinSer;

	GameEngineFile File = Dir.GetStringPath();
	File.Open(FileOpenType::Read, FileDataType::Binary);
	File.DataAllRead(BinSer);
	DeSerializer(BinSer, false);


	
	
	Level::Start();


	//기믹용 몬스터 끄기
	for (size_t i = 0; i < GimicEnemyvec.size(); i++)
	{
		GimicEnemyvec[i]->Off();
	}
	
	for (size_t i = 0; i < Gimic2Enemyvec.size(); i++)
	{
		Gimic2Enemyvec[i]->Off();
	}
		


	{
		CreateStateParameter NewPara;


		NewPara.Start = [=](class GameEngineState* _Parent)
			{

			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				//카메라 포커스
	
				std::shared_ptr<GameEngineCamera> MainCamara = GetMainCamera();
				float4 PlayePos = PlayerPtr->Transform.GetWorldPosition();

				MainCamara->Transform.SetLocalPosition(PlayePos + float4{ 0.0f,0.0f,-1000.0f });

				if (MainCamara->Transform.GetLocalPosition().X >= 10500.0f and GimmickValue == false)
				{
					State.ChangeState(PlayLevelState::GimmickIntro);
				}
			};

		State.CreateState(PlayLevelState::Normal, NewPara);
	}
	
	{
		CreateStateParameter NewPara;


		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				GimmickValue = true;
				for (size_t i = 0; i < PaperWallvec.size(); i++)
				{
					PaperWallvec[i]->GimmckStart();
				}

			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				//카메라 포커스
	
				std::shared_ptr<GameEngineCamera> MainCamara = GetMainCamera();
				float4 MainCamaraPos = MainCamara->Transform.GetWorldPosition();
				float4 TargetPos = float4{ 11000.0f,-2020.0f, MainCamaraPos.Z };
				float4 Nor = (TargetPos - MainCamaraPos).NormalizeReturn();

				float4 Pos = { Nor * _DeltaTime * 300.0f};

				MainCamara->Transform.AddLocalPosition(Pos);

				if (MainCamara->Transform.GetLocalPosition().X >= 11000.0f)
				{
					MainCamara->Transform.SetLocalPosition(TargetPos);
					State.ChangeState(PlayLevelState::Gimmick);
				}
			};

		State.CreateState(PlayLevelState::GimmickIntro, NewPara);
	}

	{
		CreateStateParameter NewPara;


		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				GimmickValue = true;
				Gimmick2Value = false;
				for (size_t i = 0; i < GimicEnemyvec.size(); i++)
				{
					GimicEnemyvec[i]->On();
				}

			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{

				if (State.GetStateTime() >= 5.0f and Gimmick2Value == false)
				{
					Gimmick2Value = true;
					for (size_t i = 0; i < Gimic2Enemyvec.size(); i++)
					{
						Gimic2Enemyvec[i]->On();
					}
				}

				if (CheckGimmickOver() == true)
				{
					State.ChangeState(PlayLevelState::GimmickEnd);
				}

			};

		State.CreateState(PlayLevelState::Gimmick, NewPara);
	}
	{
		CreateStateParameter NewPara;


		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				
				for (size_t i = 0; i < PaperWallvec.size(); i++)
				{
					PaperWallvec[i]->GimmckEnd();
				}

				float4 TargetPos = float4{ 11000.0f,-1920.0f, 0.0f };
				WeaponDropObject = CreateActor<WeaponDrop>(ContentsObjectType::BackGround);
				WeaponDropObject->Transform.SetLocalPosition(TargetPos);
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{

				if (WeaponDropObject->AerialCheck == false or WeaponDropObject->IsUpdate() == false)
				{
					State.ChangeState(PlayLevelState::Normal);
				}
				
			};

		State.CreateState(PlayLevelState::GimmickEnd, NewPara);
	}


	State.ChangeState(PlayLevelState::Normal);
}


void PlayLevel::Update(float _Delta)
{
	//카메라 포커스

	State.Update(_Delta);
}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	int a = 0; 
	GimmickValue = false; 
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}

bool PlayLevel::CheckGimmickOver()
{
	for (size_t i = 0; i < GimicEnemyvec.size(); i++)
	{
		if (GimicEnemyvec[i]->IsUpdate() == true)
		{
			return false;
		}
		
	}
	for (size_t i = 0; i < Gimic2Enemyvec.size(); i++)
	{
		if (Gimic2Enemyvec[i]->IsUpdate() == true)
		{
			return false;
		}
	}

	return true;
}
