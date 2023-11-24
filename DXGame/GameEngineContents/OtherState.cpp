#include "PreCompile.h"
#include "Player.h"
#include "BookOfTheDead.h"
#include "FX.h"

void Player::HitStart()
{
	ChangeMainAnimation("LD_Hit");
}


void Player::HitUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		if (AerialCheck == true)
		{
			ChangeState(PlayerState::Jump_Falling);
		}
		else if (GameEngineInput::IsPress('A', this) or GameEngineInput::IsPress('D', this))
		{
			ChangeState(PlayerState::Run);
		}
		else
		{
			ChangeState(PlayerState::Idle);
		}
	}
}

void Player::EnterElavatorStart()
{
	TargetPlayerPos = Transform.GetLocalPosition();
	TargetPos.Z = TargetPlayerPos.Z;
	if (TargetPlayerPos.X > TargetPos.X)
	{
		Flip = true;
	}
	else
	{
		Flip = false;
	}
	ChangeMainAnimation("LD_Run");
	MotionTime = 0.0f;
}

void Player::EnterElavatorUpdate(float _Delta)
{
	MotionTime += _Delta ;
	if (0.5f >= MotionTime)
	{
		float4 Pos = float4::LerpClamp(TargetPlayerPos, TargetPos, MotionTime * 2.0f);
		Transform.SetLocalPosition(Pos);
	}
	else if (1.0f >= MotionTime)
	{
		
		ChangeMainAnimation("LD_Elevator_Enter");
		return;
	}
	else if (MainSpriteRenderer->IsCurAnimationEnd() == true)
	{
		ChangeMainAnimation("LD_Elevator_End");

		
	}
	else if (3.0f >= MotionTime)
	{
		if (GetLevel()->GetName() == "PlayLevel")
		{
			GetContentsLevel()->LevelChangerStart("PlayLevel2");
			//GetContentsLevel()->LevelChangeStart("PlayLevel2");
		}
		else if (GetLevel()->GetName() == "PlayLevel2")
		{
			GetContentsLevel()->LevelChangerStart("BossLevel");
			//GameEngineCore::ChangeLevel("BossLevel");
		}
		else if (GetLevel()->GetName() == "BossLevel")
		{
			GetContentsLevel()->LevelChangerStart("BossLevel");
			//GameEngineCore::ChangeLevel("BossLevel");
		}
	}

}

void Player::ExitElavatorStart()
{
	On();
	
	ChangeMainAnimation("LD_Elevator_Out");
}

void Player::ExitElavatorUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd() == true)
	{
		PlayerBook->Transform.SetLocalPosition(Transform.GetLocalPosition() + 50.0f);
		PlayerBook->On();
		ChangeState(PlayerState::Idle);
	}
}

void Player::ForceWaitStart()
{
	ForceGrivityOff = false;
	ChangeMainAnimation("LD_Idle");
}

void Player::ForceWaitUpdate(float _Delta)
{
}


void Player::AcquisitionStart()
{
	ChangeMainAnimation("LD_Acquisition");
}

void Player::AcquisitionUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd() == true)
	{
		
		ChangeState(PlayerState::Idle);
	}
}

void Player::PowerUpStart()
{
	ChangeMainAnimation("LD_Acquisition_Curse");


	GetContentsLevel()->GetFXActor()->FXStart(FXType::Death, Flip, Transform.GetLocalPosition() + float4(0.0f, 0.0f,2.0f), float4(2.0f,2.0f,4.0f));
}


void Player::PowerUpUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd() == true)
	{
		AerialCheck = false;
		ChangeState(PlayerState::Idle);
	}
}
