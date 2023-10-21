#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class BulletType
{
	Fire,
	Paperplane,
};

// 설명 :
class Bullet : public GameEngineActor
{
public:
	// constrcuter destructer
	Bullet();
	~Bullet();

	// delete Function
	Bullet(const Bullet& _Other) = delete;
	Bullet(Bullet&& _Other) noexcept = delete;
	Bullet& operator=(const Bullet& _Other) = delete;
	Bullet& operator=(Bullet&& _Other) noexcept = delete;

	void Init(BulletType _Type, float4 _Pos, float _Damage, float4 _Dir, float _Power);

	void static BulletHit(GameEngineCollision* _Bullet, GameEngineCollision* _Target);

	float GetDamage()
	{
		return Damage;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer; //기본 렌더러
	std::shared_ptr<GameEngineCollision> AttackCollision;

	float4 Vecter = float4::RIGHT;
	float Damage = 0.0f;
	ContentsCollisionType TargetCollision = ContentsCollisionType::Enemy;

	float Time = 0.0f;
};

