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

};

