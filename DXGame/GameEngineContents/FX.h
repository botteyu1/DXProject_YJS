#pragma once
#include <GameEngineCore/GameEngineActor.h>
enum class FXType
{
	Surprised,
	Shockwave,
	DustLanding,
	GroundDust,

};
// 설명 :
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

	std::shared_ptr< GameEngineSpriteRenderer> AddFXRenderer();

private:
	//std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> MainSpriteRenderers;  
	std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer;  
	float4 Scale = float4::ONE; //비율스케일
	FXType Type; 

	bool Flip = false;
};

