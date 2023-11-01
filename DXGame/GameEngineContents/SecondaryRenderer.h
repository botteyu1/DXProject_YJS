#pragma once
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "FX.h"

enum class SecondaryRendererType
{
	Light,
	Shadow,
	Max,
};


// Ό³Έν :

class SecondaryRenderer : public GameEngineSpriteRenderer
{
public:
	// constrcuter destructer
	SecondaryRenderer();
	~SecondaryRenderer();

	// delete Function
	SecondaryRenderer(const SecondaryRenderer& _Other) = delete;
	SecondaryRenderer(SecondaryRenderer&& _Other) noexcept = delete;
	SecondaryRenderer& operator=(const SecondaryRenderer& _Other) = delete;
	SecondaryRenderer& operator=(SecondaryRenderer&& _Other) noexcept = delete;
	void Init(SecondaryRendererType _Type,float4 _Pos, float4 _Scale);

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	SecondaryRendererType Type = SecondaryRendererType::Max;
};

