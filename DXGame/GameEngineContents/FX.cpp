#include "PreCompile.h"
#include "FX.h"
#include "FxSpriteRenderer.h"
#include "ContentsCore.h"

FX::FX() 
{
}

FX::~FX()
{
}

std::shared_ptr<class FxSpriteRenderer> FX::FXStart(FXType _Name, bool _flip, const float4& _Pos, const float4& _Scale, const float4& _Pivot)
{

	std::shared_ptr< FxSpriteRenderer> Renderer = nullptr;
	// 돌아가고있지않은 렌더러가 있으면 사용
	for (size_t i = 0; i < MainSpriteRenderers.size(); i++)
	{
		if (MainSpriteRenderers[i]->IsUpdate() == false)
		{
			Renderer = MainSpriteRenderers[i];
			break;
		}
	}
	//모든 렌더러가 사용중이면 생성
	if (Renderer == nullptr)
	{
		Renderer = AddFXRenderer();
	}
	

	Renderer->Transform.SetLocalPosition(_Pos);
	Renderer->Transform.SetLocalRotation(float4::ZERONULL);
	
	Renderer->On();

	Renderer->Type = _Name;
	Renderer->Scale = _Scale;
	Renderer->Time = 0.0f;
	Renderer->Dir = 1.0f;

	//Renderer->SetText

	float4 Pivot = _Pivot;
	//Renderer->SetPivotValue(_Pivot);

	switch (_Name)
	{
	case FXType::Surprised:
		Renderer->ChangeAnimation("Surprised", true);
		break;
	case FXType::Shockwave:
		Renderer->ChangeAnimation("Shockwave", true);
		//MainSpriteRenderer->SetSprite("Shockwave.png");
		break;
	case FXType::DustLanding:
		Renderer->ChangeAnimation("DustLanding_atlas", true);
		break;
	case FXType::GroundDust:
		Renderer->ChangeAnimation("GroundDust", true);
		break;
	case FXType::Ghost_Attack_FX:
	{
		Renderer->ChangeAnimation("Ghost_Attack_FX", true);
		if (_flip == true)
		{
			Renderer->Transform.AddLocalPosition({ -55.0f, 50.0f });
		}
		else
		{
			Renderer->Transform.AddLocalPosition({ 55.0f, 50.0f });
		}
		break;
	}
	case FXType::SpawnEnemy:
		Renderer->ChangeAnimation("SpawnEnemy", true);
		break;
	case FXType::Flash:
	{
		Renderer->ChangeAnimation("Flash5", true);
		Renderer->GetColorData().PlusColor = float4(0.5f, 0.5f, 0.5f,0.0f);
	}
		break;

	case FXType::Circle_Gradient:
		Renderer->ChangeAnimation("Circle_Gradient", true);
		break;
		 
	case FXType::SpawnWeapon:
	{
		Renderer->ChangeAnimation("SpawnWeapon", true);
	} 
	break;
	case FXType::Splash_Water:
	{
		Renderer->ChangeAnimation("Splash_Water", true);
	}
		break;
	case FXType::Splash_Water2:
	{
		Renderer->ChangeAnimation("Splash_Water2", true);
	}
		break;
	case FXType::Slash:
	{
		Renderer->ChangeAnimation("ImpactFight_0003", true);
		Renderer->Scale = float4(0.3f, 1.3f, 1.0f);
		float Rotate = ContentsCore::MainRandom->RandomFloat(-20.0f, 20.0f);
		Renderer->Transform.AddLocalRotation(float4(0.0f, 0.0f, Rotate));
	}
		break;
	case FXType::SlashHit:
	{
		Renderer->ChangeAnimation("ImpactFight_0003", true);
		Renderer->Scale = float4(0.5f, 5.0f, 1.0f);
		float Rotate = ContentsCore::MainRandom->RandomFloat(-15.0f, 15.0f);
		Renderer->Transform.AddLocalRotation(float4(0.0f, 0.0f, Rotate));
		break;
	}
	case FXType::Hit:
	{
		Renderer->ChangeAnimation("Hit", true);
	}
		break;

	default:
		break;
	}
	

	if (_flip == false)
	{
		Renderer->RightFlip();
	}
	else
	{
		Renderer->LeftFlip();
		Pivot.X = 1.0f - Pivot.X;
	}

	Renderer->SetPivotValue(Pivot);
	Renderer->SetAutoScaleRatio(Renderer->Scale);

	Renderer->Flip = _flip;

	return Renderer;
}

void FX::FXTextStart(FXType _Name, std::string_view _Text, const float4& _Pos, const float _Scale )
{
	std::shared_ptr<class FxSpriteRenderer> Renderer = nullptr;
	// 돌아가고있지않은 렌더러가 있으면 사용
	for (size_t i = 0; i < TextSpriteRenderers.size(); i++)
	{
		if (TextSpriteRenderers[i]->IsUpdate() == false)
		{
			Renderer = TextSpriteRenderers[i];
			break;
		}
	}
	//모든 렌더러가 사용중이면 생성
	if (Renderer == nullptr)
	{
		Renderer = AddFXTextRenderer();
	}

	Renderer->SetText("메이플스토리", _Text.data(), _Scale, float4::WHITE);

	Renderer->Transform.SetLocalPosition(_Pos + float4{0.0f,0.0f, -5.0f});
	Renderer->On();

	Renderer->Type = _Name;
	Renderer->Time = 0.0f;


}




