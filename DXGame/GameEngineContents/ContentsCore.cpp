#include "PreCompile.h"
#include "ContentsCore.h"
#include "PlayLevel.h"
#include "TitleLevel.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineRenderTarget.h>

ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{

	GameEngineRenderTarget* BackBuffer = GameEngineCore::GetBackBufferRenderTarget().get();
	BackBuffer->SetClearColor({ 0.0f,0.0f,0.0f,1.0f });
	//�⺻ ���÷� ����
	//GameEngineSpriteRenderer::SetDefaultSampler("POINT");

	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::ChangeLevel("PlayLevel");

	// �ڱ� �ؽ�ó �ε��ؾ� �Ѵ�.

}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}