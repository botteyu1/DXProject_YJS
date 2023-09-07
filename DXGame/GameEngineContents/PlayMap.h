#pragma once
#include "Map.h"

// Ό³Έν :
class PlayMap : public Map
{
public:
	static PlayMap* MainMap;

public:
	// constrcuter destructer
	PlayMap();
	~PlayMap();

	// delete Function
	PlayMap(const PlayMap& _Other) = delete;
	PlayMap(PlayMap&& _Other) noexcept = delete;
	PlayMap& operator=(const PlayMap& _Other) = delete;
	PlayMap& operator=(PlayMap&& _Other) noexcept = delete;

	

protected:
	void Start() override;

private:

};

