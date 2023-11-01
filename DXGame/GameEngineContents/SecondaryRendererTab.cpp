#include "PreCompile.h"
#include "SecondaryRendererTab.h"
#include "SecondaryRenderer.h"
#include "ContentObject.h"

SecondaryRendererTab::SecondaryRendererTab() 
{
}

SecondaryRendererTab::~SecondaryRendererTab()
{
}

void SecondaryRendererTab::Start()
{
}

void SecondaryRendererTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	SelectTabUpdate(_Level);
	GameEngineInput::AddInputObject(this);

	ImGui::Text("\n\n -SelectList-");

	std::string SelectList;
	for (int Key : SelectObjects)
	{
		ImGui::Text(ObjectLoadedNamesString[Key].c_str());
		SelectList = "Position " + ObjectLoaded[Key]->Transform.GetLocalPosition().ToString() + "Scale  " + "\n";
		ImGui::Text(SelectList.c_str());
	}
}

void SecondaryRendererTab::SelectTabUpdate(GameEngineLevel* _Level)
{
	ImGui::Text("\n\n -SelectTab-");

	if (ImGui::Button("Object Reload"))
	{
		std::vector<std::shared_ptr<GameEngineActor>> ObjectUI = _Level->GetObjectGroupConvert<GameEngineActor>(ContentsObjectType::Player);
		std::vector<std::shared_ptr<GameEngineActor>> ObjectGlobalShader = _Level->GetObjectGroupConvert<GameEngineActor>(ContentsObjectType::Shader);

		ObjectLoaded.clear();

		for (size_t i = 0; i < ObjectUI.size(); i++)
		{
			std::vector<std::shared_ptr<GameEngineSpriteRenderer>> RenderertUI = ObjectUI[i]->GetObjectGroupConvert<GameEngineSpriteRenderer>(ContentsRenderType::SecondaryRenderer);

			for (size_t i = 0; i < RenderertUI.size(); i++)
			{
				if (RenderertUI[i]->GetName() != "")
				{
					ObjectLoaded.push_back(RenderertUI[i]);
				}
			}
			RenderertUI = ObjectUI[i]->GetObjectGroupConvert<GameEngineSpriteRenderer>(ContentsRenderType::Shader);

			for (size_t i = 0; i < RenderertUI.size(); i++)
			{
				if (RenderertUI[i]->GetName() != "")
				{
					ObjectLoaded.push_back(RenderertUI[i]);
				}
			}
		}

		for (size_t i = 0; i < ObjectGlobalShader.size(); i++)
		{
			std::vector<std::shared_ptr<GameEngineSpriteRenderer>> RenderertUI = ObjectGlobalShader[i]->GetObjectGroupConvert<GameEngineSpriteRenderer>(ContentsRenderType::Shader);

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

	for (int Key : SelectObjects)
	{
		ImGui::SliderFloat4(ObjectLoadedNames[Key], &ObjectLoaded[Key]->GetColorData().MulColor.R, 0.0f, 1.0f, "%.2f");
		
	}
}


