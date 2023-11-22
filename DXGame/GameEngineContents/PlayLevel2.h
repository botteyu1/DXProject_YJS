#pragma once
#include "Level.h"
#include "PlayLevel.h"
#include <GameEngineCore/GameEngineState.h>



// 설명 :

class PlayLevel2 : public Level
{
public:
	// constrcuter destructer
	PlayLevel2();
	~PlayLevel2();

	// delete Function
	PlayLevel2(const PlayLevel2& _Other) = delete;
	PlayLevel2(PlayLevel2&& _Other) noexcept = delete;
	PlayLevel2& operator=(const PlayLevel2& _Other) = delete;
	PlayLevel2& operator=(PlayLevel2&& _Other) noexcept = delete;

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

