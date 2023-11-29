#pragma once

#include "ContentObject.h"



//class FxAnimationData
//{
//public:
//	float PivotX = 0.5f;// �ִϸ��̼Ǹ��� ������ �Ǻ���
//	float4 CollisionScale = float4::ZERO; // ���� ũ��
//	float4 CollisionPosition = float4::ZERO; //���� �ݸ��� ��ġ
//	int AttackCollisionStartFrame = 0; //���� �ݸ����� ���۵� ������
//	std::string AttackFx = ""; // ���� ȿ���ؽ��� �̸�
//	float AttackPivotX = 0.0f;// �ִϸ��̼Ǹ��� ������ �Ǻ���
//};



// ���� : �����ο����̴� ��ü�� ex)���� �÷��̾�  
class Actor : public ContentObject
{
public:
	// constrcuter destructer
	Actor();
	~Actor();

	// delete Function
	Actor(const Actor& _Other) = delete;
	Actor(Actor&& _Other) noexcept = delete;
	Actor& operator=(const Actor& _Other) = delete;
	Actor& operator=(Actor&& _Other) noexcept = delete;

	//std::shared_ptr<GameEngineSpriteRenderer> CreateAnimation(std::string_view _AnimationName, float _Inter, AnimationData _Data, bool _Loop = true);

	void AddHP(int _HP)
	{
		HP += _HP;
	}

	int GetHP()
	{
		return HP ;
	}

	void virtual TakeDamage(GameEngineCollision* _Attacker, float _Damage) {}

	float GetCurDamage()
	{
		return CurDamage;
	}


protected:



	void Start() override;
	void Update(float _Delta) override;
	bool AerialPixelCheck();

	void ChangeMainAnimation(std::string_view _AnimationName);
	bool CheckStartAttackFrame(int _Index = -1 , float _Damage = 10.0f); 
	bool CheckEndAttackFrame(int _Index = -1);
	void DashProcessUpdate(float _Delta, const float4& _Dir, float _Speed); //���ݰ��� �����ҋ� �뽬������Ʈ
	void virtual FlipCheck();

	GameEngineColor PixelCollisionCheck(float4 _Pixel, GameEngineColor _DefaultColor = GameEngineColor::RED);
	GameEngineColor PosCollisionCheck(float4 _Pos, GameEngineColor _DefaultColor = GameEngineColor::RED);
	//void CheckAttackCollision();
	//void static ComboHit(class GameEngineCollision* _Left, GameEngineCollision* _Right) {};

	std::shared_ptr<GameEngineCollision> MainCollision;
	//std::shared_ptr< GameEngineSpriteRenderer> AttackfxRenderer; //���� ������

	std::shared_ptr<GameEngineCollision> AttackCollision;
	std::shared_ptr<class SecondaryRenderer> LightRenderer;
	float4 DefaultScale; // �Ǻ������� ���� �⺻ ũ��

	float4 Dir = float4::RIGHT; //�ٶ󺸴� ����/
	
	bool FlipPrev = false;
	float PivotPrev = 0.5f;

	std::map<std::string, AnimationData> AnimationDataMap;
	AnimationData* CurAnimationData; //���� �ִϸ��̼� Data
	float CurDamage = 0.f; //���� �ִϸ��̼� ������ ������

	float DashSpeed = 1000.0f;
	float CurDash = 0.0f; //������� ������ �뽬 �Ÿ�


	float4 GrivityForce = { 0.0f, 0.0f, 0.0f, 1.0f }; //�߷���
	bool ForceGrivityOff = false;  //���� ���Ͱ���  ���ƾ��ϸ� Ʈ��
	bool FrameCheck = false; // �����ϰ��ִ� ���¸� Ʈ��
	bool AerialCheck = true; // �������� üũ �����̸� Ʈ��
	bool ThroughFloorCheck = false; //Ư�� �ٴ�(�Ķ���)�� ����� �� �ִ� �� üũ
	bool DashStartCheck = true; //�뽬�� �����ص��Ǵ��� üũ
	bool NextLevelCheck = false;
	float MotionTime = 0.0f; // �⺻������ ���� �ൿ�ϴ�  �ð�


	int HP = 30;
	//class EventParameter CollisionParameter;

private:

	
};

