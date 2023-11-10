#pragma once
#include "ContentObject.h"
//설명


class StageObject : public ContentObject
{
public:
	// constrcuter destructer
	StageObject();
	~StageObject();

	// delete Function
	StageObject(const StageObject& _Other) = delete;
	StageObject(StageObject&& _Other) noexcept = delete;
	StageObject& operator=(const StageObject& _Other) = delete;
	StageObject& operator=(StageObject&& _Other) noexcept = delete;


	

protected:
	void Start() override;
	void Update(float _Delta) override;

	//std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer; //기본 렌더러
	std::shared_ptr<GameEngineCollision> MainCollision;

	float GravityTimer = 0.0f;
	bool BouncingValue = true; //바운스했으면 true;
	bool AerialCheck = false; // 공중인지 체크 공중이면 트루
	bool ForceGrivityOff = true; //공중에 있거나 중력을 안받으면 트루
	float4 GrivityForce = { 0.0f, 0.0f, 0.0f, 1.0f }; //중력힘
	float GrivityPower = 2000.0f; //중력강도;

private:
	GameEngineColor PixelCollisionCheck(float4 _Pixel, GameEngineColor _DefaultColor = GameEngineColor::RED);
	GameEngineColor PosCollisionCheck(float4 _Pos, GameEngineColor _DefaultColor = GameEngineColor::RED);


	

};

