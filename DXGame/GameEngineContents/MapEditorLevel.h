#pragma once
#include "Level.h"

// Ό³Έν :
class MapEditorLevel : public Level
{
public:
	// constrcuter destructer
	MapEditorLevel();
	~MapEditorLevel();

	// delete Function
	MapEditorLevel(const MapEditorLevel& _Other) = delete;
	MapEditorLevel(MapEditorLevel&& _Other) noexcept = delete;
	MapEditorLevel& operator=(const MapEditorLevel& _Other) = delete;
	MapEditorLevel& operator=(MapEditorLevel&& _Other) noexcept = delete;

	std::shared_ptr<class PlayMap> GetPlayMap()
	{
		return PlayMapPtr;
	}



protected:
	void Start() override;

	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:

	std::shared_ptr<PlayMap> PlayMapPtr = nullptr;
};

