#include "PreCompile.h"
#include "Player.h"

void Player::ComboMoveStart()
{
	ComboCount++;
	std::string AnimationName = "LD_ComboMove_0" + std::to_string(ComboCount);
	MainSpriteRenderer->ChangeAnimation(AnimationName);
	CurAnimationData = &PlayerAnimationDataMap.find(AnimationName)->second;
	NextCombo = false;
	CurDash = 0;
}

void Player::ComboMove_RestStart()
{
	MainSpriteRenderer->ChangeAnimation("LD_ComboMove_0" + std::to_string(ComboCount) + "_Rest");
}

// ���������� �����޺� ���� ��ġ Ȯ��
// ������ �����ӿ��� ������ �־�ߵɵ�?

void Player::ComboMoveUpdate(float _Delta)
{
	if (GameEngineInput::IsDown(VK_LBUTTON))
	{
		NextCombo = true;
	}
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		if (NextCombo == true and ComboCount < 4)
		{
			ChangeState(PlayerState::ComboMove);
		}
		else
		{
			ChangeState(PlayerState::ComboMove_Rest);
		}
	}
	// �뽬 ó��

	// ���� �뽬�Ÿ��� ��ǥ �뽬�Ÿ��� ������ �뽬ó��x
	if (CurDash == CurAnimationData->DashDistance)
	{
		return;
	}
	
	float Speed = 2000.0f;
	float NextPos = Speed * _Delta;
	
	CurDash += NextPos;

	if (CurDash >= CurAnimationData->DashDistance)
	{
		NextPos -= CurDash - CurAnimationData->DashDistance;
		CurDash = CurAnimationData->DashDistance;

		
	}
	if (Flip == true)
	{
		NextPos = -NextPos;
	}
	Transform.AddLocalPosition(NextPos);
}



void Player::ComboMove_RestUpdate(float _Delta)
{
	if (GameEngineInput::IsDown(VK_LBUTTON) and ComboCount < 4)
	{
		ChangeState(PlayerState::ComboMove);
	}
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
	}
}

void Player::InputAttackUpdate(float _Delta)
{
	if (GameEngineInput::IsDown(VK_LBUTTON))
	{
		ComboCount = 0;
		ChangeState(PlayerState::ComboMove);
		FlipCheck();
		return;
	}

	return;
}