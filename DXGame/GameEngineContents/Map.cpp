#include "PreCompile.h"
#include "Map.h"

Map::Map() 
{
}

Map::~Map()
{
}

GameEngineColor Map::GetColor(float4 _Pos, GameEngineColor _DefaultColor)
{
	// 플레이어의 위치를 이미지의 좌표계로 변경한다.
	// 이미지는 위에서부터 아래로 내려갈수록 +가 되기 때문이다.
	_Pos.Y *= -1.0f;

	std::shared_ptr<GameEngineTexture> Tex = PixelBackGround->GetCurSprite().Texture;

	float4 Scale = Tex->GetScale();

	Scale.Y *= -1.0f;

	if (_Pos.X >= Scale.X and PixelBackGround2 != nullptr)
	{
		Tex = PixelBackGround2->GetCurSprite().Texture;
		_Pos.X -= Scale.X;
	}
	
	return Tex->GetColor(_Pos, _DefaultColor);
}

void Map::Start()
{
	GameEngineInput::AddInputObject(this);
}

void Map::Update(float _Delta)
{
	if (GameEngineInput::IsDown('L',this))
	{
		MainBackGround->Off();
		PixelBackGround->On();
		if (MainBackGround2 != nullptr)
		{
			MainBackGround2->Off();
			PixelBackGround2->On();
		}
		
	}
	if (GameEngineInput::IsDown('K', this))
	{
		MainBackGround->On();
		PixelBackGround->Off();
		if (MainBackGround2 != nullptr)
		{
			MainBackGround2->On();
			PixelBackGround2->Off();
		}
	}
}

void Map::Init(std::string_view _Main, std::string_view _MainPixel, std::string_view _Main2, std::string_view _MainPixel2)
{
	{
		MainBackGround = CreateComponent<GameEngineSpriteRenderer>(-99);
		MainBackGround->SetSprite(_Main);
		

		PixelBackGround = CreateComponent<GameEngineSpriteRenderer>(-100);
		PixelBackGround->SetSprite(_MainPixel);
		PixelBackGround->Off();

		std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("Stage1.dds");

		float4 Scale = Tex->GetScale();
		Scale.Y *= -1.0f;
		float4 HScale = Scale.Half();

		if (_Main2 != "")
		{
			MainBackGround2 = CreateComponent<GameEngineSpriteRenderer>(-99);
			MainBackGround2->SetSprite(_Main2);
			PixelBackGround2 = CreateComponent<GameEngineSpriteRenderer>(-100);
			PixelBackGround2->SetSprite(_MainPixel2);
			PixelBackGround2->Off();
			MainBackGround2->Transform.SetLocalPosition(float4{ Scale.X, 0.0f } + HScale);
			PixelBackGround2->Transform.SetLocalPosition(float4{ Scale.X, 0.0f } + HScale);
		}
		

	

		MainBackGround->Transform.SetLocalPosition(HScale);
		PixelBackGround->Transform.SetLocalPosition(HScale);

	}
}
