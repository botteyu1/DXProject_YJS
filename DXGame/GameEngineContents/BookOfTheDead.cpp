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

	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Player);
	MainSpriteRenderer->CreateAnimation("BookOfTheDead_Attack_Basic", "BookOfTheDead_Attack_Basic", 0.0633f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("BookOfTheDead_Attack_Basic", {}));


	MainSpriteRenderer->CreateAnimation("BookOfTheDead_Attack_Down", "BookOfTheDead_Attack_Down", 0.0633f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("BookOfTheDead_Attack_Down", {}));

	MainSpriteRenderer->CreateAnimation("BookOfTheDead_Attack_Up", "BookOfTheDead_Attack_Up", 0.0633f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("BookOfTheDead_Attack_Up", {}));

	MainSpriteRenderer->CreateAnimation("BookOfTheDead_Deliverance", "BookOfTheDead_Deliverance", 0.0633f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("BookOfTheDead_Deliverance", {}));

	MainSpriteRenderer->CreateAnimation("BookOfTheDead_Open_Idle", "BookOfTheDead_Open_Idle", 0.0633f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("BookOfTheDead_Open_Idle", {}));

	MainSpriteRenderer->CreateAnimation("BookOfTheDead_Transition_To_Menu", "BookOfTheDead_Transition_To_Menu", 0.0633f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("BookOfTheDead_Transition_To_Menu", {}));

	MainSpriteRenderer->AutoSpriteSizeOn();
	MainSpriteRenderer->SetAutoScaleRatio({ 0.5f,0.5f,0.5f});
	//MainSpriteRenderer->SetPivotValue({ 0.5f, 1.0f });
	
	ChangeState(BookState::Deliverance);

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X - 700.0f, -HalfWindowScale.Y * 4 });
}

void BookOfTheDead::Update(float _Delta)
{
	StateUpdate(_Delta);
	TrackingPlayerUpdate(_Delta);
}

void BookOfTheDead::TrackingPlayerUpdate(float _Delta)
{
	float4 Pos = MainPlayer->Transform.GetLocalPosition() + float4{-300.0f, 200.0f};

	Transform.SetLocalPosition(Pos);
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
	ChangeMainAnimation("BookOfTheDead_Deliverance");
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
	case BookState::Max:
		break;
	default:
		break;
	}
}


