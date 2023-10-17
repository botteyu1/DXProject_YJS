#pragma once

#include <GameEngineCore/GameEngineGUI.h>

// ���� :
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
	int Select = 0;

	std::vector<std::shared_ptr<GameEngineObject>> ObjectLoaded;
	std::vector<const char*> ObjectLoadedNames;
	std::vector<std::string> ObjectLoadedNamesString;

	std::set<int> SelectObjects;

	void Start() override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;  //���� ������ �־��ش�.

protected:

private:

};

