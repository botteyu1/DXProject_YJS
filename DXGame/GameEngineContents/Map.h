#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class Map : public GameEngineActor
{
public:
	// constrcuter destructer
	Map();
	~Map();

	// delete Function
	Map(const Map& _Other) = delete;
	Map(Map&& _Other) noexcept = delete;
	Map& operator=(const Map& _Other) = delete;
	Map& operator=(Map&& _Other) noexcept = delete;


	GameEngineColor GetColor(float4 _Pos, GameEngineColor _DefaultColor = { 255, 255, 255, 255 });
protected:
	std::shared_ptr<GameEngineSpriteRenderer> MainBackGround;
	std::shared_ptr<GameEngineSpriteRenderer> MainBackGround2;
	std::shared_ptr<GameEngineSpriteRenderer> PixelBackGround;
	std::shared_ptr<GameEngineSpriteRenderer> PixelBackGround2;


	void Start() override;
	void Update(float _Delta) override;

private:

};

