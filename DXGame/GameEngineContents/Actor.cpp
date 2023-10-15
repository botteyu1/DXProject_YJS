#include "PreCompile.h"
#include "Actor.h"
#include "Map.h"
#include "PlayLevel.h"
#include "PlayMap.h"

Actor::Actor() 
{
}

Actor::~Actor()
{
}

void Actor::Start()
{
	MainCollision->SetCollisionType(ColType::AABBBOX2D);
	AttackCollision->SetCollisionType(ColType::AABBBOX2D);
	GameEngineInput::AddInputObject(this);
}



void Actor::Update(float _Delta)
{
	GameEngineColor Color = PixelCollisionCheck({ 0.0f,-1.0f });
	float MovePixel = -1.0f;

	while (GameEngineColor::WHITE != Color)
	{
		MovePixel += 1.0f;

		// 아래 픽셀
		Color = PixelCollisionCheck({ 0.0f, MovePixel });
		if (ThroughFloorCheck == false and GameEngineColor::BLUE == Color)
		{
			continue;
		}
		if (GameEngineColor::WHITE == Color)
		{
			Transform.AddLocalPosition({ 0.0f, MovePixel });
			break;
		}

		// 우측 픽셀
		Color = PixelCollisionCheck({ MovePixel, 0.0f });
		if (GameEngineColor::RED != Color)
		{
			Transform.AddLocalPosition({ MovePixel, 0.0f });
			break;
		}
		// 좌측 픽셀
		Color = PixelCollisionCheck({ -MovePixel, 0.0f });
		if (GameEngineColor::RED != Color)
		{

			Transform.AddLocalPosition({ -MovePixel, 0.0f });
			break;
		}
		
		// 위쪽 픽셀
		Color = PixelCollisionCheck({ 0.0f, -MovePixel });
		if (GameEngineColor::RED != Color)
		{

 			Transform.AddLocalPosition({ 0.0f , -MovePixel });
			break;
		}
		
		//대각선 픽셀 확인
		Color = PixelCollisionCheck({ MovePixel, MovePixel });
		if (GameEngineColor::RED != Color)
		{
			Transform.AddLocalPosition({ MovePixel, MovePixel });
			break;
		}
		Color = PixelCollisionCheck({ -MovePixel, MovePixel });
		if (GameEngineColor::RED != Color)
		{
			Transform.AddLocalPosition({ -MovePixel, MovePixel });
			break;
		}
		Color = PixelCollisionCheck({ MovePixel, -MovePixel });
		if (GameEngineColor::RED != Color)
		{
			Transform.AddLocalPosition({ MovePixel, -MovePixel });
			break;
		}
		Color = PixelCollisionCheck({ -MovePixel, -MovePixel });
		if (GameEngineColor::RED != Color)
		{
			Transform.AddLocalPosition({ -MovePixel, -MovePixel });
			break;
		}
		
		
	}

	//공중인지 체크
	 Color = PixelCollisionCheck({ 0.0f,-1.0f });

	//공중
	if (
		(GameEngineColor::WHITE == Color or
		GameEngineColor::BLUE == Color and ThroughFloorCheck == true) and  //바닥 통과 체크
		ForceGrivityOff == false 
		)
	{
		AerialCheck = true;
		GrivityForce.Y -= _Delta * 5000.f; 
		Transform.AddLocalPosition(GrivityForce * _Delta);
	}
	//중력이 꺼져도 공중인지 체크하고 중력초기화
	else if (GameEngineColor::WHITE == Color)
	{
		AerialCheck = true;
		GrivityForce = 0.0f;
	}
	//지상 
	else
	{
		GrivityForce = 0.0f;  
		AerialCheck = false;
		/*if (AerialCheck == true and ForceGrivityOff == false)*/
	}
	


	//HP 체크

	if (HP <= 0)
	{
		//Death();
	}

	
}

void Actor::ChangeMainAnimation(std::string_view _AnimationName)
{
	MainSpriteRenderer->ChangeAnimation(_AnimationName);
	CurAnimationData = &AnimationDataMap.find(_AnimationName.data())->second;
	float Pivot = CurAnimationData->PivotX;
	

	float4 CollisionScale = CurAnimationData->CollisionScale;
	float4 CollisionPosition = CurAnimationData->CollisionPosition;
	FlipCheck();
	if (Flip == true)
	{
		CollisionPosition.X = -CollisionPosition.X;
		Pivot = 1.0f - Pivot;
	}
	
	MainSpriteRenderer->SetPivotValue({ Pivot, 1.0f });
	//  공격 콜리전 활성화
	
	if(AttackCollision != nullptr  )
	{
		AttackCollision->Off();
		AttackCollision->Transform.SetLocalScale(CollisionScale);
		AttackCollision->Transform.SetLocalPosition(CollisionPosition);
	}

	CurDash = 0;
	FrameCheck = false;
}

