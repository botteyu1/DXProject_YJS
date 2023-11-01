#include "PreCompile.h"
#include "Player.h"
#include "BookOfTheDead.h"

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
		MainSpriteRenderer->ChangeAnimation("LD_Elevator_Enter");
		return;
	}
	else if (MainSpriteRenderer->IsCurAnimationEnd() == true)
	{
		ChangeMainAnimation("LD_Elevator_End");
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
	ForceGrivityOff = true;
	ChangeMainAnimation("LD_Idle");
}

void Player::ForceWaitUpdate(float _Delta)
{
}


