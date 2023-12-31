#pragma once
#include "Enemy.h"
// ���� :

class Ghost_Man : public Enemy
{
public:
	// constrcuter destructer
	Ghost_Man();
	~Ghost_Man();

	// delete Function
	Ghost_Man(const Ghost_Man& _Other) = delete;
	Ghost_Man(Ghost_Man&& _Other) noexcept = delete;
	Ghost_Man& operator=(const Ghost_Man& _Other) = delete;
	Ghost_Man& operator=(Ghost_Man&& _Other) noexcept = delete;

	
	void Init(int _Type);

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

