#pragma once
#include "Level.h"
#include <GameEngineCore/GameEngineState.h>

enum class BossLevelState
{
	Normal,
	IntroCamera,
	Intro,
	Boss,
	End,
};

// 설명 :
class BossLevel : public Level
{
public:
	// constrcuter destructer
	BossLevel();
	~BossLevel();

	// delete Function
	BossLevel(const BossLevel& _Other) = delete;
	BossLevel(BossLevel&& _Other) noexcept = delete;
	BossLevel& operator=(const BossLevel& _Other) = delete;
	BossLevel& operator=(BossLevel&& _Other) noexcept = delete;

protected:
	void Start() override;

	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	bool BossIntroOver = false; // 보스 등장씬이 시작했는 지 여부

	std::shared_ptr<class Player> PlayerPtr = nullptr;
	std::shared_ptr<class BossGargoyle> BossPtr = nullptr;
	std::shared_ptr<class PlayUI> PlayUIPtr = nullptr;
	GameEngineState State;
};

