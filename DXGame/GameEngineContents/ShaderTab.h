#pragma once
#include "Tab.h"
 
class ShaderTab : public Tab
{
public:
	// constrcuter destructer
	ShaderTab();
	~ShaderTab();

	// delete Function
	ShaderTab(const ShaderTab& _Other) = delete;
	ShaderTab(ShaderTab&& _Other) noexcept = delete;
	ShaderTab& operator=(const ShaderTab& _Other) = delete;
	ShaderTab& operator=(ShaderTab&& _Other) noexcept = delete;
	void Start();

	void OnGUI(GameEngineLevel* _Level, float _DeltaTime);

	ShaderTab(std::string_view _Name)
		: Tab(_Name)
	{

	}
protected:

private:
	int Select = 0;

	void SelectTabUpdate(class GameEngineLevel* _Level);

	std::vector<std::shared_ptr<class Shader>> ObjectLoaded;
	std::vector<std::string> ObjectLoadedNamesString;
	std::vector<const char*> ObjectLoadedNames;

	//std::set<int> SelectObjects;
	std::shared_ptr<Shader> LastSelectObject;

};

