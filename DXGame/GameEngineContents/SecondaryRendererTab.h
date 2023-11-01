#pragma once
#include "Tab.h"

class SecondaryRendererTab : public Tab
{
public:
	// constrcuter destructer
	SecondaryRendererTab();
	~SecondaryRendererTab();

	// delete Function
	SecondaryRendererTab(const SecondaryRendererTab& _Other) = delete;
	SecondaryRendererTab(SecondaryRendererTab&& _Other) noexcept = delete;
	SecondaryRendererTab& operator=(const SecondaryRendererTab& _Other) = delete;
	SecondaryRendererTab& operator=(SecondaryRendererTab&& _Other) noexcept = delete;
	void Start();

	void OnGUI(GameEngineLevel* _Level, float _DeltaTime);
	SecondaryRendererTab(std::string_view _Name)
		: Tab(_Name)
	{

	}

protected:

private:
	int Select = 0;

	void SelectTabUpdate(class GameEngineLevel* _Level);

	std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> ObjectLoaded;
	std::vector<std::string> ObjectLoadedNamesString;
	std::vector<const char*> ObjectLoadedNames;

	std::set<int> SelectObjects;
	std::shared_ptr<GameEngineSpriteRenderer> LastSelectObject;
};

