#pragma once
#include <GameEngineCore/GameEngineActor.h>
// ���� :  ����׿� �ֵܼ� ȭ��� ��Ÿ���� ��� ������Ʈ�� �ʿ��� ���
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

	std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer; //�⺻ ������
	float4 ScaleValue = float4::ONE;

private:

};

