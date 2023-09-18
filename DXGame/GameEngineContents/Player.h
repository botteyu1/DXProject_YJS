#pragma once
#include "Actor.h"

enum class PlayerState
{
	Idle,
	Jump_Falling,
	Jump_Start,
	Jump_Landing,
	Run,
	RunUturn,
	RunToIdle,
	ComboMove,
	ComboMove_Rest,
	ComboAerial,
	ComboAerial_Rest,
	Dash,
	Max, // �Ϲ������� ������� �ʴ� ��.
};

class AnimationData
{
public:
	float DashDistance; // �ִϸ��̼ǿ��� �̵��� �뽬 �Ÿ� 

	//int NextComboFrame;  //�޺��� ��� �ɋ� �ִϸ��̼��� �ٲ�� ������
	//bool HaveToIdle;
};
// ���� :
class Player : public Actor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> MainSpriteRenderer;

	float Speed = 700.0f;

	PlayerState State = PlayerState::Max;
	std::map<std::string, AnimationData> PlayerAnimationDataMap;
	
	int ComboCount = 1;
	float CurDash = 0.0f; //������� ������ �뽬 �Ÿ�
	AnimationData* CurAnimationData; //���� �ִϸ��̼� Data

	bool Flip = false;
	bool NextCombo = false; // ���� �޺� �Է��ߴ��� Ȯ�� 




	//============================
	// ����
	//============================

	void IdleStart();
	void IdleUpdate(float _Delta);

	void RunStart();
	void RunUpdate(float _Delta);

	void RunUturnStart();
	void RunUturnUpdate(float _Delta);

	void RunToIdleStart();
	void RunToIdleUpdate(float _Delta);

	void Jump_FallingStart();
	void Jump_FallingUpdate(float _Delta);

	void Jump_LandingStart();
	void Jump_LandingUpdate(float _Delta);

	void Jump_StartStart();
	void Jump_StartUpdate(float _Delta);

	void ComboMoveStart();
	void ComboMoveUpdate(float _Delta);

	void ComboMove_RestStart();
	void ComboMove_RestUpdate(float _Delta);
	
	void ComboAerialStart();
	void ComboAerialUpdate(float _Delta);

	void ComboAerial_RestStart();
	void ComboAerial_RestUpdate(float _Delta);

	void DashStart();
	void DashUpdate(float _Delta);

	void InputMoveUpdate(float _Delta);
	void InputJumpUpdate(float _Delta);
	void InputAttackUpdate(float _Delta);
	void InputDashUpdate(float _Delta);

	void FlipCheck();


	void StateUpdate(float _Delta);
	void ChangeState(PlayerState _State);
};

