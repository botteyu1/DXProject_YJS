#include "PreCompile.h"
#include "FxSpriteRenderer.h"
#include "Enemy.h"
#include "FX.h"

FxSpriteRenderer::FxSpriteRenderer() 
{
}

FxSpriteRenderer::~FxSpriteRenderer()
{
}

void FxSpriteRenderer::Update(float _Delta)
{
	Time += _Delta;
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
	case FXType::SpawnEnemy:
	{

		if (GetCurIndex() == 21)
		{
			SpawnObject->On();
		}

		if (IsCurAnimationEnd() == true)
		{
			
			Off();
		}
		break;
	}
	case FXType::SpawnWeapon:
	{

		if (IsCurAnimationEnd() == true)
		{
			Off();
		}
		break;
	}
	case FXType::Circle_Gradient:
	{

		Scale.X += _Delta * 50.0f * Dir;
		Scale.Y += _Delta * 50.0f * Dir;
		SetAutoScaleRatio(Scale);

		if (Scale.X >= 20.0f)
		{
			Off();
		}
		break;
	}
	case FXType::Flash: {

		if (Scale.X <= 2.0f)
		{
			Scale.X += _Delta * 5.0f * Dir;
			Scale.Y += _Delta * 5.0f * Dir;
		}
		
		else
		{
			Scale.X += _Delta * 20.0f * Dir;
			Scale.Y += _Delta * 20.0f * Dir;
		}
		

		SetAutoScaleRatio(Scale);

		if (Scale.X >= 4.0f)
		{
			Dir = -2.0f;
			FX* Parent = dynamic_cast<FX*>(GetParentObject());
			Parent->GetContentsLevel()->GetFXActor()->FXStart(FXType::SpawnWeapon, false, Transform.GetLocalPosition() + float4(0.0f, 20.0f), float4(10.0f, 10.0f, 1.0f));
			Parent->GetContentsLevel()->GetFXActor()->FXStart(FXType::Circle_Gradient, false, Transform.GetLocalPosition() + float4(0.0f, 20.0f), float4(0.0f, 0.0f, 1.0f));
			
			if(SpawnObject != nullptr)
			{
				SpawnObject->On();
			}
		}

		if (Scale.X < 0.0f)
		{
			Off();
		}

		break;
	}

	default:
	case FXType::DamageText:
	{
		if (Time >= 1.0f)
		{
			Off();
		}
	}
		break;
	}

	GameEngineSpriteRenderer::Update(_Delta);
}

