#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class Level : public GameEngineLevel
{
public:
	// constrcuter destructer
	Level();
	~Level();

	// delete Function
	Level(const Level& _Other) = delete;
	Level(Level&& _Other) noexcept = delete;
	Level& operator=(const Level& _Other) = delete;
	Level& operator=(Level&& _Other) noexcept = delete;

	std::shared_ptr<class Map> GetMap()
	{
		return MapPtr;
	}
	void SetMap(std::shared_ptr<Map> _MapPtr)
	{
		MapPtr = _MapPtr;
	}

protected:

private:

	std::shared_ptr<Map> MapPtr = nullptr;
};

