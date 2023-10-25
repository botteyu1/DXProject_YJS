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


	//배경오브젝트 

	BackWall_Big,
	BackWall_Down,
	BackWall_LeftT,
	BackWall_LeftT_A,
	BackWall_Middle,
	BackWall_Window,
	BackWall_Window05,
	BossDesk,
	coloneComplete,
	Colonnade02,
	Column01B,
	Column04,
	Column05,
	ColumnDown01,
	Desk,
	Desk01,
	Desk1,
	Desk2,
	Desk2_NoScreen,
	Desk3,
	Desk3_NoScreen,
	Escalator_02,
	Escalator_09,
	Escalator_Frieze,
	GhostWorkersBox1,
	GhostWorkersBox2,
	GhostWorkersBox3,
	GhostWorkersBox11,
	GhostWorkersBox22,
	GPE_DifficultyMode_Wall,
	GPE_Paper_Piles_Line,
	lamp2,
	lamp3,
	lamp4,
	OfficeCabinet2,
	OfficeCabinet3,
	OfficeCabinet4,
	PipeFrieze2,
	Rock_01,
	Rock_03,
	Rock_04,
	Rock01,
	Rock02,
	Rock2,
	Rock03,
	Rock3,
	Rock04,
	RockBG01,
	RockBG02,
	RockBG03,
	RockBG04,
	RockBG05,
	RockBG05_bis,
	RockIntegrationElements,
	RockIntegrationElements02,
	RockIntegrationElements03t,
	VerticalDeskCube,
	VerticalDeskCubeBack,



	Max,
};
