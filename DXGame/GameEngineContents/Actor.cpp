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
	//Dir = float4::ZERO;

	//�������� üũ
	float4 WorldPosition = Transform.GetWorldPosition();
	float4 UpPixel = { 0.0f, 1.0f };
	//WorldPosition.Y -= 1.0f;
	GameEngineColor Color = static_cast<Level*>(GetLevel())->GetMap()->GetColor(WorldPosition, GameEngineColor::RED);
	
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
	else
	{
		GrivityForce = 0.0f;  

		if (AerialCheck == true and ForceGrivityOff == false)
		{
			while(true)
			{
				WorldPosition += UpPixel;
				GameEngineColor Color = static_cast<Level*>(GetLevel())->GetMap()->GetColor(WorldPosition, GameEngineColor::RED);
				if (GameEngineColor::RED == Color)
				{
					Transform.AddLocalPosition(UpPixel);
				}
				else
				{
					AerialCheck = false;
					break;
				}
			}
		}
	}

	
	

}

