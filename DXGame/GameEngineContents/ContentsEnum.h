#pragma once

enum class ContentsRenderType
{
	BackGround,
	BackGroundobject,
	StageObject,
	Enemy,
	Enemy_Attack,
	Player_object,
	Player,
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
};

enum class ContentsCollisionType
{
	StageObject,
	Player,
	Player_Attack,
	Enemy,
	Enemy_Attack,
	Enemy_Detect,
};
