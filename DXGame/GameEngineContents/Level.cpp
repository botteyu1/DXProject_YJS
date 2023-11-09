#include "PreCompile.h"
#include "Level.h"
#include "Player.h"
#include "PlayMap.h"
#include "Ghost_Man.h"
#include "Ghost_Woman.h"
#include "PossessedBook.h"
#include "Ghost_Med.h" 
#include "Elevator.h"
#include "GUI.h"
#include "BGObject.h"
#include "FX.h"
#include "BossGargoyle.h"
#include "Map.h"
#include "Shader.h"
#include "WeaponDrop.h"
#include "PaperWall.h"
#include "LevelChanger.h"
#include "Contractor.h"

Level::Level() 
{
}

Level::~Level()
{
}

std::shared_ptr<ContentObject> Level::AddActor(ActorType _Type, float4 _Pos, float4 _Rotation,bool _Flip, bool _Debug)
{
	std::shared_ptr<ContentObject> Object;
	switch (_Type)
	{
	case ActorType::Player:
	{
		Object = CreateActor<Player>(ContentsObjectType::Player);
		break;
	}
	case ActorType::Ghost_Man1:
	{
		Object = CreateActor<Ghost_Man>(ContentsObjectType::Enemy);
		static int Num = 0;
		Num++;
		static_cast<Ghost_Man*>(Object.get())->Init(1);
		Object->SetName("Ghost_Man1_" + std::to_string(Num));
		break;
	}
	case ActorType::Ghost_Man2:
	{ 
		std::shared_ptr<Ghost_Man> EnemyObject = CreateActor<Ghost_Man>(ContentsObjectType::Enemy);
		Object = EnemyObject;
		static int Num = 0;
		Num++;
		EnemyObject->Init(2);
		Object->SetName("Ghost_Man2_" + std::to_string(Num));
		GimicEnemyvec.push_back(EnemyObject);
		break;
	}
		break;
	case ActorType::Ghost_Man3:
	{
		std::shared_ptr<Ghost_Man> EnemyObject = CreateActor<Ghost_Man>(ContentsObjectType::Enemy);
		Object = EnemyObject;
		static int Num = 0;
		Num++;
		static_cast<Ghost_Man*>(Object.get())->Init(2);
		Object->SetName("Ghost_Man3_" + std::to_string(Num));
		Gimic2Enemyvec.push_back(EnemyObject);
		break;
	}
		break;
	case ActorType::Ghost_Woman1:
	{
		std::shared_ptr<Ghost_Woman> EnemyObject = CreateActor<Ghost_Woman>(ContentsObjectType::Enemy);
		Object = EnemyObject;
		static int Num = 0;
		Num++;
		Object->SetName("Ghost_Woman1_" + std::to_string(Num));
		
	}
		break;
	case ActorType::Ghost_Woman2:
	{	
		std::shared_ptr<Ghost_Woman> EnemyObject = CreateActor<Ghost_Woman>(ContentsObjectType::Enemy);
		Object = EnemyObject;
		static int Num = 0;
		Num++;
		Object->SetName("Ghost_Woman2_" + std::to_string(Num));
		GimicEnemyvec.push_back(EnemyObject);
	}
		break;
	case ActorType::Ghost_Woman3:
	{
		std::shared_ptr<Ghost_Woman> EnemyObject = CreateActor<Ghost_Woman>(ContentsObjectType::Enemy);
		Object = EnemyObject;
		static int Num = 0;
		Num++;
		Object->SetName("Ghost_Woman3_" + std::to_string(Num));
		Gimic2Enemyvec.push_back(EnemyObject);
	}
		break;
	case ActorType::Ghost_Med1:
	{
		Object = CreateActor<Ghost_Med>(ContentsObjectType::Enemy);
		static int Num = 0;
		Num++;
		Object->SetName("Ghost_Med1_" + std::to_string(Num));
	}
		break;
	case ActorType::Ghost_Med2: 
	{
		std::shared_ptr<Ghost_Med> EnemyObject = CreateActor<Ghost_Med>(ContentsObjectType::Enemy);
		Object = EnemyObject;
		static int Num = 0;
		Num++;
		Object->SetName("Ghost_Med2_" + std::to_string(Num));
		GimicEnemyvec.push_back(EnemyObject);
	}
		break;
	case ActorType::Ghost_Med3: 
	{
		std::shared_ptr<Ghost_Med> EnemyObject = CreateActor<Ghost_Med>(ContentsObjectType::Enemy);
		Object = EnemyObject;
		static int Num = 0;
		Num++;
		Object->SetName("Ghost_Med3_" + std::to_string(Num));
		Gimic2Enemyvec.push_back(EnemyObject);
	}
		break;
	case ActorType::PossessedBook1:
	{
		std::shared_ptr<PossessedBook> EnemyObject = CreateActor<PossessedBook>(ContentsObjectType::Enemy);
		Object = EnemyObject;
		static int Num = 0;
		Num++;
		Object->SetName("PossessedBook1_" + std::to_string(Num));
		
	}
		break;
	case ActorType::PossessedBook2:
	{
		std::shared_ptr<PossessedBook> EnemyObject = CreateActor<PossessedBook>(ContentsObjectType::Enemy);
		Object = EnemyObject;
		static int Num = 0;
		Num++;
		Object->SetName("PossessedBook2_" + std::to_string(Num));
		GimicEnemyvec.push_back(EnemyObject);
	}
		break;
	case ActorType::PossessedBook3:
	{
		std::shared_ptr<PossessedBook> EnemyObject = CreateActor<PossessedBook>(ContentsObjectType::Enemy);
		Object = EnemyObject;
		static int Num = 0;
		Num++;
		Object->SetName("PossessedBook3_" + std::to_string(Num));
		Gimic2Enemyvec.push_back(EnemyObject);
	}
		break;
	case ActorType::ElevatorStart:
		Object = CreateActor<Elevator>(ContentsObjectType::StageObject);
		static_cast<Elevator*>(Object.get())->Init(ElevatorState::Start);
		break;
	case ActorType::ElevatorStatic:
		Object = CreateActor<Elevator>(ContentsObjectType::StageObject);
		static_cast<Elevator*>(Object.get())->Init(ElevatorState::Static);
		break;
	case ActorType::ElevatorEnd:
		Object = CreateActor<Elevator>(ContentsObjectType::StageObject);
		static_cast<Elevator*>(Object.get())->Init(ElevatorState::End);
		break;
	case ActorType::BackWall_Big:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("BackWall_Big.png");
		break;
	case ActorType::BackWall_Down:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("BackWall_Down.png");
		break;
	case ActorType::BackWall_LeftT:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("BackWall_LeftT.png");
		break;
	case ActorType::BackWall_LeftT_A:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("BackWall_LeftT_A.png");
		break;
	case ActorType::BackWall_Middle:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("BackWall_Middle.png");
		break;
	case ActorType::BackWall_Window:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("BackWall_Window.png");
		break;
	case ActorType::BackWall_Window05:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("BackWall_Window05.png");
		break;
	case ActorType::Bibli_Raw_Kit:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Bibli_Raw_Kit.png");
		break;
	case ActorType::Bibli_WIP_02:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Bibli_WIP_02.png");
		break;
	case ActorType::BossDesk:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("BossDesk.png");
		break;
	case ActorType::coloneComplete:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("coloneComplete.png");
		break;
	case ActorType::Colonnade02:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Colonnade02.png");
		break;
	case ActorType::Column01B:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Column01B.png");
		break;
	case ActorType::Column04:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Column04.png");
		break;
	case ActorType::Column05:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Column05.png");
		break;
	case ActorType::ColumnDown01:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("ColumnDown01.png");
		break;
	case ActorType::Desk:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Desk.png");
		break;
	case ActorType::Desk01:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Desk01.png");
		break;
	case ActorType::Desk1:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Desk1.png");
		break;
	case ActorType::Desk2:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Desk2.png");
		break;
	case ActorType::Desk2_NoScreen:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Desk2_NoScreen.png");
		break;
	case ActorType::Desk3:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Desk3.png");
		break;
	case ActorType::Desk3_NoScreen:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Desk3_NoScreen.png");
		break;
	case ActorType::Escalator_02:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Escalator_02.png");
		break;
	case ActorType::Escalator_09:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Escalator_09.png");
		break;
	case ActorType::Escalator_Frieze:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Escalator_Frieze.png");
		break;
	case ActorType::GhostWorkersBox1:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("GhostWorkersBox1.png");
		break;
	case ActorType::GhostWorkersBox2:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("GhostWorkersBox2.png");
		break;
	case ActorType::GhostWorkersBox3:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("GhostWorkersBox3.png");
		break;
	case ActorType::GhostWorkersBox11:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("GhostWorkersBox11.png");
		break;
	case ActorType::GhostWorkersBox22:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("GhostWorkersBox22.png");
		break;
	case ActorType::GPE_DifficultyMode_Wall:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("GPE_DifficultyMode_Wall.png");
		break;
	case ActorType::GPE_Paper_Piles_Line:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("GPE_Paper_Piles_Line.png");
		break;
	case ActorType::lamp2:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("lamp2.png");
		break;
	case ActorType::lamp3:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("lamp3.png");
		break;
	case ActorType::lamp4:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("lamp4.png");
		break;
	case ActorType::OfficeCabinet2:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("OfficeCabinet2.png");
		break;
	case ActorType::OfficeCabinet3:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("OfficeCabinet3.png");
		break;
	case ActorType::OfficeCabinet4:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("OfficeCabinet4.png");
		break;
	case ActorType::PipeFrieze2:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("PipeFrieze2.png");
		break;
	case ActorType::Rock_01:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Rock_01.png");
		break;
	case ActorType::Rock_03:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Rock_03.png");
		break;
	case ActorType::Rock_04:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Rock_04.png");
		break;
	case ActorType::Rock01:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Rock01.png");
		break;
	case ActorType::Rock02:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Rock02.png");
		break;
	case ActorType::Rock2:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Rock2.png");
		break;
	case ActorType::Rock03:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Rock03.png");
		break;
	case ActorType::Rock3:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Rock3.png");
		break;
	case ActorType::Rock04:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Rock04.png");
		break;
	case ActorType::RockBG01:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("RockBG01.png");
		break;
	case ActorType::RockBG02:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("RockBG02.png");
		break;
	case ActorType::RockBG03:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("RockBG03.png");
		break;
	case ActorType::RockBG04:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("RockBG04.png");
		break;
	case ActorType::RockBG05:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("RockBG05.png");
		break;
	case ActorType::RockBG05_bis:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("RockBG05_bis.png");
		break;
	case ActorType::RockIntegrationElements:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("RockIntegrationElements.png");
		break;
	case ActorType::RockIntegrationElements02:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("RockIntegrationElements02.png");
		break;
	case ActorType::RockIntegrationElements03t:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("RockIntegrationElements03t.png");
		break;
	case ActorType::VerticalDeskCube:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("VerticalDeskCube.png");
		break;
	case ActorType::VerticalDeskCubeBack:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("VerticalDeskCubeBack.png");
		break;
	case ActorType::GraphicStats01:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("GraphicStats01.png");
		break;
	case ActorType::GPE_WeaponX_Choice:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("GPE_WeaponX_Choice.png");
		break;
	case ActorType::Column02:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Column02.png");
		break;
	case ActorType::Column03:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Column03.png");
		break;
	case ActorType::Column06:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Column06.png");
		break;
	case ActorType::Cutton:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Cutton.png");
		break;
	case ActorType::Church:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Church.png");
		break;

	case ActorType::Pillar01:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Pillar01.png");
		break;
	case ActorType::Pillar02:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Pillar02.png");
		break;
	case ActorType::Pillar04:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Pillar04.png");
		break;
	case ActorType::Pillar05:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Pillar05.png");
		break;
	case ActorType::woker1:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("worker1.png");
		break;
	case ActorType::woker2:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("woker2.png");
		break;
	case ActorType::woker3:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("woker3.png");
		break;
	case ActorType::woker4:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("woker4.png");
		break;
	case ActorType::woker5:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("woker5.png");
		break;
	case ActorType::woker6:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("woker6.png");
		break;
	case ActorType::woker7:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("woker7.png");
		break;
	case ActorType::woker8:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("woker8.png");
		break;
	case ActorType::woker9:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("woker9.png");
		break;
	case ActorType::Scythe1:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Scythe1.png");
		break;
	case ActorType::Scythe2:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Scythe2.png");
		break;
	case ActorType::Scythe3:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Scythe3.png");
		break;
	case ActorType::Scythe4:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Scythe4.png");
		break;
	case ActorType::ColumnDown02:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("ColumnDown02.png");
		break;
	case ActorType::Bathc_Of_Graves_01:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Bathc_Of_Graves_01.png");
		break;
	case ActorType::Bathc_Of_Graves_02:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Bathc_Of_Graves_02.png");
		break;
	case ActorType::Bench01:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Bench01.png");
		break;
	case ActorType::Bench02:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Bench02.png");
		break;
	case ActorType::Bench03:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("Bench03.png");
		break;
		
	case ActorType::BonesPile1:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("BonesPile1.png");
		break;
	case ActorType::BonesPile4:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("BonesPile4.png");
		break;
	case ActorType::W1_Boss:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("W1_Boss.png");
		break;
	case ActorType::W1_Door_01:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("W1_Door_01.png");
		break;
		
	case ActorType::W1_Door_02:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("W1_Door_02.png");
		break;
	case ActorType::W1_Door_03:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("W1_Door_03.png");
		break;
	case ActorType::W1_Door_04:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("W1_Door_04.png");
		break;
	case ActorType::W1_Door_05:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("W1_Door_05.png");
		break;
	case ActorType::W1_Door_06:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("W1_Door_06.png");
		break;
		
	case ActorType::W1_Entre:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("W1_Entre.png");
		break;
	case ActorType::W1_Kit_:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("W1_Kit_.png");
		break;
	case ActorType::W1_Miniboss:
		Object = CreateActor<BGObject>(ContentsObjectType::BackGroundobject);
		static_cast<BGObject*>(Object.get())->Init("W1_Miniboss.png");
		break;
	case ActorType::WeaponDrop1:
		Object = CreateActor<WeaponDrop>(ContentsObjectType::BackGroundobject);
		//static_cast<WeaponDrop*>(Object.get())->Init("W1_Miniboss.png");
		break;
	case ActorType::WeaponDrop2:
		Object = CreateActor<WeaponDrop>(ContentsObjectType::BackGroundobject);
		//static_cast<WeaponDrop*>(Object.get())->Init("W1_Miniboss.png");
		break;
	case ActorType::WeaponDrop3:
		Object = CreateActor<WeaponDrop>(ContentsObjectType::BackGroundobject);
		//static_cast<WeaponDrop*>(Object.get())->Init("W1_Miniboss.png");
		break;
	case ActorType::PaperWall:
	{
		std::shared_ptr<class PaperWall> PaperWallObject = CreateActor<PaperWall>(ContentsObjectType::BackGroundobject);
		Object = PaperWallObject;
		PaperWallvec.push_back(PaperWallObject);
		break;
	}

	case ActorType::Contractor:
		Object = CreateActor<Contractor>(ContentsObjectType::BackGroundobject);
		//static_cast<WeaponDrop*>(Object.get())->Init("W1_Miniboss.png");
		break;

	default:
		break;
	}


	Object->Transform.SetLocalPosition(_Pos);
	Object->Transform.SetLocalRotation(_Rotation);
	Object->SetActorType(_Type);
	if (_Flip == true)
	{
		Object->LeftFlip();
	}

	if (_Debug == true)
	{
		Object->DebugValue = true;
		Object->On();
	}

	return Object;
}

