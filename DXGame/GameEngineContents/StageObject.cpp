#include "PreCompile.h"
#include "StageObject.h"
#include "Map.h"

StageObject::StageObject() 
{
}

StageObject::~StageObject()
{
}

void StageObject::Start()
{
}

void StageObject::Update(float _Delta)
{
	if (DebugValue == true)
	{
		InputDebugUpdate(_Delta);
		return;
	}
	//픽셀로 밀어내기
	GameEngineColor Color = PixelCollisionCheck({ 0.0f,-1.0f });
	float MovePixel = -1.0f;


	while (GameEngineColor::WHITE != Color)
	{
		MovePixel += 1.0f;

		// 아래 픽셀
		Color = PixelCollisionCheck({ 0.0f, MovePixel });

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



	Color = PixelCollisionCheck({ 0.0f,-1.0f });

	//공중
	if ((GameEngineColor::WHITE == Color) and ForceGrivityOff == false)
	{
		AerialCheck = true;
		GrivityForce.Y -= _Delta * 2000.f;
		Transform.AddLocalPosition(GrivityForce * _Delta);
	}
	//중력이 꺼져도 공중인지 체크하고 중력초기화
	else if (BouncingValue == false)
	{
		BouncingValue = true;
		GrivityForce.Y = 300.0f;

		Transform.AddLocalPosition({ 0.0f,2.0f });
	}
	//지상 
	else
	{
		AerialCheck = false;
		GrivityForce = 0.0f;
	}


	if (DebugValue == true)
	{
		return;
	}

}

GameEngineColor StageObject::PixelCollisionCheck(float4 _Pixel, GameEngineColor _DefaultColor)
{
	float4 WorldPosition = Transform.GetWorldPosition();
	WorldPosition += _Pixel;
	GameEngineColor Color = static_cast<Level*>(GetLevel())->GetMap()->GetColor(WorldPosition, GameEngineColor::RED);

	return Color;
}

GameEngineColor StageObject::PosCollisionCheck(float4 _Pos, GameEngineColor _DefaultColor)
{

	GameEngineColor Color = static_cast<Level*>(GetLevel())->GetMap()->GetColor(_Pos, GameEngineColor::RED);

	return Color;
}