#include "PreCompile.h"
#include "PaperWall.h"

PaperWall::PaperWall() 
{
}

PaperWall::~PaperWall()
{
}

void PaperWall::CollisionUpdate(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
}

void PaperWall::GimmckStart()
{
	State.ChangeState(PaperWallState::Start);
}

void PaperWall::GimmckEnd()
{
	State.ChangeState(PaperWallState::End);
}

void PaperWall::Start()
{
	if (nullptr == GameEngineTexture::Find("Rune_Stroke_New.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources\\Texture\\StageObject");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());

			GameEnginePath Path = File;
			GameEngineSprite::CreateSingle(Path.GetFileName());
		}
	}

	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::BackGroundobject);
	MainSpriteRenderer->SetMaterial("2DTextureAlwaysDepth");
	MainSpriteRenderer->SetSprite("GPE_Paper_Piles_Line.png");
	//MainSpriteRenderer->Transform.SetLocalPosition({ 0.0f, 150.0f, 1.0f });
	MainSpriteRenderer->AutoSpriteSizeOn();
	//MainSpriteRenderer->GetColorData().MulColor = float4{ 1.f,1.f,1.0f,0.0f };



	{
		CreateStateParameter NewPara;

		

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainSpriteRenderer->GetColorData().MulColor = float4{ 1.f,1.f,1.0f,0.0f };
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				/*if (State.GetStateTime() >= 2.0f)
				{
					State.ChangeState(PaperWallState::Start);
				}*/
			};
		State.CreateState(PaperWallState::StaticOff, NewPara);
	}
	

	{
		CreateStateParameter NewPara;


		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				On();
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				/*if (State.GetStateTime() >= 2.0f)
				{
					State.ChangeState(PaperWallState::End);
				}*/
			};
		State.CreateState(PaperWallState::StaticOn, NewPara);
	}
	

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				On();
				AlphaValue = 0.0f;
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				AlphaValue += _DeltaTime /1.0f;
				if (AlphaValue >= 1.0f)
				{
					AlphaValue = 1.0f;
					MainSpriteRenderer->GetColorData().MulColor = float4{ 1.f,1.f,1.0f,AlphaValue };
					State.ChangeState(PaperWallState::StaticOn);
				}
				MainSpriteRenderer->GetColorData().MulColor = float4{ 1.f,1.f,1.0f,AlphaValue };

			};
		State.CreateState(PaperWallState::Start, NewPara);
	}
	
	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				AlphaValue = 1.0f;
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				AlphaValue -= _DeltaTime / 1.0f;
				if (AlphaValue <= 0.0f)
				{
					AlphaValue = 0.0f;
					MainSpriteRenderer->GetColorData().MulColor = float4{ 1.f,1.f,1.0f,AlphaValue };
					State.ChangeState(PaperWallState::StaticOff);
				}
				MainSpriteRenderer->GetColorData().MulColor = float4{ 1.f,1.f,1.0f,AlphaValue };
			};
		State.CreateState(PaperWallState::End, NewPara);
	}


	State.ChangeState(PaperWallState::StaticOff);
	//State.ChangeState(PaperWallState::StaticOn);


	GameEngineInput::AddInputObject(this);
	static int Num = 0;
	Num++;

	SetName("PaperWall_" + std::to_string(Num));


}

void PaperWall::Update(float _Delta)
{
	StageObject::Update(_Delta);

	if (DebugValue == true)
	{
		return;
	}
	State.Update(_Delta);

}

