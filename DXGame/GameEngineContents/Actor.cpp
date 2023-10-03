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

}

void Actor::Update(float _Delta)
{
	GameEngineColor Color = PixelCollisionCheck({ 0.0f,-1.0f });
	float MovePixel = 0.0f;

	while (GameEngineColor::RED == Color)
	{
		// �Ʒ� �ȼ�
		Color = PixelCollisionCheck({ 0.0f, MovePixel });
		if (GameEngineColor::RED != Color)
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
		
		MovePixel += 1.0f;
	}

	//�������� üũ
	 Color = PixelCollisionCheck({ 0.0f,-1.0f });
	 MovePixel = 0.0f;

		//����
	if (GameEngineColor::RED != Color and ForceGrivityOff == false)
	{
		AerialCheck = true;
		GrivityForce.Y -= _Delta * 5000.f; 
		Transform.AddLocalPosition(GrivityForce * _Delta);
	}
	//�߷��� ������ �������� üũ�ϰ� �߷��ʱ�ȭ
	else if (GameEngineColor::RED != Color)
	{
		AerialCheck = true;
		GrivityForce = 0.0f;
	}
	//���� 
	else
	{
		GrivityForce = 0.0f;  
		AerialCheck = false;

		/*if (AerialCheck == true and ForceGrivityOff == false)*/
	}
	// ����
	

	
	
	Color = PixelCollisionCheck({ 1.0f,0.0f });
	GameEngineColor Color2 = PixelCollisionCheck({ -1.0f, 0.0f });
	
	

}

void Actor::ChangeMainAnimation(std::string_view _AnimationName)
{
	MainSpriteRenderer->ChangeAnimation(_AnimationName);
	CurAnimationData = &AnimationDataMap.find(_AnimationName.data())->second;
	if (Flip == true)
	{
		MainSpriteRenderer->SetPivotValue({ 1.0f - CurAnimationData->PivotX, 1.0f });
	}
	else
	{
		MainSpriteRenderer->SetPivotValue({ CurAnimationData->PivotX, 1.0f });
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

