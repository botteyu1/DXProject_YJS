#include "PreCompile.h"
#include "Player.h"

void Player::ComboMoveStart()
{
	MainSpriteRenderer->ChangeAnimation("LD_ComboMove_01");
	ComboCount = 2;
	NextCombo = false;
}


// 프레임으로 다음콤보 시작 위치 확인
// 마지막 프레임에서 딜레이 있어야될듯?

void Player::ComboMoveUpdate(float _Delta)
{
	if (GameEngineInput::IsDown(VK_LBUTTON))
	{
		NextCombo = true;
	}
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		if (NextCombo == true and ComboCount < 5)
		{
			MainSpriteRenderer->ChangeAnimation("LD_ComboMove_0" + std::to_string(ComboCount));
			ComboCount++;
			NextCombo = false;
		}
		else
		{
			ChangeState(PlayerState::Idle);
		}
	}
}

void Player::InputAttackUpdate(float _Delta)
{
	if (GameEngineInput::IsDown(VK_LBUTTON))
	{
		ChangeState(PlayerState::ComboMove);
		FlipCheck();
		return;
	}

	return;
}