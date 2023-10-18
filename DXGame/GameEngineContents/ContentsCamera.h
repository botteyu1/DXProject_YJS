#pragma once
#include <GameEngineCore/GameEngineCamera.h>

// Ό³Έν :
class ContentsCamera : public GameEngineCamera
{
public:

	// constrcuter destructer
	ContentsCamera();
	~ContentsCamera();

	// delete Function
	ContentsCamera(const ContentsCamera& _Other) = delete;
	ContentsCamera(ContentsCamera&& _Other) noexcept = delete;
	ContentsCamera& operator=(const ContentsCamera& _Other) = delete;
	ContentsCamera& operator=(ContentsCamera&& _Other) noexcept = delete;

protected:

	void Update(float _Delta) override;

private:

};

