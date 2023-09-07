#include "PreCompile.h"
#include "PlayMap.h"

PlayMap* PlayMap::MainMap;

PlayMap::PlayMap() 
{
	MainMap = this;
}

PlayMap::~PlayMap() 
{
}

void PlayMap::Start()
{
	{
		std::shared_ptr<GameEngineSpriteRenderer> Renderer = CreateComponent<GameEngineSpriteRenderer>(-100);
		Renderer->SetSprite("Office_background_Frieze.png");

		std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("Office_background_Frieze.png");

		float4 HScale = Tex->GetScale().Half();
		HScale.Y *= -1.0f;

		Renderer->Transform.SetLocalPosition(HScale);
	}
}