void Level::Serializer(GameEngineSerializer& _Data)
{
	std::vector<std::shared_ptr<ContentObject>> ObjectTypePlayer = GetObjectGroupConvert<ContentObject>(ContentsObjectType::Player);
	std::vector<std::shared_ptr<ContentObject>> ObjectTypeStageObject = GetObjectGroupConvert<ContentObject>(ContentsObjectType::StageObject);
	std::vector<std::shared_ptr<ContentObject>> ObjectTypeEnemy = GetObjectGroupConvert<ContentObject>(ContentsObjectType::Enemy);
	std::vector<std::shared_ptr<ContentObject>> ObjectTypeBackGroundobject = GetObjectGroupConvert<ContentObject>(ContentsObjectType::BackGroundobject);
	_Data << static_cast<unsigned int>(ObjectTypePlayer.size() + ObjectTypeStageObject.size() + ObjectTypeEnemy.size() + ObjectTypeBackGroundobject.size());

	SerializerObject(_Data, ObjectTypePlayer);
	SerializerObject(_Data, ObjectTypeStageObject);
	SerializerObject(_Data, ObjectTypeEnemy);
	SerializerObject(_Data, ObjectTypeBackGroundobject);
}

void Level::SerializerObject(GameEngineSerializer& _Data, std::vector<std::shared_ptr<ContentObject>> _vector)
{
	for (size_t i = 0; i < _vector.size(); i++)
	{
		int Type = static_cast<int>(_vector[i]->GetActorType());
		_Data << Type;

		float4 Data = _vector[i]->Transform.GetLocalPosition();
		_Data << Data;

		float4 Rotation = _vector[i]->Transform.GetLocalRotationEuler();
		_Data << Rotation;

		float4 Scale = _vector[i]->GetScaleValue();
		_Data << Scale;

		bool Flip = _vector[i]->Flip;
		_Data << Flip;
	}
}

