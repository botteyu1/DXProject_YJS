#include "PreCompile.h"
#include "LevelChanger.h"
#include "ContentsCore.h"

LevelChanger::LevelChanger() 
{
}

LevelChanger::~LevelChanger()
{
}



void LevelChanger::Start()
{
	if (nullptr == GameEngineTexture::Find("Transition01_0001.png"))
	{
		GameEngineDirectory Dir2;
		Dir2.MoveParentToExistsChild("GameEngineResources");
		Dir2.MoveChild("ContentsResources\\Sprite\\UI");
		std::vector<GameEngineDirectory> Directorys = Dir2.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& File = Directorys[i];

			GameEngineSprite::CreateFolder(File.GetStringPath());
		}
	}

	float4 WindowScale = ContentsCore::GetStartWindowSize();

	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Transition);
	MainSpriteRenderer->SetMaterial("2DTextureAlwaysDepth");
	MainSpriteRenderer->SetCameraOrder(ECAMERAORDER::UI);
	MainSpriteRenderer->AutoSpriteSizeOn();
	MainSpriteRenderer->SetAutoScaleRatio({ 2.0f,2.0f,1.0f });
	MainSpriteRenderer->CreateAnimation("TransitionIntro", "Transition", 0.0533f, -1, -1, false);
	MainSpriteRenderer->CreateAnimation("TransitionOuttro", "Transition", 0.0533f, 24, 0, false);
	MainSpriteRenderer->Transform.AddLocalPosition({ 0.0f , -WindowScale.Y/2});
	//MainSpriteRenderer->GetImageTransform().SetLocalScale(WindowScale + float4{ 0.0f,0.0f,1.0f });
	//GlobalShader->GetColorData().MulColor = float4{ 0.07f,0.11f,0.0f,0.2f };
	MainSpriteRenderer->SetPivotValue({ 0.5f,1.0f,0.5f });
	MainSpriteRenderer->SetName("Transition");
	MainSpriteRenderer->ChangeAnimation("TransitionOuttro", true);
	MainSpriteRenderer->Off();
	//MainSpriteRenderer->ChangeAnimation("TransitionOuttro", true);
}

void LevelChanger::LevelChangeStart(std::string_view _Name)
{
	MainSpriteRenderer->On();
	MainSpriteRenderer->ChangeAnimation("TransitionIntro", true);
	NextLevelName = _Name;

}


void LevelChanger::Update(float _Delta)
{
	if ( MainSpriteRenderer->IsCurAnimationEnd() == true )
	{
		
		if (MainSpriteRenderer->IsCurAnimation("TransitionIntro"))
		{
			DelayTime += _Delta;
			if (DelayTime >= 1.0f)
			{
				GameEngineCore::ChangeLevel(NextLevelName);
				DelayTime = 0.0f;
			}
		}
		else
		{
			MainSpriteRenderer->Off();
		}
	}
}

void LevelChanger::LevelStart(GameEngineLevel* _NextLevel)
{
	if (IntroOff == true)
		return;
	MainSpriteRenderer->ChangeAnimation("TransitionOuttro", true);
	MainSpriteRenderer->On();
}

void LevelChanger::LevelEnd(GameEngineLevel* _NextLevel)
{
	MainSpriteRenderer->Off();
}



