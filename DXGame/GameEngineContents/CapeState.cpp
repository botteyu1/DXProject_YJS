#include "PreCompile.h"
#include "Player.h"
#include "Bullet.h"

void Player::CapeStart()
{
	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				
			};
		

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{

			};

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				//ForceGrivityOff = true;
			};
		CapeState.CreateState(CapeType::None, NewPara);
	}

	//Ä«Å¸³ª
	{
		CreateStateParameter NewPara;


		NewPara.Start = [=](class GameEngineState* _Parent)
			{

				if (CurCapeType == CapeType::Katana)
				{
					CurCapeCoolTime = 1.5f;
				}

				if (CurCapeType2 == CapeType::Katana)
				{
					CurCapeCoolTime2 = 1.5f;
				}
				ForceGrivityOff = true;
				ChangeMainAnimation("LD_ComboKatana");

				GameEngineSound::SoundPlay("Katana");
			};
		

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				CheckStartAttackFrame(0,23.0f);
				CheckEndAttackFrame(2);
				CheckStartAttackFrame(4, 23.0f);
				CheckEndAttackFrame(8);
				DashProcessUpdate(_DeltaTime, float4::LEFT, 3000.0f);
				CheckAttackCollision();
				if (MainSpriteRenderer->GetCurIndex() > 9)
				{
					InputDashUpdate(_DeltaTime);
				}

				if (MainSpriteRenderer->IsCurAnimationEnd())
				{
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
				
			};

		NewPara.End = [=](class GameEngineState* _Parent)
			{
				ForceGrivityOff = false;
			};
		CapeState.CreateState(CapeType::Katana, NewPara);
	}

	//µ¥ºôÇÚµå
	{
		CreateStateParameter NewPara;


		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				if (CurCapeType == CapeType::EvilHands)
				{
					CurCapeCoolTime = 3.0f;
				}

				if (CurCapeType2 == CapeType::EvilHands)
				{
					CurCapeCoolTime2 = 3.0f;
				}
				ForceGrivityOff = true;

				if (GameEngineInput::IsPress('W', this) or AerialCheck == true)
				{
					ChangeMainAnimation("LD_ComboEvilHands_Up");
					GameEngineSound::SoundPlay("EvilHandsAerial");
				}
				else
				{
					ChangeMainAnimation("LD_ComboEvilHands");
					GameEngineSound::SoundPlay("EvilHandsGround");
				}
				
			};
		

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				CheckStartAttackFrame(5,70.0f);
				CheckEndAttackFrame(13);
				/*CheckStartAttackFrame(4);
				CheckEndAttackFrame(8);*/
				DashProcessUpdate(_DeltaTime, float4::LEFT, 2000.0f);
				CheckAttackCollision();

				if (MainSpriteRenderer->GetCurIndex() > 12)
				{
					InputDashUpdate(_DeltaTime);
				}

				if (MainSpriteRenderer->IsCurAnimationEnd())
				{
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
				
			};

		NewPara.End = [=](class GameEngineState* _Parent)
			{
				ForceGrivityOff = false;
			};
		CapeState.CreateState(CapeType::EvilHands, NewPara);
	}

	//±î¸¶±Í
	{
		CreateStateParameter NewPara;


		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				ForceGrivityOff = true;

				if (CurCapeType == CapeType::EvilBirds)
				{
					CurCapeCoolTime = 2.0f;
				}
				
				if (CurCapeType2 == CapeType::EvilBirds)
				{
					CurCapeCoolTime2 = 2.0f;
				}

				{
					ChangeMainAnimation("LD_EvilBirds");
					MainSpriteRenderer->SetAutoScaleRatio({ 1.5f,1.5f,1.0f });
					GameEngineSound::SoundPlay("EvilBirds");
				}
				
				
			};
		

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				CheckStartAttackFrame(3,25.0f);
				CheckEndAttackFrame(8);
				CheckStartAttackFrame(10,25.0f);
				CheckEndAttackFrame(19);
				DashProcessUpdate(_DeltaTime, float4::LEFT, 2000.0f);
				CheckAttackCollision();

				if (MainSpriteRenderer->GetCurIndex() > 18)
				{

					InputDashUpdate(_DeltaTime);

				}

				if (MainSpriteRenderer->IsCurAnimationEnd())
				{
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
				
			};

		NewPara.End = [=](class GameEngineState* _Parent)
			{
				ForceGrivityOff = false;
				MainSpriteRenderer->SetAutoScaleRatio({ 1.0f,1.0f,1.0f });
			};
		CapeState.CreateState(CapeType::EvilBirds, NewPara);
	}

	//Tornado
	{
		CreateStateParameter NewPara;


		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MP -= 40;
				ForceGrivityOff = true;
				{
					ChangeMainAnimation("LD_BookAttack_03");
				}
			};
		

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainSpriteRenderer->IsCurAnimationEnd())
				{

					std::shared_ptr <Bullet> Object = GetLevel()->CreateActor<Bullet>(ContentsObjectType::Bullet);

					float4 Dir = float4::RIGHT;
					float4 Pos;
					if (Flip == true)
					{
						Pos = Transform.GetLocalPosition() + float4{ -50.0f, 00.0f, -3.0f };
					}
					else
					{
						Pos = Transform.GetLocalPosition() + float4{ 50.0f, 00.0f, -3.0f };
					}


					float4 PlayerDir = Player::GetMainPlayer()->Transform.GetLocalPosition() - Transform.GetLocalPosition();

					Object->Init(BulletType::Tornado, Pos, 35.0f, Dir, 0.0f, Flip);


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
				
			};

		NewPara.End = [=](class GameEngineState* _Parent)
			{
				ForceGrivityOff = false;
			};
		CapeState.CreateState(CapeType::Tornado, NewPara);
	}
}

void Player::CapeUpdate(float _Delta)
{
	if (CurCapeCoolTime > 0.0f)
	{
		CurCapeCoolTime -= _Delta;
 
	}
	else
	{
		//CurCapeCoolTime  = 0.0f;
	}

	if (CurCapeCoolTime2 > 0.0f)
	{
		CurCapeCoolTime2 -= _Delta;
 
	}
	else
	{
		CurCapeCoolTime2  = 0.0f;
	}
}

void Player::CapeAttackStart()
{
	if (GameEngineInput::IsDown(VK_RBUTTON, this) and CurCapeCoolTime <= 0.0f and MP > 0.f)
	{
		CapeState.ChangeState(CurCapeType);
	}
	
	else if (GameEngineInput::IsDown(VK_MBUTTON, this) and CurCapeCoolTime2 <= 0.0f and MP > 0.f)
	{
		CapeState.ChangeState(CurCapeType2);
	}
	else if (GameEngineInput::IsDown('1', this))
	{
		CapeState.ChangeState(CurCapeType3);
	}
	else if (GameEngineInput::IsDown('2', this))
	{
		CapeState.ChangeState(CurCapeType4);
	}
	else
	{
		if (AerialPixelCheck() == true)
		{
			ChangeState(PlayerState::Jump_Falling);
		}
		else
		{
			ChangeState(PlayerState::Idle);

		}
	}

}

void Player::CapeAttackUpdate(float _Delta)
{
	
}

void Player::CapeAttackEnd()
{
	CapeState.ChangeState(CapeType::None);
}

