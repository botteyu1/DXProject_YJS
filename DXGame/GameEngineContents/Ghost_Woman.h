#pragma once
#include "Enemy.h"
// Ό³Έν :

class Ghost_Woman : public Enemy
{
public:
	// constrcuter destructer
	Ghost_Woman();
	~Ghost_Woman();

	// delete Function
	Ghost_Woman(const Ghost_Woman& _Other) = delete;
	Ghost_Woman(Ghost_Woman&& _Other) noexcept = delete;
	Ghost_Woman& operator=(const Ghost_Woman& _Other) = delete;
	Ghost_Woman& operator=(Ghost_Woman&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	void IdleStart();
	void IdleUpdate(float _Delta);

	void AttackStart();
	void AttackUpdate(float _Delta);

	void AppearStart();
	void AppearUpdate(float _Delta);

	void DeathStart();
	void DeathUpdate(float _Delta);

	void HitStart();
	void HitUpdate(float _Delta);

	void RunStart();
	void RunUpdate(float _Delta);

	void SurprisedStart();
	void SurprisedUpdate(float _Delta);

	void UturnStart();
	void UturnUpdate(float _Delta);

	void WaitingStart();
	void WaitingUpdate(float _Delta);

};
