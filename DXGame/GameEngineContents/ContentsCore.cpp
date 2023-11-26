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
#include <GameEngineCore/GameEngineDepthStencil.h>
#include "PlayLevel2.h"


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

	SoundLoad();

	{
		// �̰� �����ϴ� ����
		// order�� 2d�������� ������ �Ǵ°��� �ƴ϶�
		// z�� ���� ������ �����ϰ� �Ǳ� ������
		D3D11_DEPTH_STENCIL_DESC Desc = { 0, };
		//BOOL DepthEnable;
		//D3D11_DEPTH_WRITE_MASK DepthWriteMask;
		//D3D11_COMPARISON_FUNC DepthFunc;
		//BOOL StencilEnable;
		//UINT8 StencilReadMask;
		//UINT8 StencilWriteMask;
		//D3D11_DEPTH_STENCILOP_DESC FrontFace;
		//D3D11_DEPTH_STENCILOP_DESC BackFace;

		Desc.DepthEnable = false;
		// ���� �׽�Ʈ�� �ϰ� �Ⱦ����� �ִ�.
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		//Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;
		Desc.StencilEnable = false;
		std::shared_ptr<GameEngineDepthStencil> Rasterizer = GameEngineDepthStencil::Create("AlwaysDepthContents", Desc);
	}
	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("2DTextureAlwaysDepth");
		Mat->SetVertexShader("TextureShader_VS");
		Mat->SetPixelShader("TextureShader_PS");
		Mat->SetDepthState("AlwaysDepthContents");
	}


	Cape::CapeDataManager = std::make_shared<Cape>();
	Cape::CapeDataManager->Start();


	GameEngineGUI::CreateGUIWindow<GUI>("GUI");

	GameEngineRenderTarget* BackBuffer = GameEngineCore::GetBackBufferRenderTarget().get();
	BackBuffer->SetClearColor({ 0.0f,0.0f,0.0f,1.0f });
	//�⺻ ���÷� ����
	//GameEngineSpriteRenderer::SetDefaultSampler("POINT");
	MainRandom = std::make_shared<GameEngineRandom>();

	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<PlayLevel2>("PlayLevel2");
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

void ContentsCore::SoundLoad()
{
	if (nullptr == GameEngineSound::FindSound("character_move_01.wav"))
	{
		{
			GameEngineDirectory FilePath;
			FilePath.MoveParentToExistsChild("GameEngineResources");
			FilePath.MoveChild("ContentsResources\\Sound\\Effect");

			GameEngineSound::SoundLoad("Click", FilePath.PlusFilePath("Click.wav"));
		}


		{
			GameEngineDirectory FilePath;
			FilePath.MoveParentToExistsChild("GameEngineResources");
			FilePath.MoveChild("ContentsResources\\Sound\\BG");

			GameEngineSound::SoundLoad("OST Main Menu", FilePath.PlusFilePath("OST Main Menu.wav"));
			GameEngineSound::SoundLoad("Modern Warfare Department", FilePath.PlusFilePath("Modern Warfare Department.wav"));
			GameEngineSound::SoundLoad("It��s About Time (Original Soundtrack)", FilePath.PlusFilePath("It��s About Time (Original Soundtrack).wav"));
			GameEngineSound::SoundLoad("Head of Security Gargoyle (Original Soundtrack)", FilePath.PlusFilePath("Head of Security Gargoyle (Original Soundtrack).wav"));
			GameEngineSound::SoundLoad("Hall of Eternity (Original Soundtrack)", FilePath.PlusFilePath("Hall of Eternity (Original Soundtrack).wav"));
			GameEngineSound::SoundLoad("Brad in Shape (Original Soundtrack)", FilePath.PlusFilePath("Brad in Shape (Original Soundtrack).wav"));
		}
	
	}
}
