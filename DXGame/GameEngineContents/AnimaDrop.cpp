#include "PreCompile.h"
#include "AnimaDrop.h"
#include "FX.h"
#include "FxSpriteRenderer.h"

AnimaDrop::AnimaDrop() 
{
}

AnimaDrop::~AnimaDrop()
{
}

void AnimaDrop::Spawn(float4 _Pos)
{
	Off();
	GrivityForce = { 0.0f, 700.0f, 0.0f, 1.0f }; //�߷���
	std::shared_ptr<FxSpriteRenderer> Renderer = GetContentsLevel()->GetFXActor()->FXStart(FXType::Shard, false, _Pos + float4(0.0f, 50.0f), float4(0.1f, 0.1f, 1.0f));
	Renderer->SetSpawnObject(this);
}

void AnimaDrop::Start()
{
	if (nullptr == GameEngineTexture::Find("FX_Surprised_Atlas_0.png"))
	{
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
	GameEngineSprite::CreateCut("FX_Anima_Particle_Atlas.png", 3, 3);
	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::BackGroundobject);
	MainSpriteRenderer->CreateAnimation("Anima_Particle", "FX_Anima_Particle_Atlas.png", 0.0333f, -1, -1, true);
	MainSpriteRenderer->ChangeAnimation("Anima_Particle");
	//MainSpriteRenderer-> GetColorData().MulColor = float4(1.f, 1.f, 0.33f, 1.0f);
	MainSpriteRenderer->AutoSpriteSizeOn();
	

	MainCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::StageObject);
	MainCollision->Transform.SetLocalScale({ 100.0f, 100.0f });
	MainCollision->Transform.SetLocalPosition({ 0.0f, 50.0f });
	MainCollision->SetCollisionType(ColType::AABBBOX2D);


	ForceGrivityOff = false;

}

void AnimaDrop::Update(float _Delta)
{
	StageObject::Update(_Delta);

	if (DebugValue == true)
	{
		return;
	}

	if (MainCollision->Collision<ContentsCollisionType>(ContentsCollisionType::Player))
	{

	}
}
