#include "PreCompile.h"
#include "BookOfTheDead.h"
#include "Player.h"

BookOfTheDead::BookOfTheDead() 
{
}

BookOfTheDead::~BookOfTheDead()
{
}

void BookOfTheDead::Start()
{
	if (nullptr == GameEngineTexture::Find("BookOfTheDead_Attack_Basic_0001.png"))
	{
		GameEngineDirectory Dir2;
		Dir2.MoveParentToExistsChild("GameEngineResources");
		Dir2.MoveChild("ContentsResources\\Sprite\\BookOfTheDead");
		std::vector<GameEngineDirectory> Directorys = Dir2.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& File = Directorys[i];

			GameEngineSprite::CreateFolder(File.GetStringPath());
		}
	}

	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Player_object);
	MainSpriteRenderer->CreateAnimation("BookOfTheDead_Attack_Basic", "BookOfTheDead_Attack_Basic", 0.0533f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("BookOfTheDead_Attack_Basic", {}));


	MainSpriteRenderer->CreateAnimation("BookOfTheDead_Attack_Down", "BookOfTheDead_Attack_Down", 0.0533f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("BookOfTheDead_Attack_Down", {}));

	MainSpriteRenderer->CreateAnimation("BookOfTheDead_Attack_Up", "BookOfTheDead_Attack_Up", 0.0533f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("BookOfTheDead_Attack_Up", {}));

	MainSpriteRenderer->CreateAnimation("BookOfTheDead_Deliverance", "BookOfTheDead_Deliverance", 0.0533f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("BookOfTheDead_Deliverance", {}));

	MainSpriteRenderer->CreateAnimation("BookOfTheDead_Idle", "BookOfTheDead_Idle", 0.0533f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("BookOfTheDead_Idle", {}));

	MainSpriteRenderer->CreateAnimation("BookOfTheDead_Open_Idle", "BookOfTheDead_Open_Idle", 0.0533f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("BookOfTheDead_Open_Idle", {}));

	MainSpriteRenderer->CreateAnimation("BookOfTheDead_Transition_To_Menu", "BookOfTheDead_Transition_To_Menu", 0.0533f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("BookOfTheDead_Transition_To_Menu", {}));

	MainSpriteRenderer->CreateAnimation("BookOfTheDead_Uturn", "BookOfTheDead_Uturn", 0.0533f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("BookOfTheDead_Uturn", {}));

	MainSpriteRenderer->AutoSpriteSizeOn();
	//MainSpriteRenderer->SetAutoScaleRatio({ 0.5f,0.5f,0.5f});
	//MainSpriteRenderer->SetPivotValue({ 0.5f, 1.0f });
	
	ChangeState(BookState::Idle);

	//float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	//Transform.SetLocalPosition({ HalfWindowScale.X - 700.0f, -HalfWindowScale.Y * 4 });


	Transform.SetLocalPosition({ 953.0f, -2534.0f, 5.0f });

	PivotPos = float4{ -120.0f, 100.0f };

	SetName("BookOfDead");

	Off();
}

void BookOfTheDead::Update(float _Delta)
{
	StateUpdate(_Delta);
	TrackingPlayerUpdate(_Delta);
}

void BookOfTheDead::TrackingPlayerUpdate(float _Delta)
{
	float4 PlayerPos = MainPlayer->Transform.GetLocalPosition() + PivotPos;
	if (Flip == true)
	{
		PlayerPos.X -= 2.0f * PivotPos.X;
	}
	
	
	float4 Pos = Transform.GetLocalPosition();
	//float time = 1.0f;

	//float4 Lerp = float4::LerpClamp(Pos, PlayerPos, time);
	
	float4 Move = PlayerPos - Pos;

	Transform.AddLocalPosition(Move * _Delta * 6.0f);
}

void BookOfTheDead::Attack_BasicStart()
{
}

void BookOfTheDead::Attack_BasicUpdate(float _Delta)
{
}

void BookOfTheDead::Attack_DownStart()
{
}

void BookOfTheDead::Attack_DownUpdate(float _Delta)
{
}

void BookOfTheDead::Attack_UpStart()
{
}

void BookOfTheDead::Attack_UpUpdate(float _Delta)
{
}

void BookOfTheDead::DeliveranceStart()
{
	ChangeMainAnimation("BookOfTheDead_Idle");
}

void BookOfTheDead::DeliveranceUpdate(float _Delta)
{
}

void BookOfTheDead::Open_IdleStart()
{
}

void BookOfTheDead::Open_IdleUpdate(float _Delta)
{
}

void BookOfTheDead::Transition_To_MenuStart()
{
}

void BookOfTheDead::Transition_To_MenuUpdate(float _Delta)
{
}

void BookOfTheDead::UturnStart()
{
	ChangeMainAnimation("BookOfTheDead_Uturn");
	MainSpriteRenderer->SetAutoScaleRatio({ 1.1f,1.1f,0.27f });
	Flip = !Flip;
}

void BookOfTheDead::UturnUpdate(float _Delta)
{
	if (MainSpriteRenderer->IsCurAnimationEnd() == true)
	{
		
		MainSpriteRenderer->SetAutoScaleRatio(float4::ONE);
		ChangeState(BookState::Idle);
		return;
	}
}

void BookOfTheDead::IdleStart()
{
	ChangeMainAnimation("BookOfTheDead_Idle");
}

void BookOfTheDead::IdleUpdate(float _Delta)
{
	if (MainPlayer->Flip != Flip)
	{
		
		ChangeState(BookState::Uturn);
		return;
	}
}

void BookOfTheDead::WaitingStart()
{
}

void BookOfTheDead::WaitingUpdate(float _Delta)
{
}

void BookOfTheDead::ChangeState(BookState _State)
{
	switch (_State)
	{
	case BookState::Attack_Basic:
		Attack_BasicStart();
		break;
	case BookState::Attack_Down:
		Attack_DownStart();
		break;
	case BookState::Attack_Up:
		Attack_UpStart();
		break;
	case BookState::Deliverance:
		DeliveranceStart();
		break;
	case BookState::Open_Idle:
		Open_IdleStart();
		break;
	case BookState::Transition_To_Menu:
		Transition_To_MenuStart();
		break;
	case BookState::Idle:
		IdleStart();
		break;
	case BookState::Uturn:
		UturnStart();
		break;
	case BookState::Waiting:
		WaitingStart();
		break;
	case BookState::Max:
		break;
	default:
		break;
	}

	State = _State;
}

void BookOfTheDead::StateUpdate(float _Delta)
{
	switch (State)
	{
	case BookState::Attack_Basic:

		Attack_BasicUpdate(_Delta);
		break;
	case BookState::Attack_Down:
		Attack_DownUpdate(_Delta);
		break;
	case BookState::Attack_Up:
		Attack_UpUpdate(_Delta);
		break;
	case BookState::Deliverance:
		DeliveranceUpdate(_Delta);
		break;
	case BookState::Open_Idle:
		Open_IdleUpdate(_Delta);
		break;
	case BookState::Transition_To_Menu:
		Transition_To_MenuUpdate(_Delta);
		break;
	case BookState::Idle:
		IdleUpdate(_Delta);
		break;
	case BookState::Uturn:
		UturnUpdate(_Delta);
		break;
	case BookState::Waiting:
		WaitingUpdate(_Delta);
		break;
	case BookState::Max:
		break;
	default:
		break;
	}
}


