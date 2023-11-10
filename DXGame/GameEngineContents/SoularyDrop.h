#pragma once
#include "StageObject.h"


class SoularyDrop : public StageObject
{
public:
	// constrcuter destructer
	SoularyDrop();
	~SoularyDrop();

	// delete Function
	SoularyDrop(const SoularyDrop& _Other) = delete;
	SoularyDrop(SoularyDrop&& _Other) noexcept = delete;
	SoularyDrop& operator=(const SoularyDrop& _Other) = delete;
	SoularyDrop& operator=(SoularyDrop&& _Other) noexcept = delete;

	void Spawn(float4 _Pos);

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	

};

