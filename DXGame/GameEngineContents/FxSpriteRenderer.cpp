#include "PreCompile.h"
#include "FxSpriteRenderer.h"
#include "Enemy.h"
#include "Player.h"
#include "FX.h"


//#define NOMINMAX

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
	
	case FXType::Slash:
	{
		//Renderer->Scale = float4(0.5f, 2.0f, 1.0f);

		Scale.X += _Delta * 3.0f * Dir;
		Scale.Y -= _Delta * 4.5f * Dir;
		SetAutoScaleRatio(Scale);

		if (Scale.Y <= 0.0f)
		{
			Off();
		}
		break;
	}
	case FXType::Flash: {

		if (Scale.X <= 1.5f)
		{
			Scale.X += _Delta * 2.0f * Dir;
			Scale.Y += _Delta * 2.0f * Dir;
		}
		
		else
		{
			Scale.X += _Delta * 25.0f * Dir;
			Scale.Y += _Delta * 25.0f * Dir;
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
	case FXType::SlashHit:
	{
		//Renderer->Scale = float4(0.5f, 2.0f, 1.0f);

		Scale.X += _Delta * 10.0f * Dir;
		Scale.Y -= _Delta * 20.0f * Dir;
		SetAutoScaleRatio(Scale);

		if (Scale.Y <= 0.0f)
		{
			Off();
		}
		break;
	}
	
	case FXType::Gargoyle_Slash:
	{
		//Renderer->Scale = float4(0.5f, 2.0f, 1.0f);

		Scale.X -= _Delta * 15.0f * Dir;
		Scale.Y -= _Delta * 30.0f * Dir;
		SetAutoScaleRatio(Scale);

		if (Scale.Y <= 0.0f)
		{
			Off();
		}
		break;
	}

	case FXType::Hit:
	{
		if (IsCurAnimationEnd() == true)
		{
			Off();
		}
		break;
	}
	case FXType::Shard:
	{
		
		{
			Scale.X += _Delta * 10.0f * Dir;
			Scale.Y += _Delta * 10.0f * Dir;
		}

		if (Time >= 0.3f)
		{
			Dir = -1.0f;
			if (SpawnObject != nullptr)
			{
				SpawnObject->On();

			}
		}
		if (Time >= 0.4f)
		{
			if (SpawnObject != nullptr and false == SpawnObjectOnCheck)
			{
				SpawnObjectOnCheck = true;
				SpawnObject->On();
				SpawnObject->Transform.SetLocalPosition(Transform.GetLocalPosition() + float4(0.0f, 50.0f, -3.0f));

			}
		}

		SetAutoScaleRatio(Scale);
		float4 Rotate = float4::VectorRotationToDegZ(float4::RIGHT, Transform.GetLocalRotationEuler().Z);
		float4 NextPos = Rotate * _Delta * 400.0f;

		Transform.AddLocalPosition(NextPos);

		if (Time >= 0.5f)
		{
			
			Off();
		}
		break;
	}
	case FXType::Death:
	{
		Alpha -= _Delta * 1.6f;


		Scale.X += _Delta * 3.0f;
		Scale.Y += _Delta * 3.0f;
		SetAutoScaleRatio(Scale);

		Transform.AddLocalPosition(float4::UP* _Delta * 600.0f);

		GetColorData().MulColor = float4(1.0f, 1.0f, 1.0f, Alpha);

		if (Alpha <= 0.0f)
		{
			Off();
		}
		break;
	}
	case FXType::DamageText:
	{
		if (Alpha > 0.7f)
		{
			Alpha -= _Delta * 0.2f;

			Transform.AddLocalPosition(float4::UP* _Delta * 50.0f);

			SetTextAlpha(Alpha);
		}
		else if (Alpha > 0.0f)
		{
			
			Alpha -= _Delta * 2.5f;
			if (Alpha < 0.0f)
			{
				Alpha = 0.0f;
			}

			Transform.AddLocalPosition(float4::UP* _Delta * 400.0f);

			SetTextAlpha(Alpha);
		}
		else
		{
			SetTextAlpha(Alpha);
			Off();
		}
	}
	break;
	case FXType::TakeAnima: 
	{
		//DirectX::XMVectorSubtract
		//DirectX::XMVECTOR = D;
		//static const float GRAVITY_PULL = 1000000.0f;

		if (Time <= 0.8f)
		{
			float4 TargetNor = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(TargetPos.DirectXVector, Transform.GetLocalPosition().DirectXVector));

			float distanceToTarget = DirectX::XMVectorGetX(DirectX::XMVector3Length(DirectX::XMVectorSubtract(Transform.GetLocalPosition().DirectXVector, TargetPos.DirectXVector)));

			float pullStrength = 4000.0f;


			gravityForce += TargetNor * pullStrength * _Delta;



			Transform.AddLocalPosition(gravityForce* _Delta);


			/*Scale.X -= _Delta * 0.2f;
			Scale.Y -= _Delta * 0.2f;*/
		}
		else if (Time > 0.8f)
		{
			float4 TargetNor = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract({ -820.0f,515.0f,0.0f }, Transform.GetLocalPosition().DirectXVector));

			float distanceToTarget = DirectX::XMVectorGetX(DirectX::XMVector3Length(DirectX::XMVectorSubtract(Transform.GetLocalPosition().DirectXVector, { -820.0f,515.0f,0.0f })));

			//float pullStrength = distanceToTarget * 4.0f;
			float pullStrength = 3500.0f  ;

			if (TargetNor.X > 0.0f or TargetNor.Y < 0.0f)
			{
				pullStrength += 1500.0f;
			}


			gravityForce += gravityForce.NormalizeReturn() * (-1200.0f - (Time * 800.0f)) * _Delta;

			gravityForce += TargetNor * pullStrength * _Delta;


			Transform.AddLocalPosition(gravityForce* _Delta);

			Scale.X -= _Delta * 0.4f;
			Scale.Y -= _Delta * 0.4f;
		}
		else if (Time > 1.5f)
		{
			Scale.X -= _Delta * 1.2f;
			Scale.Y -= _Delta * 1.2f;
		}
		if(Scale.X <= 0.0f)
		{

			GameEngineSound::SoundPlay("AnimaUI");
			Player::GetMainPlayerData().AddAnima();
			Off();
		}
		SetAutoScaleRatio(Scale);
	}
	break;

	case FXType::Gargoyle_DarkTornado:
	{
		if (Time > 2.0f and IsCurAnimation("Gargoyle_DarkTornado_End") == false)
		{
			ChangeAnimation("Gargoyle_DarkTornado_End");
		}
		break;
	}
	case FXType::Gargoyle_DarkTornado_UL:
	{
		if (Time > 2.0f and IsCurAnimation("Gargoyle_DarkTornado_UL_End") == false)
		{
			ChangeAnimation("Gargoyle_DarkTornado_UL_End");
		}
		break;
	}

	default:
	{
		
	}
		break;
	}

	GameEngineSpriteRenderer::Update(_Delta);
}

