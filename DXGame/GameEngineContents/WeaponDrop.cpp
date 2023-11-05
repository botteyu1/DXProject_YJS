#include "PreCompile.h"
#include "WeaponDrop.h"
#include "Player.h"
#include "Map.h"

WeaponDrop::WeaponDrop() 
{
}

WeaponDrop::~WeaponDrop()
{
}

void WeaponDrop::CollisionUpdate(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
}

void WeaponDrop::NextStageAnimationStart()
{
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
	BGSpriteRenderer_Smoke->SetAutoScaleRatio({ 0.5f, 0.5f });
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
	


	GameEngineInput::AddInputObject(this);

	static int Num = 0;
	Num++;

	SetName("WeaponDrop_" + std::to_string(Num));
}

void WeaponDrop::Update(float _Delta)
{
	StageObject::Update(_Delta);

	MainSpriteRenderer->Transform.AddLocalRotation(float4::FORWARD * 20.0f * _Delta);
	BGSpriteRenderer->Transform.AddLocalRotation(float4::FORWARD * -20.0f * _Delta);
	BGSpriteRenderer_Smoke->Transform.AddLocalRotation(float4::FORWARD * 20.0f * _Delta);

	
	HUD_Cape->SetSprite(Cape::CapeDataManager->GetImgName(Type));
	

	// 획득 상호작용
	if (MainCollision->Collision<ContentsCollisionType>(ContentsCollisionType::Player))
	{
		if (GameEngineInput::IsDown('F', this))
		{
			Player* PlayerPtr = Player::GetMainPlayer();
			CapeType ReturnCapeType = PlayerPtr->GetCurCapeType();
			PlayerPtr->SetCurCapeType(Type);

			if (ReturnCapeType != CapeType::None)
			{
				BouncingStart();
				Type = ReturnCapeType;
			}
			else
			{
				Death();
			}

			Player::GetMainPlayer()->ChangeState(PlayerState::Acquisition);
		}

		if (GameEngineInput::IsDown('G', this))
		{
			Player* PlayerPtr = Player::GetMainPlayer();
			CapeType ReturnCapeType = PlayerPtr->GetCurCapeType2();
			PlayerPtr->SetCurCapeType2(Type);

			if (ReturnCapeType != CapeType::None)
			{
				BouncingStart();
				Type = ReturnCapeType;
			}
			else
			{
				Death();
			}

			Player::GetMainPlayer()->ChangeState(PlayerState::Acquisition);
		}
	}

	
	//픽셀로 밀어내기
	GameEngineColor Color = PixelCollisionCheck({ 0.0f,-1.0f });
	float MovePixel = -1.0f;

	while (GameEngineColor::WHITE != Color)
	{
		MovePixel += 1.0f;

		// 아래 픽셀
		Color = PixelCollisionCheck({ 0.0f, MovePixel });
		
		if (GameEngineColor::WHITE == Color)
		{
			Transform.AddLocalPosition({ 0.0f, MovePixel });
			break;
		}

		// 우측 픽셀
		Color = PixelCollisionCheck({ MovePixel, 0.0f });
		if (GameEngineColor::RED != Color)
		{
			Transform.AddLocalPosition({ MovePixel, 0.0f });
			break;
		}
		// 좌측 픽셀
		Color = PixelCollisionCheck({ -MovePixel, 0.0f });
		if (GameEngineColor::RED != Color)
		{

			Transform.AddLocalPosition({ -MovePixel, 0.0f });
			break;
		}

		// 위쪽 픽셀
		Color = PixelCollisionCheck({ 0.0f, -MovePixel });
		if (GameEngineColor::RED != Color)
		{

			Transform.AddLocalPosition({ 0.0f , -MovePixel });
			break;
		}

		//대각선 픽셀 확인
		Color = PixelCollisionCheck({ MovePixel, MovePixel });
		if (GameEngineColor::RED != Color)
		{
			Transform.AddLocalPosition({ MovePixel, MovePixel });
			break;
		}
		Color = PixelCollisionCheck({ -MovePixel, MovePixel });
		if (GameEngineColor::RED != Color)
		{
			Transform.AddLocalPosition({ -MovePixel, MovePixel });
			break;
		}
		Color = PixelCollisionCheck({ MovePixel, -MovePixel });
		if (GameEngineColor::RED != Color)
		{
			Transform.AddLocalPosition({ MovePixel, -MovePixel });
			break;
		}
		Color = PixelCollisionCheck({ -MovePixel, -MovePixel });
		if (GameEngineColor::RED != Color)
		{
			Transform.AddLocalPosition({ -MovePixel, -MovePixel });
			break;
		}
	}



	 Color = PixelCollisionCheck({ 0.0f,-1.0f });

	//공중
	if ((GameEngineColor::WHITE == Color))
	{
		AerialCheck = true;
		GrivityForce.Y -= _Delta * 2000.f;
		Transform.AddLocalPosition(GrivityForce * _Delta);
	}
	//중력이 꺼져도 공중인지 체크하고 중력초기화
	else if (BouncingValue == false)
	{
		BouncingValue = true;
		GrivityForce.Y = 300.0f;

		Transform.AddLocalPosition({ 0.0f,2.0f });
	}
	//지상 
	else 
	{
		AerialCheck = false;
		GrivityForce = 0.0f;
	}


	if (DebugValue == true)
	{
		return;
	}
}

GameEngineColor WeaponDrop::PixelCollisionCheck(float4 _Pixel, GameEngineColor _DefaultColor)
{
	float4 WorldPosition = Transform.GetWorldPosition();
	WorldPosition += _Pixel;
	GameEngineColor Color = static_cast<Level*>(GetLevel())->GetMap()->GetColor(WorldPosition, GameEngineColor::RED);

	return Color;
}

GameEngineColor WeaponDrop::PosCollisionCheck(float4 _Pos, GameEngineColor _DefaultColor)
{

	GameEngineColor Color = static_cast<Level*>(GetLevel())->GetMap()->GetColor(_Pos, GameEngineColor::RED);

	return Color;
}

void WeaponDrop::BouncingStart()
{
	Transform.AddLocalPosition({ 0.0f,2.0f });
	BouncingValue = false;
	GrivityForce.Y += 800.0f;
}
