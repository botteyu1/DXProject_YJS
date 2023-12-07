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
#include "FxSpriteRenderer.h"
#include "Shader.h"
#include "StageObject.h"
#include "BossDesk.h"
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
		 PlayerPtr->Transform.SetLocalPosition({ 1107.0f, -3574.0f, -3.0f });
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


	std::shared_ptr<BossDesk> DeskActor = CreateActor<BossDesk>(ContentsObjectType::StageObject);
	BossPtr->DeskActor = DeskActor;

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
				std::shared_ptr<GameEngineCamera> MainCamara = GetMainCamera();
				float4 PlayerPos = PlayerPtr->Transform.GetWorldPosition();
				float4 Pos = { PlayerPos.X, -3150.0f,-1000.0f };
				MainCamara->Transform.SetWorldPosition(Pos);
			};


		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				BossUIPtr->Off();

				

			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				std::shared_ptr<GameEngineCamera> MainCamara = GetMainCamera();
				float4 PlayerPos = PlayerPtr->Transform.GetWorldPosition();
				float4 MainCamaraPos = MainCamara->Transform.GetWorldPosition();
				
				float distanceToTarget = DirectX::XMVectorGetX(DirectX::XMVector3Length(DirectX::XMVectorSubtract(MainCamara->Transform.GetLocalPosition().DirectXVector, PlayerPos.DirectXVector)));


				float4 Move = PlayerPos - MainCamaraPos;

				if (distanceToTarget > 10.0f)
				{
					MainCamara->Transform.AddLocalPosition({ Move.X * _DeltaTime * 3.0f });
				}

				float4 Pos = { PlayerPos.X, -3150.0f,-1000.0f };

				if (BossIntroOver == false)
				{
					float Volume = PlayerPos.X / (3450.0f - 1107.0f) * 0.5f + 0.3f;
					Bgm.SetVolume(Volume);
				}

				if (Pos.X >= 3450.0f and BossIntroOver == false)
				{
					Bgm.Stop();
					_Parent->ChangeState(BossLevelState::IntroCamera);
				}

				//MainCamara->Transform.SetWorldPosition(Pos);
			};

		State.CreateState(BossLevelState::Normal, NewPara);
	}	

	{
		CreateStateParameter NewPara;

		


		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				BossIntroOver = true;
				MovieBarPtr->MovieBarStart();
				PlayUIPtr->Off();
				PlayerPtr->ChangeState(PlayerState::ForceWait);

				GameEngineSound::SoundPlay("BossIntro1");

				BattleBG = GameEngineSound::SoundPlay("BossBGBattle");
				BattleBG.SetVolume(0.8f);

			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				std::shared_ptr<GameEngineCamera> MainCamara = GetMainCamera();
				//float4 PlayePos = PlayerPtr->Transform.GetWorldPosition();
				float4 MainCamaraPos = MainCamara->Transform.GetWorldPosition();
				float4 Pos = { MainCamaraPos.X + 1000.0f * _DeltaTime, -3150.0f,-1000.0f };
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
				float4 PlayerPos = PlayerPtr->Transform.GetLocalPosition();
				float4 BossPos = BossPtr->Transform.GetLocalPosition();

				if (PlayerPos.X < 3250.f)
				{
					PlayerPos.X = 3250.f;
					PlayerPtr->Transform.SetLocalPosition(PlayerPos);
				}
				else if (PlayerPos.X > 5150.f)
				{
					PlayerPos.X = 5150.f;
					PlayerPtr->Transform.SetLocalPosition(PlayerPos);
				}

				if (BossPos.X < 3250.f)
				{
					BossPos.X = 3250.f;
					BossPtr->Transform.SetLocalPosition(BossPos);
				}
				else if (BossPos.X > 5150.f)
				{
					BossPos.X = 5150.f;
					BossPtr->Transform.SetLocalPosition(BossPos);
				}

				if (BossPtr->GetState() == EnemyState::Death)
				{
					_Parent->ChangeState(BossLevelState::End);
				}
			};

		State.CreateState(BossLevelState::Boss, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Init = [=](class GameEngineState* _Parent)
			{
				
			};


		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				std::shared_ptr<FxSpriteRenderer> Renderer = GetFXActor()->FXStart(FXType::Circle_Gradient, false, BossPtr->Transform.GetLocalPosition() + float4(0.0f, 20.0f, -3.0f), float4(0.0f, 0.0f, 1.0f));
				Renderer->GetColorData().MulColor = float4{ 0.0f,0.0f,0.0f,1.0f };

				Renderer = GetFXActor()->FXStart(FXType::Gargoyle_Slash, false, BossPtr->Transform.GetLocalPosition() + float4(0.0f, 30.0f, -8.0f), float4(0.0f, 0.0f, 1.0f));
				Renderer->GetColorData().MulColor = float4{ 0.0f,0.0f,0.0f,1.0f };


				Renderer = GetFXActor()->FXStart(FXType::Gargoyle_Slash, false, BossPtr->Transform.GetLocalPosition() + float4(0.0f, 30.0f, -9.0f), float4(0.0f, 0.0f, 1.0f));
				Renderer->GetColorData().MulColor = float4{ 0.0f,0.0f,0.0f,1.0f };

				Renderer = GetFXActor()->FXStart(FXType::Gargoyle_Slash, false, BossPtr->Transform.GetLocalPosition() + float4(0.0f, 30.0f, -10.0f), float4(0.0f, 0.0f, 1.0f));
				Renderer->GetColorData().MulColor = float4{ 0.0f,0.0f,0.0f,1.0f };


				Renderer = GetFXActor()->FXStart(FXType::Gargoyle_Lightning, false, float4(BossPtr->Transform.GetLocalPosition().X - 60.0f, -3574.0f, -6.0f), float4(2.0f, 2.0f, 1.0f), float4(0.5f, 1.0f, 0.5f));
				Renderer->GetColorData().MulColor = float4{ 0.3f,0.0f,00.0f,1.0f };
				CircleFx = true;

				GameEngineSound::SoundPlay("BossOuttro1");

				//PlayerPtr->ChangeState(PlayerState::Idle);
				MovieBarPtr->MovieBarStart();
				PlayUIPtr->Off(); 
				BossUIPtr->Off();

				BGVolume = 0.6f;
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (_Parent->GetStateTime() >= 0.2f and CircleFx == true)
				{
					CircleFx = false;
					std::shared_ptr<FxSpriteRenderer> Renderer = GetFXActor()->FXStart(FXType::Circle_Gradient, false, BossPtr->Transform.GetLocalPosition() + float4(0.0f, 20.0f, -4.0f), float4(0.0f, 0.0f, 1.0f));
					Renderer->GetColorData().MulColor = float4{ 0.4f,0.0f,00.0f,1.0f };
				}
				
				float4 PlayerPos = PlayerPtr->Transform.GetLocalPosition();

				if (PlayerPos.X < 3250.f)
				{
					PlayerPos.X = 3250.f;
					PlayerPtr->Transform.SetLocalPosition(PlayerPos);
				}
				else if (PlayerPos.X > 5100.f)
				{
					PlayerPos.X = 5100.f;
					PlayerPtr->Transform.SetLocalPosition(PlayerPos);
				}

				
				if (BGVolume > 0.0f)
				{
					BattleBG.SetVolume(BGVolume );
					BGVolume -= _DeltaTime * 0.3f;
				}
				else
				{
					BGVolume = 0.0f;
					BattleBG.Stop();
				}

				if (BossPtr->IsUpdate() == false)
				{
					MovieBarPtr->MovieBarEnd();
					PlayUIPtr->On();
					_Parent->ChangeState(BossLevelState::Normal);
				}
			};

		State.CreateState(BossLevelState::End, NewPara);
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

	if (GameEngineInput::IsDown('Z', this))
	{
		Player::GetMainPlayerData().DebugScale = 100.0f;
	}
	if (GameEngineInput::IsDown('X', this))
	{
		Player::GetMainPlayerData().DebugScale = 1.0f;
	}

	/*if (GameEngineInput::IsDown('3', this))
	{
		std::shared_ptr<FxSpriteRenderer> Renderer = GetFXActor()->FXStart(FXType::Circle_Gradient, false, BossPtr->Transform.GetLocalPosition() + float4(0.0f, 20.0f, -3.0f), float4(0.0f, 0.0f, 1.0f));
		Renderer->GetColorData().MulColor = float4{ 0.0f,0.0f,0.0f,1.0f };

		Renderer = GetFXActor()->FXStart(FXType::Gargoyle_Slash, false, BossPtr->Transform.GetLocalPosition() + float4(0.0f, 30.0f, -8.0f), float4(0.0f, 0.0f, 1.0f));
		Renderer->GetColorData().MulColor = float4{ 0.0f,0.0f,0.0f,1.0f };

		
		Renderer = GetFXActor()->FXStart(FXType::Gargoyle_Slash, false, BossPtr->Transform.GetLocalPosition() + float4(0.0f, 30.0f, -9.0f), float4(0.0f, 0.0f, 1.0f));
		Renderer->GetColorData().MulColor = float4{ 0.0f,0.0f,0.0f,1.0f };

		Renderer = GetFXActor()->FXStart(FXType::Gargoyle_Slash, false, BossPtr->Transform.GetLocalPosition() + float4(0.0f, 30.0f, -10.0f), float4(0.0f, 0.0f, 1.0f));
		Renderer->GetColorData().MulColor = float4{ 0.0f,0.0f,0.0f,1.0f };

		
		Renderer = GetFXActor()->FXStart(FXType::Gargoyle_Lightning, false, float4(BossPtr->Transform.GetLocalPosition().X - 60.0f, -3574.0f, -6.0f), float4(2.0f, 2.0f, 1.0f), float4(0.5f, 1.0f, 0.5f));
		Renderer->GetColorData().MulColor = float4{ 0.3f,0.0f,00.0f,1.0f };
	}
	if (GameEngineInput::IsDown('4', this))
	{
		std::shared_ptr<FxSpriteRenderer> Renderer = GetFXActor()->FXStart(FXType::Circle_Gradient, false, BossPtr->Transform.GetLocalPosition() + float4(0.0f, 20.0f, -4.0f), float4(0.0f, 0.0f, 1.0f));
		Renderer->GetColorData().MulColor = float4{ 0.4f,0.0f,00.0f,1.0f };
	}
	if (GameEngineInput::IsDown('6', this))
	{
		ShaderActor->BossOutroShaderStart();
	}
	if (GameEngineInput::IsDown('7', this))
	{
		ShaderActor->BossOutroShaderEnd();
	}
	if (GameEngineInput::IsDown('5', this))
	{
		GetFXActor()->FXStart(FXType::Gargoyle_DarkTornado_UL, false, BossPtr->Transform.GetLocalPosition() + float4(-200.0f, -43.0f, 0.33f), float4(1.0f, 1.0f, 1.0f), float4(1.0f, 1.0f, 1.0f));
		GetFXActor()->FXStart(FXType::Gargoyle_DarkTornado_UL, false, BossPtr->Transform.GetLocalPosition() + float4(-350.0f, -205.0f, 0.66f), float4(2.0f, 2.0f, 1.0f), float4(1.0f, 1.0f, 1.0f));
		GetFXActor()->FXStart(FXType::Gargoyle_DarkTornado_UL, false, BossPtr->Transform.GetLocalPosition() + float4(-500.0f, -403.0f, 0.99f), float4(3.0f, 3.0f, 1.0f), float4(1.0f, 1.0f, 1.0f));
		
		GetFXActor()->FXStart(FXType::Gargoyle_DarkTornado, false, BossPtr->Transform.GetLocalPosition() + float4(-200.0f, 0.0f, -2.0f), float4(1.0f, 1.0f, 1.0f), float4(1.0f, 1.0f, 1.0f));
		GetFXActor()->FXStart(FXType::Gargoyle_DarkTornado, false, BossPtr->Transform.GetLocalPosition() + float4(-350.0f, -120.0f, -3.0f), float4(2.0f, 2.0f, 1.0f), float4(1.0f, 1.0f, 1.0f));
		GetFXActor()->FXStart(FXType::Gargoyle_DarkTornado, false, BossPtr->Transform.GetLocalPosition() + float4(-500.0f, -273.0f, -4.0f), float4(3.0f, 3.0f, 1.0f), float4(1.0f, 1.0f, 1.0f));

	}*/
}

void BossLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	Bgm = GameEngineSound::SoundPlay("BossBGStart", 100);
	Bgm.SetVolume(0.6f);
}

void BossLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMOff();
	EndBG.Stop();
}
