#pragma once
#include "Enemy.h"

enum class GargoyleAttackPatern
{
	Combo,
	Posing,
	Dive,
	Dive_Anti,
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

	void DeathCheck() override;


	void IdleStart();
	void IdleUpdate(float _Delta);

	void AttackStart();
	void AttackUpdate(float _Delta);

	void Attack_InitStart() override;
	void Attack_InitUpdate(float _Delta) override;

	void Attack_EndStart();
	void Attack_EndUpdate(float _Delta);

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

	void IntroStart();
	void IntroUpdate(float _Delta);

	void IntroIdleStart();
	void IntroIdleUpdate(float _Delta);

	void EndStart();
	void EndUpdate(float _Delta);

	void OutroStart();
	void OutroUpdate(float _Delta);

private:
	bool ComboStart = false;
	int ComboCount = 0;
	int PosingCount = 0;
	GargoyleAttackPatern AttackPatern = GargoyleAttackPatern::Combo;
	float4 TargetPlayerPos = float4::ZERO;
	float4 TargetPos = float4::ZERO; //공격용 좌표 저장
	float4 MoveVec = float4::ZERO;
	float BulletDelay = 0.3f;
	float BulletDelayCheck = 0.0f;

	std::shared_ptr<class GameEngineSpriteRenderer> DeskSpriteRenderer; 

};

