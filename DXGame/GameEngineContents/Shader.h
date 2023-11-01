#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Shader : public GameEngineActor
{
public:
	// constrcuter destructer
	Shader();
	~Shader();

	// delete Function
	Shader(const Shader& _Other) = delete;
	Shader(Shader&& _Other) noexcept = delete;
	Shader& operator=(const Shader& _Other) = delete;
	Shader& operator=(Shader&& _Other) noexcept = delete;
	
	
	std::shared_ptr<GameEngineSpriteRenderer> GetGlobalShader()
	{
		return GlobalShader;
	}
protected:
	void Start() override;
	void Update(float _Delta)override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> GlobalShader= nullptr;	
	std::shared_ptr<GameEngineSpriteRenderer> Cloud= nullptr;

};

