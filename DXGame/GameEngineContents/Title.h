#pragma once

#include "UI.h"

// Ό³Έν :
class Title : public UI
{
public:
	// constrcuter destructer
	Title();
	~Title();

	// delete Function
	Title(const Title& _Other) = delete;
	Title(Title&& _Other) noexcept = delete;
	Title& operator=(const Title& _Other) = delete;
	Title& operator=(Title&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> LD_Body;
	std::shared_ptr<class GameEngineSpriteRenderer> LD_Forearm;
	std::shared_ptr<class GameEngineSpriteRenderer> LD_Head;
	std::shared_ptr<class GameEngineSpriteRenderer> LD_Smoke;
	std::shared_ptr<class GameEngineSpriteRenderer> LD_Reflect;
	std::shared_ptr<class GameEngineSpriteRenderer> LD_Weapon;
	std::shared_ptr<class GameEngineSpriteRenderer> UIArrow;
	std::shared_ptr<class GameEngineSpriteRenderer> TitleBG;

	int ArrowLocate = 1;
	float MoveDist = -50.0f;
	float MoveDistCheck = 0.0f;
	float4 Dir = float4::DOWN;

};

