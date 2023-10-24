#pragma once
#include "Tab.h"
// Ό³Έν : 
class LevelChangeTab : public Tab
{
public:
	// constrcuter destructer
	LevelChangeTab();
	~LevelChangeTab();

public:
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime);
	LevelChangeTab(std::string_view _Name)
		: Tab(_Name)
	{
	}

protected:

private:

};

