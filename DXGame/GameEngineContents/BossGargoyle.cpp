#include "PreCompile.h"	
#include "BossGargoyle.h"

BossGargoyle::BossGargoyle() 
{
}

BossGargoyle::~BossGargoyle()
{
}

void BossGargoyle::Start()
{
	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Enemy);
	MainSpriteRenderer->CreateAnimation("Gargoyle_Combo1", "Gargoyle_Combo1", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Combo1", { 0.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Combo2", "Gargoyle_Combo2", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Combo2", { 0.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Combo3", "Gargoyle_Combo3", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Combo3", { 0.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Dive_Attack_End", "Gargoyle_Dive_Attack_End", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Dive_Attack_End", { 0.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Dive_Attack_Loop", "Gargoyle_Dive_Attack_Loop", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Dive_Attack_Loop", { 0.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_DiveAttack_Anticipation", "Gargoyle_DiveAttack_Anticipation", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_DiveAttack_Anticipation", { 0.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_End_1", "Gargoyle_End_1", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_End_1", { 0.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_End_2", "Gargoyle_End_2", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_End_2", { 0.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Fly_Stomp_Anticipation", "Gargoyle_Fly_Stomp_Anticipation", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Fly_Stomp_Anticipation", { 0.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Fly_Stomp_Anticipation", "Gargoyle_Fly_Stomp_Anticipation", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Fly_Stomp_Anticipation", { 0.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Hit", "Gargoyle_Hit", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Hit", { 0.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Intro", "Gargoyle_Intro", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Intro", { 0.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Posing", "Gargoyle_Posing", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Posing", { 0.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_SpinAir", "Gargoyle_SpinAir", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_SpinAir", { 0.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_SpinGround", "Gargoyle_SpinGround", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_SpinGround", { 0.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Stun_End", "Gargoyle_Stun_End", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Stun_End", { 0.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Stun_idle", "Gargoyle_Stun_idle", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Stun_idle", { 0.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Stun_Start", "Gargoyle_Stun_Start", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Stun_Start", { 0.0f }));

	MainSpriteRenderer->CreateAnimation("Gargoyle_Uturn", "Gargoyle_Uturn", 0.0666f, -1, -1, true);
	AnimationDataMap.insert(std::pair<std::string, AnimationData>("Gargoyle_Uturn", { 0.0f }));

}

void BossGargoyle::Update(float _Delta)
{
}

