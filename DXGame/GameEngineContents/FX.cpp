#include "PreCompile.h"
#include "FX.h"
#include "FxSpriteRenderer.h"
FX::FX() 
{
}

FX::~FX()
{
}

void FX::FXStart(FXType _Name, bool _flip, const float4& _Pos, const float4& _Scale)
{

	std::shared_ptr<class FxSpriteRenderer> Renderer = nullptr;
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
	Renderer->SetAutoScaleRatio(_Scale);
	Renderer->On();

	Renderer->Type = _Name;
	Renderer->Scale = _Scale;

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
	}

	Renderer->Flip = _flip;

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

	
	AddFXRenderer();
	AddFXRenderer();
}

void FX::Update(float _Delta)
{
	
}

std::shared_ptr<FxSpriteRenderer> FX::AddFXRenderer()
{
	std::shared_ptr<FxSpriteRenderer> Renderer = CreateComponent<FxSpriteRenderer>(ContentsRenderType::FX);


	Renderer->CreateAnimation("Shockwave", "Shockwave.png", 0.0333f, -1, -1, true);

	Renderer->CreateAnimation("Surprised", "Surprised", 0.0333f, -1, -1, true);
	Renderer->SetEndEvent("Surprised", [=](GameEngineSpriteRenderer* _Renderer) { _Renderer->Off(); });

	Renderer->CreateAnimation("DustLanding_atlas", "DustLanding_atlas.png", 0.0333f, -1, -1, true);
	Renderer->SetEndEvent("DustLanding_atlas", [=](GameEngineSpriteRenderer* _Renderer) { _Renderer->Off(); });

	Renderer->CreateAnimation("GroundDust", "GroundDust", 0.0233f, -1, -1, true);
	Renderer->SetEndEvent("GroundDust", [=](GameEngineSpriteRenderer* _Renderer) { _Renderer->Off(); });

	Renderer->AutoSpriteSizeOn();
	Renderer->Off();

	MainSpriteRenderers.push_back(Renderer);

	return Renderer;
}

