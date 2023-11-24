#include "PreCompile.h"
#include "BossUI.h"
#include "BossGargoyle.h"
#include "Player.h"

BossUI::BossUI() 
{
}

BossUI::~BossUI()
{
}

void BossUI::Start()
{
	if (nullptr == GameEngineTexture::Find("HUD_Main_Anima_Slot_On.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\Texture\\UI\\Play");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());

			GameEnginePath Path = File;
			GameEngineSprite::CreateSingle(Path.GetFileName());
		}
	}

	HUD_Boss_Icon = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_Boss_Icon->SetCameraOrder(ECAMERAORDER::UI);
	HUD_Boss_Icon->SetMaterial("2DTextureAlwaysDepth");
	HUD_Boss_Icon->SetSprite("HUD_Boss.png");
	HUD_Boss_Icon->AutoSpriteSizeOn();
	HUD_Boss_Icon->Transform.SetLocalPosition({ 0.0f,0.0f,0.0f });
	HUD_Boss_Icon->SetName("HUD_Boss_Icon");
	
	


	HUD_LifeBar_On_Left = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_LifeBar_On_Left->SetCameraOrder(ECAMERAORDER::UI);
	HUD_LifeBar_On_Left->SetMaterial("2DTextureAlwaysDepth");
	HUD_LifeBar_On_Left->SetSprite("HUD_Main_LifeBar_On_Glow_Left.png");
	HUD_LifeBar_On_Left->SetImageScale({ 26.f,55.f,1.0f });
	HUD_LifeBar_On_Left->Transform.SetLocalPosition({ -655.0f,-480.0f,0.0f });
	HUD_LifeBar_On_Left->SetName("HUD_LifeBar_On_Left");
	HUD_LifeBar_On_Left->SetPivotType(PivotType::Left);

	HUD_LifeBar_On_Right = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_LifeBar_On_Right->SetCameraOrder(ECAMERAORDER::UI);
	HUD_LifeBar_On_Right->SetMaterial("2DTextureAlwaysDepth");
	HUD_LifeBar_On_Right->SetSprite("HUD_Main_LifeBar_On_Glow_Right.png");
	HUD_LifeBar_On_Right->SetImageScale({ 27.f,55.f,1.0f });
	HUD_LifeBar_On_Right->Transform.SetLocalPosition({ 638.0f,-480.0f,0.0f });
	HUD_LifeBar_On_Right->SetName("HUD_LifeBar_On_Right");


	HUD_LifeBar_On = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_LifeBar_On->SetCameraOrder(ECAMERAORDER::UI);
	HUD_LifeBar_On->SetMaterial("2DTextureAlwaysDepth");
	HUD_LifeBar_On->SetSprite("HUD_Main_LifeBar_On_Glow.png");
	HUD_LifeBar_On->SetImageScale({ 1253.f,55.f,1.0f });
	HUD_LifeBar_On->Transform.SetLocalPosition({ -629.0f,-480.0f,0.0f });
	HUD_LifeBar_On->SetName("HUD_LifeBar_On");
	HUD_LifeBar_On->SetPivotType(PivotType::Left);


	
}

void BossUI::Update(float _Delta)
{
	int BossHP = BossPtr->GetHP();

	if (BossHP < 30)
	{
		HUD_LifeBar_On_Right->Off();
		HUD_LifeBar_On->Off();
	}
	else
	{

		float HPBar = ((static_cast<float>(BossHP) / 1000.0f) * 1293.0f) - 39.5f;
		if (HPBar <= 0.0f)
		{
			HPBar = 0.0f;
		}
		HUD_LifeBar_On->SetImageScale({ HPBar,55.f,1.0f });
		HUD_LifeBar_On->On();

		HUD_LifeBar_On_Right->On();
		float HPBarRight = ((static_cast<float>(BossHP) / 1000.0f) * 1293.0f)  - 655.0f;
		HUD_LifeBar_On_Right->Transform.SetLocalPosition({ HPBarRight ,-480.0f,1.f });
	}

	if (BossHP <= 0)
	{
		HUD_LifeBar_On_Left->Off();
	}
	else
	{
		HUD_LifeBar_On_Left->On();
	}



}

void BossUI::LevelStart(GameEngineLevel* _NextLevel)
{
}
