#pragma once
#include "StageObject.h"
#include <GameEngineCore/GameEngineState.h>

enum class PaperWallState
{
	StaticOn,
	StaticOff,
	Start,
	End,
};

class PaperWall : public StageObject
{
public:
	// constrcuter destructer
	PaperWall();
	~PaperWall();

	// delete Function
	PaperWall(const PaperWall& _Other) = delete;
	PaperWall(PaperWall&& _Other) noexcept = delete;
	PaperWall& operator=(const PaperWall& _Other) = delete;
	PaperWall& operator=(PaperWall&& _Other) noexcept = delete;
	void static CollisionUpdate(class GameEngineCollision* _Left, GameEngineCollision* _Right);

	//void Init(ElevatorState _State);


protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	float AlphaValue = 0.0f;
	
	GameEngineState State;
};

