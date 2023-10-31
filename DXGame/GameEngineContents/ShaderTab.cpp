#include "PreCompile.h"
#include "ShaderTab.h"
#include "Shader.h"

ShaderTab::ShaderTab() 
{
}

ShaderTab::~ShaderTab()
{
}

void ShaderTab::Start()
{
}

void ShaderTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
}

void ShaderTab::SelectTabUpdate(GameEngineLevel* _Level)
{
	ImGui::Text("\n\n -SelectTab-");

	if (ImGui::Button("Object Reload"))
	{
		std::vector<std::shared_ptr<Shader>> ObjectUI = _Level->GetObjectGroupConvert<Shader>(ContentsObjectType::UI);

		ObjectLoaded.clear();

		for (size_t i = 0; i < ObjectUI.size(); i++)
		{

			std::vector<std::shared_ptr<GameEngineSpriteRenderer>> RenderertUI = ObjectUI[i]->GetObjectGroupConvert<GameEngineSpriteRenderer>(ContentsRenderType::UI);

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
			LastSelectObject = ObjectLoaded[Select];
		}
	}

	if (LastSelectObject != nullptr)
	{
		//float4ÄÃ·¯°ª
	}
}

