#pragma once
#include "ContentObject.h"
//Ό³Έν

class BGObject : public ContentObject
{
public:
	// constrcuter destructer
	BGObject();
	~BGObject();

	// delete Function
	BGObject(const BGObject& _Other) = delete;
	BGObject(BGObject&& _Other) noexcept = delete;
	BGObject& operator=(const BGObject& _Other) = delete;
	BGObject& operator=(BGObject&& _Other) noexcept = delete;

	void Init(std::string _Name, bool _Animation = false);

protected:
	void Start() override;
	void Update(float _Delta) override;


private:

};

