#pragma once

#include "UI.h"

// Ό³Έν :

class CurseUI : public UI
{
public:
	// constrcuter destructer
	CurseUI();
	~CurseUI();

	// delete Function
	CurseUI(const CurseUI& _Other) = delete;
	CurseUI(CurseUI&& _Other) noexcept = delete;
	CurseUI& operator=(const CurseUI& _Other) = delete;
	CurseUI& operator=(CurseUI&& _Other) noexcept = delete;

	void CurseUIStart(int _Type);
	void UIOn() override;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void ExitAnimationUpdate(float _Delta);
	void LevelStart(class GameEngineLevel* _NextLevel) override;

private:
	float FadeStrength = 0.0f;
	float MoveDist = 0.0f;
	int PickNum = 1;

	bool ExitValue = false;

	std::shared_ptr<class GameEngineSpriteRenderer> FadeRenderer;
	std::shared_ptr<class GameEngineSpriteRenderer> FadeRendererAfter;
	std::shared_ptr< GameEngineSpriteRenderer> Blur_LineRenderer;

	std::shared_ptr<class GameEngineSpriteRenderer> Curse_Select_Border;
	std::shared_ptr<class GameEngineSpriteRenderer> Curse_Select_Text;

	std::shared_ptr<class GameEngineSpriteRenderer> Curse_Border_Red;
	std::shared_ptr<class GameEngineSpriteRenderer> Curse_Border_On_Red;
	std::shared_ptr<class GameEngineSpriteRenderer> Curse_BG_Red;
	std::shared_ptr<class GameEngineSpriteRenderer> Curse_Rarity_Red;
	std::shared_ptr<class GameEngineSpriteRenderer> Curse_Icon_Red;
	std::shared_ptr<class GameEngineSpriteRenderer> Curse_MainText_Red;
	std::shared_ptr<class GameEngineSpriteRenderer> Curse_SubText_Red;
	std::shared_ptr<class GameEngineSpriteRenderer> Curse_Img_Red;


	std::shared_ptr<class GameEngineSpriteRenderer> Curse_Border_Blue;
	std::shared_ptr<class GameEngineSpriteRenderer> Curse_Border_On_Blue;
	std::shared_ptr<class GameEngineSpriteRenderer> Curse_BG_Blue;
	std::shared_ptr<class GameEngineSpriteRenderer> Curse_Icon_Blue;
	std::shared_ptr<class GameEngineSpriteRenderer> Curse_Rarity_Blue;
	std::shared_ptr<class GameEngineSpriteRenderer> Curse_MainText_Blue;
	std::shared_ptr<class GameEngineSpriteRenderer> Curse_SubText_Blue;
	std::shared_ptr<class GameEngineSpriteRenderer> Curse_Img_Blue;

	std::shared_ptr<class GameEngineSpriteRenderer> Curse_Border_Green;
	std::shared_ptr<class GameEngineSpriteRenderer> Curse_Border_On_Green;
	std::shared_ptr<class GameEngineSpriteRenderer> Curse_BG_Green;
	std::shared_ptr<class GameEngineSpriteRenderer> Curse_Rarity_Green;
	std::shared_ptr<class GameEngineSpriteRenderer> Curse_Icon_Green;
	std::shared_ptr<class GameEngineSpriteRenderer> Curse_MainText_Green;
	std::shared_ptr<class GameEngineSpriteRenderer> Curse_SubText_Green;
	std::shared_ptr<class GameEngineSpriteRenderer> Curse_Img_Green;

	std::shared_ptr<class GameEngineSpriteRenderer> Curse_Transition;





	//std::shared_ptr< GameEngineSpriteRenderer> Blur_LineRenderer;

};

