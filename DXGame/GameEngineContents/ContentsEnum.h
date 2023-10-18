#pragma once

enum class ContentsRenderType
{
	BackGround,

	BackGroundobject,
	StageObject,
	Enemy,
	Enemy_Attack,
	Player,
};


enum class ContentsObjectType
{
	BackGround,
	BackGroundobject,
	StageObject,
	Player,
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
