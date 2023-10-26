#include "PreCompile.h"
#include "FxSpriteRenderer.h"

FxSpriteRenderer::FxSpriteRenderer() 
{
}

FxSpriteRenderer::~FxSpriteRenderer()
{
}

void FxSpriteRenderer::Update(float _Delta)
{

	switch (Type)
	{
	case FXType::Surprised:
		break;
	case FXType::Shockwave:
		Scale.Y += _Delta * 1.5f;
		Scale.X += _Delta * 1.5f;
		SetAutoScaleRatio(Scale);
		//MainSpriteRenderer->SetSprite("Shockwave.png");
		if (Flip == false)
		{
			Transform.AddLocalPosition(float4(-300.0f * _Delta, 0.0f));
		}
		else
		{
			Transform.AddLocalPosition(float4(300.0f * _Delta, 0.0f));
		}

		if (Scale.X >= 0.6f)
		{
			Off();
		}
		break;
	default:
		break;
	}

	GameEngineSpriteRenderer::Update(_Delta);
}

