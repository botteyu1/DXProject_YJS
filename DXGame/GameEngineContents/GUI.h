#pragma once

#include <GameEngineCore/GameEngineGUI.h>
#include "Tab.h"

// 설명 :
class GUI : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	GUI();
	~GUI();

	// delete Function
	GUI(const GUI& _Other) = delete;
	GUI(GUI&& _Other) noexcept = delete;
	GUI& operator=(const GUI& _Other) = delete;
	GUI& operator=(GUI&& _Other) noexcept = delete;

public:

	std::shared_ptr<class Tab> CurTab = nullptr;
	std::vector<std::shared_ptr<class Tab>> Tabs;


	int Select = 0;




	void Start() override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;  //현재 레벨을 넣어준다.

protected:

private:

};

