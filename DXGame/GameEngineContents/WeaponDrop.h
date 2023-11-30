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

void Spawn(CapeType _Type = CapeType::EvilHands);

protected:
	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<class GameEngineSpriteRenderer> BGSpriteRenderer;
	std::shared_ptr<class GameEngineSpriteRenderer> BGSpriteRenderer_Smoke;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_Cape;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_Cape_BG;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_Cape_BG2;

private:

	
	
	

	CapeType Type = CapeType::EvilHands;

	void BouncingStart();

};

