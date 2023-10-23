#pragma once
#include "Level.h"

// Ό³Έν :
class PlayLevel : public Level
{
public:
	// constrcuter destructer
	PlayLevel();
	~PlayLevel();

	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;
	
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

