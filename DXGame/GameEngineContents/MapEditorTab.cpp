#include "PreCompile.h"
#include "MapEditorTab.h"
#include "MapEditorLevel.h"
#include "ContentObject.h"

MapEditorTab::MapEditorTab() 
{
}

MapEditorTab::~MapEditorTab()
{
}

void MapEditorTab::Start()
{
	static bool Init = true;
	if (Init == true)
	{
		Init = false;
		ObjectCreateNames.push_back("Player");
		ObjectCreateNames.push_back("Ghost_Man1");
		ObjectCreateNames.push_back("Ghost_Man2");
		ObjectCreateNames.push_back("Ghost_Man3");
		ObjectCreateNames.push_back("Ghost_Woman1");
		ObjectCreateNames.push_back("Ghost_Woman2");
		ObjectCreateNames.push_back("Ghost_Woman3");
		ObjectCreateNames.push_back("Ghost_Med1");
		ObjectCreateNames.push_back("Ghost_Med2");
		ObjectCreateNames.push_back("Ghost_Med3");
		ObjectCreateNames.push_back("PossessedBook1");
		ObjectCreateNames.push_back("PossessedBook2");
		ObjectCreateNames.push_back("PossessedBook3");
		ObjectCreateNames.push_back("ElevatorStart");
		ObjectCreateNames.push_back("ElevatorStatic");
		ObjectCreateNames.push_back("ElevatorEnd");
	}

	Tabs.clear();
	Tabs.push_back("CreatTab");
	CurTab = Tabs[0];
	
	Tabs.push_back("SelectTab");
}

void MapEditorTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	
	MapEditorLevel* MapLevel = dynamic_cast<MapEditorLevel*>(_Level);

	if (nullptr == MapLevel)
	{
		return;
	}

	for (size_t i = 0; i < Tabs.size(); i++)
	{
		if (ImGui::Button(Tabs[i].c_str()))
		{
			CurTab = Tabs[i];
		}
		if (i < Tabs.size() - 1)
		{
			ImGui::SameLine();
		}
		
	}

	if (CurTab == "CreatTab")
	{
		CreateTapUpdate(MapLevel);
	}
		
	else if (CurTab == "SelectTab")
	{
		SelectTabUpdate(MapLevel);
	}

	// 선택된 오브젝트 리스트

	ImGui::Text("\n\n\n -SelectList-");

	std::string SelectList;
	for (int Key : SelectObjects)
	{
		ImGui::Text(ObjectLoadedNamesString[Key].c_str());
		SelectList = "Position " + ObjectLoaded[Key]->Transform.GetLocalPosition().ToString() + "Scale  " +
			static_cast<ContentObject*>(ObjectLoaded[Key].get())->GetScaleValue().ToString()+ "\n";
		ImGui::Text(SelectList.c_str());
	}

	ImGui::GetFontSize();

	//save
	if (ImGui::Button("Save"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("Data");


		OPENFILENAMEA OFN;
		char filePathName[100] = "";
		char lpstrFile[100] = "";
		static char filter[] = "모든 파일\0*.*\0텍스트 파일\0*.txt\0fbx 파일\0*.fbx";

		std::string Path = Dir.GetStringPath();

		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = GameEngineCore::MainWindow.GetHWND();
		OFN.lpstrFilter = filter;
		OFN.lpstrFile = lpstrFile;
		OFN.nMaxFile = 100;
		OFN.lpstrDefExt = "GameData";
		OFN.lpstrInitialDir = Path.c_str();

		if (GetSaveFileNameA(&OFN) != 0) {
			SavePath = OFN.lpstrFile;
		}

		
		{
			GameEngineSerializer BinSer;

			MapLevel->Serializer(BinSer);
			GameEngineFile File = SavePath;
			File.Open(FileOpenType::Write, FileDataType::Binary);
			File.Write(BinSer);
		}

	}

	if ("" != SavePath)
	{
		ImGui::Text(SavePath.c_str());
	}


	////load
	if (ImGui::Button("Load"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("Data");


		OPENFILENAMEA OFN;
		char filePathName[100] = "";
		char lpstrFile[100] = "";
		static char filter[] = "모든 파일\0*.*\0텍스트 파일\0*.txt\0fbx 파일\0*.fbx";

		std::string Path = Dir.GetStringPath();

		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = GameEngineCore::MainWindow.GetHWND();
		OFN.lpstrFilter = filter;
		OFN.lpstrFile = lpstrFile;
		OFN.nMaxFile = 100;
		OFN.lpstrDefExt = "GameData";
		OFN.lpstrInitialDir = Path.c_str();

		if (GetOpenFileNameA(&OFN) != 0) {
			LoadPath = OFN.lpstrFile;
		}

		{
			GameEngineSerializer BinSer;

			GameEngineFile File = LoadPath;
			File.Open(FileOpenType::Read, FileDataType::Binary);
			File.DataAllRead(BinSer);

			MapLevel->ClearContentsObject();

			MapLevel->DeSerializer(BinSer, true);

			//std::vector<std::shared_ptr<Monster>> ObjectType = _Level->GetObjectGroupConvert<Monster>(ContentsObjectType::Monster);
			//for (size_t i = 0; i < ObjectType.size(); i++)
			//{
			//	// 다 죽인다.
			//	ObjectType[i]->Death();
			//}


			//std::string BackFileName;
			//BinSer >> BackFileName;
			//unsigned int MonsterCount = 0;
			//BinSer >> MonsterCount;

			//for (size_t i = 0; i < MonsterCount; i++)
			//{
			//	std::shared_ptr<Monster> Object = _Level->CreateActor<Monster>(ContentsObjectType::Monster);
			//	Object->DeSerializer(BinSer);
			//}
		}
	}

	if (LoadPath != "")
	{
		ImGui::Text(LoadPath.c_str());
	}
}

void MapEditorTab::CreateTapUpdate(MapEditorLevel* _Level)
{
	if (ImGui::ListBox("ObjectList", &Select, &ObjectCreateNames[0], static_cast<int>(ObjectCreateNames.size())))
	{
		float4 Pos = _Level->GetMainCamera()->Transform.GetLocalPosition();

		Pos.Z = 0.0f;

		std::shared_ptr<ContentObject> Object = _Level->AddActor(static_cast<ActorType>(Select), Pos, true);

		ObjectLoaded.push_back(Object);
		ObjectReload();

		Select = ObjectLoaded.size() - 1;
		SelectObjects.insert(Select);
		static_cast<ContentObject*>(ObjectLoaded[Select].get())->DebugValue = true;
	}
}

void MapEditorTab::ObjectReload()
{
	ObjectLoadedNamesString.clear();

	ObjectLoadedNames.clear();

	for (size_t i = 0; i < ObjectLoaded.size(); i++)
	{
		std::string str = ObjectLoaded[i]->GetName();
		ObjectLoadedNamesString.push_back(str);
	}

	for (size_t i = 0; i < ObjectLoadedNamesString.size(); i++)
	{
		std::string& str2 = ObjectLoadedNamesString[i];
		ObjectLoadedNames.push_back(str2.c_str());
	}
}

void MapEditorTab::SelectTabUpdate(MapEditorLevel* _Level)
{
	if (ImGui::Button("Object Reload"))
	{
		std::vector<std::shared_ptr<ContentObject>> ObjectTypePlayer = _Level->GetObjectGroupConvert<ContentObject>(ContentsObjectType::Player);
		std::vector<std::shared_ptr<ContentObject>> ObjectTypeStageObject = _Level->GetObjectGroupConvert<ContentObject>(ContentsObjectType::StageObject);
		std::vector<std::shared_ptr<ContentObject>> ObjectTypeEnemy = _Level->GetObjectGroupConvert<ContentObject>(ContentsObjectType::Enemy);
		std::vector<std::shared_ptr<ContentObject>> ObjectTypeBackGroundobject = _Level->GetObjectGroupConvert<ContentObject>(ContentsObjectType::BackGroundobject);

		//리로드 할 때 선택되어있던 오브젝트 디버그 모드 해제
		for (int Key : SelectObjects)
		{
			std::shared_ptr<ContentObject> Object = ObjectLoaded[Key];
			Object->DebugValue = false;
		}

		SelectObjects.clear();

		ObjectLoaded.clear();


		for (size_t i = 0; i < ObjectTypePlayer.size(); i++)
		{
			ObjectLoaded.push_back(ObjectTypePlayer[i]);
		}

		for (size_t i = 0; i < ObjectTypeStageObject.size(); i++)
		{
			ObjectLoaded.push_back(ObjectTypeStageObject[i]);
		}

		for (size_t i = 0; i < ObjectTypeEnemy.size(); i++)
		{
			ObjectLoaded.push_back(ObjectTypeEnemy[i]);
		}

		for (size_t i = 0; i < ObjectTypeBackGroundobject.size(); i++)
		{
			ObjectLoaded.push_back(ObjectTypeBackGroundobject[i]);
		}

		ObjectReload();
	}

	if (ObjectLoaded.size())
	{
		if (ImGui::ListBox("ObjectList", &Select, &ObjectLoadedNames[0], static_cast<int>(ObjectLoadedNames.size())))
		{
			if (SelectObjects.contains(Select))
			{
				SelectObjects.erase(Select);
				static_cast<ContentObject*>(ObjectLoaded[Select].get())->DebugValue = false;
			}
			else
			{
				SelectObjects.insert(Select);
				static_cast<ContentObject*>(ObjectLoaded[Select].get())->DebugValue = true;
			}
		}
	}
}
