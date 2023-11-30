#include "PreCompile.h"
#include "CurseUI.h"
#include "ContentsCore.h"
#include "Player.h"
#include "Shader.h"

CurseUI::CurseUI() 
{
}

CurseUI::~CurseUI()
{
}



void CurseUI::Start()
{
	if (nullptr == GameEngineTexture::Find("UI_Curse_CloseUp_Window.png"))
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

		GameEngineDirectory Dir2;
		Dir2.MoveParentToExistsChild("GameEngineResources");
		Dir2.MoveChild("ContentsResources\\Texture\\UI\\Curse");
		std::vector<GameEngineFile> Files2 = Dir2.GetAllFile();
		for (size_t i = 0; i < Files2.size(); i++)
		{
			GameEngineFile& File = Files2[i];
			GameEngineTexture::Load(File.GetStringPath());

			GameEnginePath Path = File;
			GameEngineSprite::CreateSingle(Path.GetFileName());
		}

		GameEngineDirectory Dir3;
		Dir3.MoveParentToExistsChild("GameEngineResources");
		Dir3.MoveChild("ContentsResources\\Sprite\\UI\\Curse");
		std::vector<GameEngineDirectory> Directorys = Dir3.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& File = Directorys[i];

			GameEngineSprite::CreateFolder(File.GetStringPath());
		}
	}

	float4 WindowScale = ContentsCore::GetStartWindowSize();

	FadeRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Fade);
	FadeRenderer->SetMaterial("2DTextureAlwaysDepth");
	FadeRenderer->SetCameraOrder(ECAMERAORDER::UI);
	FadeRenderer->SetSprite("ShaderWhite.Png");
	FadeRenderer->GetImageTransform().SetLocalScale(WindowScale + float4{ 0.0f,0.0f,-100.0f });
	FadeRenderer->GetColorData().MulColor = float4{ 0.0f,0.0f,0.0f,1.0f };
	FadeRenderer->SetName("FadeRenderer");

	FadeRendererAfter = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::FadeAfter);
	FadeRendererAfter->SetMaterial("2DTextureAlwaysDepth");
	FadeRendererAfter->SetCameraOrder(ECAMERAORDER::UI);
	FadeRendererAfter->SetSprite("ShaderWhite.Png");
	FadeRendererAfter->GetImageTransform().SetLocalScale(WindowScale + float4{ 0.0f,0.0f,-100.0f });
	FadeRendererAfter->GetColorData().MulColor = float4{ 0.0f,0.0f,0.0f,0.0f };
	FadeRendererAfter->SetName("FadeRenderer");



	/*Blur_LineRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter);
	Blur_LineRenderer->RenderBaseInfoValue.Target1 = 1;
	
	Blur_LineRenderer->SetMaterial("2DTextureAlwaysDepth");
	Blur_LineRenderer->SetCameraOrder(ECAMERAORDER::UI);
	Blur_LineRenderer->SetSprite("BackToWork_Split_Element.Png");
	Blur_LineRenderer->SetName("Blur_LineRenderer");
	Blur_LineRenderer->AutoSpriteSizeOn();
	Blur_LineRenderer->SetAutoScaleRatio({ 1.0f, 2.0f, 1.0f });
	Blur_LineRenderer->Transform.SetLocalPosition({ 0.0f, 0.0f });*/

	//셀렉트

	Curse_Select_Border = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter);
	Curse_Select_Border->SetMaterial("2DTextureAlwaysDepth");
	Curse_Select_Border->SetCameraOrder(ECAMERAORDER::UI);
	Curse_Select_Border->SetSprite("Book UI_Codex_Grid_OrnamentV1.Png");
	Curse_Select_Border->SetName("Curse_Select_Border");
	Curse_Select_Border->AutoSpriteSizeOn();
