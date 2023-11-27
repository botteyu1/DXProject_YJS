#include "PreCompile.h"
#include "Player.h"
#include "FX.h"
#include "Level.h"
#include "PlayUI.h"
#include"MovieBar.h"





void Player::ComboMoveStart()
{
	ComboCount++;
	std::string AnimationName = "LD_ComboMove_0" + std::to_string(ComboCount);
	GameEngineSound::SoundPlay("ComboAttack" + std::to_string(ComboCount));
	ChangeMainAnimation(AnimationName);

	NextCombo = false;
}
// 프레임으로 다음콤보 시작 위치 확인
// 마지막 프레임에서 딜레이 있어야될듯?

void Player::ComboMoveUpdate(float _Delta)
{
	
	switch (ComboCount)
	{
	case 1:
	{
		CheckStartAttackFrame(1);
		CheckEndAttackFrame(9);
	}
	break;
	case 2:
	{
		CheckStartAttackFrame(1);
		CheckEndAttackFrame(5);
	}
	case 3:
	{
		CheckStartAttackFrame(0);
		CheckEndAttackFrame(7);
	}
	case 4:
	{
		CheckStartAttackFrame(9);
		CheckEndAttackFrame(13);
	}
	break;
	default:
		break;
	}

	CheckAttackCollision();


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
	GameEngineSound::SoundPlay("JumpComboAttack" + std::to_string(AerialComboCount));
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
		ForceGrivityOff = false;
		if (NextCombo == true and AerialComboCount < 3)
		{
			ChangeState(PlayerState::ComboAerial);
		}
		else if(AerialPixelCheck() == true)
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

	GameEngineSound::SoundPlay("AerialAttack");
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
		if (AerialPixelCheck())
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
	GameEngineSound::SoundPlay("DownAttack");
	GrivityForce.Y -= 3500.f;
	AerialComboCount = 0;

	DustLandingValue = false;
}

void Player::AerialDownAttackUpdate(float _Delta)
{
	CheckStartAttackFrame();

	if (AerialPixelCheck() == false and  DustLandingValue == false)
	{
		DustLandingValue = true;
		GetContentsLevel()->GetFXActor()->FXStart(FXType::GroundDust, Flip, Transform.GetLocalPosition() + float4(0.0f, 40.0f)/*, float4(0.2f, 0.2f, 1.0f)*/);
	}


	if (MainSpriteRenderer->IsCurAnimationEnd() and AerialPixelCheck() == false)
	{
 		ChangeState(PlayerState::Idle);
	}
	CheckAttackCollision();
}

void Player::UltAttackStart()
{
	Flip = false;
	GameEngineSound::SoundPlay("UltKatana"); 
	ChangeMainAnimation("LD_ComboKatanas_Ult_Init");
	GetContentsLevel()->GetMovieBarPtr()->MovieBarStart();
}

void Player::UltAttackUpdate(float _Delta)
{

	if (MainSpriteRenderer->IsCurAnimation("LD_ComboKatanas_Ult_Init") == true)
	{
		if (MainSpriteRenderer->IsCurAnimationEnd())
		{
			//MainSpriteRenderer->Off();
			ChangeMainAnimation("LD_ComboKatanas_Ult");
			MainSpriteRenderer->GetColorData().MulColor = float4::ZERONULL;

			GetContentsLevel()->GetPlayUIPtr()->GetUltmateSpriteRenderer()->On();
			GetContentsLevel()->GetPlayUIPtr()->GetUltmateSpriteRenderer()->ChangeAnimation("LD_ComboKatanas_Ult", true);

			//UltmateSpriteRenderer->On();
			//UltmateSpriteRenderer->ChangeAnimation("LD_ComboKatanas_Ult",true);
			//MainSpriteRenderer->SetAutoScaleRatio({ 3.0f,3.0f,1.0f });
			//ChangeMainAnimation("LD_ComboKatanas_Ult");
		} 
		return;
	}


	CheckStartAttackFrame(0,15);
	CheckEndAttackFrame(1);

	CheckStartAttackFrame(3, 15);
	CheckEndAttackFrame(5);

	CheckStartAttackFrame(7, 15);
	CheckEndAttackFrame(9);

	CheckStartAttackFrame(11, 15);
	CheckEndAttackFrame(13);

	CheckStartAttackFrame(15, 15);
	CheckEndAttackFrame(17);

	CheckStartAttackFrame(19, 15);
	CheckEndAttackFrame(21);

	CheckStartAttackFrame(23, 15);
	CheckEndAttackFrame(25);

	CheckStartAttackFrame(27, 15);
	CheckEndAttackFrame(28);

	

	CheckAttackCollision();

	
	
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		GetContentsLevel()->GetPlayUIPtr()->GetUltmateSpriteRenderer()->Off();
		MainSpriteRenderer->GetColorData().MulColor = float4::ONE;
		GetContentsLevel()->GetMovieBarPtr()->MovieBarEnd();
		ChangeState(PlayerState::UltAttack_Rest);
	}
}

void Player::UltAttack_RestStart()
{
	ChangeMainAnimation("LD_ComboKatanas_Ult_Rest");
}

void Player::UltAttack_RestUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
	}
}

bool Player::InputAttackUpdate(float _Delta)
{
	if(GameEngineInput::IsDown('R', this)/* and UltGauge >= MaxUltGauge*/)
	{
		ChangeState(PlayerState::UltAttack);
	}
	
	if (GameEngineInput::IsDown(VK_LBUTTON, this))
	{
		ComboCount = 0;
		FlipCheck();
		if (GameEngineInput::IsPress('W', this))
		{
			ChangeState(PlayerState::JumpingAttack);
			return true;
		}
		else if (AerialPixelCheck() == true and GameEngineInput::IsPress('S', this))
		{
			ChangeState(PlayerState::AerialDownAttack);
		}
 		else if (AerialPixelCheck() == true and AerialComboCount < 3)
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