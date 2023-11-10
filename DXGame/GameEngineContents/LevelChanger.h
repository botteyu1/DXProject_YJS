#pragma once

#include "UI.h"

// Ό³Έν :

class LevelChanger : public UI
{
public:
	// constrcuter destructer
	LevelChanger();
	~LevelChanger();

	// delete Function
	LevelChanger(const LevelChanger& _Other) = delete;
	LevelChanger(LevelChanger&& _Other) noexcept = delete;
	LevelChanger& operator=(const LevelChanger& _Other) = delete;
	LevelChanger& operator=(LevelChanger&& _Other) noexcept = delete;

	void LevelChangeStart(std::string_view _Name);
	bool IntroOff = false;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	

private:
	std::string NextLevelName; 
	float DelayTime = 0.0f;
};

