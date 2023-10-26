#include "PreCompile.h"
#include "LevelChangeTab.h"

LevelChangeTab::LevelChangeTab() 
{
}

LevelChangeTab::~LevelChangeTab()
{
}


void LevelChangeTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (ImGui::Button("Collision OnOff"))
	{
		GameEngineLevel::IsDebug = !GameEngineLevel::IsDebug;
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