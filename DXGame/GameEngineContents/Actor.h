#pragma once

#include "ContentObject.h"



//class FxAnimationData
//{
//public:
//	float PivotX = 0.5f;// 애니메이션마다 적용할 피봇값
//	float4 CollisionScale = float4::ZERO; // 공격 크기
//	float4 CollisionPosition = float4::ZERO; //공긱 콜리전 위치
//	int AttackCollisionStartFrame = 0; //공격 콜리전이 시작될 프레임
//	std::string AttackFx = ""; // 공격 효과텍스쳐 이름
//	float AttackPivotX = 0.0f;// 애니메이션마다 적용할 피봇값
//};



// 설명 : 실제로움직이는 객체들 ex)몬스터 플레이어  
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
	void DashProcessUpdate(float _Delta, const float4& _Dir, float _Speed); //공격같은 실행할떄 대쉬업데이트
	void virtual FlipCheck();

	GameEngineColor PixelCollisionCheck(float4 _Pixel, GameEngineColor _DefaultColor = GameEngineColor::RED);
	GameEngineColor PosCollisionCheck(float4 _Pos, GameEngineColor _DefaultColor = GameEngineColor::RED);
	//void CheckAttackCollision();
	//void static ComboHit(class GameEngineCollision* _Left, GameEngineCollision* _Right) {};

	std::shared_ptr<GameEngineCollision> MainCollision;
	//std::shared_ptr< GameEngineSpriteRenderer> AttackfxRenderer; //공격 렌더러

	std::shared_ptr<GameEngineCollision> AttackCollision;
	std::shared_ptr<class SecondaryRenderer> LightRenderer;
	float4 DefaultScale; // 피봇설정을 위한 기본 크기

	float4 Dir = float4::RIGHT; //바라보는 방향/
	
	bool FlipPrev = false;
	float PivotPrev = 0.5f;

	std::map<std::string, AnimationData> AnimationDataMap;
	AnimationData* CurAnimationData; //현재 애니메이션 Data
	float CurDamage = 0.f; //현재 애니메이션 공격의 데미지

	float DashSpeed = 1000.0f;
	float CurDash = 0.0f; //현재까지 움직인 대쉬 거리


	float4 GrivityForce = { 0.0f, 0.0f, 0.0f, 1.0f }; //중력힘
	bool ForceGrivityOff = false;  //공중 몬스터같이  날아야하면 트루
	bool FrameCheck = false; // 공격하고있는 상태면 트루
	bool AerialCheck = true; // 공중인지 체크 공중이면 트루
	bool ThroughFloorCheck = false; //특정 바닥(파란색)을 통과할 수 있는 지 체크
	bool DashStartCheck = true; //대쉬가 시작해도되는지 체크
	bool NextLevelCheck = false;
	float MotionTime = 0.0f; // 기본적으로 적이 행동하는  시간


	int HP = 30;
	//class EventParameter CollisionParameter;

private:

	
};

