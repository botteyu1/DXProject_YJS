#include "PreCompile.h"
#include "Player.h"

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
		else if (GameEngineInput::IsPress('A') or GameEngineInput::IsPress('D'))
		{
			ChangeState(PlayerState::Run);
		}
		else
		{
			ChangeState(PlayerState::Idle);
		}
	}
}
