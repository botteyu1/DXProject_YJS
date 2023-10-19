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
		GameEngineSprite::CreateSingle("Stage1.dds");
		GameEngineSprite::CreateSingle("Stage2.dds");
		GameEngineSprite::CreateSingle("StagePixel1.png");
		GameEngineSprite::CreateSingle("StagePixel2.png");
	}


	{
		PixelBackGround = CreateComponent<GameEngineSpriteRenderer>(-100);
		PixelBackGround->SetSprite("StagePixel1.png");
		PixelBackGround->Off();
		PixelBackGround2 = CreateComponent<GameEngineSpriteRenderer>(-100);
		PixelBackGround2->SetSprite("StagePixel2.png");
		PixelBackGround2->Off();
		MainBackGround = CreateComponent<GameEngineSpriteRenderer>(-99);
		MainBackGround->SetSprite("Stage1.dds");
		MainBackGround2 = CreateComponent<GameEngineSpriteRenderer>(-99);
		MainBackGround2->SetSprite("Stage2.dds");
		//MainBackGround2->Off();

		std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("Stage1.dds");

		float4 Scale = Tex->GetScale();
		Scale.Y *= -1.0f;
		float4 HScale = Scale.Half();

		MainBackGround->Transform.SetLocalPosition(HScale);
		PixelBackGround->Transform.SetLocalPosition(HScale);
		MainBackGround2->Transform.SetLocalPosition(float4{Scale.X, 0.0f} + HScale);
		PixelBackGround2->Transform.SetLocalPosition(float4{Scale.X, 0.0f} + HScale);
	}

	Map::Start();
}
