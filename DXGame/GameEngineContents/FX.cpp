#include "PreCompile.h"
#include "FX.h"

FX::FX() 
{
}

FX::~FX()
{
}

void FX::FXStart(std::string_view _Name, bool _flip, const float4& _Pos, const float4& Scale)
{

	// ���ư����������� �������� ������ ���
	for (size_t i = 0; i < MainSpriteRenderers.size(); i++)
	{
		if (MainSpriteRenderers[i]->IsUpdate() == false)
		{
			MainSpriteRenderers[i]->ChangeAnimation(_Name, true);
			MainSpriteRenderers[i]->On();
			return;
		}
	}
	//��� �������� ������̸� ����


	std::shared_ptr< GameEngineSpriteRenderer> Renderer = AddFXRenderer();
	Renderer->ChangeAnimation(_Name, true);
	Renderer->On();

	
}

void FX::Start()
{
	if (nullptr == GameEngineTexture::Find("FX_Surprised_Atlas_0.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\Sprite\\Player");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());

		}
	}

	AddFXRenderer();
	AddFXRenderer();
}

void FX::Update(float _Delta)
{

}

std::shared_ptr<GameEngineSpriteRenderer> FX::AddFXRenderer()
{
	std::shared_ptr< GameEngineSpriteRenderer> Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::FX);
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::FX);
	Renderer->CreateAnimation("Surprised", "Surprised", 0.0333f, -1, -1, true);
	Renderer->SetEndEvent("Surprised", [=](GameEngineSpriteRenderer* _Renderer) { _Renderer->Off(); });

	MainSpriteRenderers.push_back(Renderer);

	return Renderer;
}

