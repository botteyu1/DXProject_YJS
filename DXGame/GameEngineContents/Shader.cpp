#include "PreCompile.h"
#include "Shader.h"
#include "ContentsCore.h"

Shader::Shader() 
{
}

Shader::~Shader()
{
}



void Shader::Start()
{
	if (nullptr == GameEngineTexture::Find("ShaderEmpty.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\Texture\\Global");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());

			GameEnginePath Path = File;
			GameEngineSprite::CreateSingle(Path.GetFileName());
		}

		GameEngineDirectory Dir3;
		Dir3.MoveParentToExistsChild("GameEngineResources");
		Dir3.MoveChild("ContentsResources\\Sprite\\ShaderAtlas");
		std::vector<GameEngineFile> Atlas = Dir3.GetAllFile();

		for (size_t i = 0; i < Atlas.size(); i++)
		{
			GameEngineFile& File = Atlas[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
		GameEngineSprite::CreateCut("FX_Hit_Player_Vignette_Atlas.png", 2, 2);
	}
	
	

	/*Cloud = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Shader);
	Cloud->SetSprite("snowCloudI.Png");
	Cloud->AutoSpriteSizeOn();
	Cloud->Transform.SetWorldPosition({ 1971.0f,-2966.0f,-10.0f });
	Cloud->SetName("Cloud"); */

	//Cloud->GetImageTransform().SetLocalScale(WindowScale);
	//Cloud->GetColorData().MulColor = float4{ 0.07f,0.11f,0.0f,0.2f };

	float4 WindowScale = ContentsCore::GetStartWindowSize();
	SetName("Shader");

	GlobalShader = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Shader);
	GlobalShader->SetMaterial("2DTextureAlwaysDepth");
	GlobalShader->SetCameraOrder(ECAMERAORDER::UI);
	GlobalShader->SetSprite("ShaderWhite.Png");
	GlobalShader->GetImageTransform().SetLocalScale(WindowScale + float4{0.0f,0.0f,1.0f});
	GlobalShader->GetColorData().MulColor = float4{ 0.07f,0.11f,0.0f,0.2f }; 
	GlobalShader->SetName("GlobalShader");


	UltVignetteShader = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Shader);
	UltVignetteShader->SetMaterial("2DTextureAlwaysDepth");
	UltVignetteShader->SetCameraOrder(ECAMERAORDER::UI);
	UltVignetteShader->CreateAnimation("FX_Hit_Player_Vignette_Atlas", "FX_Hit_Player_Vignette_Atlas.png", 0.05f, -1, -1, true);
	UltVignetteShader->GetImageTransform().SetLocalScale(WindowScale + float4{ 0.0f,-240.0f,1.0f });
	UltVignetteShader->GetColorData().MulColor = float4{ 0.0f,0.0f,0.0f,0.6f };
	UltVignetteShader->SetName("UltVignetteShader");
	UltVignetteShader->ChangeAnimation("FX_Hit_Player_Vignette_Atlas");
	UltVignetteShader->Off();


}
void Shader::Update(float _Delta)
{
	AnimationTime += _Delta;
	if (BossOutroStartAnimationValue == true)
	{
		float Alpha = AnimationTime * 1.0f;
		if (Alpha > 1.0f)
		{
			Alpha = 1.0f;
		}
		GlobalShader->GetColorData().MulColor = float4{ 1.0f - (  Alpha * 0.9f),1.0f - (Alpha *1.0f ),1.0f - (Alpha * 0.75f),1.0f - (Alpha * 0.3f ) };
	}

	if (CurseStartAnimationValue == true)
	{
		float Alpha = AnimationTime * 1.0f;
		if (Alpha > 1.0f)
		{
			Alpha = 1.0f;
		}
		else
		{
			CurseStartAnimationValue = false;
			GlobalShader->GetColorData().MulColor = float4{ 0.07f,0.11f,0.0f,0.2f };
			return;
		}
		GlobalShader->GetColorData().MulColor = float4{ 1.0f - (  Alpha * 0.93f),1.0f - (Alpha * 0.89f ),1.0f - (Alpha * 1.0f), 1.0f - (Alpha * 0.8f ) };
	}
	
	if (UltStartAnimationValue == true)
	{
		float Alpha = AnimationTime * 3.0f;
		if (Alpha > 1.0f)
		{
			Alpha = 1.0f;
		}
		GlobalShader->GetColorData().MulColor = float4{Alpha * 0.5f + 0.07f, 0.11f - (Alpha *0.11f ),0.0f, (Alpha * 0.3f ) + 0.2f};
	}


}

void Shader::BossOutroShaderStart()
{
	BossOutroStartAnimationValue = true;
	BossOutroEndAnimationValue = false;
	AnimationTime = 0.0f;
}

void Shader::BossOutroShaderEnd()
{
	BossOutroEndAnimationValue = true;
	BossOutroStartAnimationValue = false;
	AnimationTime = 0.0f;
	GlobalShader->GetColorData().MulColor = float4{ 0.07f,0.11f,0.0f,0.2f };
}

void Shader::UltShaderStart()
{
	UltStartAnimationValue = true;
	UltEndAnimationValue = false;
	AnimationTime = 0.0f;
	UltVignetteShader->On();
}

void Shader::UltShaderEnd()
{
	UltEndAnimationValue = true;
	UltStartAnimationValue = false;
	
	UltVignetteShader->Off();
	AnimationTime = 0.0f;
	GlobalShader->GetColorData().MulColor = float4{ 0.07f,0.11f,0.0f,0.2f };
}

void Shader::CurseShaderStart()
{
	CurseStartAnimationValue = true;
	//UltEndAnimationValue = false;
	AnimationTime = 0.0f;
	//UltVignetteShader->On();
}

void Shader::CurseShaderEnd()
{
}
