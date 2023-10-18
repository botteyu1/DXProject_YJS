#include "PreCompile.h"
#include "Player.h"



void Player::IdleStart()
{
	ChangeMainAnimation("LD_Idle");
}

void Player::Jump_FallingStart()
{ 
	ChangeMainAnimation("LD_Jump_Falling");
}
void Player::Jump_LandingStart()
{
	ChangeMainAnimation("LD_Jump_Landing");
	ThroughFloorCheck = false;
	AerialComboCount = 0;
}
void Player::Jump_StartStart()
{
	ChangeMainAnimation("LD_Jump_Start");

	GrivityForce.Y += JumpingSpeed;
	Transform.AddLocalPosition({ 0.0f,1.0f });
}

void Player::RunStart()
{
	
	ChangeMainAnimation("LD_Run");
}

void Player::RunUturnStart()
{
	Flip = !Flip;
	ChangeMainAnimation("LD_RunUturn");
}

void Player::RunToIdleStart()
{
	
	ChangeMainAnimation("LD_RunToIdle");
}

void Player::DashStart()
{
	ChangeMainAnimation("LD_Dash");
	CurDash = 0.0f;
	ForceGrivityOff = true;
}




void Player::IdleUpdate(float _Delta)
{
	bool PreFlip = Flip;

	InputMoveUpdate(_Delta);
	InputJumpUpdate(_Delta);
	InputAttackUpdate(_Delta);
	InputDashUpdate(_Delta);

	if (Dir != float4::ZERO)
	{
		if (Flip == PreFlip)
		{
			ChangeState(PlayerState::Run);
		}
		else
		{
			ChangeState(PlayerState::RunUturn);
		}
	}
	
}

void Player::RunUpdate(float _Delta)
{
	bool PreFlip = Flip;
	InputMoveUpdate(_Delta);
	InputJumpUpdate(_Delta);
	InputAttackUpdate(_Delta);
	InputDashUpdate(_Delta);
	
	if (Flip != PreFlip)
	{
		ChangeState(PlayerState::RunUturn);
	}

	if (Dir == float4::ZERO)
	{
		ChangeState(PlayerState::RunToIdle);
	}

	
}

void Player::RunUturnUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		
		ChangeState(PlayerState::Run);
	}


	if (Dir == float4::ZERO)
	{
		ChangeState(PlayerState::Idle);
	}

	InputMoveUpdate(_Delta);
	InputJumpUpdate(_Delta);
	InputDashUpdate(_Delta);
	InputAttackUpdate(_Delta);
}

void Player::RunToIdleUpdate(float _Delta)
{
	bool PreFlip = Flip;
	InputMoveUpdate(_Delta);
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
	}

	if (Dir != float4::ZERO)
	{
		if (Flip == PreFlip)
		{
			ChangeState(PlayerState::Run);
		}
		else
		{
			ChangeState(PlayerState::RunUturn);
		}
	}

	InputJumpUpdate(_Delta);
	InputAttackUpdate(_Delta);
	InputDashUpdate(_Delta);

}



void Player::Jump_FallingUpdate(float _Delta)
{
	InputMoveUpdate(_Delta);

	if (AerialCheck == false)
	{
		ChangeState(PlayerState::Jump_Landing);
	}
	FlipCheck();
	InputAttackUpdate(_Delta);
	InputDashUpdate(_Delta);
}


void Player::Jump_LandingUpdate(float _Delta)
{
	bool PreFlip = Flip;
	InputMoveUpdate(_Delta);

	if (Flip != PreFlip)
	{
		ChangeState(PlayerState::RunUturn);
	}
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
	}
	InputJumpUpdate(_Delta);
	InputDashUpdate(_Delta);
	InputAttackUpdate(_Delta);
	 //혹시모르는 점프시작 콤보 초기화
}



void Player::Jump_StartUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(PlayerState::Jump_Falling);
	}
	if (GameEngineInput::IsPress(VK_SPACE, this))
	{
		GrivityForce.Y += 5000.0f * _Delta;
	}
	InputDashUpdate(_Delta);
	InputMoveUpdate(_Delta);
	InputAttackUpdate(_Delta);

	InputDashUpdate(_Delta);
	//AerialComboCount = 0; // 착지할떄 공중콤보 초기화
	
}

void Player::DashUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ForceGrivityOff = false;
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

	if (Flip == true)
	{
		Transform.AddLocalPosition(float4::LEFT * _Delta * 2000.0f);
	}
	if (Flip == false)
	{
		Transform.AddLocalPosition(float4::RIGHT * _Delta * 2000.0f);
	}

}




void Player::InputMoveUpdate(float _Delta)
{
	Dir = float4::ZERO;

	if (GameEngineInput::IsPress('A', this))
	{
		Dir += float4::LEFT;
		Flip = true;
	}
	if (GameEngineInput::IsPress('D', this))
	{
		Dir += float4::RIGHT;
		Flip = false;
	}
	

	if (Dir == float4::RIGHT)
	{
		Flip = false;
	}
	
	if (Dir == float4::LEFT)
	{
		Flip = true;
	}
	

	if (Dir != float4::ZERO)
	{
		Transform.AddLocalPosition(Dir * _Delta * MoveSpeed * 1.0f);
	}
}

//점프 시작 업데이트
void Player::InputJumpUpdate(float _Delta)
{
	if (GameEngineInput::IsDown(VK_SPACE, this) and GameEngineInput::IsPress('S', this) and AerialCheck == false)
	{
		ChangeState(PlayerState::Jump_Falling);
		ThroughFloorCheck = true;
		return;
	}
		

	if (GameEngineInput::IsDown(VK_SPACE, this))
	{
		ChangeState(PlayerState::Jump_Start);
	}
}


void Player::InputDashUpdate(float _Delta)
{
	/*if (GameEngineInput::IsDown(VK_LSHIFT, this))
	{
		ChangeState(PlayerState::Dash);
	}*/
}

