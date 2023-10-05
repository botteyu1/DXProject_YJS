#include "PreCompile.h"
#include "PlayMap.h"

PlayMap* PlayMap::MainMap;

PlayMap::PlayMap() 
{
	MainMap = this;
}

PlayMap::~PlayMap() 
{
}

void PlayMap::Start()
{
	{
		// 엔진용 쉐이더를 전부다 전부다 로드하는 코드를 친다.
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\Texture\\Map");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			// 구조적으로 잘 이해하고 있는지를 자신이 명확하게 인지하기 위해서
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());

		}

		

		GameEngineSprite::CreateSingle("Office_background_Frieze.png");
		GameEngineSprite::CreateSingle("OfficePixel2.png");
		GameEngineSprite::CreateSingle("W1_Kit_background_Traile_Pixel.png");
		GameEngineSprite::CreateSingle("W1_Kit_background_Traile.png");
		GameEngineSprite::CreateSingle("Stage1.dds");
		GameEngineSprite::CreateSingle("Stage1_Pixel.png");
	}


	{
		PixelBackGround = CreateComponent<GameEngineSpriteRenderer>(-100);
		PixelBackGround->SetSprite("Stage1_Pixel.png");
		PixelBackGround->Off();
		MainBackGround = CreateComponent<GameEngineSpriteRenderer>(-99);
		MainBackGround->SetSprite("Stage1.dds");

		std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("Stage1.dds");

		float4 HScale = Tex->GetScale().Half();
		HScale.Y *= -1.0f;

		MainBackGround->Transform.SetLocalPosition(HScale);
		PixelBackGround->Transform.SetLocalPosition(HScale);


	}
}
