#include "PreCompile.h"
#include "WeaponDrop.h"
#include "Player.h"
#include "Map.h"
#include "FxSpriteRenderer.h"

WeaponDrop::WeaponDrop() 
{
}

WeaponDrop::~WeaponDrop()
{
}

void WeaponDrop::CollisionUpdate(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
}



void WeaponDrop::Spawn()
{
	Off();
	GetContentsLevel()->StartScreenShake(0.5f, 8.0f, 10.0f);
	std::shared_ptr<FxSpriteRenderer> Renderer = GetContentsLevel()->GetFXActor()->FXStart(FXType::Flash, false, Transform.GetLocalPosition() + float4(0.0f, 20.0f), float4(0.0f,0.0f,1.0f));
	Renderer->SetSpawnObject(this);
	BouncingStart();
	GetContentsLevel()->StartScreenShake(0.5f, 12.0f, 10.0f);

	GameEngineSound::SoundPlay("WeaponDrop");
}

void WeaponDrop::Start()
{

	if (nullptr == GameEngineTexture::Find("Rune_Stroke_New.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\Texture\\StageObject");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());

			GameEnginePath Path = File;
			GameEngineSprite::CreateSingle(Path.GetFileName());
		}

		
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\Texture\\UI\\Play");
		Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());

			GameEnginePath Path = File;
			GameEngineSprite::CreateSingle(Path.GetFileName());
		}
	}

	BGSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::BackGroundobject);
	BGSpriteRenderer->SetSprite("Rune_Circle.png");
	BGSpriteRenderer->AutoSpriteSizeOn();
	//BGSpriteRenderer->SetAutoScaleRatio({ 0.5f, 0.5f });
	BGSpriteRenderer->GetColorData().MulColor = float4{ 0.7f,0.9f,0.7f,0.4f };
	BGSpriteRenderer->Transform.SetLocalPosition({ 0.0f, 150.0f, 1.5f });

	BGSpriteRenderer_Smoke = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::BackGroundobject);
	BGSpriteRenderer_Smoke->SetMaterial("2DTextureAlwaysDepth");
	BGSpriteRenderer_Smoke->SetSprite("Rune_Stroke_New_Smoke.png");
	BGSpriteRenderer_Smoke->AutoSpriteSizeOn();
	//BGSpriteRenderer_Smoke->SetAutoScaleRatio({ 0.5f, 0.5f });
	BGSpriteRenderer_Smoke->GetColorData().MulColor = float4{ 0.6f,0.8f,0.0f,1.0f };
	BGSpriteRenderer_Smoke->Transform.SetLocalPosition({ 0.0f, 150.0f, 0.5f });

	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::BackGroundobject);
	MainSpriteRenderer->SetSprite("Rune_Stroke_New.png");
	MainSpriteRenderer->GetColorData().MulColor = float4{ 0.2f,0.6f,0.05f,1.0f };
	MainSpriteRenderer->AutoSpriteSizeOn();
	MainSpriteRenderer->Transform.SetLocalPosition({ 0.0f, 150.0f, 1.0f });

	

	HUD_Cape_BG2 = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::BackGroundobject);
	HUD_Cape_BG2->SetSprite("Dust_01.png");
	HUD_Cape_BG2->AutoSpriteSizeOn();
	HUD_Cape_BG2->GetColorData().MulColor = float4{ 0.0f,0.05f,0.02f,1.0f };
	HUD_Cape_BG2->Transform.SetLocalPosition({ 0.0f, 150.0f, -1.0f });
	HUD_Cape_BG2->SetAutoScaleRatio({ 0.6f, 0.6f });
	
	HUD_Cape_BG = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::BackGroundobject);
	HUD_Cape_BG->SetSprite("Circle_Mask_Gradient.png");
	HUD_Cape_BG->AutoSpriteSizeOn();
	HUD_Cape_BG->SetAutoScaleRatio({ 0.8f, 0.8f });
	HUD_Cape_BG->GetColorData().MulColor = float4{ 0.4f,0.7f,0.4f,0.6f };
	HUD_Cape_BG->Transform.SetLocalPosition({ 0.0f, 150.0f, 0.0f });

	HUD_Cape = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::BackGroundobject);
	HUD_Cape->AutoSpriteSizeOn();
	HUD_Cape->SetSprite("PLACEHOLDER_Wind.png");
	HUD_Cape->SetAutoScaleRatio({ 0.75f,0.75f,0.75f });
	HUD_Cape->Transform.SetLocalPosition({ 0.0f, 150.0f, -2.0f });

	
	MainCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::StageObject);
	MainCollision->Transform.SetLocalScale({ 150.0f, 300.0f });
	MainCollision->Transform.SetLocalPosition({ 0.0f, 150.0f });
	MainCollision->SetCollisionType(ColType::AABBBOX2D);
	
	ForceGrivityOff = false;

	GameEngineInput::AddInputObject(this);

	static int Num = 0;
	Num++;

	SetName("WeaponDrop_" + std::to_string(Num));

}

void WeaponDrop::Update(float _Delta)
{
	StageObject::Update(_Delta);

	if (DebugValue == true)
	{
		return;
	}

	MainSpriteRenderer->Transform.AddLocalRotation(float4::FORWARD * 20.0f * _Delta);
	BGSpriteRenderer->Transform.AddLocalRotation(float4::FORWARD * -20.0f * _Delta);
	BGSpriteRenderer_Smoke->Transform.AddLocalRotation(float4::FORWARD * 20.0f * _Delta);

	
	HUD_Cape->SetSprite(Cape::CapeDataManager->GetImgName(Type));



	//등장 애니메이션
	

	// 획득 상호작용
	if (MainCollision->Collision<ContentsCollisionType>(ContentsCollisionType::Player))
	{
		if (GameEngineInput::IsDown('F', this))
		{
			Player* PlayerPtr = Player::GetMainPlayer();
			CapeType ReturnCapeType = PlayerPtr->GetCurCapeType();
			PlayerPtr->SetCurCapeType(Type);

			GetContentsLevel()->StartScreenShake(0.5f, 8.0f, 10.0f);

			if (ReturnCapeType != CapeType::None)
			{
				BouncingStart();
				Type = ReturnCapeType;
			}
			else
			{
				Death();
			}

			GameEngineSound::SoundPlay("WeaponGet");
			Player::GetMainPlayer()->ChangeState(PlayerState::Acquisition);
		}

		if (GameEngineInput::IsDown('G', this))
		{
			Player* PlayerPtr = Player::GetMainPlayer();
			CapeType ReturnCapeType = PlayerPtr->GetCurCapeType2();
			PlayerPtr->SetCurCapeType2(Type);
			GetContentsLevel()->StartScreenShake(0.5f, 8.0f, 10.0f);

			if (ReturnCapeType != CapeType::None)
			{
				BouncingStart();
				Type = ReturnCapeType;
			}
			else
			{
				Death();
			}

			GameEngineSound::SoundPlay("WeaponGet");
			Player::GetMainPlayer()->ChangeState(PlayerState::Acquisition);
		}
	}

	
	
}



void WeaponDrop::BouncingStart()
{
	Transform.AddLocalPosition({ 0.0f,4.0f });
	BouncingValue = false;
	GrivityForce.Y += 900.0f;
}
