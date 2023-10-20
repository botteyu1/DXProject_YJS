#pragma once
#include <GameEngineCore/GameEngineActor.h>

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

	void FXStart(std::string_view _Name, bool _flip, const float4& _Pos, const float4& Scale);

protected:

	void Start() override;
	void Update(float _Delta);

	std::shared_ptr< GameEngineSpriteRenderer> AddFXRenderer();

private:
	std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> MainSpriteRenderers;  

};

