#include "PreCompile.h"
#include "UIEditorTab.h"
#include "UI.h"

UIEditorTab::UIEditorTab() 
{
}

UIEditorTab::~UIEditorTab()
{
}

void UIEditorTab::Start()
{
}

void UIEditorTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	
}

void UIEditorTab::SelectTabUpdate(GameEngineLevel* _Level)
{
	ImGui::Text("\n\n -SelectTab-");

	if (ImGui::Button("Object Reload"))
	{
		std::vector<std::shared_ptr<UI>> ObjectUI = _Level->GetObjectGroupConvert<UI>(ContentsObjectType::UI);

		ObjectLoaded.clear();

		for (size_t i = 0; i < ObjectUI.size(); i++)
		{

			std::vector<std::shared_ptr<GameEngineSpriteRenderer>> RenderertUI = ObjectLoaded[i]->GetObjectGroupConvert<GameEngineSpriteRenderer>(ContentsRenderType::UI);

			for (size_t i = 0; i < RenderertUI.size(); i++)
			{
				if (RenderertUI[i]->GetName() != "")
				{
					ObjectLoaded.push_back(RenderertUI[i]);
				}
			}
		}

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

	if (ObjectLoaded.size())
	{
		if (ImGui::ListBox("ObjectList", &Select, &ObjectLoadedNames[0], static_cast<int>(ObjectLoadedNames.size())))
		{
			if (SelectObjects.contains(Select))
			{
				SelectObjects.erase(Select);
				//static_cast<GameEngineSpriteRenderer*>(ObjectLoaded[Select].get())->SelectValue = false;
			}
			else
			{
				SelectObjects.insert(Select);
				//static_cast<GameEngineSpriteRenderer*>(ObjectLoaded[Select].get())->SelectValue = true;
			}
		}


	}
}

