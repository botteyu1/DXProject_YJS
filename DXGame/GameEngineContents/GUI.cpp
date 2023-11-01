#include "PreCompile.h"
#include "GUI.h"
#include "ContentObject.h"
#include "LevelChangeTab.h"
#include "MapEditorTab.h"
#include "Tab.h"
#include "UIEditorTab.h"
#include "ShaderTab.h"
#include "SecondaryRendererTab.h"

GUI::GUI() 
{
}

GUI::~GUI()
{
	
}



void GUI::Start()
{
	Tabs.push_back(std::make_shared<LevelChangeTab>("DebugTab"));
	CurTab = Tabs[0];
	CurTab->Start();
	Tabs.push_back(std::make_shared<MapEditorTab>("MapEditor"));
	Tabs.push_back(std::make_shared<UIEditorTab>("UITab"));
	Tabs.push_back(std::make_shared<ShaderTab>("ShaderTab"));
	Tabs.push_back(std::make_shared<SecondaryRendererTab>("SecondaryRendererTab"));
}

void GUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	std::string Frame = std::to_string(1.0f / _DeltaTime);

	ImGui::Text(Frame.c_str());

	std::string CameraPos = _Level->GetMainCamera()->Transform.GetWorldPosition().ToString();

	ImGui::Text(CameraPos.c_str());

	// ���� UI ���� UI �ø�������� ��ø��������
	for (size_t i = 0; i < Tabs.size(); i++)
	{
		if (i != 0)
		{
			ImGui::SameLine();
		}
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
	


	//std::string MousePos = GameEngineCore::MainWindow.GetMousePos().ToString();

	//ImGui::Text(MousePos.c_str());
	
	/*if (ImGui::Button("Collision OnOff"))
	{
		GameEngineLevel::IsDebug = !GameEngineLevel::IsDebug;
	}*/


}