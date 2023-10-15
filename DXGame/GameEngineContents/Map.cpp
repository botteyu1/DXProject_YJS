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
	// �÷��̾��� ��ġ�� �̹����� ��ǥ��� �����Ѵ�.
	// �̹����� ���������� �Ʒ��� ���������� +�� �Ǳ� �����̴�.
	_Pos.Y *= -1.0f;

	std::shared_ptr<GameEngineTexture> Tex = PixelBackGround->GetCurSprite().Texture;

	float4 Scale = Tex->GetScale();

	Scale.Y *= -1.0f;

	if (_Pos.X >= Scale.X)
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
		MainBackGround2->Off();
		PixelBackGround->On();
		PixelBackGround2->On();
	}
	if (GameEngineInput::IsDown('K', this))
	{
		MainBackGround->On();
		MainBackGround2->On();
		PixelBackGround->Off();
		PixelBackGround2->Off();
	}
}
