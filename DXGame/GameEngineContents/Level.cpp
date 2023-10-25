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

Level::Level() 
{
}

Level::~Level()
{
}

std::shared_ptr<ContentObject> Level::AddActor(ActorType _Type, float4 _Pos, bool _Debug)
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
		break;
	}
	case ActorType::Ghost_Man2:
		Object = CreateActor<Ghost_Man>(ContentsObjectType::Enemy);
		break;
	case ActorType::Ghost_Man3:
		Object = CreateActor<Ghost_Man>(ContentsObjectType::Enemy);
		break;
	case ActorType::Ghost_Woman1:
		Object = CreateActor<Ghost_Woman>(ContentsObjectType::Enemy);
		break;
	case ActorType::Ghost_Woman2:
		Object = CreateActor<Ghost_Woman>(ContentsObjectType::Enemy);
		break;
	case ActorType::Ghost_Woman3:
		Object = CreateActor<Ghost_Woman>(ContentsObjectType::Enemy);
		break;
	case ActorType::Ghost_Med1:
		Object = CreateActor<Ghost_Med>(ContentsObjectType::Enemy);
		break;
	case ActorType::Ghost_Med2:
		Object = CreateActor<Ghost_Med>(ContentsObjectType::Enemy);
		break;
	case ActorType::Ghost_Med3:
		Object = CreateActor<Ghost_Med>(ContentsObjectType::Enemy);
		break;
	case ActorType::PossessedBook1:
		Object = CreateActor<PossessedBook>(ContentsObjectType::Enemy);
		break;
	case ActorType::PossessedBook2:
		Object = CreateActor<PossessedBook>(ContentsObjectType::Enemy);
		break;
	case ActorType::PossessedBook3:
		Object = CreateActor<PossessedBook>(ContentsObjectType::Enemy);
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
	default:
		break;
	}
	Object->Transform.SetLocalPosition(_Pos);
	Object->SetActorType(_Type);

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

	for (size_t i = 0; i < ObjectTypePlayer.size(); i++)
	{
		int Type = static_cast<int>(ObjectTypePlayer[i]->GetActorType());
		_Data << Type;
		
		float4 Data = ObjectTypePlayer[i]->Transform.GetLocalPosition();
		_Data << Data;

		float4 Scale = ObjectTypePlayer[i]->GetScaleValue();
		_Data << Scale;
	}
	for (size_t i = 0; i < ObjectTypeStageObject.size(); i++)
	{
		int Type = static_cast<int>(ObjectTypeStageObject[i]->GetActorType());
		_Data << Type;
		
		float4 Data = ObjectTypeStageObject[i]->Transform.GetLocalPosition();
		_Data << Data;

		float4 Scale = ObjectTypeStageObject[i]->GetScaleValue();
		_Data << Scale;
	}
	for (size_t i = 0; i < ObjectTypeEnemy.size(); i++)
	{
		int Type = static_cast<int>(ObjectTypeEnemy[i]->GetActorType());
		_Data << Type;
		
		float4 Data = ObjectTypeEnemy[i]->Transform.GetLocalPosition();
		_Data << Data;

		float4 Scale = ObjectTypeEnemy[i]->GetScaleValue();
		_Data << Scale;
	}
	for (size_t i = 0; i < ObjectTypeBackGroundobject.size(); i++)
	{
		int Type = static_cast<int>(ObjectTypeBackGroundobject[i]->GetActorType());
		_Data << Type;
		
		float4 Data = ObjectTypeBackGroundobject[i]->Transform.GetLocalPosition();
		_Data << Data;


		float4 Scale = ObjectTypeBackGroundobject[i]->GetScaleValue();
		_Data << Scale;
	}
}

void Level::DeSerializer(GameEngineSerializer& _Data, bool _Debug)
{
	float4 Data;
	float4 Scale;
	unsigned int Count = 0;
	int Type = 0;
	_Data >> Count;
	for (size_t i = 0; i < Count; i++)
	{
		_Data >> Type;
		_Data >> Data;
		_Data >> Scale;

		std::shared_ptr<ContentObject> Object = AddActor(static_cast<ActorType>(Type), Data, _Debug);
		Object->SetScaleValue(Scale);
		//std::shared_ptr<Monster> Object = _Level->CreateActor<Monster>(ContentsObjectType::Monster);
		//Object->DeSerializer(BinSer);
	}
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

