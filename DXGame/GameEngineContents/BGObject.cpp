#include "PreCompile.h"
#include "BGObject.h"

BGObject::BGObject() 
{
}

BGObject::~BGObject()
{
}

void BGObject::Start()
{
	if (nullptr == GameEngineTexture::Find("ColumnTop.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\Texture\\BGObject");
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
		Dir2.MoveChild("ContentsResources\\Sprite\\BGObject");
		std::vector<GameEngineDirectory> Directorys = Dir2.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& File = Directorys[i];

			GameEngineSprite::CreateFolder(File.GetStringPath());
		}
	}
	

	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::BackGroundobject);
	MainSpriteRenderer->AutoSpriteSizeOn();


	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X - 700.0f, -HalfWindowScale.Y * 4 });
}

void BGObject::Update(float _Delta)
{
	
	if (DebugValue == true)
	{
		InputDebugUpdate(_Delta);
		return;
	}
}

void BGObject::Init(std::string _Name, bool _Animation)
{
	if (_Animation == false)
	{

		MainSpriteRenderer->SetSprite(_Name);
	}
	else
	{
		MainSpriteRenderer->CreateAnimation(_Name, _Name, 0.0666f, -1, -1, true);
	}

	static int Num = 0;
	Num++;
	SetName(_Name + "_" + std::to_string(Num));
}

