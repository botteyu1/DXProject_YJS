#pragma once
#include "Tab.h"
// Ό³Έν :
class MapEditorTab : public Tab
{
public:
	// constrcuter destructer
	MapEditorTab();
	~MapEditorTab();

public:
	std::string DefSavePath;
	std::string SavePath;
	std::string LoadPath;
	std::string InputPath;

	void Start();
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime);

	std::string CurTab;
	std::vector<std::string> Tabs;

	void CreateTapUpdate(class MapEditorLevel* _Level);
	void SelectTabUpdate(MapEditorLevel* _Level);
	void ObjectReload();

	std::vector<const char*> ObjectCreateNames;

	std::vector<std::shared_ptr<class ContentObject>> ObjectLoaded;
	std::vector<std::string> ObjectLoadedNamesString;
	std::vector<const char*> ObjectLoadedNames;

	std::set<int> SelectObjects;
	std::shared_ptr<GameEngineObject> LastSelectObject;
	
public:
	MapEditorTab(std::string_view _Name)
		: Tab(_Name)
	{

	}
	int Select = 0;

protected:


private:

};
