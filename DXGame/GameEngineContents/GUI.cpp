#include "PreCompile.h"
#include "GUI.h"
#include "ContentObject.h"
#include "LevelChangeTab.h"
#include "MapEditorTab.h"
#include "Tab.h"

GUI::GUI() 
{
}

GUI::~GUI()
{
	
}



void GUI::Start()
{
	Tabs.push_back(std::make_shared<LevelChangeTab>("LevelChangeTab"));
	CurTab = Tabs[0];
	CurTab->Start();
	Tabs.push_back(std::make_shared<MapEditorTab>("MapEditor"));
}

void GUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{

	// 생성 UI 편집 UI 시리얼라이저 디시리얼라이저
	for (size_t i = 0; i < Tabs.size(); i++)
	{
		ImGui::SameLine();
		if (ImGui::Button(Tabs[i]->Name.c_str()))
		{
			CurTab = Tabs[i];
			CurTab->Start();
		}
	}

	if (nullptr != CurTab)
	{
		CurTab->OnGUI(_Level, _DeltaTime);
	}


	/*std::string MousePos = GameEngineCore::MainWindow.GetMousePos().ToString();

	ImGui::Text(MousePos.c_str());*/
	
	/*if (ImGui::Button("Collision OnOff"))
	{
		GameEngineLevel::IsDebug = !GameEngineLevel::IsDebug;
	}*/


}