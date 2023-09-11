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
		// ������ ���̴��� ���δ� ���δ� �ε��ϴ� �ڵ带 ģ��.
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\Texture\\Map");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			// ���������� �� �����ϰ� �ִ����� �ڽ��� ��Ȯ�ϰ� �����ϱ� ���ؼ�
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());

		}

		

		GameEngineSprite::CreateSingle("Office_background_Frieze.png");
		GameEngineSprite::CreateSingle("OfficePixel2.png");
	}


	{
		PixelBackGround = CreateComponent<GameEngineSpriteRenderer>(-100);
		PixelBackGround->SetSprite("OfficePixel2.png");
		MainBackGround = CreateComponent<GameEngineSpriteRenderer>(-99);
		MainBackGround->SetSprite("Office_background_Frieze.png");

		std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("Office_background_Frieze.png");

		float4 HScale = Tex->GetScale().Half();
		HScale.Y *= -1.0f;

		MainBackGround->Transform.SetLocalPosition(HScale);
		PixelBackGround->Transform.SetLocalPosition(HScale);


	}
}
