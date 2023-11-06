#pragma once
#include "StageObject.h"
#include "Cape.h"



class WeaponDrop : public StageObject
{
	friend class PlayLevel;
public:
	// constrcuter destructer
	WeaponDrop();
	~WeaponDrop();

	// delete Function
	WeaponDrop(const WeaponDrop& _Other) = delete;
	WeaponDrop(WeaponDrop&& _Other) noexcept = delete;
	WeaponDrop& operator=(const WeaponDrop& _Other) = delete;
	WeaponDrop& operator=(WeaponDrop&& _Other) noexcept = delete;

void static CollisionUpdate(class GameEngineCollision* _Left, GameEngineCollision* _Right);

//void Init(ElevatorState _State);



protected:
	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<class GameEngineSpriteRenderer> BGSpriteRenderer;
	std::shared_ptr<class GameEngineSpriteRenderer> BGSpriteRenderer_Smoke;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_Cape;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_Cape_BG;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_Cape_BG2;

private:
	GameEngineColor PixelCollisionCheck(float4 _Pixel, GameEngineColor _DefaultColor = GameEngineColor::RED);
	GameEngineColor PosCollisionCheck(float4 _Pos, GameEngineColor _DefaultColor = GameEngineColor::RED);

	bool BouncingValue = true; //바운스했으면 true;
	bool AerialCheck = false;
	float4 GrivityForce = { 0.0f, 0.0f, 0.0f, 1.0f }; //중력힘
	CapeType Type = CapeType::EvilHands;

	void BouncingStart();

};

