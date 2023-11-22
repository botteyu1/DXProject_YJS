#include "PreCompile.h"
#include "AnimaDrop.h"
#include "FX.h"
#include "FxSpriteRenderer.h"
#include "Player.h"


AnimaDrop::AnimaDrop() 
{
}

AnimaDrop::~AnimaDrop()
{
}

void AnimaDrop::Spawn(float4 _Pos)
{
	Off();
	GrivityForce = { 0.0f, 700.0f, 0.0f, 1.0f }; //Áß·ÂÈû
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
	MainSpriteRenderer->SetMaterial("2DTextureAlwaysDepth");
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





	ForceGrivityOff = false;

	const TransformData& CameraTransform = GetLevel()->GetMainCamera()->Transform.GetConstTransformDataRef();
	//const TransformData& CameraTransform = GetLevel()->GetCamera(10)->Transform.GetConstTransformDataRef();

	Transform.CalculationViewAndProjection(CameraTransform);

	//float4x4 ViewPort;
	//float4 Scale = GameEngineCore::MainWindow.GetScale();
	//ViewPort.ViewPort(Scale.X, Scale.Y, 0, 0);

	////Transform.SetLocalPosition(float4::RIGHT);

	//const TransformData& CameraTransform = GetLevel()->GetCamera(10)->Transform.GetConstTransformDataRef();

	//Transform.CalculationViewAndProjection(CameraTransform);

	//float4 ScreenPos = Transform.GetWorldPosition();


	//float4x4 VM = Transform.GetConstTransformDataRef().ViewMatrix;
	//float4x4 PM = Transform.GetConstTransformDataRef().ProjectionMatrix;


	//ScreenPos *= VM;
	//ScreenPos *= PM;




	//const float RHW = 1.0f / ScreenPos.W;

	//float4 PosInScreenSpace = float4(ScreenPos.X * RHW, ScreenPos.Y * RHW, ScreenPos.Z * RHW, ScreenPos.W);
	//const float NormalizedX = (PosInScreenSpace.X / 2.f) + 0.5f;
	//const float NormalizedY = 1.f - (PosInScreenSpace.Y / 2.f) - 0.5f;

	//float4 RayStartViewRectSpace;

	//RayStartViewRectSpace.X = NormalizedX * Scale.X;
	//RayStartViewRectSpace.Y = NormalizedY * Scale.Y;

	//float4 Result = RayStartViewRectSpace + float4(0, 0, 0, 0);


	if (MainCollision->Collision<ContentsCollisionType>(ContentsCollisionType::Player) and AerialCheck == false)
	{
		GetContentsLevel()->GetFXActor()->FXUIStart(FXType::TakeAnima,Flip, Transform.GetConstTransformDataRef());
		//Player::GetMainPlayer()->AddSoulary(1);
		Death();
	}
}
