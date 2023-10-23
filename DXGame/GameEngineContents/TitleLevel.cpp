#include "PreCompile.h"
#include "TitleLevel.h"
#include "Title.h"

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Start()
{

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -5000.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	CreateActor<Title>(ContentsObjectType::BackGroundobject);
	
}


void TitleLevel::Update(float _Delta)
{
	if (GameEngineInput::IsPress('P', this))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}
}


void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	int a = 0;
}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}