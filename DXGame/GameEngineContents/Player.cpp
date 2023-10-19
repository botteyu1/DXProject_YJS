#include "PreCompile.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include "PlayMap.h"
#include "Enemy.h"
#include "BookOfTheDead.h"

Player* Player::MainPlayer = nullptr;

Player::Player() 
{
	
}

Player::~Player() 
{
}

void Player::TakeDamage(class GameEngineCollision* _Attacker, float _Damage)
{
	HP -= static_cast<int>(_Damage);
	ChangeState(PlayerState::Hit);
}

void Player::Start()
{
	MainPlayer = this;
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\Sprite\\Player");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());

		}


		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Player);
		MainSpriteRenderer->CreateAnimation("LD_Idle", "LD_Idle", 0.0333f, -1, -1, true);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_Idle", {}));

		MainSpriteRenderer->CreateAnimation("LD_RunUturn", "LD_RunUturn", 0.0333f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_RunUturn", {}));
		MainSpriteRenderer->CreateAnimation("LD_Run", "LD_Run", 0.0333f, -1, -1, true);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_Run", {}));
		MainSpriteRenderer->CreateAnimation("LD_RunToIdle", "LD_RunToIdle", 0.0333f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_RunToIdle", {}));

		MainSpriteRenderer->CreateAnimation("LD_Jump_Start", "LD_Jump_Start", 0.0333f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_Jump_Start", {}));
		MainSpriteRenderer->CreateAnimation("LD_Jump_Landing", "LD_Jump_Landing", 0.0333f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_Jump_Landing", {}));
		MainSpriteRenderer->CreateAnimation("LD_Jump_Falling", "LD_Jump_Falling", 0.3333f, -1, -1, true);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_Jump_Falling", {}));

		MainSpriteRenderer->CreateAnimation("LD_ComboMove_01", "LD_ComboMove_01", 0.0233f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_ComboMove_01", { 0.8f , 30.0f, false, {350.0f, 70.0f}, {130.0f, 50.0f} }));
		MainSpriteRenderer->CreateAnimation("LD_ComboMove_02", "LD_ComboMove_02", 0.0333f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_ComboMove_02", { 0.8f, 100.0f, false, {250.0f, 200.0f}, {100.0f, 100.0f} }));
		MainSpriteRenderer->CreateAnimation("LD_ComboMove_03", "LD_ComboMove_03", 0.0333f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_ComboMove_03", { 0.8f, 200.0f, false, {300.0f, 200.0f}, {150.0f, 100.0f} }));
		MainSpriteRenderer->CreateAnimation("LD_ComboMove_04", "LD_ComboMove_04", 0.0333f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_ComboMove_04", { 0.8f ,50.0f, true ,{300.0f, 200.0f}, {150.0f, 100.0f} }));

		MainSpriteRenderer->CreateAnimation("LD_ComboAerial_01", "LD_ComboAerial_01", 0.0333f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_ComboAerial_01", { 0.8f , 00.0f, false, {250.0f, 200.0f}, {100.0f, 100.0f} }));
		MainSpriteRenderer->CreateAnimation("LD_ComboAerial_02", "LD_ComboAerial_02", 0.0233f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_ComboAerial_02", { 0.8f, 30.0f , false, {350.0f, 70.0f}, {130.0f, 50.0f} }));
		MainSpriteRenderer->CreateAnimation("LD_ComboAerial_03", "LD_ComboAerial_03", 0.0333f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_ComboAerial_03", { 0.8f, 100.0f , true , {300.0f, 200.0f}, {150.0f, 100.0f} }));

		MainSpriteRenderer->CreateAnimation("LD_JumpingAttack", "LD_JumpingAttack", 0.0333f, -1, -1, true);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_JumpingAttack", { 0.5f, 500.0f , true , {280.0f, 320.0f}, {0.0f, 170.0f} }));
		MainSpriteRenderer->CreateAnimation("LD_AerialDownAttack", "LD_AerialDownAttack", 0.0333f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_AerialDownAttack", { 0.5f, 0.0f , true , {280.0f, 280.0f}, {0.0f, 150.0f} }));

		MainSpriteRenderer->CreateAnimation("LD_ComboMove_01_Rest", "LD_ComboMove_01_Rest", 0.0333f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_ComboMove_01_Rest", {}));
		MainSpriteRenderer->CreateAnimation("LD_ComboMove_02_Rest", "LD_ComboMove_02_Rest", 0.0333f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_ComboMove_02_Rest", {}));
		MainSpriteRenderer->CreateAnimation("LD_ComboMove_03_Rest", "LD_ComboMove_03_Rest", 0.0333f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_ComboMove_03_Rest", {}));
		MainSpriteRenderer->CreateAnimation("LD_ComboMove_04_Rest", "LD_ComboMove_04_Rest", 0.0333f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_ComboMove_04_Rest", {}));

		MainSpriteRenderer->CreateAnimation("LD_ComboAerial_01_Rest", "LD_ComboAerial_01_Rest", 0.0333f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_ComboAerial_01_Rest", {}));
		MainSpriteRenderer->CreateAnimation("LD_ComboAerial_02_Rest", "LD_ComboAerial_02_Rest", 0.0333f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_ComboAerial_02_Rest", {}));
		MainSpriteRenderer->CreateAnimation("LD_ComboAerial_03_Rest", "LD_ComboAerial_03_Rest", 0.0333f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_ComboAerial_03_Rest", {}));
		MainSpriteRenderer->CreateAnimation("LD_Dash", "LD_Dash", 0.0333f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_Dash", {}));

		MainSpriteRenderer->CreateAnimation("LD_Hit", "LD_Hit", 0.0333f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_Hit", {}));
		//MainSpriteRenderer->SetEndEvent("LD_RunUturn", std::bind(&Player::EndUturnEvent, this, MainSpriteRenderer.get()));

		MainSpriteRenderer->AutoSpriteSizeOn();
		MainSpriteRenderer->SetPivotValue({ 0.5f, 1.0f });
		ChangeState(PlayerState::Idle);

		DefaultScale = MainSpriteRenderer->GetCurSprite().Texture.get()->GetScale();  
	} 
	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y});

	// 콜리전 추가

	MainCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Player);
	MainCollision->Transform.SetLocalScale({ 50.0f, 100.0f, 1.0f });
	MainCollision->Transform.SetLocalPosition({ 0.0f, 80.0f, 1.0f });

	AttackCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Player_Attack);
	AttackCollision->Off();

	// BookOfTheDead
	PlayerBook = GetLevel()->CreateActor<BookOfTheDead>(ContentsObjectType::Player_object);
	PlayerBook->MainPlayer = this;


	//카메라 포커스
	GetLevel()->GetMainCamera()->CameraTargetSetting(Transform, float4::BACKWARD *1000.0f);

	static int Num = 0;
	Num++;
	SetName("Player_" + std::to_string(Num));


	Actor::Start();
}


void Player::Update(float _Delta)
{
	
	//플레이어 카메라 포커스
	//GameEngineColor Color = PlayMap::MainMap->GetColor(Transform.GetWorldPosition(), GameEngineColor::RED);
	/*std::shared_ptr<GameEngineCamera> MainCamara = GetLevel()->GetMainCamera();
	MainCamara->Transform.SetLocalPosition(Transform.GetWorldPosition());*/
	Actor::Update(_Delta);

	//디버그 모드중 업뎃안함
	if (DebugValue == true)
	{
		return;
	}

	if (AerialCheck == false)
	{
		JumpingAttackEnd = false;
		ThroughFloorCheck = false;
		AerialComboCount = 0;
	}

	StateUpdate(_Delta);


	EventParameter Parameter;

	Parameter.Enter = ComboHit;

	AttackCollision->CollisionEvent<ContentsCollisionType>(ContentsCollisionType::Enemy,{ ComboHit,nullptr,nullptr});

	DashStartCheck = true;

}



void Player::ComboHit(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
	float Damage = _Left->GetParent<Player>()->GetDamageComobo() * _Left->GetParent<Player>()->GetDamageComoboScale();
	_Right->GetParent<Enemy>()->TakeDamage(_Left, Damage);
}




void Player::ChangeState(PlayerState _State)
{
	
	switch (_State)
	{
	case PlayerState::Idle:	
		IdleStart();
		break;
	case PlayerState::Jump_Falling:
		Jump_FallingStart();
		break;
	case PlayerState::Jump_Landing:
		Jump_LandingStart();
		break;
	case PlayerState::Jump_Start:
		Jump_StartStart();
		break;
	case PlayerState::Run:
		RunStart();
		break;
	case PlayerState::RunUturn:
		RunUturnStart();
		break;
	case PlayerState::RunToIdle:
		RunToIdleStart();
		break;
	case PlayerState::ComboMove:
		ComboMoveStart();
		break;
	case PlayerState::ComboMove_Rest:
		ComboMove_RestStart();
		break;
	case PlayerState::ComboAerial:
		ComboAerialStart();
		break;
	case PlayerState::ComboAerial_Rest:
		ComboAerial_RestStart();
		break;
	case PlayerState::JumpingAttack:
		JumpingAttackStart();
		break;
	case PlayerState::AerialDownAttack:
		AerialDownAttackStart();
		break;
	case PlayerState::Dash:
		DashStart();
		break;
	case PlayerState::Hit:
		HitStart();
		break;
	default:
		break;
	}
	
	State = _State;
}


void Player::StateUpdate(float _Delta)
{
	switch (State)
	{
	case PlayerState::Idle:
		IdleUpdate(_Delta);
		break;
	case PlayerState::Jump_Falling:
		Jump_FallingUpdate(_Delta);
		break;
	case PlayerState::Jump_Landing:
		Jump_LandingUpdate(_Delta);
		break;
	case PlayerState::Jump_Start:
		Jump_StartUpdate(_Delta);
		break;
	case PlayerState::Run:
		RunUpdate(_Delta);
		break;	
	case PlayerState::RunUturn:
		RunUturnUpdate(_Delta);
		break;
	case PlayerState::RunToIdle:
		RunToIdleUpdate(_Delta);
		break;
	case PlayerState::ComboMove:
		ComboMoveUpdate(_Delta);
		break;
	case PlayerState::ComboMove_Rest:
		ComboMove_RestUpdate(_Delta);
		break;
	case PlayerState::ComboAerial:
		ComboAerialUpdate(_Delta);
		break;
	case PlayerState::ComboAerial_Rest:
		ComboAerial_RestUpdate(_Delta);
		break;
	case PlayerState::JumpingAttack:
		JumpingAttackUpdate(_Delta);
		break;
	case PlayerState::AerialDownAttack:
		AerialDownAttackUpdate(_Delta);
		break;
	case PlayerState::Dash:
		DashUpdate(_Delta);
		break;
	case PlayerState::Hit:
		HitUpdate(_Delta);
		break;
	default:
		break;
	}
}
