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
}



void Actor::Update(float _Delta)
{
	GameEngineColor Color = PixelCollisionCheck({ 0.0f,-1.0f });
	float MovePixel = -1.0f;

	while (GameEngineColor::WHITE != Color)
	{
		MovePixel += 1.0f;

		// �Ʒ� �ȼ�
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

		// ���� �ȼ�
		Color = PixelCollisionCheck({ MovePixel, 0.0f });
		if (GameEngineColor::RED != Color)
		{
			Transform.AddLocalPosition({ MovePixel, 0.0f });
			break;
		}
		// ���� �ȼ�
		Color = PixelCollisionCheck({ -MovePixel, 0.0f });
		if (GameEngineColor::RED != Color)
		{

			Transform.AddLocalPosition({ -MovePixel, 0.0f });
			break;
		}
		
		// ���� �ȼ�
		Color = PixelCollisionCheck({ 0.0f, -MovePixel });
		if (GameEngineColor::RED != Color)
		{

 			Transform.AddLocalPosition({ 0.0f , -MovePixel });
			break;
		}
		
		//�밢�� �ȼ� Ȯ��
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

	//�������� üũ
	 Color = PixelCollisionCheck({ 0.0f,-1.0f });

	//����
	if (
		(GameEngineColor::WHITE == Color or
		GameEngineColor::BLUE == Color and ThroughFloorCheck == true) and  //�ٴ� ��� üũ
		ForceGrivityOff == false 
		)
	{
		AerialCheck = true;
		GrivityForce.Y -= _Delta * 5000.f; 
		Transform.AddLocalPosition(GrivityForce * _Delta);
	}
	//�߷��� ������ �������� üũ�ϰ� �߷��ʱ�ȭ
	/*else if (GameEngineColor::WHITE == Color)
	{
		AerialCheck = true;
		GrivityForce = 0.0f;
	}*/
	//���� 
	else
	{
		GrivityForce = 0.0f;  
		AerialCheck = false;
		/*if (AerialCheck == true and ForceGrivityOff == false)*/
	}
	


	//HP üũ

	if (HP <= 0)
	{
		Death();
	}

}

void Actor::ChangeMainAnimation(std::string_view _AnimationName)
{
	MainSpriteRenderer->ChangeAnimation(_AnimationName);
	CurAnimationData = &AnimationDataMap.find(_AnimationName.data())->second;
	float Pivot = CurAnimationData->PivotX;
	float4 CollisionScale = CurAnimationData->CollisionScale;
	float4 CollisionPosition = CurAnimationData->CollisionPosition;

	if (Flip == true)
	{
		Pivot = 1.0f - Pivot;
		CollisionPosition.X = -CollisionPosition.X;
	}
	MainSpriteRenderer->SetPivotValue({ Pivot, 1.0f });

	//  ���� �ݸ��� Ȱ��ȭ
	if (CollisionScale != float4::ZERO)
	{
		AttackCollision->On();
		AttackCollision->Transform.SetLocalScale(CollisionScale);
		AttackCollision->Transform.SetLocalPosition(CollisionPosition);
	}
	else if(AttackCollision != nullptr)
	{
		AttackCollision->Off();
		AttackCollision->Transform.SetLocalScale(CollisionScale);
		AttackCollision->Transform.SetLocalPosition(CollisionPosition);
	}

	CurDash = 0;
}

void Actor::DashProcessUpdate(float _Delta,const float4& _Dir, float _Speed)
{
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

GameEngineColor Actor::PixelCollisionCheck(float4 _Pixel, GameEngineColor _DefaultColor)
{
	float4 WorldPosition = Transform.GetWorldPosition();
	WorldPosition += _Pixel;
	GameEngineColor Color = static_cast<Level*>(GetLevel())->GetMap()->GetColor(WorldPosition, GameEngineColor::RED);

	return Color;
}

