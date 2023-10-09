#pragma once
#include <GameEngineCore/GameEngineActor.h>

class AnimationData
{
public:
	float PivotX = 0.5f;// 애니메이션마다 적용할 피봇값
	float DashDistance = 0.0f; // 애니메이션에서 이동할 대쉬 거리
	bool ComboEnd = false; //마지막 콤보인지 여부
	float4 CollisionScale = float4::ZERO; // 공격 크기
	float4 CollisionPosition = float4::ZERO; //공긱 콜리전 위치

	//int NextComboFrame;  //콤보가 계속 될떄 애니메이션이 바뀌는 프레임
	//bool HaveToIdle;
};


// 설명 : 실제로움직이는 객체들 ex)몬스터 플레이어  
class Actor : public GameEngineActor
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

protected:

	void Start() override;
	void Update(float _Delta) override;
	void ChangeMainAnimation(std::string_view _AnimationName);
	void DashProcessUpdate(float _Delta, const float4& _Dir, float _Speed); //공격같은 실행할떄 대쉬업데이트

	GameEngineColor PixelCollisionCheck(float4 _Pixel, GameEngineColor _DefaultColor = GameEngineColor::RED);
	GameEngineColor PosCollisionCheck(float4 _Pos, GameEngineColor _DefaultColor = GameEngineColor::RED);

	std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer; //기본 렌더러
	std::shared_ptr<GameEngineCollision> MainCollision;
	std::shared_ptr<GameEngineCollision> AttackCollision;
	float4 DefaultScale; // 피봇설정을 위한 기본 크기

	float4 Dir = float4::ZERO; //바라보는 방향/
	
	bool FlipPrev = true;
	bool Flip = false;


	std::map<std::string, AnimationData> AnimationDataMap;
	AnimationData* CurAnimationData; //현재 애니메이션 Data

	float DashSpeed = 1000.0f;
	float CurDash = 0.0f; //현재까지 움직인 대쉬 거리


	float4 GrivityForce = { 0.0f, 0.0f, 0.0f, 1.0f }; //중력힘
	bool ForceGrivityOff = false; 
	bool AerialCheck = true; // 공중인지 체크 공중이면 트루
	bool ThroughFloorCheck = false; //특정 바닥(파란색)을 통과할 수 있는 지 체크

	int HP = 50;

private:

	
};

