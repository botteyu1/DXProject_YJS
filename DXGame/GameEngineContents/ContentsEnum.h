#pragma once

enum class ContentsRenderType
{
	//StageObject,
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
	Shader,

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
	Bibli_Raw_Kit,
	Bibli_WIP_02,
	GraphicStats01,
	GPE_WeaponX_Choice,
	Column02,
	Column03,
	Column06,
	Cutton,
	Church,
	Pillar01,
	Pillar02,
	Pillar04,
	Pillar05,
	woker1,
	woker2,
	woker3,
	woker4,
	woker5,
	woker6,
	woker7,
	woker8,
	woker9,
	Scythe1,
	Scythe2,
	Scythe3,
	Scythe4,
	ColumnDown02,
	Bathc_Of_Graves_01,
	Bathc_Of_Graves_02,
	Bench01,
	Bench02,
	Bench03,
	BonesPile1,
	BonesPile4,
	W1_Boss,
	W1_Door_01,
	W1_Door_02,
	W1_Door_03,
	W1_Door_04,
	W1_Door_05,
	W1_Door_06,
	W1_Entre,
	W1_Kit_,
	W1_Miniboss,


	Max,
};
