#pragma once
#include "Enemy.h"

enum class MedAttackPatern
{
	Combo,
	Power,

};

// 설명 :

class Ghost_Med : public Enemy
{
public:
	// constrcuter destructer
	Ghost_Med();
	~Ghost_Med();

	// delete Function
	Ghost_Med(const Ghost_Med& _Other) = delete;
	Ghost_Med(Ghost_Med&& _Other) noexcept = delete;
	Ghost_Med& operator=(const Ghost_Med& _Other) = delete;
	Ghost_Med& operator=(Ghost_Med&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:

	bool ComboStart = false;
	int ComboCount = 0;
	MedAttackPatern AttackPatern = MedAttackPatern::Combo;  //공격 패턴 종류 카운트



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
