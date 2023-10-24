#pragma once

// Ό³Έν :
class Tab
{
public:
	// constrcuter destructer
	Tab();
	~Tab();

	std::string Name;
	int Index;

	virtual void Start() {}
	virtual void OnGUI(GameEngineLevel* _Level, float _DeltaTime) = 0;

	Tab(std::string_view _Name)
	{
		Name = _Name;
	}

protected:

private:

};

