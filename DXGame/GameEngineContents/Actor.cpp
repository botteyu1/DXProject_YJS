#include "PreCompile.h"
#include "Actor.h"
#include "Map.h"
#include "PlayLevel.h"
#include "FX.h"
#include "PlayMap.h"
#include "SecondaryRenderer.h"

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
	LightRenderer = CreateComponent<SecondaryRenderer>(ContentsRenderType::SecondaryRenderer);
	LightRenderer->Init(SecondaryRendererType::Light, { 0.0f,100.0f, 3.0f }, { 500.0f,500.0f,1.0f });

	//FXActor = GetLevel()->CreateActor<FX>(ContentsObjectType::FX);
	
}



void Actor::Update(float _Delta)
{
    // ����׸�����̸� ������Ʈ ����
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
	else if (GameEngineColor::WHITE == Color)
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
	


	//HP üũ

	if (HP <= 0)
	{
		//Death();
	}

	
}

void Actor::ChangeMainAnimation(std::string_view _AnimationName)
{
	MainSpriteRenderer->ChangeAnimation(_AnimationName);
	CurAnimationData = &AnimationDataMap.find(_AnimationName.data())->second;
	

	
	FlipCheck();
	
	//  ���� �ݸ��� ��Ȱ��ȭ
	
	if(AttackCollision != nullptr  )
	{
		///AttackCollision->Off();
		AttackCollision->Transform.SetLocalScale({ 0.0f,0.0f,0.0f });
		AttackCollision->Transform.SetLocalPosition({ 0.0f,0.0f,0.0f });
	}

	CurDash = 0;
	FrameCheck = false;
}

bool Actor::CheckStartAttackFrame(int _Index)
{
	//�������
	int AttackCollisionStartFrame = CurAnimationData->AttackCollisionStartFrame;

	//�ֽ�
	if (_Index != -1)
	{
		AttackCollisionStartFrame = _Index;
	}


	if (AttackCollisionStartFrame == MainSpriteRenderer->GetCurIndex() and FrameCheck == false)
	{
	
		float4 CollisionScale = CurAnimationData->CollisionScale;
		float4 CollisionPosition = CurAnimationData->CollisionPosition;

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
	
		return true;
	}
	return false;
}

bool Actor::CheckEndAttackFrame(int _Index)
{
	int AttackCollisionEndFrame = _Index;

	if (AttackCollisionEndFrame == MainSpriteRenderer->GetCurIndex() and FrameCheck == true)
	{
		FrameCheck = false;

		AttackCollision->Transform.SetLocalScale({ 0.0f,0.0f,0.0f });
		AttackCollision->Transform.SetLocalPosition({ 0.0f,0.0f,0.0f });

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

	if (CurDash == CurAnimationData->DashDistance and MainSpriteRenderer->GetCurIndex() < static_cast<unsigned int>(CurAnimationData->AttackCollisionStartFrame))
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
	float PivotY = CurAnimationData->PivotY;
	float4 PrevPivot = MainSpriteRenderer->GetPivotValue();

	if (Flip == true)
	{
		Pivot = 1.0f - Pivot;
		if (Flip != FlipPrev)
		{
			
		}
		Dir = float4::LEFT;
		MainSpriteRenderer->SetPivotValue({ Pivot, PivotY });

		MainSpriteRenderer->LeftFlip();
		float MovePos = (Pivot - PrevPivot.X) * -0.8f * DefaultScale.X;
		MainSpriteRenderer->Transform.AddLocalPosition({ MovePos,0.0f });
		FlipPrev = Flip;
	}
	if (Flip == false)
	{
		if (Flip != FlipPrev)
		{
		
		}
		Dir = float4::RIGHT;
		MainSpriteRenderer->SetPivotValue({ Pivot, PivotY });

		float MovePos = (Pivot - PrevPivot.X) * -0.8f * DefaultScale.X;
		MainSpriteRenderer->Transform.AddLocalPosition({ MovePos,0.0f });
		MainSpriteRenderer->RightFlip();

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
//
//void Actor::CheckAttackCollision()
//{
//	EventParameter Parameter;
//
//	Parameter.Enter = ComboHit;
//	Parameter.Exit =[](){}
//	AttackCollision->CollisionEvent<ContentsCollisionType>(ContentsCollisionType::Player, { ComboHit,nullptr,nullptr });
//}
