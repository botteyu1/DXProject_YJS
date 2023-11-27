#include "UI.h"

// Ό³Έν :
class BossUI : public UI
{
public:
	// constrcuter destructer
	BossUI();
	~BossUI();

	// delete Function
	BossUI(const BossUI& _Other) = delete;
	BossUI(BossUI&& _Other) noexcept = delete;
	BossUI& operator=(const BossUI& _Other) = delete;
	BossUI& operator=(BossUI&& _Other) noexcept = delete;

	void SetBoss(std::shared_ptr<class BossGargoyle> _Ptr)
	{
		BossPtr = _Ptr;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(class GameEngineLevel* _NextLevel) override;


private:
	//std::shared_ptr< class GameEngineSpriteRenderer> HUD_LifeBar;
	//std::shared_ptr< GameEngineSpriteRenderer> HUD_LifeBar_Hit;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_LifeBar_On;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_LifeBar_On_Right;
	std::shared_ptr< GameEngineSpriteRenderer> HUD_LifeBar_On_Left;

	std::shared_ptr< GameEngineSpriteRenderer> HUD_Boss_Icon;



	std::shared_ptr<class BossGargoyle> BossPtr;



};