//	Curse_Select_Border->SetAutoScaleRatio({ 2.5f,2.5f,2.5f });
	Curse_Select_Border->Transform.SetLocalPosition({ 0.0f, 400.0f });

	Curse_Select_Text = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter);
	Curse_Select_Text->SetCameraOrder(ECAMERAORDER::UI);
	Curse_Select_Text->SetText("메이플스토리", "저주를 선택하세요", 60.0f, float4(1.f, 1.0f, 1.f, 1.0f));
	Curse_Select_Text->Transform.SetLocalPosition({ -200.0f,500.0f,0.0f });
	Curse_Select_Text->SetName("Curse_Select_Text");
	



	//레드

	Curse_BG_Red = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter);
	Curse_BG_Red->SetMaterial("2DTextureAlwaysDepth");
	Curse_BG_Red->SetCameraOrder(ECAMERAORDER::UI);
	Curse_BG_Red->SetSprite("UI_Curse_CloseUp_Window_Neutral.Png");
	Curse_BG_Red->SetName("Curse_BG_Red");
	Curse_BG_Red->AutoSpriteSizeOn();

	Curse_Rarity_Red = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter);
	Curse_Rarity_Red->SetMaterial("2DTextureAlwaysDepth");
	Curse_Rarity_Red->SetCameraOrder(ECAMERAORDER::UI);
	Curse_Rarity_Red->SetSprite("UI_Rarity_Curse_Window_05.Png");
	Curse_Rarity_Red->SetName("Curse_Rarity_Red");
	Curse_Rarity_Red->SetAutoScaleRatio({ 2.0f,2.0f,2.5f });
	Curse_Rarity_Red->AutoSpriteSizeOn();

	Curse_Border_Red = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter);
	Curse_Border_Red->SetMaterial("2DTextureAlwaysDepth");
	Curse_Border_Red->SetCameraOrder(ECAMERAORDER::UI);
	Curse_Border_Red->SetSprite("UI_Curse_CloseUp_Window.Png");
	Curse_Border_Red->SetName("Curse_Border_Red");
	Curse_Border_Red->AutoSpriteSizeOn();

	Curse_Border_On_Red = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter);
	Curse_Border_On_Red->SetMaterial("2DTextureAlwaysDepth");
	Curse_Border_On_Red->SetCameraOrder(ECAMERAORDER::UI);
	Curse_Border_On_Red->SetSprite("UI_Curse_CloseUp_Window_ON.Png");
	Curse_Border_On_Red->SetName("Curse_Border_Red");
	Curse_Border_On_Red->AutoSpriteSizeOn();

	Curse_Icon_Red = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter);
	Curse_Icon_Red->SetMaterial("2DTextureAlwaysDepth");
	Curse_Icon_Red->SetCameraOrder(ECAMERAORDER::UI);
	Curse_Icon_Red->SetSprite("UI_Curse_CloseUp_Curse_Red2.Png");
	Curse_Icon_Red->SetName("Curse_Icon_Red");
	Curse_Icon_Red->AutoSpriteSizeOn();


	Curse_Img_Red = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter);
	Curse_Img_Red->SetMaterial("2DTextureAlwaysDepth");
	Curse_Img_Red->SetCameraOrder(ECAMERAORDER::UI);
	Curse_Img_Red->SetSprite("ICONS_CURSE_BLUE_0035.Png");
	Curse_Img_Red->SetName("Curse_Img_Blue");
	Curse_Img_Red->AutoSpriteSizeOn();
	Curse_Img_Red->SetAutoScaleRatio({ 0.75f,0.75f,2.5f });
	Curse_Img_Red->GetColorData().MulColor = float4(0.8f, 0.2f, 0.2f, 1.0f);

	Curse_MainText_Red = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter);
	Curse_MainText_Red->SetCameraOrder(ECAMERAORDER::UI);
	Curse_MainText_Red->SetName("Curse_MainText_Blue");
	Curse_SubText_Red = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter);
	Curse_SubText_Red->SetCameraOrder(ECAMERAORDER::UI);
	Curse_SubText_Red->SetName("Curse_SubText_Blue");


	//블루

	Curse_BG_Blue = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter);
	Curse_BG_Blue->SetMaterial("2DTextureAlwaysDepth");
	Curse_BG_Blue->SetCameraOrder(ECAMERAORDER::UI);
	Curse_BG_Blue->SetSprite("UI_Curse_CloseUp_Window_Neutral.Png");
	Curse_BG_Blue->SetName("Curse_BG_Red");
	Curse_BG_Blue->AutoSpriteSizeOn();
	
	Curse_Rarity_Blue = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter);
	Curse_Rarity_Blue->SetMaterial("2DTextureAlwaysDepth");
	Curse_Rarity_Blue->SetCameraOrder(ECAMERAORDER::UI);
	Curse_Rarity_Blue->SetSprite("UI_Rarity_Curse_Window_03.Png");
	Curse_Rarity_Blue->SetName("Curse_Rarity_Red");
	Curse_Rarity_Blue->SetAutoScaleRatio({ 2.0f,2.0f,2.5f });
	Curse_Rarity_Blue->AutoSpriteSizeOn();

	Curse_Border_Blue = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter); 
	Curse_Border_Blue->SetMaterial("2DTextureAlwaysDepth");
	Curse_Border_Blue->SetCameraOrder(ECAMERAORDER::UI);
	Curse_Border_Blue->SetSprite("UI_Curse_CloseUp_Window.Png");
	Curse_Border_Blue->SetName("Curse_Border_Blue");
	Curse_Border_Blue->AutoSpriteSizeOn();

	Curse_Border_On_Blue = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter);
	Curse_Border_On_Blue->SetMaterial("2DTextureAlwaysDepth");
	Curse_Border_On_Blue->SetCameraOrder(ECAMERAORDER::UI);
	Curse_Border_On_Blue->SetSprite("UI_Curse_CloseUp_Window_ON.Png");
	Curse_Border_On_Blue->SetName("Curse_Border_Blue");
	Curse_Border_On_Blue->AutoSpriteSizeOn();


	Curse_Icon_Blue = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter);
	Curse_Icon_Blue->SetMaterial("2DTextureAlwaysDepth");
	Curse_Icon_Blue->SetCameraOrder(ECAMERAORDER::UI);
	Curse_Icon_Blue->SetSprite("UI_Curse_CloseUp_Curse_Blue2.Png");
	Curse_Icon_Blue->SetName("Curse_Icon_Red");
	Curse_Icon_Blue->AutoSpriteSizeOn();

	Curse_Img_Blue = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter);
	Curse_Img_Blue->SetMaterial("2DTextureAlwaysDepth");
	Curse_Img_Blue->SetCameraOrder(ECAMERAORDER::UI);
	Curse_Img_Blue->SetSprite("ICONS_CURSE_BLUE_0035.Png");
	Curse_Img_Blue->SetName("Curse_Img_Blue");
	Curse_Img_Blue->AutoSpriteSizeOn();
	Curse_Img_Blue->SetAutoScaleRatio({ 0.75f,0.75f,2.5f });
	Curse_Img_Blue->GetColorData().MulColor = float4(0.2f, 0.2f, 0.7f,1.0f);

	Curse_MainText_Blue = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter);
	Curse_MainText_Blue->SetCameraOrder(ECAMERAORDER::UI);
	Curse_MainText_Blue->SetName("Curse_MainText_Blue");
	Curse_SubText_Blue = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter);
	Curse_SubText_Blue->SetCameraOrder(ECAMERAORDER::UI);
	Curse_SubText_Blue->SetName("Curse_SubText_Blue");


	//그린

	Curse_BG_Green = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter);
	Curse_BG_Green->SetMaterial("2DTextureAlwaysDepth");
	Curse_BG_Green->SetCameraOrder(ECAMERAORDER::UI);
	Curse_BG_Green->SetSprite("UI_Curse_CloseUp_Window_Neutral.Png");
	Curse_BG_Green->SetName("Curse_BG_Red");
	Curse_BG_Green->AutoSpriteSizeOn();

	Curse_Rarity_Green = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter);
	Curse_Rarity_Green->SetMaterial("2DTextureAlwaysDepth");
	Curse_Rarity_Green->SetCameraOrder(ECAMERAORDER::UI);
	Curse_Rarity_Green->SetSprite("UI_Rarity_Curse_Window_04.Png");
	Curse_Rarity_Green->SetName("Curse_Rarity_Red");
	Curse_Rarity_Green->SetAutoScaleRatio({ 2.0f,2.0f,2.5f });
	Curse_Rarity_Green->AutoSpriteSizeOn();

	Curse_Border_Green = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter); 
	Curse_Border_Green->SetMaterial("2DTextureAlwaysDepth");
	Curse_Border_Green->SetCameraOrder(ECAMERAORDER::UI);
	Curse_Border_Green->SetSprite("UI_Curse_CloseUp_Window.Png");
	Curse_Border_Green->SetName("Curse_Border_Green");
	Curse_Border_Green->AutoSpriteSizeOn();

	Curse_Border_On_Green = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter);
	Curse_Border_On_Green->SetMaterial("2DTextureAlwaysDepth");
	Curse_Border_On_Green->SetCameraOrder(ECAMERAORDER::UI);
	Curse_Border_On_Green->SetSprite("UI_Curse_CloseUp_Window_ON.Png");
	Curse_Border_On_Green->SetName("Curse_Border_Green");
	Curse_Border_On_Green->AutoSpriteSizeOn();

	Curse_Icon_Green = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter);
	Curse_Icon_Green->SetMaterial("2DTextureAlwaysDepth");
	Curse_Icon_Green->SetCameraOrder(ECAMERAORDER::UI);
	Curse_Icon_Green->SetSprite("UI_Curse_CloseUp_Curse_Green2.Png");
	Curse_Icon_Green->SetName("Curse_Icon_Red");
	Curse_Icon_Green->AutoSpriteSizeOn();

	Curse_Img_Green = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter);
	Curse_Img_Green->SetMaterial("2DTextureAlwaysDepth");
	Curse_Img_Green->SetCameraOrder(ECAMERAORDER::UI);
	Curse_Img_Green->SetSprite("ICONS_CURSE_BLUE_0035.Png");
	Curse_Img_Green->SetName("Curse_Img_Blue");
	Curse_Img_Green->AutoSpriteSizeOn();
	Curse_Img_Green->SetAutoScaleRatio({ 0.75f,0.75f,2.5f });
	Curse_Img_Green->GetColorData().MulColor = float4(0.2f, 0.8f, 0.2f, 1.0f);

	Curse_MainText_Green = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter);
	Curse_MainText_Green->SetCameraOrder(ECAMERAORDER::UI);
	Curse_MainText_Green->SetName("Curse_MainText_Blue");
	Curse_SubText_Green = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter);
	Curse_SubText_Green->SetCameraOrder(ECAMERAORDER::UI);
	Curse_SubText_Green->SetName("Curse_SubText_Blue");

	Curse_Transition = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter);
	Curse_Transition->SetCameraOrder(ECAMERAORDER::UI);
	Curse_Transition->CreateAnimation("CurseTansition", "CurseTansition", 0.033f, -1, -1, false);
	Curse_Transition->ChangeAnimation("CurseTansition");
	Curse_Transition->Off();
	Curse_Transition->AutoSpriteSizeOn();
	Curse_Transition->SetAutoScaleRatio({ 2.f,2.f,2.5f });



	GameEngineInput::AddInputObject(this);
	Off();
	ExitValue = false;
}

