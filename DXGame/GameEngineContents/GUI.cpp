#include "PreCompile.h"
#include "GUI.h"
#include "ContentObject.h"

GUI::GUI() 
{
}

GUI::~GUI()
{
}



void GUI::Start()
{

}

void GUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	std::string MousePos = GameEngineCore::MainWindow.GetMousePos().ToString();

	ImGui::Text(MousePos.c_str());
	
	if (ImGui::Button("Collision OnOff"))
	{
		GameEngineLevel::IsDebug = !GameEngineLevel::IsDebug;
	}

	if (ImGui::Button("Object Reload"))
	{
		std::list<std::shared_ptr<GameEngineObject>> ObjectListsEnemy = _Level->GetObjectGroup<ContentsObjectType>(ContentsObjectType::Enemy);
		std::list<std::shared_ptr<GameEngineObject>> ObjectListsStageObject = _Level->GetObjectGroup<ContentsObjectType>(ContentsObjectType::StageObject);
		std::list<std::shared_ptr<GameEngineObject>> ObjectListsBackGroundobject = _Level->GetObjectGroup<ContentsObjectType>(ContentsObjectType::BackGroundobject);
		std::list<std::shared_ptr<GameEngineObject>> ObjectListsPlayerObject = _Level->GetObjectGroup<ContentsObjectType>(ContentsObjectType::Player_object);

		for (int Key : SelectObjects)
		{
			static_cast<ContentObject*>(ObjectLoaded[Key].get())->DebugValue = false;
		}

		SelectObjects.clear();

		ObjectLoaded.clear();

		ObjectLoadedNamesString.clear();

		ObjectLoadedNames.clear();

	
		for (std::shared_ptr<GameEngineObject> Ptr : ObjectListsStageObject)
		{
			ObjectLoaded.push_back(Ptr);
		}
		for (std::shared_ptr<GameEngineObject> Ptr : ObjectListsBackGroundobject)
		{
			ObjectLoaded.push_back(Ptr);
		}
		
		for (std::shared_ptr<GameEngineObject> Ptr : ObjectListsPlayerObject)
		{
			ObjectLoaded.push_back(Ptr);
		}
		for (std::shared_ptr<GameEngineObject> Ptr : ObjectListsEnemy)
		{
			ObjectLoaded.push_back(Ptr);
		}

		for (std::shared_ptr<GameEngineObject> Ptr : ObjectLoaded)
		{
			std::string str = Ptr->GetName();
			ObjectLoadedNamesString.push_back(str);
		}
		for (size_t i = 0; i < ObjectLoadedNamesString.size(); i++)
		{
			std::string& str2 = ObjectLoadedNamesString[i];
			ObjectLoadedNames.push_back(str2.c_str());
		}

		/*int i = 0;
		for (std::shared_ptr<GameEngineObject> Ptr : ObjectLoaded)
		{
			std::string str = Ptr->GetName();
			ObjectLoadedNamesString.push_back(str);
			std::string& str2 = ObjectLoadedNamesString[i];
			ObjectLoadedNames.push_back(str2.c_str());
			i++;
		}*/
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


	ImGui::Text("\n\n\n -SelectList-");

	std::string SelectList;
	for (int Key : SelectObjects)
	{
		ImGui::Text(ObjectLoadedNamesString[Key].c_str());
		SelectList = "Position " + ObjectLoaded[Key]->Transform.GetLocalPosition().ToString() + "\nScale  " + 
			static_cast<ContentObject*>(ObjectLoaded[Key].get())->GetScaleValue().ToString();
		ImGui::Text(SelectList.c_str());
	}

	ImGui::GetFontSize();



}