#include "PreCompile.h"
#include "BossLevel.h"

#include "BossGargoyle.h"
#include "PlayMap.h"
#include "Player.h"
#include "FX.h"

BossLevel::BossLevel() 
{
}

BossLevel::~BossLevel()
{
}

void BossLevel::Start()
{
	{
		std::shared_ptr<Player> Object = CreateActor<Player>(ContentsObjectType::Player);
	}

	{
		std::shared_ptr<PlayMap> Object = CreateActor<PlayMap>(ContentsObjectType::BackGround);
		Object->Init("StageBoss.dds", "StagePixelBoss.png");
		SetMap(Object);
	}

	FXActor = CreateActor<FX>(ContentsObjectType::FX);
}

void BossLevel::Update(float _Delta)
{
}

void BossLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
}

void BossLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
}
