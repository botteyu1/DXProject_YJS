#pragma once
#include "StageObject.h"



class AnimaDrop : public StageObject
{
public:
	// constrcuter destructer
	AnimaDrop();
	~AnimaDrop();

	// delete Function
	AnimaDrop(const AnimaDrop& _Other) = delete;
	AnimaDrop(AnimaDrop&& _Other) noexcept = delete;
	AnimaDrop& operator=(const AnimaDrop& _Other) = delete;
	AnimaDrop& operator=(AnimaDrop&& _Other) noexcept = delete;

	void Spawn(float4 _Pos);

protected:
	void Start() override;
	void Update(float _Delta) override;
private:

};

