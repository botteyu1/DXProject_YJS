#pragma once

// ���� :  ����׿� �ֵܼ� ȭ��� ��Ÿ���� ��� ������Ʈ�� �ʿ��� ���
class ContentObject
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

	void InputDebugUpdate(float _Delta, class GameEngineObject& _Object);

	bool DebugValue = false;
	
protected:


private:

};

