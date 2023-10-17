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

		for (int Key : SelectObjects)
		{
			static_cast<ContentObject*>(ObjectLoaded[Key].get())->DebugValue = false;
		}

		SelectObjects.clear();

		ObjectLoaded.clear();

		ObjectLoadedNamesString;

		ObjectLoadedNames.clear();

		for (std::shared_ptr<GameEngineObject> Ptr : ObjectListsEnemy)
		{
			ObjectLoaded.push_back(Ptr);
		}
		for (std::shared_ptr<GameEngineObject> Ptr : ObjectListsStageObject)
		{
			ObjectLoaded.push_back(Ptr);
		}

		
		

		for (std::shared_ptr<GameEngineObject> Ptr : ObjectLoaded)
		{
			ObjectLoadedNamesString.push_back(Ptr->GetName());
			ObjectLoadedNames.push_back(ObjectLoadedNamesString.back().c_str());
		}
	}

	
	
	if (ObjectLoaded.size())
	{
		if (ImGui::ListBox("ObjectList", &Select, &ObjectLoadedNames[0], ObjectLoadedNames.size()))
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

		/*if (nullptr != SelectObject)
		{
			if (ImGui::Button("Select Object Off"))
			{
				SelectObject->Off();
			}
		}*/
	}


	ImGui::Text("\n\n\n -SelectList-");

	std::string SelectList;
	for (int Key : SelectObjects)
	{
		ImGui::Text(ObjectLoadedNamesString[Key].c_str());
	}
}