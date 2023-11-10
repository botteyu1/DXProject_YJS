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
	}
	
	float4 WindowScale = ContentsCore::GetStartWindowSize();
	SetName("Shader");

	Cloud = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Shader);
	Cloud->SetSprite("snowCloudI.Png");
	Cloud->AutoSpriteSizeOn();
	Cloud->Transform.SetWorldPosition({ 1971.0f,-2966.0f,-10.0f });
	Cloud->SetName("Cloud"); 

	//Cloud->GetImageTransform().SetLocalScale(WindowScale);
	//Cloud->GetColorData().MulColor = float4{ 0.07f,0.11f,0.0f,0.2f };

	GlobalShader = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Shader);
	GlobalShader->SetMaterial("2DTextureAlwaysDepth");
	GlobalShader->SetCameraOrder(ECAMERAORDER::UI);
	GlobalShader->SetSprite("ShaderWhite.Png");
	GlobalShader->GetImageTransform().SetLocalScale(WindowScale + float4{0.0f,0.0f,1.0f});
	GlobalShader->GetColorData().MulColor = float4{ 0.07f,0.11f,0.0f,0.2f };
	GlobalShader->SetName("GlobalShader");


}

void Shader::Update(float _Delta)
{
}

