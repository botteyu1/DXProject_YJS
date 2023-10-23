#pragma once
#include "Enemy.h"
// Ό³Έν :
class BossGargoyle : public Enemy
{
public:
	// constrcuter destructer
	BossGargoyle();
	~BossGargoyle();

	// delete Function
	BossGargoyle(const BossGargoyle& _Other) = delete;
	BossGargoyle(BossGargoyle&& _Other) noexcept = delete;
	BossGargoyle& operator=(const BossGargoyle& _Other) = delete;
	BossGargoyle& operator=(BossGargoyle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:

};