void CurseUI::CurseUIStart(int _Type)
{
	Player::GetMainPlayer()->ChangeState(PlayerState::ForceWait);

	ExitValue = false;
	On();
	Type = _Type;
	FadeStrength = 0.0f;
	FadeRendererAfter->GetColorData().MulColor = float4(1.0f, 1.0f, 1.0f, 0.0f);
	switch (_Type)
	{
	case 1:
		Curse_MainText_Red->SetText("메이플스토리", "화신의 망토", 35.0f, float4(1.f, 1.0f, 1.f, 1.0f), FW1_CENTER);
		Curse_SubText_Red->SetText("메이플스토리", "망토 무기 피해량 +25%", 25.0f, float4(1.f, 1.0f, 1.f, 1.0f), FW1_CENTER);
		Curse_Img_Red->SetSprite("ICONS_CURSE_RED_0086.Png");
		

		Curse_MainText_Blue->SetText("메이플스토리", "빨리, 더 빨리!", 35.0f, float4(1.f, 1.0f, 1.f, 1.0f), FW1_CENTER);
		Curse_SubText_Blue->SetText("메이플스토리", "대쉬의 횟수 1회 증가", 25.0f, float4(1.f, 1.0f, 1.f, 1.0f),FW1_CENTER);
		Curse_Img_Blue->SetSprite("ICONS_CURSE_BLUE_0035.Png");

		Curse_MainText_Green->SetText("메이플스토리", "아케인 연구", 35.0f, float4(1.f, 1.0f, 1.f, 1.0f), FW1_CENTER);
		Curse_SubText_Green->SetText("메이플스토리", "주문 피해량 +50%", 25.0f, float4(1.f, 1.0f, 1.f, 1.0f),FW1_CENTER);
		Curse_Img_Green->SetSprite("ICONS_CURSE_GREEN_0006.Png");


		break;
	case 2:
		
		Curse_MainText_Red->SetText("메이플스토리", "아다만티움 대낫", 35.0f, float4(1.f, 1.0f, 1.f, 1.0f), FW1_CENTER);
		Curse_SubText_Red->SetText("메이플스토리", "낫 무기 피해량 +5", 25.0f, float4(1.f, 1.0f, 1.f, 1.0f), FW1_CENTER);
		Curse_Img_Red->SetSprite("ICONS_CURSE_RED_0095.Png");

		Curse_MainText_Blue->SetText("메이플스토리", "더 있다니까...", 35.0f, float4(1.f, 1.0f, 1.f, 1.0f), FW1_CENTER);
		Curse_SubText_Blue->SetText("메이플스토리", "아니마 보관 슬롯 +1", 25.0f, float4(1.f, 1.0f, 1.f, 1.0f), FW1_CENTER);
		Curse_Img_Blue->SetSprite("ICONS_CURSE_BLUE_0040.Png");

		Curse_MainText_Green->SetText("메이플스토리", "숙련된 학자", 35.0f, float4(1.f, 1.0f, 1.f, 1.0f), FW1_CENTER);
		Curse_SubText_Green->SetText("메이플스토리", "마나 재생 속도 +100%", 25.0f, float4(1.f, 1.0f, 1.f, 1.0f), FW1_CENTER);
		Curse_Img_Green->SetSprite("ICONS_CURSE_GREEN_0005.Png");

		break;
	default:
		break;
	}

		

		Curse_BG_Red->Transform.SetLocalPosition({ 0.0f,-17.0f,0.0f });
		Curse_BG_Blue->Transform.SetLocalPosition({ 0.0f,-17.0f,0.0f });
		Curse_BG_Green->Transform.SetLocalPosition({ 0.0f,-17.0f,0.0f });


		Curse_Border_Red->Transform.SetLocalPosition({ 0.0f,0.0f,0.0f });
		Curse_Border_Blue->Transform.SetLocalPosition({ 0.0f,0.0f,0.0f });
		Curse_Border_Green->Transform.SetLocalPosition({ 0.0f,0.0f,0.0f });

		Curse_Border_On_Red->Transform.SetLocalPosition({ 0.0f,0.0f,0.0f });
		Curse_Border_On_Blue->Transform.SetLocalPosition({ 0.0f,0.0f,0.0f });
		Curse_Border_On_Green->Transform.SetLocalPosition({ 0.0f,0.0f,0.0f });

		

		Curse_Rarity_Red->Transform.SetLocalPosition({ 2.0f,-10.0f,0.0f });
		Curse_Rarity_Blue->Transform.SetLocalPosition({ 2.0f,-10.0f,0.0f });
		Curse_Rarity_Green->Transform.SetLocalPosition({ 2.0f,3.0f,0.0f });

		Curse_Icon_Red->Transform.SetLocalPosition({ 8.0f,300.0f,0.0f });
		Curse_Icon_Blue->Transform.SetLocalPosition({ 8.0f,300.0f,0.0f });
		Curse_Icon_Green->Transform.SetLocalPosition({ 8.0f,300.0f,0.0f });

		Curse_MainText_Red->Transform.SetLocalPosition({ 0.0f,200.0f,0.0f });
		Curse_MainText_Blue->Transform.SetLocalPosition({ 0.0f,200.0f,0.0f });
		Curse_MainText_Green->Transform.SetLocalPosition({ 0.0f,200.0f,0.0f });

		Curse_SubText_Red->Transform.SetLocalPosition({ 0.0f,-105.0f,0.0f });
		Curse_SubText_Blue->Transform.SetLocalPosition({ 0.0f, -105.0f,0.0f });
		Curse_SubText_Green->Transform.SetLocalPosition({ 0.0f, -105.0f,0.0f });

		Curse_Img_Red->Transform.SetLocalPosition({ 0.0f,50.0f,0.0f });
		Curse_Img_Blue->Transform.SetLocalPosition({ 0.0f,50.0f,0.0f });
		Curse_Img_Green->Transform.SetLocalPosition({ 0.0f,50.0f,0.0f });



		GameEngineSound::SoundPlay("CurseUIOn");
}

