#pragma once

#include "ContentObject.h"

// ���� :
class Title : public ContentObject
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


};
