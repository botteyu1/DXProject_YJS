#include "PreCompile.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include "PlayMap.h"
#include "Enemy.h"
#include "BookOfTheDead.h"
#include "FX.h"
#include "SecondaryRenderer.h"
#include "ContentsCore.h"

Player* Player::MainPlayer = nullptr;
PlayerData Player::MainPlayerData;

Player::Player() 
{
	
}

Player::~Player() 
{
}

void Player::TakeDamage(class GameEngineCollision* _Attacker, float _Damage)
{
	if (State == PlayerState::Dash or State == PlayerState::UltAttack_Rest or State == PlayerState::UltAttack)
		return;

	if (DamagedDelayTimer >= DamagedDelay)
	{
		DamagedDelayTimer = 0.0f;
		HP -= static_cast<int>(_Damage);
		ForceGrivityOff = false;
		ChangeState(PlayerState::Hit);
		ForceGrivityOff = false;

		GameEngineSound::SoundPlay("PlayerHit");

		GetContentsLevel()->StartScreenShake(0.5f, 12.0f, 10.0f);

		GetContentsLevel()->GetFXActor()->FXStart(FXType::Hit, Flip, Transform.GetLocalPosition() + float4(0.0f, 50.0f), float4(3.0f, 3.0f, 2.0f));
		GetContentsLevel()->GetFXActor()->FXStart(FXType::SlashHit, Flip, Transform.GetLocalPosition() + float4(0.0f, 50.0f));
		GetContentsLevel()->GetFXActor()->FXStart(FXType::SlashHit, Flip, Transform.GetLocalPosition() + float4(0.0f, 50.0f));
	}

	
}

void Player::ComboHit(GameEngineCollision* _Left, GameEngineCollision* _Right)
{


	float Damage;
	if (Player::GetMainPlayer()->State == PlayerState::CapeAttack)
	{
		Damage = (_Left->GetParent<Player>()->GetCurDamage() + Player::GetMainPlayerData().DamageCape) * Player::GetMainPlayerData().DamageCapeScale * Player::GetMainPlayerData().DebugScale;
		_Right->GetParent<Enemy>()->TakeDamage(_Left, Damage);
	}
	else
	{
		Damage = (_Left->GetParent<Player>()->GetCurDamage() + Player::GetMainPlayerData().DamageComobo) * Player::GetMainPlayerData().DamageComoboScale * Player::GetMainPlayerData().DebugScale;
		_Right->GetParent<Enemy>()->TakeDamage(_Left, Damage);

	}
	 
}

void Player::CheckAttackCollision()
{
	EventParameter Parameter;

	Parameter.Enter = ComboHit;

	AttackCollision->CollisionEvent<ContentsCollisionType>(ContentsCollisionType::Enemy, Parameter);
}