void CurseUI::UIOn()
{
	
}

void CurseUI::ExitAnimationUpdate(float _Delta)
{
	ExitTimer += _Delta;
	if (FadeStrength > 0.0f)
	{
		FadeStrength -= _Delta * 2.0f;
	}
	else
	{
		FadeStrength = 0.0f;
	}
	FadeRendererAfter->GetColorData().MulColor = float4(1.0f, 1.0f, 1.0f, FadeStrength);

	switch (PickNum)
	{
	case 1:
		if (Type == 1)
		{
			Player::GetMainPlayerData().DamageCapeScale += 0.25f;
		}
		else
		{
			Player::GetMainPlayerData().DamageComobo += 5.0f;
		}

		BlueMove(float4{ 1.0f,0.0f,0.0f } *5000.0f * _Delta);
		GreenMove(float4{ 1.0f,0.0f,0.0f } *5000.0f * _Delta);

		break;
	case 2:
		if (Type == 1)
		{
			Player::GetMainPlayerData().DashCount += 1;
		}
		else
		{
			Player::GetMainPlayerData().AnimaSocket += 1;
		}

		RedMove(float4{ 1.0f,0.0f,0.0f } * 5000.0f * _Delta);
		GreenMove(float4{ 1.0f,0.0f,0.0f } * 5000.0f * _Delta);

		break;
	case 3:

		if (Type == 1)
		{
			Player::GetMainPlayerData().DamageMagicScale += 0.5f;
		}
		else
		{
			Player::GetMainPlayerData().MPScale += 1.0f;
		}
		RedMove(float4{ 1.0f,0.0f,0.0f } *5000.0f * _Delta);
		BlueMove(float4{ 1.0f,0.0f,0.0f } *5000.0f * _Delta);

		break;
	default:
		break;
	}

	if (ExitTimer >= 1.0f)
	{
		Player::GetMainPlayer()->ChangeState(PlayerState::PowerUp);
		Off();
	}


}

