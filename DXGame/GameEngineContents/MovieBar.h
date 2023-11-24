#pragma once

#include "UI.h"

// 설명 : 위아래 영화같은 비율 만드는 바

class MovieBar : public UI
{
public:
	// constrcuter destructer
	MovieBar();
	~MovieBar();

	// delete Function
	MovieBar(const MovieBar& _Other) = delete;
	MovieBar(MovieBar&& _Other) noexcept = delete;
	MovieBar& operator=(const MovieBar& _Other) = delete;
	MovieBar& operator=(MovieBar&& _Other) noexcept = delete;

	void MovieBarStart();
	void MovieBarEnd();

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(class GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr< GameEngineSpriteRenderer> MovieBar_Renderer_Up;
	std::shared_ptr< GameEngineSpriteRenderer> MovieBar_Renderer_Down;

	float Dir = 0.0f;
	float CurAlpha = 0.0f;

};

