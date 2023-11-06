#pragma once
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "FX.h"

// ���� :
class FxSpriteRenderer : public GameEngineSpriteRenderer
{
	friend class  FX;

public:
	// constrcuter destructer
	FxSpriteRenderer();
	~FxSpriteRenderer();

	// delete Function
	FxSpriteRenderer(const FxSpriteRenderer& _Other) = delete;
	FxSpriteRenderer(FxSpriteRenderer&& _Other) noexcept = delete;
	FxSpriteRenderer& operator=(const FxSpriteRenderer& _Other) = delete;
	FxSpriteRenderer& operator=(FxSpriteRenderer&& _Other) noexcept = delete;

	

protected:
	void Update(float _Delta) override;

private:
	FXType Type;
	float4 Scale = float4::ONE; //����������
	bool Flip = false;
	float Time = 0.0f;
};

