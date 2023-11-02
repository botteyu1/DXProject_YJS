#include "PreCompile.h"
#include "Player.h"
#include "FX.h"
#include "Level.h"






void Player::ComboMoveStart()
{
	ComboCount++;
	std::string AnimationName = "LD_ComboMove_0" + std::to_string(ComboCount);
	ChangeMainAnimation(AnimationName);

	NextCombo = false;
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

	CheckAttackCollision();
}

void Player::ComboMove_RestStart()
{
	std::string AnimationName = "LD_ComboMove_0" + std::to_string(ComboCount) + "_Rest";
	ChangeMainAnimation(AnimationName);
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


void Player::ComboAerialStart()
{
	AerialComboCount++;
	std::string AnimationName = "LD_ComboAerial_0" + std::to_string(AerialComboCount);
	ChangeMainAnimation(AnimationName);

	NextCombo = false;
	ForceGrivityOff = true;
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
		else if(AerialCheck == true)
		{
			ChangeState(PlayerState::ComboAerial_Rest);
		}
		else
		{
			ChangeState(PlayerState::Idle);
		}
	}

	

	InputDashUpdate(_Delta);

	DashProcessUpdate(_Delta, float4::RIGHT, DashSpeed);
	CheckAttackCollision();
}

void Player::ComboAerial_RestStart()
{
	ForceGrivityOff = false;

	if (AerialComboCount <= 0)
	{
		AerialComboCount = 1;
	}
	ChangeMainAnimation("LD_ComboAerial_0" + std::to_string(AerialComboCount) + "_Rest");
	
	CheckAttackCollision();
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

void Player::JumpingAttackStart()
{
	ChangeMainAnimation("LD_JumpingAttack");
	CurAnimationData = &AnimationDataMap.find("LD_JumpingAttack")->second;
	ForceGrivityOff = true;
	CurDash = 0;
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

	CheckAttackCollision();
}


void Player::AerialDownAttackStart()
{
	ChangeMainAnimation("LD_AerialDownAttack");
	GrivityForce.Y -= 3500.f;
	AerialComboCount = 0;

	DustLandingValue = false;
}

void Player::AerialDownAttackUpdate(float _Delta)
{
	CheckStartAttackFrame();

	if (AerialCheck == false and  DustLandingValue == false)
	{
		DustLandingValue = true;
		GetContentsLevel()->GetFXActor()->FXStart(FXType::GroundDust, Flip, Transform.GetLocalPosition() + float4(0.0f, 40.0f)/*, float4(0.2f, 0.2f, 1.0f)*/);
	}


	if (MainSpriteRenderer->IsCurAnimationEnd() and AerialCheck == false)
	{
 		ChangeState(PlayerState::Idle);
	}
	CheckAttackCollision();
}

bool Player::InputAttackUpdate(float _Delta)
{
	if (GameEngineInput::IsDown(VK_LBUTTON, this))
	{
		ComboCount = 0;
		FlipCheck();
		if (GameEngineInput::IsPress('W', this))
		{
			ChangeState(PlayerState::JumpingAttack);
			return true;
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
		return true;
	}

	if (GameEngineInput::IsDown(VK_RBUTTON, this) or GameEngineInput::IsDown(VK_MBUTTON, this) or GameEngineInput::IsDown('1', this) or GameEngineInput::IsDown('2', this))
	{
		FlipCheck();
		ChangeState(PlayerState::CapeAttack);
		return true;
	}
	

	return false;
}