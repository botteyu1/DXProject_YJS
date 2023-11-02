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

		//MapLevel->ClearContentsObject();

	DeSerializer(BinSer, false);
	

	Level::Start();
}


void PlayLevel::Update(float _Delta)
{
	//카메라 포커스
	std::shared_ptr<GameEngineCamera> MainCamara = GetMainCamera();
	float4 PlayePos = PlayerPtr->Transform.GetWorldPosition();
	//float4 Pos = PlayePos

	MainCamara->Transform.SetLocalPosition(PlayePos + float4{ 0.0f,0.0f,-1000.0f });
}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	int a = 0;
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}
