#pragma once
#include "StageObject.h"
#include <GameEngineCore/GameEngineState.h>
//Ό³Έν

enum class ContractorState
{
	Appear,
	DisAppear,
	Idle,
	Hide,
	ON,
	OFF,
};


class Contractor : public StageObject
{
public:
	// constrcuter destructer
	Contractor();
	~Contractor();

	// delete Function
	Contractor(const Contractor& _Other) = delete;
	Contractor(Contractor&& _Other) noexcept = delete;
	Contractor& operator=(const Contractor& _Other) = delete;
	Contractor& operator=(Contractor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;


private:
	class GameEngineState State;
	std::shared_ptr<GameEngineCollision> DetectCollision;

};

