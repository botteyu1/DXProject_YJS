#include "PreCompile.h"
#include "MapEditorTab.h"
#include "MapEditorLevel.h"
#include "ContentObject.h"
#include "UIEditorTab.h"

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


		//배경오브젝트 

		ObjectCreateNames.push_back("BackWall_Big");
		ObjectCreateNames.push_back("BackWall_Down");
		ObjectCreateNames.push_back("BackWall_LeftT");
		ObjectCreateNames.push_back("BackWall_LeftT_A");
		ObjectCreateNames.push_back("BackWall_Middle");
		ObjectCreateNames.push_back("BackWall_Window");
		ObjectCreateNames.push_back("BackWall_Window05");
		ObjectCreateNames.push_back("BossDesk");
		ObjectCreateNames.push_back("coloneComplete");
		ObjectCreateNames.push_back("Colonnade02");
		ObjectCreateNames.push_back("Column01B");
		ObjectCreateNames.push_back("Column04");
		ObjectCreateNames.push_back("Column05");
		ObjectCreateNames.push_back("ColumnDown01");
		ObjectCreateNames.push_back("Desk");
		ObjectCreateNames.push_back("Desk01");
		ObjectCreateNames.push_back("Desk1");
		ObjectCreateNames.push_back("Desk2");
		ObjectCreateNames.push_back("Desk2_NoScreen");
		ObjectCreateNames.push_back("Desk3");
		ObjectCreateNames.push_back("Desk3_NoScreen");
		ObjectCreateNames.push_back("Escalator_02");
		ObjectCreateNames.push_back("Escalator_09");
		ObjectCreateNames.push_back("Escalator_Frieze");
		ObjectCreateNames.push_back("GhostWorkersBox1");
		ObjectCreateNames.push_back("GhostWorkersBox2");
		ObjectCreateNames.push_back("GhostWorkersBox3");
		ObjectCreateNames.push_back("GhostWorkersBox11");
		ObjectCreateNames.push_back("GhostWorkersBox22");
		ObjectCreateNames.push_back("GPE_DifficultyMode_Wall");
		ObjectCreateNames.push_back("GPE_Paper_Piles_Line");
		ObjectCreateNames.push_back("lamp2");
		ObjectCreateNames.push_back("lamp3");
		ObjectCreateNames.push_back("lamp4");
		ObjectCreateNames.push_back("OfficeCabinet2");
		ObjectCreateNames.push_back("OfficeCabinet3");
		ObjectCreateNames.push_back("OfficeCabinet4");
		ObjectCreateNames.push_back("PipeFrieze2");
		ObjectCreateNames.push_back("Rock_01");
		ObjectCreateNames.push_back("Rock_03");
		ObjectCreateNames.push_back("Rock_04");
		ObjectCreateNames.push_back("Rock01");
		ObjectCreateNames.push_back("Rock02");
		ObjectCreateNames.push_back("Rock2");
		ObjectCreateNames.push_back("Rock03");
		ObjectCreateNames.push_back("Rock3");
		ObjectCreateNames.push_back("Rock04");
		ObjectCreateNames.push_back("RockBG01");
		ObjectCreateNames.push_back("RockBG02");
		ObjectCreateNames.push_back("RockBG03");
		ObjectCreateNames.push_back("RockBG04");
		ObjectCreateNames.push_back("RockBG05");
		ObjectCreateNames.push_back("RockBG05_bis");
		ObjectCreateNames.push_back("RockIntegrationElements");
		ObjectCreateNames.push_back("RockIntegrationElements02");
		ObjectCreateNames.push_back("RockIntegrationElements03t");
		ObjectCreateNames.push_back("VerticalDeskCube");
		ObjectCreateNames.push_back("VerticalDeskCubeBack");
		ObjectCreateNames.push_back("Bibli_Raw_Kit");
		ObjectCreateNames.push_back("Bibli_WIP_02");
		ObjectCreateNames.push_back("GraphicStats01");
		ObjectCreateNames.push_back("GPE_WeaponX_Choice");
		ObjectCreateNames.push_back("Column02");
		ObjectCreateNames.push_back("Column03");
		ObjectCreateNames.push_back("Column06");
		ObjectCreateNames.push_back("Cutton");
		ObjectCreateNames.push_back("Church");
		ObjectCreateNames.push_back("Pillar01");
		ObjectCreateNames.push_back("Pillar02");
		ObjectCreateNames.push_back("Pillar04");
		ObjectCreateNames.push_back("Pillar05");
		ObjectCreateNames.push_back("woker1");
		ObjectCreateNames.push_back("woker2");
		ObjectCreateNames.push_back("woker3");
		ObjectCreateNames.push_back("woker4");
		ObjectCreateNames.push_back("woker5");
		ObjectCreateNames.push_back("woker6");
		ObjectCreateNames.push_back("woker7");
		ObjectCreateNames.push_back("woker8");
		ObjectCreateNames.push_back("woker9");
		ObjectCreateNames.push_back("Scythe1");
		ObjectCreateNames.push_back("Scythe2");
		ObjectCreateNames.push_back("Scythe3");
		ObjectCreateNames.push_back("Scythe4");
		ObjectCreateNames.push_back("ColumnDown02");

		ObjectCreateNames.push_back("Bathc_Of_Graves_01");
		ObjectCreateNames.push_back("Bathc_Of_Graves_02");
		ObjectCreateNames.push_back("Bench01");
		ObjectCreateNames.push_back("Bench02");
		ObjectCreateNames.push_back("Bench03");
		ObjectCreateNames.push_back("BonesPile1");
		ObjectCreateNames.push_back("BonesPile4");
		ObjectCreateNames.push_back("W1_Boss");
		ObjectCreateNames.push_back("W1_Door_01");
		ObjectCreateNames.push_back("W1_Door_02");
		ObjectCreateNames.push_back("W1_Door_03");
		ObjectCreateNames.push_back("W1_Door_04");
		ObjectCreateNames.push_back("W1_Door_05");
		ObjectCreateNames.push_back("W1_Door_06");
		ObjectCreateNames.push_back("W1_Entre");
		ObjectCreateNames.push_back("W1_Kit_");
		ObjectCreateNames.push_back("W1_Miniboss");

		ObjectCreateNames.push_back("WeaponDrop1");
		ObjectCreateNames.push_back("WeaponDrop2");
		ObjectCreateNames.push_back("WeaponDrop3");
		ObjectCreateNames.push_back("PaperWall");
		ObjectCreateNames.push_back("Contractor");



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

	ImGui::Text("\n\n -SelectList-");

	std::string SelectList;
	for (int Key : SelectObjects)
	{
		ImGui::Text(ObjectLoadedNamesString[Key].c_str());
		SelectList = "Position " + ObjectLoaded[Key]->Transform.GetLocalPosition().ToString() + "Scale  " +
			static_cast<ContentObject*>(ObjectLoaded[Key].get())->GetScaleValue().ToString()+ "\n";
		ImGui::Text(SelectList.c_str());
	}

	ImGui::Text("\n\n -Control-");

	if (ImGui::Button("Copy"))
	{
		for (int Key : SelectObjects)
		{
			std::shared_ptr<ContentObject> Object = MapLevel->CopyObject(ObjectLoaded[Key]);

			/*ObjectLoaded.push_back(Object);
			ObjectNameReload();

			Select = static_cast<int>(ObjectLoaded.size()) - 1;
			SelectObjects.insert(Select);
			static_cast<ContentObject*>(ObjectLoaded[Select].get())->DebugValue = true;*/
		}
		
	}

	if (ImGui::Button("30Z"))
	{
		SelectSetZPos(30.0f);
	}
	ImGui::SameLine();
	
	if (ImGui::Button("50Z"))
	{
		SelectSetZPos(50.0f);
	}
	ImGui::SameLine();

	if (ImGui::Button("70Z"))
	{
		SelectSetZPos(70.0f);
	}
	
	
	if (ImGui::Button("Z--"))
	{
		SelectAddZPos(-1.0f);
	}

	ImGui::SameLine();

	if (ImGui::Button("Z++"))
	{
		SelectAddZPos(1.0f);
	}

	if (ImGui::Button("RightFlip"))
	{
		for (int Key : SelectObjects)
		{
			ObjectLoaded[Key]->RightFlip();

		}
	}
	ImGui::SameLine();
	if(ImGui::Button("LeftFlip"))
	{
		for (int Key : SelectObjects)
		{
			ObjectLoaded[Key]->LeftFlip();
		}
	}

	

	if (ImGui::Button("SelectDelete"))
	{
		SelectObjectClear(MapLevel);
	}

	//ImGui::GetFontSize();


	
	MapLevel->OtherWindow = false;


	ImGui::Text("\n\n -Input/Output-");

	//save
	if (ImGui::Button("Save"))
	{

		MapLevel->OtherWindow = true;
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

		if ("" != SavePath)
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
		MapLevel->OtherWindow = true;

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

		if(LoadPath != "")
		{
			GameEngineSerializer BinSer;

			GameEngineFile File = LoadPath;
			File.Open(FileOpenType::Read, FileDataType::Binary);
			File.DataAllRead(BinSer);

			MapLevel->ClearContentsObject();

			MapLevel->DeSerializer(BinSer, true);
			ReloadValue = true;
		}
	}

	if (LoadPath != "")
	{
		ImGui::Text(LoadPath.c_str());
	}
}

