#include "PreCompile.h"
#include "LevelChangeTab.h"
#include "Shader.h"

LevelChangeTab::LevelChangeTab() 
{
}

LevelChangeTab::~LevelChangeTab()
{
}


void LevelChangeTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ImGui::Text("\n-Manual-\n");
	ImGui::Text("Move: WASD \nJump: Space \nShift: Dash\n\nLB: ComboAtt\nLB+W:JumpinhAtt\nLB+S+AirTime:DownAtt\n\nRB: CapeAtt\nMB: CapeAtt2\n1,2:CapeAtt3,4");
	
	if (ImGui::Button("Collision OnOff"))
	{
		GameEngineLevel::IsDebug = !GameEngineLevel::IsDebug;
		std::vector<std::shared_ptr<Shader>> ObjectGlobalShader = _Level->GetObjectGroupConvert<Shader>(ContentsObjectType::Shader);
		if (GameEngineLevel::IsDebug == true)
		{
			for (size_t i = 0; i < ObjectGlobalShader.size(); i++)
			{
				ObjectGlobalShader[i]->GetGlobalShader()->Off();
			}
		}
		else
		{
			for (size_t i = 0; i < ObjectGlobalShader.size(); i++)
			{
				ObjectGlobalShader[i]->GetGlobalShader()->On();
			}
		}
	}



	std::map<std::string, std::shared_ptr<GameEngineLevel>>& AllLevels = GameEngineCore::GetAllLevel();

	for (std::pair<const std::string, std::shared_ptr<GameEngineLevel>> Pair : AllLevels)
	{
		if (ImGui::Button(Pair.first.c_str()))
		{
			GameEngineCore::ChangeLevel(Pair.first);
		}
	}
}