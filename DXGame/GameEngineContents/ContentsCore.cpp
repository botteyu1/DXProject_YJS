#include "PreCompile.h"
#include "ContentsCore.h"
#include "PlayLevel.h"
#include "TitleLevel.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineRenderTarget.h>
#include <GameEngineCore/GameEngineGUI.h>
#include "GUI.h"
#include "MapEditorLevel.h"
#include "BossLevel.h"
#include "Cape.h"


std::shared_ptr< GameEngineRandom> ContentsCore::MainRandom;

ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{
	GameEngineFont::Load("�ü�");
	GameEngineFont::Load("�����ý��丮");



	GameEngineGUI::CreateGUIWindow<GUI>("GUI");

	GameEngineRenderTarget* BackBuffer = GameEngineCore::GetBackBufferRenderTarget().get();
	BackBuffer->SetClearColor({ 0.0f,0.0f,0.0f,1.0f });
	//�⺻ ���÷� ����
	//GameEngineSpriteRenderer::SetDefaultSampler("POINT");
	MainRandom = std::make_shared<GameEngineRandom>();

	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<BossLevel>("BossLevel");
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<MapEditorLevel>("MapEditorLevel");
	GameEngineCore::ChangeLevel("PlayLevel");

	

	// �ڱ� �ؽ�ó �ε��ؾ� �Ѵ�.

}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}