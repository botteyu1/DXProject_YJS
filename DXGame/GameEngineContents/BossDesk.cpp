#include "PreCompile.h"
#include "BossDesk.h"

BossDesk::BossDesk() 
{
}

BossDesk::~BossDesk()
{
}

void BossDesk::ChangeDeskAnimation(std::string_view _str)
{
	MainSpriteRenderer->ChangeAnimation(_str);
}

void BossDesk::Start()
{


	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::BackGroundobject);
	MainSpriteRenderer->CreateAnimation("Gargoyle_Intro_Desk", "Gargoyle_Intro_Desk", 0.0633f, -1, -1, true);
	MainSpriteRenderer->CreateAnimation("Gargoyle_Intro_Desk_Lock", "Gargoyle_Intro_Desk", 0.0633f, 0, 0, false);
	MainSpriteRenderer->ChangeAnimation("Gargoyle_Intro_Desk_Lock");
	MainSpriteRenderer->AutoSpriteSizeOn();
	//->MainSpriteRenderer->Off();
	MainSpriteRenderer->LeftFlip();
	MainSpriteRenderer->SetPivotValue({ 0.0f,1.0f });

	Transform.SetLocalPosition({ 4975.0f, -3516.0f , -4.0f });
	Off();

	//ForceGrivityOff = false;

}

void BossDesk::Update(float _Delta)
{
	if (MainSpriteRenderer->GetCurIndex() >= 6)
	{
		Transform.AddLocalPosition(float4::RIGHT * 1500.0f * _Delta);
	}
}

