#pragma once
#include "Tab.h"
// 설명 :
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

	void SelectSetZPos(float _Pos);

	void SelectAddZPos(float _Pos);

	void SelectObjectClear(MapEditorLevel* _Level);
	void ObjectReload(MapEditorLevel* _Level);
	void ObjectNameReload();

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
	bool ReloadValue = false; //삭제완료후 리로드하기위한 밸류값

};
