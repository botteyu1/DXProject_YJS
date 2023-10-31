#include "PreCompile.h"
#include "Title.h"
#include "ContentObject.h"

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
	MainSpriteRenderer->Transform.SetLocalPosition({ 400.0f,-300.0f,0.0f });

	TitleBG = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::BackGroundobject);
	TitleBG->AutoSpriteSizeOn();
	TitleBG->SetAutoScaleRatio({ 1.0f,1.0f,0.5f });
	TitleBG->SetSprite("Lobby_2_bg_01.png");
	TitleBG->Transform.SetLocalPosition({ 950.0f,-550.0f,100.0f });
	TitleBG->GetColorData().MulColor = float4(0.5f, 0.1f, 0.1f, 1.0f);

	SetName("Tilte");

	UIArrow = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	UIArrow->AutoSpriteSizeOn();
	UIArrow->SetSprite("UI_Missions_Arrow_Right_On.png");
	UIArrow->Transform.SetLocalPosition({ 100.0f,-650.0f, -1.0f});

	LD_Weapon = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	LD_Weapon->AutoSpriteSizeOn();
	LD_Weapon->SetAutoScaleRatio({ 1.8f,1.8f,1.0f });
	//LD_Weapon->SetPivotValue({ 1.0f, 0.0f });
	LD_Weapon->SetSprite("LD_HomeScreen_Weapon.png");
	LD_Weapon->Transform.SetLocalPosition({1049.0f, -739.0f, -0.5f});
	LD_Weapon->Transform.SetLocalRotation({ 0.0f, 0.0f, 20.0f});
	LD_Weapon->SetName("LD_Weapon");
	LD_Weapon->LeftFlip();

	LD_Body = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	LD_Body->AutoSpriteSizeOn();
	LD_Body->SetAutoScaleRatio({ 2.0f,2.0f,1.0f});
	LD_Body->SetPivotValue({ 1.0f, 0.0f });
	LD_Body->CreateAnimation("LD_HomeScreen_Body", "LD_HomeScreen_Body", 0.0433f, -1, -1, true);
	LD_Body->ChangeAnimation("LD_HomeScreen_Body");
	LD_Body->Transform.SetLocalPosition({ 1100.0f,-550.0f, -1.0f });
	LD_Body->SetName("LD_Body");
	LD_Body->LeftFlip();

	LD_Forearm = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	LD_Forearm->AutoSpriteSizeOn();
	LD_Forearm->SetAutoScaleRatio({ 2.0f,2.0f,1.0f });
	LD_Forearm->SetPivotValue({ 0.0f, 0.0f });
	LD_Forearm->CreateAnimation("LD_HomeScreen_Forearm", "LD_HomeScreen_Forearm", 0.0433f, -1, -1, true);
	LD_Forearm->ChangeAnimation("LD_HomeScreen_Forearm");
	LD_Forearm->Transform.SetLocalPosition({ 1628.0f,-688.0f, -2.0f });
	LD_Forearm->LeftFlip();
	LD_Forearm->SetName("LD_Forearm");

	LD_Head = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	LD_Head->AutoSpriteSizeOn();
	LD_Head->SetAutoScaleRatio({ 1.7f,1.7f,1.0f });
	LD_Head->SetPivotValue({ 0.0f, 0.0f });
	LD_Head->CreateAnimation("LD_HomeScreen_Head", "LD_HomeScreen_Head", 0.0433f, -1, -1, true);
	LD_Head->ChangeAnimation("LD_HomeScreen_Head");
	LD_Head->Transform.SetLocalPosition({ 1756.0f,-158.0f, -3.0f });
	LD_Head->LeftFlip();
	LD_Head->SetName("LD_Head");

	LD_Smoke = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	LD_Smoke->AutoSpriteSizeOn();
	LD_Smoke->SetAutoScaleRatio({ 2.0f,2.0f,1.0f });
	LD_Smoke->SetPivotValue({ 0.5f, 0.0f });
	LD_Smoke->CreateAnimation("LD_HomeScreen_Smoke", "LD_HomeScreen_Smoke", 0.0433f, -1, -1, true);
	LD_Smoke->ChangeAnimation("LD_HomeScreen_Smoke");
	LD_Smoke->Transform.SetLocalPosition({ 1630.0f,-329.0f, -4.0f });
	LD_Smoke->LeftFlip();
	LD_Smoke->SetName("LD_Smoke");
	
	LD_Reflect = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::UI);
	LD_Reflect->AutoSpriteSizeOn();
	LD_Reflect->SetAutoScaleRatio({ 1.8f,1.8f,1.0f });
	LD_Reflect->SetPivotValue({ 0.0f, 0.0f });
	LD_Reflect->CreateAnimation("HomeScreen_Weapon_Reflect", "HomeScreen_Weapon_Reflect", 0.0433f, -1, -1, true);
	LD_Reflect->ChangeAnimation("HomeScreen_Weapon_Reflect");
	LD_Reflect->Transform.SetLocalPosition({ 1116.0f,-82.0f, -1.0f });
	LD_Reflect->Transform.SetLocalRotation({ 0.0f, 0.0f, 20.0f });
	LD_Reflect->LeftFlip();
	LD_Reflect->SetName("LD_Reflect");

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
	
	float4 NextAddPos = Dir * _Delta * 25.0f;
	MoveDistCheck += NextAddPos.Y;
	if (MoveDistCheck <= MoveDist)
	{
		NextAddPos.Y -= MoveDistCheck - MoveDist;
		Dir = float4::UP;
	}
	else if(MoveDistCheck >= 0.0f)
	{
		NextAddPos.Y += 0.0f- MoveDistCheck;
		Dir = float4::DOWN;
	}
	LD_Body->Transform.AddLocalPosition(NextAddPos);
	LD_Forearm->Transform.AddLocalPosition(NextAddPos);
	LD_Head->Transform.AddLocalPosition(NextAddPos);
	LD_Smoke->Transform.AddLocalPosition(NextAddPos);
	LD_Reflect->Transform.AddLocalPosition(NextAddPos);
	LD_Weapon->Transform.AddLocalPosition(NextAddPos);

}

