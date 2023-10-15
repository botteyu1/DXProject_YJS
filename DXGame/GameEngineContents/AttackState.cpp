#include "PreCompile.h"
#include "Player.h"

void Player::ComboMoveStart()
{
	ComboCount++;
	std::string AnimationName = "LD_ComboMove_0" + std::to_string(ComboCount);
	ChangeMainAnimation(AnimationName);

	NextCombo = false;
}

void Player::ComboMove_RestStart()
{
	std::string AnimationName = "LD_ComboMove_0" + std::to_string(ComboCount) + "_Rest";
	ChangeMainAnimation(AnimationName);
}


void Player::ComboAerialStart()
{
	AerialComboCount++;
	std::string AnimationName = "LD_ComboAerial_0" + std::to_string(AerialComboCount);
	ChangeMainAnimation(AnimationName);

	NextCombo = false;
	ForceGrivityOff = true;
} 

void Player::ComboAerial_RestStart()
{
	ForceGrivityOff = false;
	ChangeMainAnimation("LD_ComboAerial_0" + std::to_string(AerialComboCount) + "_Rest");
}

void Player::JumpingAttackStart()
{
	ChangeMainAnimation("LD_JumpingAttack");
	CurAnimationData = &AnimationDataMap.find("LD_JumpingAttack")->second;
	ForceGrivityOff = true;
	CurDash = 0;
}

void Player::AerialDownAttackStart()
{
	ChangeMainAnimation("LD_AerialDownAttack");
	GrivityForce.Y -= 3500.f;
	AerialComboCount = 0;
}

// 프레임으로 다음콤보 시작 위치 확인
// 마지막 프레임에서 딜레이 있어야될듯?

void Player::ComboMoveUpdate(float _Delta)
{
	CheckStartAttackFrame();
	if (GameEngineInput::IsDown(VK_LBUTTON,this))
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
	InputDashUpdate(_Delta);
	DashProcessUpdate(_Delta, float4::RIGHT, DashSpeed);
	
}



void Player::ComboMove_RestUpdate(float _Delta)
{
	if (GameEngineInput::IsPress('W', this) and GameEngineInput::IsDown(VK_LBUTTON, this))
	{
		ChangeState(PlayerState::JumpingAttack);
	}

	else if (GameEngineInput::IsDown(VK_LBUTTON, this) and ComboCount < 4)
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

	CheckStartAttackFrame();
	if (GameEngineInput::IsDown(VK_LBUTTON, this))
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

	DashProcessUpdate(_Delta, float4::RIGHT, DashSpeed);
}

void Player::ComboAerial_RestUpdate(float _Delta)
{
	if (GameEngineInput::IsPress('W', this) and GameEngineInput::IsDown(VK_LBUTTON, this))
	{
		ChangeState(PlayerState::JumpingAttack);
		
	}
	else if (GameEngineInput::IsDown(VK_LBUTTON, this) and AerialComboCount < 3)
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
	CheckStartAttackFrame();
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

	DashProcessUpdate(_Delta, float4::UP, 2000.0f);
	
}




void Player::AerialDownAttackUpdate(float _Delta)
{
	CheckStartAttackFrame();
	if (MainSpriteRenderer->IsCurAnimationEnd() and AerialCheck == false)
	{
 		ChangeState(PlayerState::Idle);
	}
}


void Player::InputAttackUpdate(float _Delta)
{
	if (GameEngineInput::IsDown(VK_LBUTTON, this))
	{
		ComboCount = 0;
		FlipCheck();
		if (GameEngineInput::IsPress('W', this))
		{
			ChangeState(PlayerState::JumpingAttack);
		}
		else if (AerialCheck == true and GameEngineInput::IsPress('S', this))
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