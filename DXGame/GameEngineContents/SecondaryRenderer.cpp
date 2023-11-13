#include "PreCompile.h"
#include "SecondaryRenderer.h"

SecondaryRenderer::SecondaryRenderer() 
{
}

SecondaryRenderer::~SecondaryRenderer()
{
}

void SecondaryRenderer::Init(SecondaryRendererType _Type, float4 _Pos, float4 _Scale)
{
	Type = _Type;
	Transform.SetLocalPosition(_Pos);
	GetImageTransform().SetLocalScale(_Scale);

	switch (_Type)
	{
	case SecondaryRendererType::Light:

		SetSprite("Glow.png");
		GetColorData().MulColor = float4{ 0.93f,0.93f,1.0f,0.25f };
		SetName("Light");

		break;
	case SecondaryRendererType::Shadow:
		SetSprite("ProjectedShadow_Sprite.png");
		GetColorData().MulColor = float4{ 0.93f,0.93f,1.0f,0.25f };
		SetName("Shadow");
		break;
	case SecondaryRendererType::Max:
		break;
	default:
		break;
	}
}

void SecondaryRenderer::Start()
{
	if (nullptr == GameEngineTexture::Find("Glow.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\Texture\\Shader");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());

			GameEnginePath Path = File;
			GameEngineSprite::CreateSingle(Path.GetFileName());
		}
	}
	GameEngineSpriteRenderer::Start();
	SetMaterial("2DTextureAlwaysDepth");
}

void SecondaryRenderer::Update(float _Delta)
{
	switch (Type)
	{
	case SecondaryRendererType::Light:
		break;
	case SecondaryRendererType::Shadow:
	/*	GetParentObject()
		SetSprite("ProjectedShadow_Sprite.png");
		GetColorData().MulColor = float4{ 0.93f,0.93f,1.0f,0.25f };
		SetName("Shadow");*/
		break;
	case SecondaryRendererType::Max:
		break;
	default:
		break;
	}

	GameEngineSpriteRenderer::Update(_Delta);
}

