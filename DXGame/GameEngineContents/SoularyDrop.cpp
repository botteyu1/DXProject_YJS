#include "PreCompile.h"
#include "SoularyDrop.h"
#include "Player.h"
#include "ContentsCore.h"

SoularyDrop::SoularyDrop() 
{
}

SoularyDrop::~SoularyDrop()
{
}

void SoularyDrop::Spawn(float4 _Pos)
{
	Transform.SetLocalPosition(_Pos + float4(0.0f, 50.f, -5.0f));
	float ForceX = ContentsCore::MainRandom->RandomFloat(-600.0f, 600.0f);
	float ForceY = ContentsCore::MainRandom->RandomFloat(700.0f, 1100.0f);
	GrivityForce = { ForceX, ForceY, 0.0f, 1.0f };
}

void SoularyDrop::Start()
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
	}

	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::BackGroundobject);
	MainSpriteRenderer->SetMaterial("2DTextureAlwaysDepth");
	//MainSpriteRenderer->CreateAnimation("Soulary", "Collectible_BadSoulSingle.png", 0.0333f, -1, -1, true);
	MainSpriteRenderer->SetSprite("Collectible_BadSoulSingle.png");
	MainSpriteRenderer->AutoSpriteSizeOn();
	MainSpriteRenderer->SetAutoScaleRatio({ 0.3f,0.3f,1.0f });

	MainCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::StageObject);
	MainCollision->Transform.SetLocalScale({ 100.0f, 100.0f });
	MainCollision->Transform.SetLocalPosition({ 0.0f, 20.0f });
	MainCollision->SetCollisionType(ColType::AABBBOX2D);

	ForceGrivityOff = false;
}

void SoularyDrop::Update(float _Delta)
{
	
	StageObject::Update(_Delta);

	if (DebugValue == true)
	{
		return;
	}

	if (AerialCheck == false)
	{
		GravityTimer += _Delta;
	}

	if (GravityTimer >= 0.5f)
	{
		ForceGrivityOff = true;

		float4 PlayerPos = Player::GetMainPlayer()->Transform.GetLocalPosition();


		float4 Pos = Transform.GetLocalPosition();
		//float time = 1.0f;

		//float4 Lerp = float4::LerpClamp(Pos, PlayerPos, time);
		

		float4 Move = PlayerPos - Pos;

		Transform.AddLocalPosition(Move * _Delta * 4.0f);

		if (GravityTimer >= 1.5f)
		{
			Transform.AddLocalPosition(Move * _Delta * 20.0f);

		}



		if (MainCollision->Collision<ContentsCollisionType>(ContentsCollisionType::Player))
		{
			Player::GetMainPlayer()->AddSoulary(1);
			Death();
		}
	}
}
