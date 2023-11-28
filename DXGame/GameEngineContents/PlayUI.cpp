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

		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("GameEngineResources");
			Dir.MoveChild("ContentsResources\\Sprite\\Boss");
			std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

			for (size_t i = 0; i < Directorys.size(); i++)
			{
				GameEngineDirectory& Dir = Directorys[i];

				GameEngineSprite::CreateFolder(Dir.GetStringPath());

			}
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
	HUD_Cape_BG->SetMaterial("2DTextureAlwaysDepth");
	HUD_Cape_BG->SetAutoScaleRatio({ 0.9f,0.9f,0.9f });
	HUD_Cape_BG->GetColorData().MulColor = float4(0.15f, 0.15f, 0.15f, 1.0f);
	HUD_Cape_BG->SetSprite("HUD_Main_Black.png");
	HUD_Cape_BG->Transform.SetLocalPosition({-865.0f,475.0f,1.0f });
	HUD_Cape_BG->SetName("HUD_Cape_BG");

	HUD_Cape_Outline = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_Cape_Outline->AutoSpriteSizeOn();
	HUD_Cape_Outline->SetMaterial("2DTextureAlwaysDepth");
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

	HUD_Cape_Text = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_Cape_Text->SetCameraOrder(ECAMERAORDER::UI);
	HUD_Cape_Text->SetText("메이플스토리", "50 / 65", 20.0f, float4(0.f, 0.7f, 0.f, 1.0f));
	HUD_Cape_Text->Transform.SetLocalPosition({ -866.0f,487.0f,0.0f });
	HUD_Cape_Text->SetName("HUD_Cape_Text");

	HUD_Cape2_BG = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_Cape2_BG->AutoSpriteSizeOn();
	HUD_Cape2_BG->SetMaterial("2DTextureAlwaysDepth");
	HUD_Cape2_BG->SetAutoScaleRatio({ 0.9f,0.9f,0.9f });
	HUD_Cape2_BG->SetCameraOrder(ECAMERAORDER::UI);
	HUD_Cape2_BG->SetSprite("HUD_Main_Black.png");
	HUD_Cape2_BG->GetColorData().MulColor = float4(0.15f,0.15f,0.15f,1.0f);
	HUD_Cape2_BG->Transform.SetLocalPosition({-820.0f,430.0f,1.0f });
	HUD_Cape2_BG->SetName("HUD_Cape2_BG");

	HUD_Cape2_Outline = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_Cape2_Outline->SetAutoScaleRatio({ 1.2f,1.2f,1.2f });
	HUD_Cape2_Outline->AutoSpriteSizeOn();
	HUD_Cape2_Outline->SetMaterial("2DTextureAlwaysDepth");
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


	HUD_Cape2_Text = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_Cape2_Text->SetCameraOrder(ECAMERAORDER::UI);
	HUD_Cape2_Text->SetText("메이플스토리", "50 / 65", 20.0f, float4(0.f, 0.7f, 0.f, 1.0f));
	HUD_Cape2_Text->Transform.SetLocalPosition({ -850.0f,440.0f,0.0f });
	HUD_Cape2_Text->SetName("HUD_Cape2_Text");

	HUD_Ult_BG = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	//HUD_Ult->SetAutoScaleRatio({ 1.2f,1.2f,1.2f });
	HUD_Ult_BG->SetMaterial("2DTextureAlwaysDepth");
	HUD_Ult_BG->AutoSpriteSizeOn();
	HUD_Ult_BG->SetCameraOrder(ECAMERAORDER::UI);
	HUD_Ult_BG->SetSprite("HUD_Main_Jauge.png");
	HUD_Ult_BG->Transform.SetLocalPosition({ -865.0f,390.0f,-2.0f });
	HUD_Ult_BG->SetName("HUD_Ult");

	HUD_Ult = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_Ult-> SetMaterial("2DTextureAlwaysDepth");
	HUD_Ult->AutoSpriteSizeOn();
	HUD_Ult->SetAutoScaleRatio({ 0.75f,0.75f,0.75f });
	HUD_Ult->SetCameraOrder(ECAMERAORDER::UI);
	HUD_Ult->SetSprite("HUD_Main_Purple.png");
	HUD_Ult->Transform.SetLocalPosition({-865.0f,390.0f,-1.0f });
	HUD_Ult->SetName("HUD_Ult_BG");
	//HUD_Ult->GetColorData().MulColor = float4(0.2f,0.2f,0.2f,1.0f);

	

	
	HUD_LifeBar = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_LifeBar->SetMaterial("2DTextureAlwaysDepth");
	HUD_LifeBar->SetCameraOrder(ECAMERAORDER::UI);
	HUD_LifeBar->SetSprite("HUD_Main_LifeBar.png");
	HUD_LifeBar->SetImageScale({ 440.0f,30.0f,1.0f });
	HUD_LifeBar->Transform.SetLocalPosition({ -825.f,485.0f,1.0f });
	HUD_LifeBar->SetName("HUD_LifeBar");
	HUD_LifeBar->SetPivotType(PivotType::Left);

	
	HUD_LifeBar_On_Left = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_LifeBar_On_Left->SetCameraOrder(ECAMERAORDER::UI);
	HUD_LifeBar_On_Left->SetMaterial("2DTextureAlwaysDepth");
	HUD_LifeBar_On_Left->SetSprite("HUD_Main_LifeBar_On_Glow_Left.png");
	HUD_LifeBar_On_Left->SetImageScale({ 26.f,55.f,1.0f });
	HUD_LifeBar_On_Left->Transform.SetLocalPosition({ -832.0f,485.0f,0.0f });
	HUD_LifeBar_On_Left->SetName("HUD_LifeBar_On_Left");
	HUD_LifeBar_On_Left->SetPivotType(PivotType::Left);
	//HUD_LifeBar_On_Left->Off();

	HUD_LifeBar_On_Right = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_LifeBar_On_Right->SetCameraOrder(ECAMERAORDER::UI);
	HUD_LifeBar_On_Right->SetMaterial("2DTextureAlwaysDepth");
	HUD_LifeBar_On_Right->SetSprite("HUD_Main_LifeBar_On_Glow_Right.png");
	HUD_LifeBar_On_Right->SetImageScale({ 27.f,55.f,1.0f });
	HUD_LifeBar_On_Right->Transform.SetLocalPosition({ -405.0f,485.0f,0.0f });
	HUD_LifeBar_On_Right->SetName("HUD_LifeBar_On_Right");
	//HUD_LifeBar_On_Right->Off();
	//HUD_ManaBar_On_Right->SetPivotType(PivotType::Right);


	HUD_LifeBar_On = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_LifeBar_On->SetCameraOrder(ECAMERAORDER::UI);
	HUD_LifeBar_On->SetMaterial("2DTextureAlwaysDepth");
	HUD_LifeBar_On->SetSprite("HUD_Main_LifeBar_On_Glow.png");
	HUD_LifeBar_On->SetImageScale({ 387.f,55.f,1.0f });
	HUD_LifeBar_On->Transform.SetLocalPosition({ -806.0f,485.0f,0.0f });
	HUD_LifeBar_On->SetName("HUD_LifeBar_On");
	HUD_LifeBar_On->SetPivotType(PivotType::Left);
	//HUD_LifeBar_On->Off();

	

	HUD_LifeBar_Text = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_LifeBar_Text->SetCameraOrder(ECAMERAORDER::UI);
	HUD_LifeBar_Text->SetText("메이플스토리","55 / 65", 25.0f, float4::WHITE );
	HUD_LifeBar_Text->Transform.SetLocalPosition({ -375.0f,500.0f,0.0f });
	HUD_LifeBar_Text->SetName("HUD_LifeBar_Text");


	HUD_ManaBar = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_ManaBar->SetCameraOrder(ECAMERAORDER::UI);
	HUD_ManaBar->SetSprite("HUD_Main_LifeBar.png");
	HUD_ManaBar->SetImageScale({ 350.0f,20.0f,1.0f });
	HUD_ManaBar->Transform.SetLocalPosition({ -801.f,461.0f,1.0f });
	HUD_ManaBar->SetName("HUD_ManaBar");
	HUD_ManaBar->SetPivotType(PivotType::Left);

	HUD_ManaBar_On_Right = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_ManaBar_On_Right->SetMaterial("2DTextureAlwaysDepth");
	HUD_ManaBar_On_Right->SetCameraOrder(ECAMERAORDER::UI);
	HUD_ManaBar_On_Right->SetSprite("HUD_Main_LifeBar_On_Glow_Right.png");
	HUD_ManaBar_On_Right->SetImageScale({ 12.25f,19.f,1.0f });
	HUD_ManaBar_On_Right->Transform.SetLocalPosition({ -483.0f,461.0f,0.0f });
	HUD_ManaBar_On_Right->SetName("HUD_ManaBar_On_Right");
	HUD_ManaBar_On_Right->SetPivotType(PivotType::Left);
	HUD_ManaBar_On_Right->GetColorData().MulColor = float4(0.f, 0.7f, 0.f, 1.0f);

	HUD_ManaBar_On_Left = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_ManaBar_On_Left->SetMaterial("2DTextureAlwaysDepth");
	HUD_ManaBar_On_Left->SetCameraOrder(ECAMERAORDER::UI);
	HUD_ManaBar_On_Left->SetSprite("HUD_Main_LifeBar_On_Glow_Left.png");
	HUD_ManaBar_On_Left->SetImageScale({ 11.5f,19.f,1.0f });
	HUD_ManaBar_On_Left->Transform.SetLocalPosition({ -794.0f,461.0f,0.0f });
	HUD_ManaBar_On_Left->SetName("HUD_ManaBar_On_Left");
	HUD_ManaBar_On_Left->SetPivotType(PivotType::Left);
	HUD_ManaBar_On_Left->GetColorData().MulColor = float4(0.f, 0.7f, 0.f, 1.0f);

	HUD_ManaBar_On = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_ManaBar_On->SetMaterial("2DTextureAlwaysDepth");
	HUD_ManaBar_On->SetCameraOrder(ECAMERAORDER::UI);
	HUD_ManaBar_On->SetSprite("HUD_Main_LifeBar_On_Glow.png");
	HUD_ManaBar_On->SetImageScale({ 300.f,19.f,1.0f });
	HUD_ManaBar_On->Transform.SetLocalPosition({ -783.0f,461.0f,0.0f });
	HUD_ManaBar_On->SetName("HUD_ManaBar_On");
	HUD_ManaBar_On->SetPivotType(PivotType::Left);
	HUD_ManaBar_On->GetColorData().MulColor = float4(0.f, 0.7f, 0.f, 1.0f);

	

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
	HUD_Animavec.push_back(HUD_Anima);

	HUD_Anima = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_Anima->AutoSpriteSizeOn();
	HUD_Anima->SetCameraOrder(ECAMERAORDER::UI);
	HUD_Anima->SetSprite("HUD_Main_Anima_Slot_On.png");
	HUD_Anima->Transform.SetLocalPosition({ -807.0f,515.0f,0.0f });
	HUD_Anima->SetName("HUD_Anima");
	HUD_Anima->GetColorData().MulColor = float4(1.f, 1.f, 0.33f, 1.0f);
	HUD_Animavec.push_back(HUD_Anima);

	HUD_Anima = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_Anima->AutoSpriteSizeOn();
	HUD_Anima->SetCameraOrder(ECAMERAORDER::UI);
	HUD_Anima->SetSprite("HUD_Main_Anima_Slot_Off.png");
	HUD_Anima->Transform.SetLocalPosition({ -782.0f,515.0f,0.0f });
	HUD_Anima->SetName("HUD_Anima");
	HUD_Animavec.push_back(HUD_Anima);

	HUD_Anima = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_Anima->AutoSpriteSizeOn();
	HUD_Anima->SetCameraOrder(ECAMERAORDER::UI);
	HUD_Anima->SetSprite("HUD_Main_Anima_Slot_Off.png");
	HUD_Anima->Transform.SetLocalPosition({ -756.0f,515.0f,0.0f });
	HUD_Anima->SetName("HUD_Anima");
	HUD_Animavec.push_back(HUD_Anima);
	//HUD_Anima3->GetColorData().MulColor = float4(1.f, 1.f, 0.33f, 1.0f);


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
 //= CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	/*Renderer->CreateAnimation("Gargoyle_DarkTornado_Loop", "Gargoyle_DarkTornado_Loop", 0.0233f, -1, -1, true);
	Renderer->ChangeAnimation("Gargoyle_DarkTornado_Loop");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetName("Gargoyle_DarkTornado_Loop");
	Renderer->Transform.SetLocalPosition({ 5000.0f, -3000.0f, -2.0f });
	Renderer->SetPivotValue({ 1.0f,1.0f,1.0f });
	Renderer->LeftFlip();

	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	Renderer->CreateAnimation("Gargoyle_DarkTornado_Loop", "Gargoyle_DarkTornado_Loop", 0.0233f, -1, -1, true);
	Renderer->ChangeAnimation("Gargoyle_DarkTornado_Loop");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetName("Gargoyle_DarkTornado_Loop2");
	Renderer->Transform.SetLocalPosition({ 5000.0f, -3000.0f, -3.0f });	
	Renderer->SetAutoScaleRatio({ 2.0f,2.0f,2.0f });
	Renderer->SetPivotValue({ 1.0f,1.0f,1.0f });
	Renderer->LeftFlip();

	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	Renderer->CreateAnimation("Gargoyle_DarkTornado_Loop", "Gargoyle_DarkTornado_Loop", 0.0233f, -1, -1, true);
	Renderer->ChangeAnimation("Gargoyle_DarkTornado_Loop");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetName("Gargoyle_DarkTornado_Loop3");
	Renderer->Transform.SetLocalPosition({ 5000.0f, -3000.0f, -4.0f });
	Renderer->SetPivotValue({ 1.0f,1.0f,1.0f });
	Renderer->SetAutoScaleRatio({ 3.0f,3.0f,3.0f });
	Renderer->LeftFlip();

	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	Renderer->CreateAnimation("Gargoyle_DarkTornado_UL_Loop", "Gargoyle_DarkTornado_UL_Loop", 0.0233f, -1, -1, true);
	Renderer->ChangeAnimation("Gargoyle_DarkTornado_UL_Loop");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetName("Gargoyle_DarkTornado_UL_Loop");
	Renderer->Transform.SetLocalPosition({ 5000.0f, -3000.0f, 0.0f });
	Renderer->SetPivotValue({ 1.0f,1.0f,1.0f });
	Renderer->LeftFlip();

	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	Renderer->CreateAnimation("Gargoyle_DarkTornado_UL_Loop", "Gargoyle_DarkTornado_UL_Loop", 0.0233f, -1, -1, true);
	Renderer->ChangeAnimation("Gargoyle_DarkTornado_UL_Loop");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetName("Gargoyle_DarkTornado_UL_Loop2");
	Renderer->Transform.SetLocalPosition({ 5000.0f, -3000.0f, 0.5f });
	Renderer->SetAutoScaleRatio({ 2.0f,2.0f,2.0f });
	Renderer->SetPivotValue({ 1.0f,1.0f,1.0f });

	Renderer->LeftFlip();

	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	Renderer->CreateAnimation("Gargoyle_DarkTornado_UL_Loop", "Gargoyle_DarkTornado_UL_Loop", 0.0233f, -1, -1, true);
	Renderer->ChangeAnimation("Gargoyle_DarkTornado_UL_Loop");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetName("Gargoyle_DarkTornado_UL_Loop3");
	Renderer->Transform.SetLocalPosition({ 5000.0f, -3000.0f, 1.0f });
	Renderer->SetAutoScaleRatio({ 3.0f,3.0f,3.0f });
	Renderer->SetPivotValue({ 1.0f,1.0f,1.0f });
	Renderer->LeftFlip();


	

	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	Renderer->CreateAnimation("Gargoyle_Intro_Desk", "Gargoyle_Intro_Desk", 0.0633f, -1, -1, false);
	Renderer->CreateAnimation("Gargoyle_Intro_Desk_Lock", "Gargoyle_Intro_Desk", 0.0633f, 0, 0, false);
	Renderer->ChangeAnimation("Gargoyle_Intro_Desk_Lock");
	Renderer->AutoSpriteSizeOn();
	Renderer->LeftFlip();
	Renderer->SetPivotValue({ 0.0f,1.0f });
	Renderer->Transform.SetLocalPosition({ 5000.0f, -3000.0f , -3.0f });
	Renderer->SetName("Gargoyle_Intro_Desk_Lock");*/


	UltmateSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::MovieBar);
	UltmateSpriteRenderer->SetCameraOrder(ECAMERAORDER::UI);
	UltmateSpriteRenderer->SetMaterial("2DTextureAlwaysDepth");
	UltmateSpriteRenderer->AutoSpriteSizeOn();
	UltmateSpriteRenderer->SetAutoScaleRatio({ 1.0f,1.0f,1.0f,1.0f });
	UltmateSpriteRenderer->SetImageScale({ 1920.0,840.0f,10.0f });
	//UltmateSpriteRenderer->Transform.SetLocalRotation({ 0.0f, 0.0f,-500.0f });
	UltmateSpriteRenderer->CreateAnimation("LD_ComboKatanas_Ult", "LD_ComboKatanas_Ult", 0.0333f, -1, -1, false);
	UltmateSpriteRenderer->GetColorData().MulColor = float4{ 1.0f,0.7f,0.7f,1.0f }; ;
	UltmateSpriteRenderer->Off();

}

