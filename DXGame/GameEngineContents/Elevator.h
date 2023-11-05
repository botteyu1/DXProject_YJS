#pragma once
#include "StageObject.h"

enum class ElevatorState
{
	Static,
	Start,
	End,
};

// Ό³Έν :

class Elevator : public StageObject
{
public:
	// constrcuter destructer
	Elevator();
	~Elevator();

	// delete Function
	Elevator(const Elevator& _Other) = delete;
	Elevator(Elevator&& _Other) noexcept = delete;
	Elevator& operator=(const Elevator& _Other) = delete;
	Elevator& operator=(Elevator&& _Other) noexcept = delete;

	void static CollisionUpdate(class GameEngineCollision* _Left, GameEngineCollision* _Right);

	void Init(ElevatorState _State);

	void NextStageAnimationStart();

protected:
	void Start() override;
	void Update(float _Delta) override;

	
private:
	ElevatorState State = ElevatorState::Static;
};

