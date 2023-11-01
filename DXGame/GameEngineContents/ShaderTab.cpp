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
	SelectTabUpdate(_Level);
	GameEngineInput::AddInputObject(this);
}

void ShaderTab::SelectTabUpdate(GameEngineLevel* _Level)
{
	ImGui::Text("\n\n -SelectTab-");

	if (ImGui::Button("Object Reload"))
	{
		std::vector<std::shared_ptr<Shader>> ObjectUI = _Level->GetObjectGroupConvert<Shader>(ContentsObjectType::Shader);

		ObjectLoaded.clear();

		for (size_t i = 0; i < ObjectUI.size(); i++)
		{

			if (ObjectUI[i]->GetName() != "")
			{
				ObjectLoaded.push_back(ObjectUI[i]);
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

	//if (LastSelectObject != nullptr)
	//{
	//	if (ImGui::SliderFloat4("Global Shader", &LastSelectObject->GetShader_Renderer()->GetColorData().MulColor.R, 0.0f, 1.0f, "%.2f"))
	//	{
	//		//SkyLerp::SkyManager->SetSkyColor();
	//	}
	//}
}

