#include "PreCompile.h"
#include "Player.h"


void Player::IdleStart()
{
	MainSpriteRenderer->ChangeAnimation("LD_Idle");
}

void Player::JumpStart()
{
}

void Player::RunStart()
{
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

void Player::AttackStart()
{
}


void Player::IdleUpdate(float _Delta)
{

	Dir = float4::ZERO;

	if (GameEngineInput::IsPress('A'))
	{
		Dir += float4::LEFT;
	}
	if (GameEngineInput::IsPress('D'))
	{
		Dir += float4::RIGHT;
	}

	if (Dir == float4::LEFT)
	{
		Transform.AddLocalPosition(Dir * _Delta * Speed);
		if (Flip == true)
		{
			ChangeState(PlayerState::Run);
		}
		else
		{
			ChangeState(PlayerState::RunUturn);
		}
	}
	else if (Dir == float4::RIGHT)
	{
		Transform.AddLocalPosition(Dir * _Delta * Speed);
		if (Flip == false)
		{
			ChangeState(PlayerState::Run);
		}
		else
		{
			ChangeState(PlayerState::RunUturn);
		}
	}
}

void Player::JumpUpdate(float _Delta)
{
}

void Player::RunUpdate(float _Delta)
{
	Dir = float4::ZERO;

	if (GameEngineInput::IsPress('A'))
	{
		Dir += float4::LEFT;
	}
	if (GameEngineInput::IsPress('D'))
	{
		Dir += float4::RIGHT;
	}
	if (Dir == float4::ZERO)
	{
		ChangeState(PlayerState::RunToIdle);
	}
	else
	{
		Transform.AddLocalPosition(Dir * _Delta * Speed);
	}
	
}

void Player::RunUturnUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		if (Dir == float4::LEFT)
		{
			MainSpriteRenderer->FlipOn();
			Flip = true;
		}
		if (Dir == float4::RIGHT)
		{
			MainSpriteRenderer->FlipOff();
			Flip = false;
		}
		ChangeState(PlayerState::Run);
	}

	Dir = float4::ZERO;

	if (GameEngineInput::IsPress('A'))
	{
		Dir += float4::LEFT;
	}
	if (GameEngineInput::IsPress('D'))
	{
		Dir += float4::RIGHT;
	}

	if (Dir == float4::ZERO)
	{
		MainSpriteRenderer->Flip();
		Flip = !Flip;
		ChangeState(PlayerState::RunToIdle);
	}
	else
	{
		Transform.AddLocalPosition(Dir * _Delta * Speed * 0.5f);
	}
}

void Player::RunToIdleUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
	}

	Dir = float4::ZERO;

	if (GameEngineInput::IsPress('A'))
	{
		Dir += float4::LEFT;
	}
	if (GameEngineInput::IsPress('D'))
	{
		Dir += float4::RIGHT;
	}

	if (Dir == float4::LEFT)
	{
		Transform.AddLocalPosition(Dir * _Delta * Speed);
		if (Flip == true)
		{
			ChangeState(PlayerState::Run);
		}
		else
		{
			ChangeState(PlayerState::RunUturn);
		}
	}
	else if (Dir == float4::RIGHT)
	{

		Transform.AddLocalPosition(Dir * _Delta * Speed);
		if (Flip == false)
		{
			ChangeState(PlayerState::Run);
		}
		else
		{
			ChangeState(PlayerState::RunUturn);
		}
	}
}

void Player::EndUturnEvent(GameEngineRenderer* _Renderer)
{
	MainSpriteRenderer->Flip();

}


void Player::AttackUpdate(float _Delta)
{
}