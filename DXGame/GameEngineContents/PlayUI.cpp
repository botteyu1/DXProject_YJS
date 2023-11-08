#include "PreCompile.h"
#include "PlayUI.h"
#include "Player.h"

PlayUI::PlayUI() 
{
}

PlayUI::~PlayUI()
{
}

void PlayUI::Start()
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
	
	HUD_Scythe_BG = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_Scythe_BG->SetMaterial("2DTextureAlwaysDepth");
	HUD_Scythe_BG->AutoSpriteSizeOn();
	HUD_Scythe_BG->SetCameraOrder(ECAMERAORDER::UI);
	HUD_Scythe_BG->SetAutoScaleRatio({ 0.9f,0.9f,0.9f });
	HUD_Scythe_BG->GetColorData().MulColor = float4(0.15f, 0.15f, 0.15f, 1.0f);
	HUD_Scythe_BG->SetSprite("HUD_Main_Black.png");
	HUD_Scythe_BG->Transform.SetLocalPosition({ -910.0f,430.0f,1.0f });
	HUD_Scythe_BG->SetName("HUD_Main");

	HUD_Scythe_Outline = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_Scythe_Outline->SetMaterial("2DTextureAlwaysDepth");
	HUD_Scythe_Outline->AutoSpriteSizeOn();
	HUD_Scythe_Outline->SetAutoScaleRatio({ 1.2f,1.2f,1.2f });
	HUD_Scythe_Outline->SetCameraOrder(ECAMERAORDER::UI);
	HUD_Scythe_Outline->SetSprite("HUD_Main_Jauge.png");
	HUD_Scythe_Outline->Transform.SetLocalPosition({-910.0f,430.0f,0.0f });
	HUD_Scythe_Outline->SetName("HUD_Main_BG");

	HUD_Scythe = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_Scythe->SetMaterial("2DTextureAlwaysDepth");
	HUD_Scythe->AutoSpriteSizeOn();
	HUD_Scythe->SetAutoScaleRatio({ 0.33f,0.33f,0.4f });
	HUD_Scythe->SetCameraOrder(ECAMERAORDER::UI);
	HUD_Scythe->SetSprite("PLACEHOLDER_Scythe_Basic.png");
	HUD_Scythe->Transform.SetLocalPosition({-910.0f,430.0f,0.0f });
	HUD_Scythe->SetName("HUD_Scythe");


	HUD_Cape_BG = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_Cape_BG->AutoSpriteSizeOn();
	HUD_Cape_BG->SetCameraOrder(ECAMERAORDER::UI);
	HUD_Cape_BG->SetAutoScaleRatio({ 0.9f,0.9f,0.9f });
	HUD_Cape_BG->GetColorData().MulColor = float4(0.15f, 0.15f, 0.15f, 1.0f);
	HUD_Cape_BG->SetSprite("HUD_Main_Black.png");
	HUD_Cape_BG->Transform.SetLocalPosition({-865.0f,475.0f,1.0f });
	HUD_Cape_BG->SetName("HUD_Cape_BG");

	HUD_Cape_Outline = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_Cape_Outline->AutoSpriteSizeOn();
	HUD_Cape_Outline->SetAutoScaleRatio({ 1.2f,1.2f,1.2f });
	HUD_Cape_Outline->SetCameraOrder(ECAMERAORDER::UI);
	HUD_Cape_Outline->SetSprite("HUD_Main_Jauge.png");
	HUD_Cape_Outline->Transform.SetLocalPosition({-865.0f,475.0f,0.0f });
	HUD_Cape_Outline->SetName("HUD_Cape");


	HUD_Cape = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_Cape->SetMaterial("2DTextureAlwaysDepth");
	HUD_Cape->AutoSpriteSizeOn();
	HUD_Cape->SetAutoScaleRatio({ 0.33f,0.33f,0.4f });
	HUD_Cape->SetCameraOrder(ECAMERAORDER::UI);
	HUD_Cape->SetSprite("PLACEHOLDER_Big_Hands.png");
	HUD_Cape->Transform.SetLocalPosition({ -865.0f,475.0f,0.0f });
	HUD_Cape->SetName("HUD_Cape");

	HUD_Cape2_BG = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_Cape2_BG->AutoSpriteSizeOn();
	HUD_Cape2_BG->SetAutoScaleRatio({ 0.9f,0.9f,0.9f });
	HUD_Cape2_BG->SetCameraOrder(ECAMERAORDER::UI);
	HUD_Cape2_BG->SetSprite("HUD_Main_Black.png");
	HUD_Cape2_BG->GetColorData().MulColor = float4(0.15f,0.15f,0.15f,1.0f);
	HUD_Cape2_BG->Transform.SetLocalPosition({-820.0f,430.0f,1.0f });
	HUD_Cape2_BG->SetName("HUD_Cape2_BG");

	HUD_Cape2_Outline = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_Cape2_Outline->SetAutoScaleRatio({ 1.2f,1.2f,1.2f });
	HUD_Cape2_Outline->AutoSpriteSizeOn();
	HUD_Cape2_Outline->SetCameraOrder(ECAMERAORDER::UI);
	HUD_Cape2_Outline->SetSprite("HUD_Main_Jauge.png");
	HUD_Cape2_Outline->Transform.SetLocalPosition({ -820.0f,430.0f,0.0f });
	HUD_Cape2_Outline->SetName("HUD_Cape2");

	HUD_Cape2 = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_Cape2->SetMaterial("2DTextureAlwaysDepth");
	HUD_Cape2->AutoSpriteSizeOn();
	HUD_Cape2->SetAutoScaleRatio({ 0.33f,0.33f,0.4f });
	HUD_Cape2->SetCameraOrder(ECAMERAORDER::UI);
	HUD_Cape2->SetSprite("PLACEHOLDER_Wind.png");
	HUD_Cape2->Transform.SetLocalPosition({ -820.0f,430.0f,0.0f });
	HUD_Cape2->SetName("HUD_Cape2");

	HUD_Ult_BG = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_Ult_BG->AutoSpriteSizeOn();
	HUD_Ult_BG->SetAutoScaleRatio({ 0.75f,0.75f,0.75f });
	HUD_Ult_BG->SetCameraOrder(ECAMERAORDER::UI);
	HUD_Ult_BG->SetSprite("HUD_Main_Black.png");
	HUD_Ult_BG->Transform.SetLocalPosition({-865.0f,390.0f,-1.0f });
	HUD_Ult_BG->SetName("HUD_Ult_BG");
	HUD_Ult_BG->GetColorData().MulColor = float4(0.2f,0.2f,0.2f,1.0f);

	HUD_Ult = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	//HUD_Ult->SetAutoScaleRatio({ 1.2f,1.2f,1.2f });
	HUD_Ult->SetMaterial("2DTextureAlwaysDepth");
	HUD_Ult->AutoSpriteSizeOn();
	HUD_Ult->SetCameraOrder(ECAMERAORDER::UI);
	HUD_Ult->SetSprite("HUD_Main_Jauge.png");
	HUD_Ult->Transform.SetLocalPosition({ -865.0f,390.0f,-2.0f });
	HUD_Ult->SetName("HUD_Ult");

	
	HUD_LifeBar = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_LifeBar->SetMaterial("2DTextureAlwaysDepth");
	HUD_LifeBar->SetCameraOrder(ECAMERAORDER::UI);
	HUD_LifeBar->SetSprite("HUD_Main_LifeBar.png");
	HUD_LifeBar->SetImageScale({ 446.0f,30.0f,1.0f });
	HUD_LifeBar->Transform.SetLocalPosition({ -825.f,485.0f,1.0f });
	HUD_LifeBar->SetName("HUD_LifeBar");
	HUD_LifeBar->SetPivotType(PivotType::Left);
	


	HUD_LifeBar_On = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_LifeBar_On->SetCameraOrder(ECAMERAORDER::UI);
	HUD_LifeBar_On->SetMaterial("2DTextureAlwaysDepth");
	HUD_LifeBar_On->SetSprite("HUD_Main_LifeBar_On.png");
	HUD_LifeBar_On->SetImageScale({ 420.f,18.f,1.0f });
	HUD_LifeBar_On->Transform.SetLocalPosition({ -818.0f,485.0f,0.0f });
	HUD_LifeBar_On->SetName("HUD_LifeBar_On");
	HUD_LifeBar_On->SetPivotType(PivotType::Left);

	HUD_LifeBar_Text = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_LifeBar_Text->SetCameraOrder(ECAMERAORDER::UI);
	HUD_LifeBar_Text->SetText("메이플스토리","55 / 65", 25.0f, float4::WHITE );
	HUD_LifeBar_Text->Transform.SetLocalPosition({ -375.0f,500.0f,0.0f });
	HUD_LifeBar_Text->SetName("HUD_LifeBar_Text");


	HUD_ManaBar = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_ManaBar->SetCameraOrder(ECAMERAORDER::UI);
	HUD_ManaBar->SetSprite("HUD_Main_LifeBar.png");
	HUD_ManaBar->SetImageScale({ 350.0f,15.0f,1.0f });
	HUD_ManaBar->Transform.SetLocalPosition({ -801.f,461.0f,1.0f });
	HUD_ManaBar->SetName("HUD_ManaBar");
	HUD_ManaBar->SetPivotType(PivotType::Left);


	HUD_ManaBar_On = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_ManaBar_On->SetMaterial("2DTextureAlwaysDepth");
	HUD_ManaBar_On->SetCameraOrder(ECAMERAORDER::UI);
	HUD_ManaBar_On->SetSprite("HUD_Main_LifeBar_On.png");
	HUD_ManaBar_On->SetImageScale({ 330.f,9.f,1.0f });
	HUD_ManaBar_On->Transform.SetLocalPosition({ -798.0f,461.0f,0.0f });
	HUD_ManaBar_On->SetName("HUD_ManaBar_On");
	HUD_ManaBar_On->SetPivotType(PivotType::Left);
	HUD_ManaBar_On->GetColorData().MulColor = float4(0.f, 1.f, 0.f, 1.0f);

	HUD_ManaBar_Text = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_ManaBar_Text->SetCameraOrder(ECAMERAORDER::UI);
	HUD_ManaBar_Text->SetText("메이플스토리","50 / 65", 20.0f, float4(0.f, 0.7f, 0.f, 1.0f));
	HUD_ManaBar_Text->Transform.SetLocalPosition({ -450.0f,470.0f,0.0f });
	HUD_ManaBar_Text->SetName("HUD_ManaBar_Text");

	HUD_Anima = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_Anima->AutoSpriteSizeOn();
	HUD_Anima->SetCameraOrder(ECAMERAORDER::UI);
	HUD_Anima->SetSprite("HUD_Main_Anima_Slot_On.png");
	HUD_Anima->Transform.SetLocalPosition({ -833.0f,515.0f,0.0f });
	HUD_Anima->SetName("HUD_Anima");

	HUD_Anima2 = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_Anima2->AutoSpriteSizeOn();
	HUD_Anima2->SetCameraOrder(ECAMERAORDER::UI);
	HUD_Anima2->SetSprite("HUD_Main_Anima_Slot_On.png");
	HUD_Anima2->Transform.SetLocalPosition({ -807.0f,515.0f,0.0f });
	HUD_Anima2->SetName("HUD_Anima");
	HUD_Anima2->GetColorData().MulColor = float4(1.f, 1.f, 0.33f, 1.0f);

	HUD_Anima3 = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_Anima3->AutoSpriteSizeOn();
	HUD_Anima3->SetCameraOrder(ECAMERAORDER::UI);
	HUD_Anima3->SetSprite("HUD_Main_Anima_Slot_Off.png");
	HUD_Anima3->Transform.SetLocalPosition({ -782.0f,515.0f,0.0f });
	HUD_Anima3->SetName("HUD_Anima");
	HUD_Anima3->GetColorData().MulColor = float4(1.f, 1.f, 0.33f, 1.0f);

	HUD_Soulary = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_Soulary->AutoSpriteSizeOn();
	HUD_Soulary->SetAutoScaleRatio({ 0.5f,0.5f,0.5f });
	HUD_Soulary->SetCameraOrder(ECAMERAORDER::UI);
	HUD_Soulary->SetSprite("Icon_Soulary.png");
	HUD_Soulary->Transform.SetLocalPosition({ 900.0f,475.0f,0.0f });
	HUD_Soulary->SetName("HUD_Soulary");


	HUD_Soulary_Text = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_Soulary_Text->SetCameraOrder(ECAMERAORDER::UI);
	HUD_Soulary_Text->SetText("메이플스토리", "0", 45.0f, float4::WHITE,FW1_RIGHT);
	HUD_Soulary_Text->Transform.SetLocalPosition({ 853.0f,495.0f,0.0f });
	HUD_Soulary_Text->SetName("HUD_ManaBar_Text");


}

