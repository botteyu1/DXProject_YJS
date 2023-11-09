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

	void SetSpawnObject(class ContentObject* _Ptr)
	{
		SpawnObject = _Ptr;
	}

protected:
	void Update(float _Delta) override;

private:
	FX* ParentFx = nullptr;
	class ContentObject* SpawnObject = nullptr;
	FXType Type;

	float Dir = 1.0f;

	float4 Scale = float4::ONE; //비율스케일
	bool Flip = false;
	bool SpawnObjectOnCheck = false;
	float Time = 0.0f;
};

