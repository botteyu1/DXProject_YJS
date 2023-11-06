#pragma once
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "FX.h"

// 설명 :
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

	void SetSpawnEnemy(class Enemy* _Ptr)
	{
		SpawnEnemy = _Ptr;
	}

protected:
	void Update(float _Delta) override;

private:
	class Enemy* SpawnEnemy = nullptr;
	FXType Type;
	float4 Scale = float4::ONE; //비율스케일
	bool Flip = false;
	float Time = 0.0f;
};

