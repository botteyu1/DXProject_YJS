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
		std::shared_ptr<Player> Object = CreateActor<Player>(ContentsObjectType::Player);
	}

	{
		std::shared_ptr<PlayMap> Object = CreateActor<PlayMap>(ContentsObjectType::BackGround);
		Object->Init("Stage1.dds", "StagePixel1.png", "Stage2.dds", "StagePixel2.png");
		SetMap(Object);
	}
	FXActor = CreateActor<FX>(ContentsObjectType::FX);

	//CreateActor<Ghost_Man>(ContentsObjectType::Enemy);
	//CreateActor<Ghost_Woman>(ContentsObjectType::Enemy);
	//CreateActor<PossessedBook>(ContentsObjectType::Enemy);
	//CreateActor<BossGargoyle>(ContentsObjectType::Enemy);
	//CreateActor<Ghost_Med>(ContentsObjectType::Enemy);
	{
		std::shared_ptr<Elevator> Object = CreateActor<Elevator>(ContentsObjectType::StageObject);
		Object->Init(ElevatorState::Start);
	}

	
	std::shared_ptr<BGObject> Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
	Object->Init("GhostWorkersBox1.png"); 

	Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
	Object->Init("GhostWorkersBox11.png");

	Level::Start();
}


void PlayLevel::Update(float _Delta)
{
	
}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	int a = 0;
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}
