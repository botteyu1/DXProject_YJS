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

	//공중인지 체크
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
	//중력이 꺼져도 공중인지 체크하고 중력초기화
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

