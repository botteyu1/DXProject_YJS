#include "PreCompile.h"
#include "PlayUI.h"

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
	HUD_Main = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_Main->AutoSpriteSizeOn();
	HUD_Main->SetCameraOrder(ECAMERAORDER::UI);
	HUD_Main->SetSprite("HUD_Main_Jauge.png");
	HUD_Main->Transform.SetLocalPosition({-910.0f,430.0f,0.0f });
	HUD_Main->SetName("HUD_Main");

	HUD_Cape = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_Cape->AutoSpriteSizeOn();
	HUD_Cape->SetCameraOrder(ECAMERAORDER::UI);
	HUD_Cape->SetSprite("HUD_Main_Jauge.png");
	HUD_Cape->Transform.SetLocalPosition({-865.0f,475.0f,0.0f });
	HUD_Cape->SetName("HUD_Cape");
	
	HUD_Cape2 = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	HUD_Cape2->AutoSpriteSizeOn();
	HUD_Cape2->SetCameraOrder(ECAMERAORDER::UI);
	HUD_Cape2->SetSprite("HUD_Main_Jauge.png");
	HUD_Cape2->Transform.SetLocalPosition({-820.0f,430.0f,0.0f });
	HUD_Cape2->SetName("HUD_Cape2");


}

void PlayUI::Update(float _Delta)
{
}

