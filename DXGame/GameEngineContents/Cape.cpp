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
				ForceGrivityOff = true;
				ChangeMainAnimation("LD_ComboKatana");
			};
		

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				CheckStartAttackFrame(0);
				CheckEndAttackFrame(2);
				CheckStartAttackFrame(4);
				CheckEndAttackFrame(8);
				DashProcessUpdate(_DeltaTime, float4::LEFT, 2000.0f);
				CheckAttackCollision();

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
				ForceGrivityOff = true;

				if (GameEngineInput::IsPress('W', this) or AerialCheck == true)
				{
					ChangeMainAnimation("LD_ComboEvilHands_Up");
				}
				else
				{
					ChangeMainAnimation("LD_ComboEvilHands");
				}
				
			};
		

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				CheckStartAttackFrame(0);
				CheckEndAttackFrame(2);
				/*CheckStartAttackFrame(4);
				CheckEndAttackFrame(8);*/
				DashProcessUpdate(_DeltaTime, float4::LEFT, 2000.0f);
				CheckAttackCollision();

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

				/*if (GameEngineInput::IsPress('W', this))
				{
					ChangeMainAnimation("LD_EvilBirds");
				}
				else*/
				{
					ChangeMainAnimation("LD_EvilBirds");
					MainSpriteRenderer->SetAutoScaleRatio({ 1.5f,1.5f,1.0f });
				}
				
				
			};
		

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				CheckStartAttackFrame(0);
				CheckEndAttackFrame(2);
				/*CheckStartAttackFrame(4);
				CheckEndAttackFrame(8);*/
				DashProcessUpdate(_DeltaTime, float4::LEFT, 2000.0f);
				CheckAttackCollision();

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
				ForceGrivityOff = true;

				/*if (GameEngineInput::IsPress('W', this))
				{
					ChangeMainAnimation("LD_EvilBirds");
				}
				else*/
				{
					ChangeMainAnimation("LD_EvilBirds");
					MainSpriteRenderer->SetAutoScaleRatio({ 1.5f,1.5f,1.0f });

					std::shared_ptr <Bullet> Object = GetLevel()->CreateActor<Bullet>(ContentsObjectType::Bullet);

					float4 Dir;
					float4 Pos;
					if (Flip == true)
					{
						Pos = Transform.GetLocalPosition() + float4{ 50.0f, 50.0f };
						Dir = float4::LEFT;
					}
					else
					{
						Pos = Transform.GetLocalPosition() + float4{ -50.0f, 50.0f };
						Dir = float4::RIGHT;
					}


					float4 PlayerDir = Player::GetMainPlayer()->Transform.GetLocalPosition() - Transform.GetLocalPosition();

					Object->Init(BulletType::Tornado, Pos, 100.0f, Dir, 0.0f);
				}

			};
		

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				CheckStartAttackFrame(0);
				CheckEndAttackFrame(2);
				/*CheckStartAttackFrame(4);
				CheckEndAttackFrame(8);*/
				DashProcessUpdate(_DeltaTime, float4::LEFT, 2000.0f);
				CheckAttackCollision();

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
		CapeState.CreateState(CapeType::Tornado, NewPara);
	}
}

void Player::CapeUpdate(float _Delta)
{
}

void Player::CapeAttackStart()
{
	CapeState.ChangeState(CurCapeType);
}

void Player::CapeAttackUpdate(float _Delta)
{
}

void Player::CapeAttackEnd()
{
	CapeState.ChangeState(CapeType::None);
}