void CurseUI::Update(float _Delta)
{

	if (ExitValue == true)
	{
		ExitAnimationUpdate(_Delta);
		return;
	}

	if (FadeStrength < 0.75f)
	{
		FadeStrength += _Delta * 0.8f;
		MoveDist = 0.0f;
		FadeRenderer->GetColorData().MulColor = float4(0.0f, 0.0f, 0.0f, FadeStrength);
		return;
	}

	FadeStrength = 0.75f;
	FadeRenderer->GetColorData().MulColor = float4(0.0f, 0.0f, 0.0f, FadeStrength);
	

	float NextDist = 0.0f;

	if (MoveDist < 450.0f)
	{
		NextDist = _Delta * 900.0f;
		MoveDist += NextDist;
	}

	if (MoveDist > 450.0f)
	{
		NextDist -= MoveDist - 450.0f;
		MoveDist = 450.0f;
	}

	RedMove({ -NextDist });
	GreenMove({ NextDist });

	//Curse_Border_On_Blue->Transform.SetLocalPosition({ 0.0f,0.0f,0.0f });

	

	
	

	if (GameEngineInput::IsDown('F', this))
	{
		Curse_Transition->ChangeAnimation("CurseTansition", true);
		GetContentsLevel()->GetShaderActor()->CurseShaderStart();
		Curse_Transition->On();
		FadeStrength = 1.0f;
		ExitValue = true;

		GetContentsLevel()->StartScreenShake(0.5f, 12.0f, 10.0f);
		GameEngineSound::SoundPlay("CurseUISelect");
	}

	if (PickNum > 1 and GameEngineInput::IsDown('A', this))
	{
		PickNum--;
		GameEngineSound::SoundPlay("Click");

	}
	else if (PickNum < 3 and GameEngineInput::IsDown('D', this)) 
	{
		PickNum++;
		GameEngineSound::SoundPlay("Click");
	}

	switch (PickNum)
	{
	case 1:
		Curse_Border_On_Red->On();
		Curse_Border_On_Blue->Off();
		Curse_Border_On_Green->Off();
		break;
	case 2:
		Curse_Border_On_Red->Off();
		Curse_Border_On_Blue->On();
		Curse_Border_On_Green->Off();
		break;
	case 3:
		Curse_Border_On_Red->Off();
		Curse_Border_On_Blue->Off();
		Curse_Border_On_Green->On();
		break;
	default:
		break;
	}


}

