#include "PreCompile.h"
#include "TitleLevel.h"
#include "Title.h"
#include "LevelChanger.h"

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

	CreateActor<Title>(ContentsObjectType::UI);
	Level::Start();

	LevelChangerPtr->IntroOff = true;
	
}


void TitleLevel::Update(float _Delta)
{
	
}


void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	Bgm = GameEngineSound::SoundPlay("OST Main Menu", 100);
}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	Bgm.Stop();
}