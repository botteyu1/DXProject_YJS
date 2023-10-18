#pragma once
#include <GameEngineCore/GameEngineActor.h>
// 설명 :  디버그용 콘솔등 화면상에 나타나는 모든 오브젝트에 필요한 기능
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

protected:

	std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer; //기본 렌더러
	float4 ScaleValue = float4::ONE;

private:

};

