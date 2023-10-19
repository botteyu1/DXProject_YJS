#pragma once
#include "Actor.h"

enum class BookState
{
	Attack_Basic,
	Attack_Down,
	Attack_Up,
	Deliverance,
	Open_Idle,
	Transition_To_Menu,
	Idle,
	Uturn,
	Max, // 일반적으로 사용하지 않는 값.
};


// 설명 :
class BookOfTheDead : public Actor
{
	friend class Player;
public:
	// constrcuter destructer
	BookOfTheDead();
	~BookOfTheDead();

	// delete Function
	BookOfTheDead(const BookOfTheDead& _Other) = delete;
	BookOfTheDead(BookOfTheDead&& _Other) noexcept = delete;
	BookOfTheDead& operator=(const BookOfTheDead& _Other) = delete;
	BookOfTheDead& operator=(BookOfTheDead&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update(float _Delta) override;

private:
	float4 PivotPos = float4::ZERO;

	class Player* MainPlayer = nullptr;

	void TrackingPlayerUpdate(float _Delta);

	void Attack_BasicStart();
	void Attack_BasicUpdate(float _Delta);

	void Attack_DownStart();
	void Attack_DownUpdate(float _Delta);

	void Attack_UpStart();
	void Attack_UpUpdate(float _Delta);

	void DeliveranceStart();
	void DeliveranceUpdate(float _Delta);

	void Open_IdleStart();
	void Open_IdleUpdate(float _Delta);

	void Transition_To_MenuStart();
	void Transition_To_MenuUpdate(float _Delta);

	void UturnStart();
	void UturnUpdate(float _Delta);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void StateUpdate(float _Delta);
	void ChangeState(BookState _State);

	BookState State = BookState::Max;




};