void Player::Start()
{
	
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

		// 이동
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Player);
		
		//MainSpriteRenderer->SetMaterial("2DTextureAlwaysDepth");
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

		// 기본 공격
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

		//망토


		MainSpriteRenderer->CreateAnimation("LD_ComboKatana", "LD_ComboKatana", 0.0433f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_ComboKatana", { 0.8f, 300.0f, false, {700.0f, 70.0f}, {300.0f, 50.0f} }));
		

		MainSpriteRenderer->CreateAnimation("LD_ComboEvilHands", "LD_ComboEvilHands", 0.0483f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_ComboEvilHands", { 0.75f, 0.0f, false, {500.0f, 150.0f}, {150.0f, 70.0f} }));
		
		
		MainSpriteRenderer->CreateAnimation("LD_ComboEvilHands_Up", "LD_ComboEvilHands_Up", 0.0433f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_ComboEvilHands_Up", { 0.5f, 0.0f, false, {250.0f, 300.0f}, {100.0f, 150.0f} }));
		
		MainSpriteRenderer->CreateAnimation("LD_EvilBirds", "LD_EvilBirds", 0.0233f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_EvilBirds", { 0.5f, 0.0f, false, {500.0f, 500.0f}, {0.0f, 250.0f}, 0 , 0.9f }));
		
		/*MainSpriteRenderer->CreateAnimation("LD_EvilBirds_Up", "LD_EvilBirds_Up", 0.0333f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_EvilBirds_Up", { 0.7f, 0.0f, false, {700.0f, 70.0f}, {300.0f, 50.0f}, 0 , 1.0f }));*/

		MainSpriteRenderer->CreateAnimation("LD_BookAttack_01", "LD_BookAttack_01", 0.0333f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_BookAttack_01", {}));
		MainSpriteRenderer->CreateAnimation("LD_BookAttack_02", "LD_BookAttack_02", 0.0333f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_BookAttack_02", {}));
		MainSpriteRenderer->CreateAnimation("LD_BookAttack_03", "LD_BookAttack_03", 0.0333f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_BookAttack_03", {}));


		MainSpriteRenderer->CreateAnimation("LD_ComboKatanas_Ult_Init", "LD_ComboKatanas_Ult_Init", 0.11923f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_ComboKatanas_Ult_Init", {}));

		MainSpriteRenderer->CreateAnimation("LD_ComboKatanas_Ult", "LD_ComboKatanas_Ult", 0.0333f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_ComboKatanas_Ult", { 0.5f, 0.0f, false, {3000.0f, 1880.0f} }));
		
		MainSpriteRenderer->CreateAnimation("LD_ComboKatanas_Ult_Rest", "LD_ComboKatanas_Ult_Rest", 0.0833f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_ComboKatanas_Ult_Rest", {}));

		/*UltSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::MovieBar);
		UltSpriteRenderer->SetCameraOrder(ECAMERAORDER::UI);
		UltSpriteRenderer->SetMaterial("2DTextureAlwaysDepth");
		UltSpriteRenderer->AutoSpriteSizeOn();
		UltSpriteRenderer->SetAutoScaleRatio({ 1.0f,1.0f,1.0f,1.0f });
		UltSpriteRenderer->SetImageScale({ 1920.0,840.0f,10.0f });
		UltSpriteRenderer->Transform.SetLocalRotation({ 0.0f, 0.0f,-500.0f });
		UltSpriteRenderer->CreateAnimation("LD_ComboKatanas_Ult", "LD_ComboKatanas_Ult", 0.0333f, -1, -1, false);
		UltSpriteRenderer->On();*/
		
		//UltmateSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::MovieBar);
		//UltmateSpriteRenderer->SetCameraOrder(ECAMERAORDER::UI);
		//UltmateSpriteRenderer->SetMaterial("2DTextureAlwaysDepth");
		//UltmateSpriteRenderer->AutoSpriteSizeOn();
		//UltmateSpriteRenderer->SetAutoScaleRatio({ 1.0f,1.0f,1.0f,1.0f });
		//UltmateSpriteRenderer->SetImageScale({ 1920.0,840.0f,10.0f });
		////UltmateSpriteRenderer->Transform.SetLocalRotation({ 0.0f, 0.0f,-500.0f });
		//UltmateSpriteRenderer->CreateAnimation("LD_ComboKatanas_Ult", "LD_ComboKatanas_Ult", 0.0333f, -1, -1, false);
		//UltmateSpriteRenderer->On();

		//AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_ComboKatanas_Ult", {}));


		//마무리 행동
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

		//상호작용
		MainSpriteRenderer->CreateAnimation("LD_Elevator_Enter", "LD_Elevator_Enter", 0.0433f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_Elevator_Enter", {}));
		MainSpriteRenderer->CreateAnimation("LD_Elevator_Out", "LD_Elevator_Out", 0.0633f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_Elevator_Out", {}));
		MainSpriteRenderer->CreateAnimation("LD_Elevator_End", "LD_Elevator_End", 0.0433f, -1, -1, true);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_Elevator_End", { 0.1f }));

		MainSpriteRenderer->CreateAnimation("LD_Acquisition", "LD_Acquisition", 0.0633f, -1, -1, true);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_Acquisition", { }));

		MainSpriteRenderer->CreateAnimation("LD_Acquisition_Curse", "LD_Acquisition_Curse", 0.0733f, -1, -1, true);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_Acquisition_Curse", { }));



		// 그외 
		MainSpriteRenderer->CreateAnimation("LD_Dash", "LD_Dash", 0.0333f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_Dash", {}));

		MainSpriteRenderer->CreateAnimation("LD_Hit", "LD_Hit", 0.0483f, -1, -1, false);
		AnimationDataMap.insert(std::pair<std::string, AnimationData>("LD_Hit", {}));

	


		MainSpriteRenderer->AutoSpriteSizeOn();
		MainSpriteRenderer->SetPivotValue({ 0.5f, 1.0f });
		ChangeState(PlayerState::Idle);

		

		/*ShadowRenderer = CreateComponent<SecondaryRenderer>(ContentsRenderType::Shader);
		ShadowRenderer->Init(SecondaryRendererType::Shadow, { 0.0f,0.0f, -1.0f }, { 133.0f,63.0f,1.0f });*/


		DefaultScale = MainSpriteRenderer->GetCurSprite().Texture.get()->GetScale();  
	} 
	

	// 콜리전 추가

	MainCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Player);
	MainCollision->Transform.SetLocalScale({ 50.0f, 100.0f, 1.0f });
	MainCollision->Transform.SetLocalPosition({ 0.0f, 80.0f, 1.0f });

	AttackCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Player_Attack);
	AttackCollision->Off();

	// BookOfTheDead
	PlayerBook = GetLevel()->CreateActor<BookOfTheDead>(ContentsObjectType::Player_object);
	PlayerBook->MainPlayer = this;

	CapeStart();
	

	//이름 추가
	static int Num = 0;
	Num++;
	SetName("Player_" + std::to_string(Num));

	//카메라 포커스
	//GetLevel()->GetMainCamera()->CameraTargetSetting(Transform, float4::BACKWARD * 1000.0f);

	Actor::Start();

	
}


void Player::Update(float _Delta)
{

	//플레이어 카메라 포커스
	//GameEngineColor Color = PlayMap::MainMap->GetColor(Transform.GetWorldPosition(), GameEngineColor::RED);

	Actor::Update(_Delta);

	//디버그 모드중 업뎃안함
	if (DebugValue == true)
	{
		return;
	}

	

	if (AerialCheck == false and ForceGrivityOff == false)
	{
		JumpingAttackEnd = false;
		ThroughFloorCheck = false;
		AerialComboCount = 0;
		//JumpingAttackCount = 0;
	}

	StateUpdate(_Delta);
	CapeState.Update(_Delta);
	CapeUpdate(_Delta);
	DashStartCheck = true;
	DamagedDelayTimer += _Delta;
	DashDelayTimer += _Delta;

	if (DashDelayTimer > DashDelay)
	{
		DashCountCur = 0;
	}

	if (MP < MaxMP)
	{
		MP += _Delta * 20.0f * Player::GetMainPlayerData().MPScale;
	}
	else
	{
		MP = MaxMP;
	}
	if (GameEngineInput::IsDown('Q', this))
	{
		PlayerData& PlayerDataPtr = Player::GetMainPlayerData();
		if (PlayerDataPtr.Anima > 0 and PlayerDataPtr.HP < PlayerDataPtr.MaxHP)
		{
			PlayerDataPtr.Anima--;
			GameEngineSound::SoundPlay("AnimaConsume");

			if (HP + 35 <= MaxHP)
			{
				HP += 25;
			}
			else
			{
				HP = MaxHP;
			}
			GetContentsLevel()->GetFXActor()->FXStart(FXType::Hit, Flip, Transform.GetLocalPosition() + float4(0.0f, 50.0f), float4(3.0f, 3.0f, 2.0f));
			GetContentsLevel()->GetFXActor()->FXStart(FXType::EatAnima, Flip, Transform.GetLocalPosition() + float4(0.0f, 80.0f));
		}

	}

	if (HP < 0)
	{
		HP = 50;
	}


	DataUpdate();
	
}


void Player::DataUpdate()
{
	PlayerData& PlayerDataPtr = Player::GetMainPlayerData();
	PlayerDataPtr.HP = HP;
	PlayerDataPtr.MaxMP = MaxMP;
	PlayerDataPtr.MP = MP;
	PlayerDataPtr.MaxHP = MaxHP;
	PlayerDataPtr.Soulary = Soulary;
	PlayerDataPtr.CurCapeType = CurCapeType;
	PlayerDataPtr.CurCapeType2 = CurCapeType2;

}





void Player::ChangeState(PlayerState _State)
{

	// 스테이지 전환전 엔드 돌리기
	switch (State)
	{
	case PlayerState::Idle:
		break;
	case PlayerState::Jump_Falling:
		break;
	case PlayerState::Jump_Start:
		break;
	case PlayerState::Jump_Landing:
		break;
	case PlayerState::Run:
		break;
	case PlayerState::RunUturn:
		break;
	case PlayerState::RunToIdle:
		break;
	case PlayerState::ComboMove:
		break;
	case PlayerState::ComboMove_Rest:
		break;
	case PlayerState::ComboAerial:
		break;
	case PlayerState::ComboAerial_Rest:
		break;
	case PlayerState::JumpingAttack:
		break;
	case PlayerState::AerialDownAttack:
		break;
	case PlayerState::CapeAttack:
		CapeAttackEnd();
		break;
	case PlayerState::Dash:
		break;
	case PlayerState::Hit:
		break;
	case PlayerState::EnterElavator:
		break;
	case PlayerState::ExitElavator:
		break;
	case PlayerState::ForceWait:
		break;
	case PlayerState::Max:
		break;
	default:
		break;
	}

	State = _State;
	AttackCollisionValue = false;

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
	case PlayerState::CapeAttack:
		CapeAttackStart();
		break;
	case PlayerState::Dash:
		DashStart();
		break;
	case PlayerState::Hit:
		HitStart();
		break;
	case PlayerState::EnterElavator:
		EnterElavatorStart();
		break;
	case PlayerState::ExitElavator:
		ExitElavatorStart();
		break;
	case PlayerState::Acquisition:
		AcquisitionStart();
		break;
	case PlayerState::ForceWait:
		ForceWaitStart();
		break;
	case PlayerState::PowerUp:
		PowerUpStart();
		break;
	case PlayerState::UltAttack:
		UltAttackStart();
		break;
	case PlayerState::UltAttack_Rest:
		UltAttack_RestStart();
		break;
	default:
		break;
	}
	
	
	
}

void Player::LevelStart(GameEngineLevel* _NextLevel)
{
	MainPlayer = this;
	
	PlayerData& PlayerDataPtr = Player::GetMainPlayerData();
	HP = PlayerDataPtr.HP;
	MP = PlayerDataPtr.MP;
	MaxHP = PlayerDataPtr.MaxHP;
	MaxMP = PlayerDataPtr.MaxMP;
	Soulary = PlayerDataPtr.Soulary;
	CurCapeType2 = PlayerDataPtr.CurCapeType2;
	CurCapeType = PlayerDataPtr.CurCapeType;

	Off();
}

void Player::LevelEnd(GameEngineLevel* _NextLevel)
{
	DataUpdate();
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
	case PlayerState::CapeAttack:
		CapeAttackUpdate(_Delta);
		break;
	case PlayerState::Dash:
		DashUpdate(_Delta);
		break;
	case PlayerState::Hit:
		HitUpdate(_Delta);
		break;
	case PlayerState::EnterElavator:
		EnterElavatorUpdate(_Delta);
		break;
	case PlayerState::ExitElavator:
		ExitElavatorUpdate(_Delta);
		break;
	case PlayerState::Acquisition:
		AcquisitionUpdate(_Delta);
		break;
	case PlayerState::ForceWait:
		ForceWaitUpdate(_Delta);
		break;
	case PlayerState::PowerUp:
		PowerUpUpdate(_Delta);
		break;
	case PlayerState::UltAttack:
		UltAttackUpdate(_Delta);
		break;
	case PlayerState::UltAttack_Rest:
		UltAttack_RestUpdate(_Delta);
		break;
	default:
		break;
	}
}

