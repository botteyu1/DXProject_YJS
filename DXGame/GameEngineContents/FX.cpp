#include "PreCompile.h"
#include "FX.h"

FX::FX() 
{
}

FX::~FX()
{
}

void FX::FXStart(FXType _Name, bool _flip, const float4& _Pos, const float4& _Scale)
{

	//std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
	// 돌아가고있지않은 렌더러가 있으면 사용
	//for (size_t i = 0; i < MainSpriteRenderers.size(); i++)
	//{
	//	if (MainSpriteRenderers[i]->IsUpdate() == false)
	//	{
	//		Renderer = MainSpriteRenderers[i];
	//		return;
	//	}
	//}
	////모든 렌더러가 사용중이면 생성

	//Renderer = AddFXRenderer();
	MainSpriteRenderer->Transform.SetLocalPosition(_Pos);
	MainSpriteRenderer->SetAutoScaleRatio(_Scale);
	MainSpriteRenderer->On();
	On();
	Type = _Name;
	Scale = _Scale;

	switch (_Name)
	{
	case FXType::Surprised:
		MainSpriteRenderer->ChangeAnimation("Surprised", true);
		break;
	case FXType::Shockwave:
		MainSpriteRenderer->ChangeAnimation("Shockwave", true);
		//MainSpriteRenderer->SetSprite("Shockwave.png");
		break;
	case FXType::DustLanding:
		MainSpriteRenderer->ChangeAnimation("DustLanding_atlas", true);
		break;
	case FXType::GroundDust:
		MainSpriteRenderer->ChangeAnimation("GroundDust", true);
		break;
	default:
		break;
	}
	

	if (_flip == false)
	{
		MainSpriteRenderer->RightFlip();
	}
	else
	{
		MainSpriteRenderer->LeftFlip();
	}

	Flip = _flip;

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

	std::shared_ptr< GameEngineSpriteRenderer> Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::FX);
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::FX);

	Renderer->CreateAnimation("Shockwave", "Shockwave.png", 0.0333f, -1, -1, true);

	Renderer->CreateAnimation("Surprised", "Surprised", 0.0333f, -1, -1, true);
	Renderer->SetEndEvent("Surprised", [=](GameEngineSpriteRenderer* _Renderer) { _Renderer->GetParentObject()->Off(); });

	Renderer->CreateAnimation("DustLanding_atlas", "DustLanding_atlas.png", 0.0333f, -1, -1, true);
	Renderer->SetEndEvent("DustLanding_atlas", [=](GameEngineSpriteRenderer* _Renderer) { _Renderer->GetParentObject()->Off(); });

	Renderer->CreateAnimation("GroundDust", "GroundDust", 0.0233f, -1, -1, true);
	Renderer->SetEndEvent("GroundDust", [=](GameEngineSpriteRenderer* _Renderer) { _Renderer->GetParentObject()->Off(); });

	Renderer->AutoSpriteSizeOn();
	Renderer->Off();
	Off();

	MainSpriteRenderer = Renderer;
	//AddFXRenderer();
	//AddFXRenderer();
}

void FX::Update(float _Delta)
{
	switch (Type)
	{
	case FXType::Surprised:
		break;
	case FXType::Shockwave:
		Scale.Y += _Delta * 1.5f;
		Scale.X += _Delta * 1.5f;
		MainSpriteRenderer->SetAutoScaleRatio(Scale);
		//MainSpriteRenderer->SetSprite("Shockwave.png");
		if (Flip == false)
		{
			MainSpriteRenderer->Transform.AddLocalPosition(float4(-300.0f*_Delta, 0.0f));
		}
		else
		{
			MainSpriteRenderer->Transform.AddLocalPosition(float4(300.0f*_Delta,0.0f));
		}
		
		if (Scale.X >= 0.6f)
		{
			Off();
		}
		break;
	default:
		break;
	}
}

std::shared_ptr<GameEngineSpriteRenderer> FX::AddFXRenderer()
{
	

	return nullptr;
}

