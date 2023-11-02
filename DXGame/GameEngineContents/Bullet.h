#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class BulletType
{
	Fire,
	Paperplane,
	Tornado,
	Rock,
	Max,
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

	void Init(BulletType _Type, float4 _Pos, float _Damage, float4 _Dir, float _Power, bool _Flip = false);

	void static BulletHit(GameEngineCollision* _Bullet, GameEngineCollision* _Target);

	float GetDamage()
	{
		return Damage;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

	int BulletCount = 0; //발사된 총알이 몇번쨰 총알인지

private:
	GameEngineColor PixelCollisionCheck(float4 _Pixel, GameEngineColor _DefaultColor = GameEngineColor::RED);
	GameEngineColor PosCollisionCheck(float4 _Pos, GameEngineColor _DefaultColor = GameEngineColor::RED);

	std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer; //기본 렌더러
	std::shared_ptr<GameEngineCollision> AttackCollision;

	float4 Vecter = float4::RIGHT;
	float Damage = 0.0f;
	ContentsCollisionType TargetCollision = ContentsCollisionType::Enemy;

	BulletType Type = BulletType::Max;

	float Time = 0.0f;

	float4 GrivityForce = { 0.0f, 0.0f, 0.0f, 1.0f }; //중력힘

	bool ForceGrivityOff = true; //중력을 받는지 체크 트루면 받지 않는다.
	bool AerialCheck = false;
	bool Flip = false;
};

