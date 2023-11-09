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
	//�ȼ��� �о��
	GameEngineColor Color = PixelCollisionCheck({ 0.0f,-1.0f });
	float MovePixel = -1.0f;


	while (GameEngineColor::WHITE != Color)
	{
		MovePixel += 1.0f;

		// �Ʒ� �ȼ�
		Color = PixelCollisionCheck({ 0.0f, MovePixel });

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



	Color = PixelCollisionCheck({ 0.0f,-1.0f });

	//����
	if ((GameEngineColor::WHITE == Color) and ForceGrivityOff == false)
	{
		AerialCheck = true;
		GrivityForce.Y -= _Delta * 2000.f;
		Transform.AddLocalPosition(GrivityForce * _Delta);
	}
	//�߷��� ������ �������� üũ�ϰ� �߷��ʱ�ȭ
	else if (BouncingValue == false)
	{
		BouncingValue = true;
		GrivityForce.Y = 300.0f;

		Transform.AddLocalPosition({ 0.0f,2.0f });
	}
	//���� 
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