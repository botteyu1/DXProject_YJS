#include "PreCompile.h"
#include "MapEditorLevel.h"
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
MapEditorLevel::MapEditorLevel() 
{
}

MapEditorLevel::~MapEditorLevel()
{
}

void MapEditorLevel::Start()
{
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -1005.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);

	{
		std::shared_ptr<PlayMap> Object = CreateActor<PlayMap>(ContentsObjectType::BackGround);
		Object->Init("Stage3.dds", "StagePixel3.png", "Stage2.dds", "StagePixel2.png");
		//Object->Init("StageBoss.dds", "StagePixelBoss.png");
		SetMap(Object);
	}
	FXActor = CreateActor<FX>(ContentsObjectType::FX);

	//Map::Start();
	GameEngineInput::AddInputObject(this);

	Level::Start();
}


void MapEditorLevel::Update(float _Delta)
{


	float MoveSpeed = 500;

	if (GameEngineInput::IsPress(VK_SHIFT, this))
	{
		MoveSpeed = 1000;
	}

	if (GameEngineInput::IsPress('A', this))
	{
		GetMainCamera()->Transform.AddLocalPosition(float4::LEFT * _Delta * MoveSpeed);
	}


	if (GameEngineInput::IsPress('D', this))
	{
		GetMainCamera()->Transform.AddLocalPosition(float4::RIGHT * _Delta * MoveSpeed);
	}

	if (GameEngineInput::IsPress('W', this))
	{
		GetMainCamera()->Transform.AddLocalPosition(float4::UP * _Delta * MoveSpeed);
	}


	if (GameEngineInput::IsPress('S', this))
	{
		GetMainCamera()->Transform.AddLocalPosition(float4::DOWN * _Delta * MoveSpeed);
	}
}

void MapEditorLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	int a = 0;
}

void MapEditorLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}