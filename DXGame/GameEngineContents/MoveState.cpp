#include "PreCompile.h"
#include "Player.h"


void Player::IdleStart()
{
	MainSpriteRenderer->ChangeAnimation("LD_Idle");
}

void Player::Jump_FallingStart()
{
	MainSpriteRenderer->ChangeAnimation("LD_Jump_Falling");
}
void Player::Jump_LandingStart()
{
	MainSpriteRenderer->ChangeAnimation("LD_Jump_Landing");
}
void Player::Jump_StartStart()
{
	MainSpriteRenderer->ChangeAnimation("LD_Jump_Start");
	
	GrivityForce.Y += 1500.f;
	Transform.AddLocalPosition({ 0.0f,1.0f });
	
}

void Player::RunStart()
{
	FlipCheck();
	MainSpriteRenderer->ChangeAnimation("LD_Run");
}

void Player::RunUturnStart()
{
	MainSpriteRenderer->ChangeAnimation("LD_RunUturn");
}

void Player::RunToIdleStart()
{
	
	MainSpriteRenderer->ChangeAnimation("LD_RunToIdle");
}





void Player::IdleUpdate(float _Delta)
{
	bool PreFlip = Flip;
	InputMoveUpdate(_Delta);


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
	
}

void Player::RunUpdate(float _Delta)
{
	bool PreFlip = Flip;
	InputMoveUpdate(_Delta);
	
	if (Flip != PreFlip)
	{
		ChangeState(PlayerState::RunUturn);
	}

	if (Dir == float4::ZERO)
	{
		ChangeState(PlayerState::RunToIdle);
	}

	InputJumpUpdate(_Delta);
}

void Player::RunUturnUpdate(float _Delta)
{
	bool PreFlip = Flip;
	InputMoveUpdate(_Delta);
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		//FlipCheck();
		ChangeState(PlayerState::Run);
	}


	if (Dir == float4::ZERO)
	{
		
		FlipCheck();
		//MainSpriteRenderer->Flip();
		ChangeState(PlayerState::Idle);
	}
	InputJumpUpdate(_Delta);
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
}



void Player::Jump_FallingUpdate(float _Delta)
{
	InputMoveUpdate(_Delta);

	if (GrivityCheck == false)
	{
		ChangeState(PlayerState::Jump_Landing);
	}
	FlipCheck();
}


void Player::Jump_LandingUpdate(float _Delta)
{
	InputMoveUpdate(_Delta);
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
	}
	InputJumpUpdate(_Delta);
}



void Player::Jump_StartUpdate(float _Delta)
{
	InputMoveUpdate(_Delta);
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(PlayerState::Jump_Falling);
	}
	if (GameEngineInput::IsPress(VK_SPACE))
	{
		GrivityForce.Y += 5000.0f * _Delta;
	}
}






void Player::InputMoveUpdate(float _Delta)
{
	Dir = float4::ZERO;

	if (GameEngineInput::IsPress('A'))
	{
		Dir += float4::LEFT;
		Flip = true;
	}
	if (GameEngineInput::IsPress('D'))
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
		Transform.AddLocalPosition(Dir * _Delta * Speed * 1.0f);
	}
}

//점프 시작 업데이트
void Player::InputJumpUpdate(float _Delta)
{
	if (GameEngineInput::IsDown(VK_SPACE))
	{
		ChangeState(PlayerState::Jump_Start);
	}
	
}


void Player::FlipCheck()
{
	if (Flip == true)
	{
		MainSpriteRenderer->FlipOn();
		//Flip = true;
	}
	else if (Flip == false)
	{
		MainSpriteRenderer->FlipOff();
		//Flip = false;
	}
}
