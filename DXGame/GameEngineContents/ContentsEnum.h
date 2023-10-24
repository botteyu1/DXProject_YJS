#pragma once

enum class ContentsRenderType
{
	StageObject,
	BackGround,
	BackGroundobject,
	Enemy,
	Enemy_Attack,
	Player_object,
	Player,
	FX,
	UI,
};


enum class ContentsObjectType
{
	BackGround,
	BackGroundobject,
	StageObject,
	Player,
	Player_object,
	Enemy,
	Bullet,
	FX,
	UI,
};

enum class ContentsCollisionType
{
	StageObject,
	Player,
	Player_Attack,
	Enemy,
	Enemy_Attack,
	Enemy_Detect,
	UI,
};

enum class ActorType
{
	Player,
	Ghost_Man1,
	Ghost_Man2,
	Ghost_Man3,
	Ghost_Woman1,
	Ghost_Woman2,
	Ghost_Woman3,
	Ghost_Med1,
	Ghost_Med2,
	Ghost_Med3,
	PossessedBook1,
	PossessedBook2,
	PossessedBook3,
	ElevatorStart,
	ElevatorStatic,
	ElevatorEnd,
	Max,
};