void PlayUI::Update(float _Delta)
{
	Player* PlayerPtr = Player::GetMainPlayer();
	int PlayerHP = Player::GetMainPlayer()->GetHP();

	std::string HPstr = std::to_string(PlayerHP) + " / " + std::to_string(PlayerPtr->MaxHP);
	std::string MPstr = std::to_string(PlayerPtr->MP) + " / " + std::to_string(PlayerPtr->MaxMP);
	std::string Soularystr = std::to_string(PlayerPtr->Soulary);

	HUD_LifeBar_Text->SetText("메이플스토리", HPstr, 25.0f, float4::WHITE);
	HUD_ManaBar_Text->SetText("메이플스토리", MPstr, 20.0f, float4(0.f, 0.7f, 0.f, 1.0f));
	HUD_Soulary_Text->SetText("메이플스토리", Soularystr, 45.0f, float4::WHITE, FW1_RIGHT);


	float HPBar = ( static_cast<float>(PlayerHP)/ 80.0f) * 420.f;
	HUD_LifeBar_On->SetImageScale({ HPBar,18.f,1.0f });

	float MaxHPBar = (static_cast<float>(PlayerPtr->MaxHP) / 80.0f) * 446.0f;
	HUD_LifeBar->SetImageScale({ MaxHPBar,30.0f,1.0f });


	float ManaBar = (static_cast<float>(PlayerPtr->MP) / 50.f) * 350.0f;
	HUD_ManaBar_On->SetImageScale({ ManaBar,9.f,1.0f });

	float MaxMPBar = (static_cast<float>(PlayerPtr->MaxMP) / 50.f) * 330.f;
	HUD_ManaBar->SetImageScale({ MaxMPBar,15.0f,1.0f });


	

	//HUD_Scythe->SetSprite(Cape::CapeDataManager->GetImgName());
	HUD_Cape->SetSprite(Cape::CapeDataManager->GetImgName(PlayerPtr->CurCapeType));
	HUD_Cape2->SetSprite(Cape::CapeDataManager->GetImgName(PlayerPtr->CurCapeType2));

}

