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
	SelectTabUpdate(_Level);
	GameEngineInput::AddInputObject(this);

	ImGui::Text("\n\n -SelectList-");

	std::string SelectList;
	for (int Key : SelectObjects)
	{
		ImGui::Text(ObjectLoadedNamesString[Key].c_str());
		SelectList = "Position " + ObjectLoaded[Key]->Transform.GetLocalPosition().ToString() ;
		ImGui::Text(SelectList.c_str());
		ImGui::Text(ObjectLoadedNamesString[Key].c_str());
		SelectList = "Scale " + ObjectLoaded[Key]->GetImageTransform().GetLocalScale().ToString();
		ImGui::Text(SelectList.c_str());
	}
}

void UIEditorTab::SelectTabUpdate(GameEngineLevel* _Level)
{
	ImGui::Text("\n\n -SelectTab-");

	if (ImGui::Button("Object Reload"))
	{
		std::vector<std::shared_ptr<UI>> ObjectUI = _Level->GetObjectGroupConvert<UI>(ContentsObjectType::UI);
		//std::vector<std::shared_ptr<UI>> ObjectUIAfter = _Level->GetObjectGroupConvert<UI>(ContentsObjectType::);

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
			{
				std::vector<std::shared_ptr<GameEngineSpriteRenderer>> RenderertUI = ObjectUI[i]->GetObjectGroupConvert<GameEngineSpriteRenderer>(ContentsRenderType::UIAfter);

				for (size_t i = 0; i < RenderertUI.size(); i++)
				{
					if (RenderertUI[i]->GetName() != "")
					{
						ObjectLoaded.push_back(RenderertUI[i]);
					}
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
		if (GameEngineInput::IsPress(VK_LBUTTON, this) and static_cast<Level*>(_Level)->OtherWindow == false)
		{
			float4 Pos = _Level->GetMainCamera()->GetScreenMouseDir();
			//float4 PrevPos = Transform.GetLocalPosition();
			Pos.X = -Pos.X;
			ObjectLoaded[Key]->Transform.AddLocalPosition(Pos);
		}

		if (GameEngineInput::IsDown('C', this) and static_cast<Level*>(_Level)->OtherWindow == false)
		{
			
			ObjectLoaded[Key]->GetImageTransform().AddLocalScale(float4::ONE * -1.0f);
		}
		if (GameEngineInput::IsDown('V', this) and static_cast<Level*>(_Level)->OtherWindow == false)
		{
			ObjectLoaded[Key]->GetImageTransform().AddLocalScale(float4::ONE);
		}
		if (GameEngineInput::IsDown('Z', this) and static_cast<Level*>(_Level)->OtherWindow == false)
		{
			
			ObjectLoaded[Key]->GetImageTransform().AddLocalScale(float4::ONE * -10.0f);
		}
		if (GameEngineInput::IsDown('X', this) and static_cast<Level*>(_Level)->OtherWindow == false)
		{
			ObjectLoaded[Key]->GetImageTransform().AddLocalScale(float4::ONE * 10.0f);
		}
	}
}

