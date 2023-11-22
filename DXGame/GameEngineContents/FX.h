#pragma once
#include "ContentObject.h"

enum class FXType
{
	Surprised,
	Shockwave,
	DustLanding,
	GroundDust,
	Ghost_Attack_FX,
	SpawnEnemy,
	DamageText,
	Flash,
	Circle_Gradient,
	SpawnWeapon,
	Splash_Water,
	Splash_Water2,
	Slash,
	SlashHit,
	Hit,
	Shard,
	Death,
	TakeAnima,





};
// Ό³Έν :
class FX : public ContentObject
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

	std::shared_ptr<class FxSpriteRenderer> FXStart(FXType _Name, bool _flip, const float4& _Pos, const float4& _Scale = float4::ONE, const float4& _Pivot = float4(0.5f,0.5f));

	std::shared_ptr< FxSpriteRenderer> FXUIStart(FXType _Name, bool _flip, const TransformData& _Transform);
	void FXTextStart(FXType _Name, std::string_view _Text, const float4& _Pos, const float _Scale = 20.0f);

protected:

	void Start() override;
	void Update(float _Delta);

	std::shared_ptr< class FxSpriteRenderer> AddFXRenderer();
	std::shared_ptr< class FxSpriteRenderer> AddFXTextRenderer();
	std::shared_ptr< class FxSpriteRenderer> AddFXUIRenderer();

private:
	std::vector<std::shared_ptr<class FxSpriteRenderer>> MainSpriteRenderers;
	std::vector<std::shared_ptr<class FxSpriteRenderer>> TextSpriteRenderers;
	std::vector<std::shared_ptr<class FxSpriteRenderer>> UISpriteRenderers;
	//std::vector<FXType> MainSpriteRenderers;
	//std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer;  
	
};

