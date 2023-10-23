#include "PreCompile.h"
#include "Title.h"

Title::Title() 
{
}

Title::~Title()
{
}

void Title::Start()
{
	if (nullptr == GameEngineTexture::Find("HaND_LOGO.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\Texture\\UI\\Title");
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
		Dir2.MoveChild("ContentsResources\\Sprite\\UI\\Title");
		std::vector<GameEngineDirectory> Directorys = Dir2.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& File = Directorys[i];

			GameEngineSprite::CreateFolder(File.GetStringPath());
		}
	}
	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::BackGroundobject);
	MainSpriteRenderer->AutoSpriteSizeOn();
	MainSpriteRenderer->SetAutoScaleRatio({ 0.5f,0.5f,0.5f });
	MainSpriteRenderer->SetSprite("HaND_LOGO.png");
	MainSpriteRenderer->Transform.SetLocalPosition({ 450.0f,-300.0f,0.0f });

	TitleBG = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::BackGroundobject);
	TitleBG->AutoSpriteSizeOn();
	TitleBG->SetAutoScaleRatio({ 1.0f,1.0f,0.5f });
	TitleBG->SetSprite("Lobby_2_bg_01.png");
	TitleBG->Transform.SetLocalPosition({ 950.0f,-550.0f,100.0f });

	SetName("Tilte");

	UIArrow = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	UIArrow->AutoSpriteSizeOn();
	UIArrow->SetSprite("Book UI_Missions_Arrow_Right_On.png");
	UIArrow->Transform.SetLocalPosition({ 100.0f,-650.0f, -1.0f});

	GameEngineInput::AddInputObject(this);
}

void Title::Update(float _Delta)
{
	InputDebugUpdate(_Delta);

	if (GameEngineInput::IsDown('W', this) and ArrowLocate > 1)
	{
		ArrowLocate--;
		UIArrow->Transform.AddLocalPosition({ 0.0f,100.0f });
	}
	if (GameEngineInput::IsDown('S', this) and ArrowLocate < 4)
	{
		ArrowLocate++;
		UIArrow->Transform.AddLocalPosition({ 0.0f, -100.0f });
	}

	if (GameEngineInput::IsDown(VK_RETURN, this) and ArrowLocate == 1)
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}
	
}

