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
	GameEngineColor Color = static_cast<Level*>(GetLevel())->GetMap()->GetColor(Transform.GetWorldPosition(), GameEngineColor::RED);

	if (GameEngineColor::RED != Color)
	{
		GrivityForce.Y -= _Delta * 100.0f;
		Transform.AddLocalPosition(GrivityForce * _Delta);
	}
	else 
	{
		GrivityForce = 0.0f;
	}

}

