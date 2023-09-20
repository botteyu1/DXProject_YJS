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


void Player::ComboAerialStart()
{
	AerialComboCount++;
	std::string AnimationName = "LD_ComboAerial_0" + std::to_string(AerialComboCount);
	MainSpriteRenderer->ChangeAnimation(AnimationName);
	CurAnimationData = &PlayerAnimationDataMap.find(AnimationName)->second;
	NextCombo = false;
	CurDash = 0;
	ForceGrivityOff = true;
} 

void Player::ComboAerial_RestStart()
{
	ForceGrivityOff = false;
	MainSpriteRenderer->ChangeAnimation("LD_ComboAerial_0" + std::to_string(AerialComboCount) + "_Rest");
}

void Player::JumpingAttackStart()
{
	MainSpriteRenderer->ChangeAnimation("LD_JumpingAttack");
	CurAnimationData = &PlayerAnimationDataMap.find("LD_JumpingAttack")->second;
	ForceGrivityOff = true;
	CurDash = 0;
}

void Player::AerialDownAttackStart()
{
	MainSpriteRenderer->ChangeAnimation("LD_AerialDownAttack");
	GrivityForce.Y -= 3500.f;
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
		if (NextCombo == true and AerialComboCount < 4)
		{
			ChangeState(PlayerState::ComboMove);
		}
		else
		{
			ChangeState(PlayerState::ComboMove_Rest);
		}
	}
	InputDashUpdate(_Delta);
	// 대쉬 처리

	// 현재 대쉬거리와 목표 대쉬거리가 같으면 대쉬처리x
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
	if (GameEngineInput::IsPress('W') and GameEngineInput::IsDown(VK_LBUTTON))
	{
		ChangeState(PlayerState::JumpingAttack);
	}

	else if (GameEngineInput::IsDown(VK_LBUTTON) and ComboCount < 4)
	{
		ChangeState(PlayerState::ComboMove);
	}
	else if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
	}

	InputDashUpdate(_Delta);
}



void Player::ComboAerialUpdate(float _Delta)
{
	if (GameEngineInput::IsDown(VK_LBUTTON))
	{
		NextCombo = true;
	}
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		if (NextCombo == true and AerialComboCount < 3)
		{
			ChangeState(PlayerState::ComboAerial);

		}
		else
		{
			ChangeState(PlayerState::ComboAerial_Rest);
		}
	}

	

	InputDashUpdate(_Delta);
	// 대쉬 처리

	// 현재 대쉬거리와 목표 대쉬거리가 같으면 대쉬처리x
	if (CurDash == CurAnimationData->DashDistance)
	{
		return;
	}

	
	float NextPos = DashSpeed * _Delta;

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

void Player::ComboAerial_RestUpdate(float _Delta)
{
	if (GameEngineInput::IsPress('W') and GameEngineInput::IsDown(VK_LBUTTON))
	{
		ChangeState(PlayerState::JumpingAttack);
	}
	else if (GameEngineInput::IsDown(VK_LBUTTON) and AerialComboCount < 3)
	{
		ChangeState(PlayerState::ComboAerial);
	}
	else if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(PlayerState::Jump_Falling);
	}

	InputDashUpdate(_Delta);
}

void Player::JumpingAttackUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ForceGrivityOff = false;
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

	// 대쉬처리
	if (CurDash == CurAnimationData->DashDistance)
	{
		return;
	}

	float NextPos = JumpingAttackSpeed * _Delta;

	CurDash += NextPos;

	if (CurDash >= CurAnimationData->DashDistance)
	{
		NextPos -= CurDash - CurAnimationData->DashDistance;
		CurDash = CurAnimationData->DashDistance;
	}

	Transform.AddLocalPosition(float4::UP * NextPos);
}




void Player::AerialDownAttackUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd() and AerialCheck == false)
	{
 		ChangeState(PlayerState::Idle);
	}
}


void Player::InputAttackUpdate(float _Delta)
{
	if (GameEngineInput::IsDown(VK_LBUTTON))
	{
		ComboCount = 0;
		FlipCheck();
		if (GameEngineInput::IsPress('W'))
		{
			ChangeState(PlayerState::JumpingAttack);
		}
		else if (AerialCheck == true and GameEngineInput::IsPress('S'))
		{
			ChangeState(PlayerState::AerialDownAttack);
		}
 		else if (AerialCheck == true and AerialComboCount < 3)
		{
			ChangeState(PlayerState::ComboAerial);
		}
		else
		{
			ChangeState(PlayerState::ComboMove);
		}
		
	}

	return;
}