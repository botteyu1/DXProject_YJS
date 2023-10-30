#pragma once
#include "Tab.h"
// Ό³Έν : 
class UIEditorTab : public Tab
{
public:
	// constrcuter destructer
	UIEditorTab();
	~UIEditorTab();

	// delete Function
	UIEditorTab(const UIEditorTab& _Other) = delete;
	UIEditorTab(UIEditorTab&& _Other) noexcept = delete;
	UIEditorTab& operator=(const UIEditorTab& _Other) = delete;
	UIEditorTab& operator=(UIEditorTab&& _Other) noexcept = delete;

	void Start();
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime);

protected:

private:
	int Select = 0;

	void SelectTabUpdate(class GameEngineLevel* _Level);

	std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> ObjectLoaded;
	std::vector<std::string> ObjectLoadedNamesString;
	std::vector<const char*> ObjectLoadedNames;

	std::set<int> SelectObjects;
	std::shared_ptr<GameEngineObject> LastSelectObject;

};