void FX::Start()
{
	if (nullptr == GameEngineTexture::Find("FX_Surprised_Atlas_0.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\Sprite\\FX");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());

		}

		GameEngineDirectory Dir2;
		Dir2.MoveParentToExistsChild("GameEngineResources");
		Dir2.MoveChild("ContentsResources\\Texture\\FX");
		std::vector<GameEngineFile> Files = Dir2.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());

			GameEnginePath Path = File;
			GameEngineSprite::CreateSingle(Path.GetFileName());
		}

		GameEngineDirectory Dir3;
		Dir3.MoveParentToExistsChild("GameEngineResources");
		Dir3.MoveChild("ContentsResources\\Sprite\\FXAtlas");
		std::vector<GameEngineFile> Atlas = Dir3.GetAllFile();

		for (size_t i = 0; i < Atlas.size(); i++)
		{
			GameEngineFile& File = Atlas[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
	}

	GameEngineSprite::CreateCut("DustLanding_atlas.png",7,2);
	GameEngineSprite::CreateCut("FX_Splash_Water_01_Atlas.png",2,4);
	GameEngineSprite::CreateCut("FX_Splash_Water_03_Atlas.png",4,4);

	
	AddFXRenderer();
	AddFXRenderer();
	AddFXTextRenderer();
	AddFXTextRenderer();
}

void FX::Update(float _Delta)
{
	
}

std::shared_ptr<FxSpriteRenderer> FX::AddFXRenderer()
{
	std::shared_ptr<FxSpriteRenderer> Renderer = CreateComponent<FxSpriteRenderer>(ContentsRenderType::FX);
	Renderer->SetMaterial("2DTextureAlwaysDepth");


	Renderer->CreateAnimation("Ghost_Attack_FX", "Ghost_Attack_FX", 0.0666f, -1, -1, false);
	Renderer->SetEndEvent("Ghost_Attack_FX", [=](GameEngineSpriteRenderer* _Renderer) { _Renderer->Off(); });


	Renderer->CreateAnimation("Shockwave", "Shockwave.png", 0.0333f, -1, -1, true);

	Renderer->CreateAnimation("Surprised", "Surprised", 0.0333f, -1, -1, true);
	Renderer->SetEndEvent("Surprised", [=](GameEngineSpriteRenderer* _Renderer) { _Renderer->Off(); });

	Renderer->CreateAnimation("DustLanding_atlas", "DustLanding_atlas.png", 0.0333f, -1, -1, true);
	Renderer->SetEndEvent("DustLanding_atlas", [=](GameEngineSpriteRenderer* _Renderer) { _Renderer->Off(); });

	Renderer->CreateAnimation("GroundDust", "GroundDust", 0.0233f, -1, -1, true);
	Renderer->SetEndEvent("GroundDust", [=](GameEngineSpriteRenderer* _Renderer) { _Renderer->Off(); });

	Renderer->CreateAnimation("Splash_Water", "FX_Splash_Water_01_Atlas.png", 0.0233f, -1, -1, true);
	Renderer->SetEndEvent("Splash_Water", [=](GameEngineSpriteRenderer* _Renderer) { _Renderer->Off(); });

	Renderer->CreateAnimation("Splash_Water2", "FX_Splash_Water_03_Atlas.png", 0.0233f, -1, -1, true);
	Renderer->SetEndEvent("Splash_Water2", [=](GameEngineSpriteRenderer* _Renderer) { _Renderer->Off(); });
	



	Renderer->CreateAnimation("SpawnEnemy", "SpawnEnemy", 0.0633f, -1, -1, true);

	Renderer->CreateAnimation("Circle_Gradient", "Circle_Mask_Gradient.png", 0.0633f, -1, -1, true);

	Renderer->CreateAnimation("Flash5", "Flash23.png", 0.0633f, -1, -1, true);

	Renderer->CreateAnimation("SpawnWeapon", "SpawnWeapon", 0.0333f, -1, -1, true);
	Renderer->CreateAnimation("Hit", "SpawnWeapon", 0.0333f, -1, -1, true);

	Renderer->CreateAnimation("ImpactFight_0003", "ImpactFight_0003.png", 0.0333f, -1, -1, true);

	

	Renderer->AutoSpriteSizeOn();
	Renderer->Off();

	MainSpriteRenderers.push_back(Renderer);

	return Renderer;
}

std::shared_ptr< FxSpriteRenderer> FX::AddFXTextRenderer()
{
	std::shared_ptr<FxSpriteRenderer> Renderer = CreateComponent<FxSpriteRenderer>(ContentsRenderType::FX);
	Renderer->Off();

	return Renderer;
}

