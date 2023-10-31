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
	
	SetName("Shader");
	float4 WindowScale = ContentsCore::GetStartWindowSize();

	Shader_Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Shader);
	Shader_Renderer->SetCameraOrder(ECAMERAORDER::UI);
	Shader_Renderer->SetSprite("ShaderWhite.Png");
	Shader_Renderer->GetImageTransform().SetLocalScale(WindowScale);
	Shader_Renderer->GetColorData().MulColor = float4{ 0.07f,0.11f,0.0f,0.2f };
}

void Shader::Update(float _Delta)
{
}