void MapEditorTab::CreateTapUpdate(MapEditorLevel* _Level)
{

	ImGui::Text("\n\n -CreateTab-");
	if (ImGui::ListBox("ObjectList", &Select, &ObjectCreateNames[0], static_cast<int>(ObjectCreateNames.size())))
	{
		float4 Pos = _Level->GetMainCamera()->Transform.GetLocalPosition();

		Pos.Z = 0.0f;

		std::shared_ptr<ContentObject> Object = _Level->AddActor(static_cast<ActorType>(Select), Pos, float4::ZERONULL, false,  true);

		for (int Key : SelectObjects)
		{
			std::shared_ptr<ContentObject> Object = ObjectLoaded[Key];
			Object->SelectValue = false;
		}

		SelectObjects.clear();

		ObjectLoaded.push_back(Object);
		ObjectNameReload();

		Select = static_cast<int>(ObjectLoaded.size()) - 1;
		SelectObjects.insert(Select);
		static_cast<ContentObject*>(ObjectLoaded[Select].get())->SelectValue = true;
	}
}

void MapEditorTab::ObjectReload(MapEditorLevel* _Level)
{
	ReloadValue = false;

	std::vector<std::shared_ptr<ContentObject>> ObjectTypePlayer = _Level->GetObjectGroupConvert<ContentObject>(ContentsObjectType::Player);
	std::vector<std::shared_ptr<ContentObject>> ObjectTypeStageObject = _Level->GetObjectGroupConvert<ContentObject>(ContentsObjectType::StageObject);
	std::vector<std::shared_ptr<ContentObject>> ObjectTypeEnemy = _Level->GetObjectGroupConvert<ContentObject>(ContentsObjectType::Enemy);
	std::vector<std::shared_ptr<ContentObject>> ObjectTypeBackGroundobject = _Level->GetObjectGroupConvert<ContentObject>(ContentsObjectType::BackGroundobject);

	//리로드 할 때 선택되어있던 오브젝트 디버그 모드 해제
	for (int Key : SelectObjects)
	{
		std::shared_ptr<ContentObject> Object = ObjectLoaded[Key];
		Object->SelectValue = false;
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

	ObjectNameReload();
	
}

void MapEditorTab::ObjectNameReload()
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

void MapEditorTab::SelectObjectClear(MapEditorLevel* _Level)
{
	for (int Key : SelectObjects)
	{
		ObjectLoaded[Key]->Death();
	}
	
	ReloadValue = true;

	//std::vector<std::shared_ptr<ContentObject>> ObjectTypePlayer = _Level->GetObjectGroupConvert<ContentObject>(ContentsObjectType::Player);
	//std::vector<std::shared_ptr<ContentObject>> ObjectTypeStageObject = _Level->GetObjectGroupConvert<ContentObject>(ContentsObjectType::StageObject);
	//std::vector<std::shared_ptr<ContentObject>> ObjectTypeEnemy = _Level->GetObjectGroupConvert<ContentObject>(ContentsObjectType::Enemy);
	//std::vector<std::shared_ptr<ContentObject>> ObjectTypeBackGroundobject = _Level->GetObjectGroupConvert<ContentObject>(ContentsObjectType::BackGroundobject);

	////리로드 할 때 선택되어있던 오브젝트 디버그 모드 해제

	//SelectObjects.clear();

	//ObjectLoaded.clear();


	//for (size_t i = 0; i < ObjectTypePlayer.size(); i++)
	//{
	//	ObjectLoaded.push_back(ObjectTypePlayer[i]);
	//}

	//for (size_t i = 0; i < ObjectTypeStageObject.size(); i++)
	//{
	//	ObjectLoaded.push_back(ObjectTypeStageObject[i]);
	//}

	//for (size_t i = 0; i < ObjectTypeEnemy.size(); i++)
	//{
	//	ObjectLoaded.push_back(ObjectTypeEnemy[i]);
	//}

	//for (size_t i = 0; i < ObjectTypeBackGroundobject.size(); i++)
	//{
	//	ObjectLoaded.push_back(ObjectTypeBackGroundobject[i]);
	//}

	//ObjectReload();
}

void MapEditorTab::SelectTabUpdate(MapEditorLevel* _Level)
{

	ImGui::Text("\n\n -SelectTab-");

	if (ImGui::Button("Object Reload") or ReloadValue == true)
	{
		ObjectReload(_Level);
	}
	ImGui::SameLine();

	if (ImGui::Button("All Select"))
	{
		for (int i = 0; i < ObjectLoaded.size(); i++)
		{
			SelectObjects.insert(i);
			static_cast<ContentObject*>(ObjectLoaded[i].get())->SelectValue = true;
		}
	}



	if (ObjectLoaded.size())
	{
		if (ImGui::ListBox("ObjectList", &Select, &ObjectLoadedNames[0], static_cast<int>(ObjectLoadedNames.size())))
		{
			if (SelectObjects.contains(Select))
			{
				SelectObjects.erase(Select);
				static_cast<ContentObject*>(ObjectLoaded[Select].get())->SelectValue = false;
			}
			else
			{
				SelectObjects.insert(Select);
				static_cast<ContentObject*>(ObjectLoaded[Select].get())->SelectValue = true;
			}
		}


	}
}

void MapEditorTab::SelectSetZPos(float _Pos)
{
	for (int Key : SelectObjects)
	{

		float4 Pos = ObjectLoaded[Key]->Transform.GetLocalPosition();
		Pos.Z = _Pos;
		ObjectLoaded[Key]->Transform.SetLocalPosition(Pos);
		
	}
}

void MapEditorTab::SelectAddZPos(float _Pos)
{
	for (int Key : SelectObjects)
	{

		ObjectLoaded[Key]->Transform.AddLocalPosition({0.0f,0.0f,_Pos});
		
	}
}