std::shared_ptr<ContentObject> Level::CopyObject(std::shared_ptr<ContentObject> _Object)
{

	int Type = static_cast<int>(_Object->GetActorType());

	float4 Data = _Object->Transform.GetLocalPosition();

	float4 Rotation = _Object->Transform.GetLocalRotationEuler();

	float4 Scale = _Object->GetScaleValue();

	bool Flip = _Object->Flip;

	std::shared_ptr<ContentObject> Object = AddActor(static_cast<ActorType>(Type), Data, Rotation, Flip, true);
	Object->SetScaleValue(Scale);
	return Object;
}

void Level::DeSerializer(GameEngineSerializer& _Data, bool _Debug)
{
	float4 Data;
	float4 Rotation;
	float4 Scale;
	unsigned int Count = 0;
	int Type = 0;
	bool Flip = false;
	_Data >> Count;
	for (size_t i = 0; i < Count; i++)
	{
		_Data >> Type;
		_Data >> Data;
		_Data >> Rotation;
		_Data >> Scale;
		_Data >> Flip;

		std::shared_ptr<ContentObject> Object = AddActor(static_cast<ActorType>(Type), Data, Rotation, Flip,  _Debug);
		Object->SetScaleValue(Scale);
		//std::shared_ptr<Monster> Object = _Level->CreateActor<Monster>(ContentsObjectType::Monster);
		//Object->DeSerializer(BinSer);
	}
}



