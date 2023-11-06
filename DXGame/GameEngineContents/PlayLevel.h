#pragma once
#include "Level.h"
#include <GameEngineCore/GameEngineState.h>

enum class PlayLevelState
{
	Normal,
	GimmickIntro,
	Gimmick,
	GimmickEndIntro,
	GimmickEnd,
};


// 설명 :
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
	bool CheckGimmickOver();


	std::shared_ptr<PlayMap> PlayMapPtr = nullptr;
	std::shared_ptr<class Player> PlayerPtr = nullptr;
	std::shared_ptr<class PlayUI> PlayUIPtr = nullptr;
	std::shared_ptr <class  WeaponDrop > WeaponDropObject = nullptr;

	bool GimmickValue = false; //기믹이 실행되고 나면면 트루 카메라 체크용
	bool Gimmick2Value = false; //기믹이 실행되고 나면면 트루 몬스터 2번쨰 소환용

	GameEngineState State;
	
};

