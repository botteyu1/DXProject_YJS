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

	
	return Tex->GetColor(_Pos, _DefaultColor);
}

void Map::Update(float _Delta)
{
	if (GameEngineInput::IsDown('L'))
	{
		MainBackGround->Off();
		PixelBackGround->On();
	}
	if (GameEngineInput::IsDown('K'))
	{
		MainBackGround->On();
		PixelBackGround->Off();
	}
}