bool Actor::CheckStartAttackFrame()
{
	float4 CollisionScale = CurAnimationData->CollisionScale;
	float4 CollisionPosition = CurAnimationData->CollisionPosition;
	float4 AttackPivot = CurAnimationData->AttackFxPivot;
	float4 AttackPosition = CurAnimationData->AttackFxPos;

	int Frame = MainSpriteRenderer->GetCurIndex();

	

	if (CurAnimationData->AttackCollisionStartFrame == MainSpriteRenderer->GetCurIndex() and FrameCheck == false)
	{

		FrameCheck = true;
		if (Flip == true)
		{
			CollisionPosition.X = -CollisionPosition.X;
		}
		
		
		if (CollisionScale != float4::ZERO)
		{
			AttackCollision->On();
			AttackCollision->Transform.SetLocalScale(CollisionScale);
			AttackCollision->Transform.SetLocalPosition(CollisionPosition);
		}
		
		//공격 이펙트 처리
		if (CurAnimationData->AttackFx != "")
		{
			AttackfxRenderer->On();
			if (Flip == true)
			{
				AttackPosition.X = -AttackPosition.X;
				AttackfxRenderer->Transform.SetLocalPosition(AttackPosition);
				AttackfxRenderer->LeftFlip();
			}
			else
			{
				AttackfxRenderer->RightFlip();
				AttackfxRenderer->Transform.SetLocalPosition(AttackPosition);
				AttackPivot.X = 1.0f - AttackPivot.X;
			}
			AttackfxRenderer->SetPivotValue( AttackPivot);
			AttackfxRenderer->ChangeAnimation(CurAnimationData->AttackFx,true);
		}

		return true;
	}
	return false;
}

void Actor::DashProcessUpdate(float _Delta,const float4& _Dir, float _Speed)
{

	if (DashStartCheck == false)
	{
		return;
	}

	if (CurDash == CurAnimationData->DashDistance)
	{
		return;
	}

	float NextSpeed = _Speed * _Delta;

	CurDash += NextSpeed;

	if (CurDash >= CurAnimationData->DashDistance)
	{
		NextSpeed -= CurDash - CurAnimationData->DashDistance;
		CurDash = CurAnimationData->DashDistance;
	}

	float4 NextPos = _Dir * NextSpeed;

	if (Flip == true)
	{
		NextPos.X = -NextPos.X;
	}
	Transform.AddLocalPosition(NextPos);
}

void Actor::FlipCheck()
{
	float Pivot = CurAnimationData->PivotX;
	float4 PrevPivot = MainSpriteRenderer->GetPivotValue();

	if (Flip == true)
	{
		Pivot = 1.0f - Pivot;
		if (Flip != FlipPrev)
		{
			Dir = float4::LEFT;
			MainSpriteRenderer->SetPivotValue({ Pivot, 1.0f });

			MainSpriteRenderer->LeftFlip();
			float MovePos = (Pivot - PrevPivot.X) * -0.8f * DefaultScale.X;
			MainSpriteRenderer->Transform.AddLocalPosition({ MovePos,0.0f });
		}
		FlipPrev = Flip;
	}
	if (Flip == false)
	{
		if (Flip != FlipPrev)
		{
			Dir = float4::RIGHT;
			MainSpriteRenderer->SetPivotValue({ Pivot, 1.0f });
			MainSpriteRenderer->RightFlip();
			
			float MovePos = (Pivot - PrevPivot.X) * -0.8f * DefaultScale.X;
			MainSpriteRenderer->Transform.AddLocalPosition({ MovePos,0.0f });
		}
		FlipPrev = Flip;
	}
}

GameEngineColor Actor::PixelCollisionCheck(float4 _Pixel, GameEngineColor _DefaultColor)
{
	float4 WorldPosition = Transform.GetWorldPosition();
	WorldPosition += _Pixel;
	GameEngineColor Color = static_cast<Level*>(GetLevel())->GetMap()->GetColor(WorldPosition, GameEngineColor::RED);

	return Color;
}

GameEngineColor Actor::PosCollisionCheck(float4 _Pos, GameEngineColor _DefaultColor)
{
	
	GameEngineColor Color = static_cast<Level*>(GetLevel())->GetMap()->GetColor(_Pos, GameEngineColor::RED);

	return Color;
}

