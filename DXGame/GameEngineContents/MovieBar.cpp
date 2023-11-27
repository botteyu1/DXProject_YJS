#include "PreCompile.h"
#include "MovieBar.h"
#include "ContentsCore.h"

MovieBar::MovieBar() 
{
}

MovieBar::~MovieBar()
{
}


void MovieBar::MovieBarStart()
{
	On();
	MovieBar_Renderer_Up->GetColorData().MulColor = float4{ 0.0f,0.0f,0.0f,0.0f };
	MovieBar_Renderer_Down->GetColorData().MulColor = float4{ 0.0f,0.0f,0.0f,0.0f };
	//GetLevel()

	Dir = 1.0f;
	CurAlpha = 0.0f;
}

void MovieBar::MovieBarEnd()
{
	Dir = -1.0f;
	CurAlpha = 1.0f;
}

void MovieBar::Start()
{
	float4 WindowScale = ContentsCore::GetStartWindowSize();

	MovieBar_Renderer_Up = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::MovieBar);
	MovieBar_Renderer_Up->SetMaterial("2DTextureAlwaysDepth");
	MovieBar_Renderer_Up->SetCameraOrder(ECAMERAORDER::UI);
	MovieBar_Renderer_Up->SetSprite("ShaderWhite.Png");
	MovieBar_Renderer_Up->GetImageTransform().SetLocalScale(float4{ WindowScale.X,120.0f,1.0f });
	MovieBar_Renderer_Up->Transform.SetLocalPosition({0.0f, 480.0});
	MovieBar_Renderer_Up->GetColorData().MulColor = float4{ 0.0f,0.0f,0.0f,1.0f };
	MovieBar_Renderer_Up->SetName("MovieBar_Renderer_Up");

	MovieBar_Renderer_Down = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::MovieBar);
	MovieBar_Renderer_Down->SetMaterial("2DTextureAlwaysDepth");
	MovieBar_Renderer_Down->SetCameraOrder(ECAMERAORDER::UI);
	MovieBar_Renderer_Down->SetSprite("ShaderWhite.Png");
	MovieBar_Renderer_Down->GetImageTransform().SetLocalScale( float4{WindowScale.X,120.0f,1.0f });
	MovieBar_Renderer_Down->Transform.SetLocalPosition({0.0f, -480.0});
	MovieBar_Renderer_Down->GetColorData().MulColor = float4{ 0.0f,0.0f,0.0f,1.0f };
	MovieBar_Renderer_Down->SetName("MovieBar_Renderer_Up");
}

void MovieBar::Update(float _Delta)
{
	CurAlpha += _Delta * Dir;

	if (CurAlpha < 0.0f)
	{
		Off();
	}
	else if (CurAlpha > 1.0f)
	{
		CurAlpha = 1.0f;
	}

	MovieBar_Renderer_Up->GetColorData().MulColor = float4{ 0.0f,0.0f,0.0f,CurAlpha };
	MovieBar_Renderer_Down->GetColorData().MulColor = float4{ 0.0f,0.0f,0.0f,CurAlpha };
}

void MovieBar::LevelStart(GameEngineLevel* _NextLevel)
{
}
