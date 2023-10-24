#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Level.h"

class AnimationData
{
public:
	float PivotX = 0.5f;// 애니메이션마다 적용할 피봇값
	float DashDistance = 0.0f; // 애니메이션에서 이동할 대쉬 거리
	bool ComboEnd = false; //마지막 콤보인지 여부
	float4 CollisionScale = float4::ZERO; // 공격 크기
	float4 CollisionPosition = float4::ZERO; //공긱 콜리전 위치
	int AttackCollisionStartFrame = 0; //공격 콜리전이 시작될 프레임
	std::string AttackFx = ""; // 공격 효과텍스쳐 이름
	float4 AttackFxPivot = { 0.5f, 0.5f };// 애니메이션마다 적용할 피봇값
	float4 AttackFxPos = { 0.0f, 0.0f,0.0f };// 애니메이션마다 적용할 피봇값
};

// 설명 :  디버그용 콘솔등 화면상에 나타나는 모든 주요 오브젝트에 필요한 기능
class ContentObject : public GameEngineActor
{
public:
	// constrcuter destructer
	ContentObject();
	~ContentObject();

	// delete Function
	ContentObject(const ContentObject& _Other) = delete;
	ContentObject(ContentObject&& _Other) noexcept = delete;
	ContentObject& operator=(const ContentObject& _Other) = delete;
	ContentObject& operator=(ContentObject&& _Other) noexcept = delete;

	void InputDebugUpdate(float _Delta);

	bool DebugValue = false;
	
	float4 GetScaleValue()
	{
		return ScaleValue;
	}

	class Level* GetContentsLevel()
	{
		return GetParent<Level>();
	}

	void SetActorType(ActorType _Type)
	{
		ActorTypeValue = _Type;
	}

	ActorType GetActorType()
	{
		return ActorTypeValue;
	}

protected:

	std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer; //기본 렌더러
	float4 ScaleValue = float4::ONE;

private:
	ActorType ActorTypeValue = ActorType::Max;
};

