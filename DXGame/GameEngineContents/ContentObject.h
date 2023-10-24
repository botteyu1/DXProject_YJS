#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Level.h"

class AnimationData
{
public:
	float PivotX = 0.5f;// �ִϸ��̼Ǹ��� ������ �Ǻ���
	float DashDistance = 0.0f; // �ִϸ��̼ǿ��� �̵��� �뽬 �Ÿ�
	bool ComboEnd = false; //������ �޺����� ����
	float4 CollisionScale = float4::ZERO; // ���� ũ��
	float4 CollisionPosition = float4::ZERO; //���� �ݸ��� ��ġ
	int AttackCollisionStartFrame = 0; //���� �ݸ����� ���۵� ������
	std::string AttackFx = ""; // ���� ȿ���ؽ��� �̸�
	float4 AttackFxPivot = { 0.5f, 0.5f };// �ִϸ��̼Ǹ��� ������ �Ǻ���
	float4 AttackFxPos = { 0.0f, 0.0f,0.0f };// �ִϸ��̼Ǹ��� ������ �Ǻ���
};

// ���� :  ����׿� �ֵܼ� ȭ��� ��Ÿ���� ��� �ֿ� ������Ʈ�� �ʿ��� ���
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

	std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer; //�⺻ ������
	float4 ScaleValue = float4::ONE;

private:
	ActorType ActorTypeValue = ActorType::Max;
};

