#pragma once
#include "Level.h"
#include "PlayLevel.h"
#include <GameEngineCore/GameEngineState.h>



// ���� :

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

	bool GimmickValue = false; //����� ����ǰ� ����� Ʈ�� ī�޶� üũ��
	bool Gimmick2Value = false; //����� ����ǰ� ����� Ʈ�� ���� 2���� ��ȯ��

	GameEngineState State;
};