void PlayUI::Update(float _Delta)
{
	Player* PlayerPtr = Player::GetMainPlayer();
	int PlayerHP = Player::GetMainPlayer()->GetHP();

	int MP = static_cast<int>(PlayerPtr->MP);
	if (MP < 0)
	{
		MP = 0;
	}

	std::string HPstr = std::to_string(PlayerHP) + " / " + std::to_string(PlayerPtr->MaxHP);
	std::string MPstr = std::to_string(MP) + " / " + std::to_string(static_cast<int>(PlayerPtr->MaxMP));
	std::string Soularystr = std::to_string(PlayerPtr->Soulary);

	HUD_LifeBar_Text->SetText("메이플스토리", HPstr, 25.0f, float4::WHITE);
	HUD_ManaBar_Text->SetText("메이플스토리", MPstr, 20.0f, float4(0.f, 0.7f, 0.f, 1.0f));
	HUD_Soulary_Text->SetText("메이플스토리", Soularystr, 45.0f, float4::WHITE, FW1_RIGHT);
	HPTimer += _Delta;
	HPAnimaTimer += _Delta;

	if (PrevHP > PlayerHP)
	{
		HPTimer = 0.0f;
		HUD_LifeBar_On->GetColorData().MulColor = float4(0.4f, 0.0, 0.0, 1.0f);
		HUD_LifeBar_On_Right->GetColorData().MulColor = float4(0.8f, 0.0, 0.0, 1.0f);
		HUD_LifeBar_On_Left->GetColorData().MulColor = float4(0.8f, 0.0, 0.0, 1.0f);
	}
	if (PrevHP < PlayerHP)
	{
		HPAnimaTimer = 0.0f;
		HUD_LifeBar_On->GetColorData().MulColor = float4(0.0f, 0.3f, 0.4f, 1.0f);
		HUD_LifeBar_On_Right->GetColorData().MulColor = float4(0.0f, 0.3f, 0.4f, 1.0f);
		HUD_LifeBar_On_Left->GetColorData().MulColor = float4(0.0f, 0.3f, 0.4f, 1.0f);
	}
	PrevHP = PlayerHP;


	// 피격 색깔
	if (HPAnimaTimer < 1.0f)
	{
		HUD_LifeBar_On->GetColorData().MulColor = float4(HPAnimaTimer * 1.0f, 0.3f + HPAnimaTimer * 0.7f, 0.4f + HPAnimaTimer * 0.6f, 1.0f);
		HUD_LifeBar_On_Right->GetColorData().MulColor = float4(HPAnimaTimer * 1.0f, 0.3f + HPAnimaTimer * 0.7f, 0.4f + HPAnimaTimer * 0.6f, 1.0f);
		HUD_LifeBar_On_Left->GetColorData().MulColor = float4(HPAnimaTimer * 1.0f, 0.3f + HPAnimaTimer * 0.7f, 0.4f + HPAnimaTimer * 0.6f, 1.0f);
	}
	else if (HPTimer < 1.0f)
	{
		HUD_LifeBar_On->GetColorData().MulColor = float4(0.4f + HPTimer * 0.6f, HPTimer * 1.0f, HPTimer * 1.f, 1.0f);
		HUD_LifeBar_On_Right->GetColorData().MulColor = float4(0.4f + HPTimer * 0.6f, HPTimer * 1.0f, HPTimer * 1.0f, 1.0f);
		HUD_LifeBar_On_Left->GetColorData().MulColor = float4(0.4f + HPTimer * 0.6f, HPTimer * 1.0f, HPTimer * 1.0f, 1.0f);
	}
	// 회복 색깔
	else
	{
		HUD_LifeBar_On->GetColorData().MulColor = float4(1.f, 1.0, 1.0, 1.0f);
		HUD_LifeBar_On_Right->GetColorData().MulColor = float4(1.f, 1.0, 1.0, 1.0f);
		HUD_LifeBar_On_Left->GetColorData().MulColor = float4(1.f, 1.0, 1.0, 1.0f);
	}
	
	

	if (PlayerHP < 7)
	{
		HUD_LifeBar_On_Right->Off();
		HUD_LifeBar_On->Off();
	}
	else
	{

		float HPBar = ((static_cast<float>(PlayerHP) / 80.0f) * 427.0f) - 39.5f;
		if (HPBar <= 0.0f)
		{
			HPBar = 0.0f;
		}
		HUD_LifeBar_On->SetImageScale({ HPBar,55.f,1.0f });
		HUD_LifeBar_On->On();

		HUD_LifeBar_On_Right->On();
		float HPBarRight = ((static_cast<float>(PlayerHP) / 80.0f) * 427.0f) - 832.0f;
		HUD_LifeBar_On_Right->Transform.SetLocalPosition({ HPBarRight ,485.0f,1.f });
	}

	if (PlayerHP <= 0)
	{
		HUD_LifeBar_On_Left->Off();
	}
	else
	{
		HUD_LifeBar_On_Left->On();
	}




	float MaxHPBar = ((static_cast<float>(PlayerPtr->MaxHP) / 80.0f) * 440.0f);
	HUD_LifeBar->SetImageScale({ MaxHPBar,30.0f,1.0f });


	
	/*if (ManaBar <= 0.0f)
	{
		ManaBar = 0.0f;
	}*/
	
	//HUD_ManaBar_On->Off();




	if (MP <5)
	{
		HUD_ManaBar_On_Right->Off();
		HUD_ManaBar_On->Off();
	}
	else
	{
		HUD_ManaBar_On_Right->On();
		HUD_ManaBar_On->On();

		float ManaBar = (static_cast<float>(MP) / 50.f) * 300.0f;
		HUD_ManaBar_On->SetImageScale({ ManaBar,19.f,1.0f });

		float ManaBarRight = ((static_cast<float>(MP) / 50.f) * 350.0f) - 833.0f;
		HUD_ManaBar_On_Right->Transform.SetLocalPosition({ ManaBarRight,461.0f,1.0f });
	}
	if (MP <= 0)
	{
		HUD_ManaBar_On_Left->Off();
	}
	else {
		HUD_ManaBar_On_Left->On();
	}

	


	float MaxMPBar = (static_cast<float>(PlayerPtr->MaxMP) / 50.f) * 350.0f;
	HUD_ManaBar->SetImageScale({ MaxMPBar,20.0f,1.0f });


	

	//HUD_Scythe->SetSprite(Cape::CapeDataManager->GetImgName());
	HUD_Cape->SetSprite(Cape::CapeDataManager->GetImgName(PlayerPtr->CurCapeType));
	HUD_Cape2->SetSprite(Cape::CapeDataManager->GetImgName(PlayerPtr->CurCapeType2));

	if (PlayerPtr->CurCapeCoolTime > 0.0f)
	{
		HUD_Cape_Text->On();
		std::ostringstream stream;
		stream << std::fixed << std::setprecision(1) << PlayerPtr->CurCapeCoolTime;
		HUD_Cape_Text->SetText("메이플스토리", stream.str(), 25.0f, float4(1.f, 1.f, 1.f, 1.0f),FW1_CENTER);
		HUD_Cape->GetColorData().MulColor = float4(1.f, 1.f, 1.f, 0.5f);
	}
	else
	{
		HUD_Cape->GetColorData().MulColor = float4(1.f, 1.f, 1.f, 1.f);
		HUD_Cape_Text->Off();
	}

	if (PlayerPtr->CurCapeCoolTime2 > 0.0f)
	{
		HUD_Cape2_Text->On();
		std::ostringstream stream;
		stream << std::fixed << std::setprecision(1) << PlayerPtr->CurCapeCoolTime2;
		HUD_Cape2_Text->SetText("메이플스토리", stream.str(), 25.0f, float4(1.f, 1.f, 1.f, 1.0f),FW1_CENTER);
		HUD_Cape2->GetColorData().MulColor = float4(1.f, 1.f, 1.f, 0.5f);
	}
	else
	{
		HUD_Cape2->GetColorData().MulColor = float4(1.f, 1.f, 1.f, 1.f);
		HUD_Cape2_Text->Off();
	}

	const PlayerData& Data =  Player::GetMainPlayerData();

	//애니마 체크

	for (size_t i = 0; i < HUD_Animavec.size(); i++)
	{
		if (i < Data.Anima)
		{
			HUD_Animavec[i]->SetSprite("HUD_Main_Anima_Slot_On.png");
			HUD_Animavec[i]->GetColorData().MulColor = float4(1.f, 1.f, 0.33f, 1.0f);
		}
		else
		{
			HUD_Animavec[i]->SetSprite("HUD_Main_Anima_Slot_Off.png");
			HUD_Animavec[i]->GetColorData().MulColor = float4(1.f, 1.f, 1.0f, 1.0f);
		}
			
	}
	


}

void PlayUI::LevelStart(GameEngineLevel* _NextLevel)
{
	PrevHP = Player::GetMainPlayer()->GetHP();
}

