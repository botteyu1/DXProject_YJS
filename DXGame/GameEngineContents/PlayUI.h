#pragma once

#include "UI.h"

// Ό³Έν :
class PlayUI : public UI
{
public:
	// constrcuter destructer
	PlayUI();
	~PlayUI();

	// delete Function
	PlayUI(const PlayUI& _Other) = delete;
	PlayUI(PlayUI&& _Other) noexcept = delete;
	PlayUI& operator=(const PlayUI& _Other) = delete;
	PlayUI& operator=(PlayUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(class GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> HUD_Scythe_Outline;
	std::shared_ptr<class GameEngineSpriteRenderer> HUD_Scythe_BG;
	std::shared_ptr<class GameEngineSpriteRenderer> HUD_Cape_Outline;
	std::shared_ptr<class GameEngineSpriteRenderer> HUD_Cape_BG;
	std::shared_ptr<class GameEngineSpriteRenderer> HUD_Cape2_Outline;
	std::shared_ptr<class GameEngineSpriteRenderer> HUD_Cape2_BG;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_Ult;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_Ult_BG;

	std::shared_ptr< GameEngineSpriteRenderer> HUD_LifeBar;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_LifeBar_Hit;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_LifeBar_On;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_LifeBar_On_Right;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_LifeBar_On_Left;

	std::shared_ptr< GameEngineSpriteRenderer> HUD_LifeBar_Text;


	std::shared_ptr< GameEngineSpriteRenderer> HUD_ManaBar;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_ManaBar_On;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_ManaBar_On_Left;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_ManaBar_On_Right;

	std::shared_ptr< GameEngineSpriteRenderer> HUD_ManaBar_Text;

	std::shared_ptr< GameEngineSpriteRenderer> HUD_Anima;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_Anima2;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_Anima3;

	std::shared_ptr< GameEngineSpriteRenderer> HUD_Soulary;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_Soulary_Text;

	std::shared_ptr< GameEngineSpriteRenderer> HUD_Scythe;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_Cape;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_Cape_Text;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_Cape2;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_Cape2_Text;

	int PrevHP = 0;
	float HPTimer = 500.0f;



};