void CurseUI::LevelStart(GameEngineLevel* _NextLevel)
{
}

void CurseUI::RedMove(const float4& _Pos)
{
	Curse_Border_Red->Transform.AddLocalPosition({ _Pos });
	Curse_BG_Red->Transform.AddLocalPosition({ _Pos });
	Curse_Icon_Red->Transform.AddLocalPosition({ _Pos });
	Curse_Rarity_Red->Transform.AddLocalPosition({ _Pos });
	Curse_MainText_Red->Transform.AddLocalPosition({ _Pos });
	Curse_SubText_Red->Transform.AddLocalPosition({ _Pos });
	Curse_Img_Red->Transform.AddLocalPosition({ _Pos });
	Curse_Border_On_Red->Transform.AddLocalPosition({ _Pos });
}

void CurseUI::BlueMove(const float4& _Pos)
{
	Curse_Border_Blue->Transform.AddLocalPosition({ _Pos });
	Curse_BG_Blue->Transform.AddLocalPosition({ _Pos });
	Curse_Icon_Blue->Transform.AddLocalPosition({ _Pos });
	Curse_Rarity_Blue->Transform.AddLocalPosition({ _Pos });
	Curse_MainText_Blue->Transform.AddLocalPosition({ _Pos });
	Curse_SubText_Blue->Transform.AddLocalPosition({ _Pos });
	Curse_Img_Blue->Transform.AddLocalPosition({ _Pos });
	Curse_Border_On_Blue->Transform.AddLocalPosition({ _Pos });
}

void CurseUI::GreenMove(const float4& _Pos)
{
	Curse_Border_Green->Transform.AddLocalPosition({ _Pos });
	Curse_BG_Green->Transform.AddLocalPosition({ _Pos });
	Curse_Icon_Green->Transform.AddLocalPosition({ _Pos });
	Curse_Rarity_Green->Transform.AddLocalPosition({ _Pos });
	Curse_MainText_Green->Transform.AddLocalPosition({ _Pos });
	Curse_SubText_Green->Transform.AddLocalPosition({ _Pos });
	Curse_Img_Green->Transform.AddLocalPosition({ _Pos });
	Curse_Border_On_Green->Transform.AddLocalPosition({ _Pos });
}
