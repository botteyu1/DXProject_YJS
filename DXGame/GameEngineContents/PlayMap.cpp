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

	if (nullptr == GameEngineTexture::Find("W1_Kit_background_Traile_Pixel.png"))
	{
		// ������ ���̴��� ���δ� ���δ� �ε��ϴ� �ڵ带 ģ��.
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\Texture\\Map");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());

		}
		GameEngineSprite::CreateSingle("Stage1.dds");
		GameEngineSprite::CreateSingle("Stage2.dds");
		GameEngineSprite::CreateSingle("StageBoss.dds");
		GameEngineSprite::CreateSingle("StagePixel1.png");
		GameEngineSprite::CreateSingle("StagePixel2.png");
		GameEngineSprite::CreateSingle("StagePixelBoss.png");
	}


	

	Map::Start();
}
