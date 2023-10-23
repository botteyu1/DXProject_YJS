#pragma once
#include "Enemy.h"

enum class GargoyleAttackPatern
{
	Combo,
	Posing,
	Dive,
	Spin,
	Max,

};

// 설명 :
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

	void TakeDamage(class GameEngineCollision* _Attacker, float _Damage) override;

protected:
	void Start() override;
	void Update(float _Delta) override;

	virtual void IdleStart();
	virtual void IdleUpdate(float _Delta);

	virtual void AttackStart();
	virtual void AttackUpdate(float _Delta);

	virtual void AppearStart();
	virtual void AppearUpdate(float _Delta);

	virtual void DeathStart();
	virtual void DeathUpdate(float _Delta);

	virtual void HitStart();
	virtual void HitUpdate(float _Delta);

	virtual void RunStart();
	virtual void RunUpdate(float _Delta);

	virtual void SurprisedStart();
	virtual void SurprisedUpdate(float _Delta);

	virtual void UturnStart();
	virtual void UturnUpdate(float _Delta);

	virtual void WaitingStart();
	virtual void WaitingUpdate(float _Delta);

private:
	bool ComboStart = false;
	int ComboCount = 0;
	int PosingCount = 0;
	GargoyleAttackPatern AttackPatern = GargoyleAttackPatern::Posing;
	float4 TargetPlayerPos = float4::ZERO;
	float4 TargetPos = float4::ZERO; //공격용 좌표 저장

};

