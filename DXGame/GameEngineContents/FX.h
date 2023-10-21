#pragma once
#include <GameEngineCore/GameEngineActor.h>
enum class FXType
{
	Surprised,
	Shockwave,
	DustLanding,
	GroundDust,

};
// Ό³Έν :
class FX : public GameEngineActor
{
public:
	// constrcuter destructer
	FX();
	~FX();

	// delete Function
	FX(const FX& _Other) = delete;
	FX(FX&& _Other) noexcept = delete;
	FX& operator=(const FX& _Other) = delete;
	FX& operator=(FX&& _Other) noexcept = delete;

	void FXStart(FXType _Name, bool _flip, const float4& _Pos, const float4& _Scale = float4::ONE);

protected:

	void Start() override;
	void Update(float _Delta);

	std::shared_ptr< class FxSpriteRenderer> AddFXRenderer();

private:
	std::vector<std::shared_ptr<class FxSpriteRenderer>> MainSpriteRenderers;
	//std::vector<FXType> MainSpriteRenderers;
	//std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer;  
	
};

