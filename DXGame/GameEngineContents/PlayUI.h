#pragma once

#include "UI.h"

// ���� :
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

private:
	std::shared_ptr<class GameEngineSpriteRenderer> HUD_Main;
	std::shared_ptr<class GameEngineSpriteRenderer> HUD_Main_BG;
	std::shared_ptr<class GameEngineSpriteRenderer> HUD_Cape;
	std::shared_ptr<class GameEngineSpriteRenderer> HUD_Cape_BG;
	std::shared_ptr<class GameEngineSpriteRenderer> HUD_Cape2;
	std::shared_ptr<class GameEngineSpriteRenderer> HUD_Cape2_BG;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_Ult;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_Ult_BG;

	std::shared_ptr< GameEngineSpriteRenderer> HUD_LifeBar;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_LifeBar_On;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_LifeBar_Text;


	std::shared_ptr< GameEngineSpriteRenderer> HUD_ManaBar;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_ManaBar_On;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_ManaBar_Text;

	std::shared_ptr< GameEngineSpriteRenderer> HUD_Anima;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_Anima2;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_Anima3;

	std::shared_ptr< GameEngineSpriteRenderer> HUD_Soulary;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_Soulary_Text;

};

