#include "PreCompile.h"
#include "PlayLevel2.h"
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
#include <GameEngineCore/EngineEnum.h>
#include <GameEngineCore/FadePostEffect.h>
#include "CurseUI.h"

PlayLevel2::PlayLevel2() 
{
}

PlayLevel2::~PlayLevel2()
{
}

void PlayLevel2::Start()
{

	FXActor = CreateActor<FX>(ContentsObjectType::FX);
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -5000.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);

	{
		PlayerPtr = CreateActor<Player>(ContentsObjectType::Player);
		PlayerPtr->Transform.SetLocalPosition({ 1085.0f, -3507.0f, 5.0f });
	}
	{
		std::shared_ptr<PlayMap> Object = CreateActor<PlayMap>(ContentsObjectType::BackGround);
		Object->Init("Stage3.dds", "StagePixel3.png", "Stage2.dds", "StagePixel2.png");
		SetMap(Object);
	}

	PlayUIPtr = CreateActor<PlayUI>(ContentsObjectType::UI);

	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("GameEngineResources");
	Dir.MoveChild("ContentsResources\\Data\\Stage3.GameData");

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
				std::shared_ptr<GameEngineCamera> MainCamara = GetMainCamera();
				float4 PlayerPos = PlayerPtr->Transform.GetWorldPosition() + float4{ 0.0f,0.0f,-1000.0f };
				MainCamara->Transform.SetLocalPosition(PlayerPos);
				
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				//카메라 포커스

				std::shared_ptr<GameEngineCamera> MainCamara = GetMainCamera();
				float4 PlayerPos = PlayerPtr->Transform.GetWorldPosition();
				float4 CameraPos = MainCamara->Transform.GetLocalPosition();
				CameraPos.Z = PlayerPos.Z;

				//float4 TargetNor = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(PlayerPos.DirectXVector, CameraPos.DirectXVector));

				float distanceToTarget = DirectX::XMVectorGetX(DirectX::XMVector3Length(DirectX::XMVectorSubtract(MainCamara->Transform.GetLocalPosition().DirectXVector, PlayerPos.DirectXVector)));


				float4 Move = PlayerPos - CameraPos;

				if (distanceToTarget > 10.0f)
				{
					MainCamara->Transform.AddLocalPosition(Move * _DeltaTime * 3.0f);
				}

				CameraPos = MainCamara->Transform.GetLocalPosition();


				if (CameraPos.X < 830.0f)
				{
					CameraPos.X = 830.0f;
					MainCamara->Transform.SetLocalPosition(CameraPos);
				}
				if (CameraPos.Y < -3800.0f)
				{
					CameraPos.Y = -3800.0f;
					MainCamara->Transform.SetLocalPosition(CameraPos);
				}

				if (MainCamara->Transform.GetLocalPosition().X >= 11200.0f and GimmickValue == false)
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
				PaperWallValue = true;
				GameEngineSound::SoundPlay("PaperWallOn");

			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				//카메라 포커스

				std::shared_ptr<GameEngineCamera> MainCamara = GetMainCamera();
				float4 MainCamaraPos = MainCamara->Transform.GetWorldPosition();
				float4 TargetPos = float4{ 11760.0f,-930.0f, MainCamaraPos.Z };
				float4 Nor = (TargetPos - MainCamaraPos).NormalizeReturn();

				float4 Pos = { Nor * _DeltaTime * 300.0f };

				MainCamara->Transform.AddLocalPosition(Pos);

				if (MainCamara->Transform.GetLocalPosition().X >= 11760.0f)
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
					GimicEnemyvec[i]->Spawn();
				}


			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{

				if (State.GetStateTime() >= 5.0f and Gimmick2Value == false)
				{
					Gimmick2Value = true;
					for (size_t i = 0; i < Gimic2Enemyvec.size(); i++)
					{
						Gimic2Enemyvec[i]->Spawn();
					}
				}

				if (CheckGimmickOver() == true and State.GetStateTime() >= 9.0f)
				{
					State.ChangeState(PlayLevelState::GimmickEndIntro);
				}

			};

		State.CreateState(PlayLevelState::Gimmick, NewPara);
	}

	{
		CreateStateParameter NewPara;


		NewPara.Start = [=](class GameEngineState* _Parent)
			{

			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				std::shared_ptr<GameEngineCamera> MainCamara = GetMainCamera();
				float4 MainCamaraPos = MainCamara->Transform.GetWorldPosition();
				float4 TargetPos = float4{ 11780.0f,-650.0f, MainCamaraPos.Z };
				float4 Nor = (TargetPos - MainCamaraPos).NormalizeReturn();

				float4 Pos = { Nor * _DeltaTime * 300.0f };

				MainCamara->Transform.AddLocalPosition(Pos);

				if (MainCamara->Transform.GetLocalPosition().Y <= -650.0f)
				{
					MainCamara->Transform.SetLocalPosition(TargetPos);
					State.ChangeState(PlayLevelState::GimmickEnd);
				}

			};

		State.CreateState(PlayLevelState::GimmickEndIntro, NewPara);
	}
	{
		CreateStateParameter NewPara;


		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				for (size_t i = 0; i < PaperWallvec.size(); i++)
				{
					PaperWallvec[i]->GimmckEnd();
				}
				PaperWallValue = false;


				float4 TargetPos = float4{ 11780.0f,-650.0f, 5.0f };
				WeaponDropObject = CreateActor<WeaponDrop>(ContentsObjectType::BackGround);
				WeaponDropObject->Transform.SetLocalPosition(TargetPos);
				WeaponDropObject->Spawn();
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{


				if (State.GetStateTime() >= 3.0f)
				{

					State.ChangeState(PlayLevelState::Normal);
				}

				/*if (WeaponDropObject->AerialCheck == false or WeaponDropObject->IsUpdate() == false)
				{
					State.ChangeState(PlayLevelState::Normal);
				}*/

			};

		State.CreateState(PlayLevelState::GimmickEnd, NewPara);
	}


	State.ChangeState(PlayLevelState::Normal);

	GameEngineInput::AddInputObject(this);
}


void PlayLevel2::Update(float _Delta)
{
	//카메라 포커스

	State.Update(_Delta);


	//if (GameEngineInput::IsDown('V', this))
	//{
	//	/*GetCurseUI()->CurseUIStart(1);

	//	GetCamera(static_cast<int>(ECAMERAORDER::UI))->GetCameraAllRenderTarget()->CreateEffect<FadePostEffect>();*/
	//	if (WeaponDropObject != nullptr)
	//	{
	//		WeaponDropObject->Death();
	//	}

	//	WeaponDropObject = CreateActor<WeaponDrop>(ContentsObjectType::BackGround);
	//	WeaponDropObject->Transform.SetLocalPosition(PlayerPtr->Transform.GetLocalPosition());
	//	WeaponDropObject->Spawn();
	//}
}

void PlayLevel2::LevelStart(GameEngineLevel* _PrevLevel)
{
	int a = 0;
	GimmickValue = false;
}

void PlayLevel2::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}

bool PlayLevel2::CheckGimmickOver()
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