void Level::LevelChangerStart(std::string_view _Name)
{
	LevelChangerPtr->LevelChangeStart(_Name);
}


void Level::ClearContentsObject()
{
	std::vector<std::shared_ptr<ContentObject>> ObjectTypePlayer = GetObjectGroupConvert<ContentObject>(ContentsObjectType::Player);
	std::vector<std::shared_ptr<ContentObject>> ObjectTypeStageObject = GetObjectGroupConvert<ContentObject>(ContentsObjectType::StageObject);
	std::vector<std::shared_ptr<ContentObject>> ObjectTypeEnemy = GetObjectGroupConvert<ContentObject>(ContentsObjectType::Enemy);
	std::vector<std::shared_ptr<ContentObject>> ObjectTypeBackGroundobject = GetObjectGroupConvert<ContentObject>(ContentsObjectType::BackGroundobject);

	// ´Ù Á×ÀÎ´Ù.
	for (size_t i = 0; i < ObjectTypePlayer.size(); i++)
		{			
			ObjectTypePlayer[i]->Death();
		}
	for (size_t i = 0; i < ObjectTypeStageObject.size(); i++)
		{
			ObjectTypeStageObject[i]->Death();
		}
	for (size_t i = 0; i < ObjectTypeEnemy.size(); i++)
		{
			ObjectTypeEnemy[i]->Death();
		}
	for (size_t i = 0; i < ObjectTypeBackGroundobject.size(); i++)
		{
			ObjectTypeBackGroundobject[i]->Death();
		}
}

void Level::Start()
{
	GetMainCamera()->SetZSort<ContentsRenderType>(ContentsRenderType::BackGroundobject);
	GetMainCamera()->SetZSort<ContentsRenderType>(ContentsRenderType::Enemy);
	GetMainCamera()->SetZSort<ContentsRenderType>(ContentsRenderType::SecondaryRenderer);
	GetMainCamera()->SetZSort<ContentsRenderType>(ContentsRenderType::Enemy_Attack);
	GetMainCamera()->SetZSort<ContentsRenderType>(ContentsRenderType::FX);
	ShaderActor = CreateActor<Shader>(ContentsObjectType::Shader);
	LevelChangerPtr = CreateActor<LevelChanger>(ContentsObjectType::Shader);
	GameEngineLevel::IsDebug = false;
}

void Level::Update(float _Delta)
{
	
}

