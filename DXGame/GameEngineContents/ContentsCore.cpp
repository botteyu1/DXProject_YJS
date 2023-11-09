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
	GameEngineCore::CreateLevel<BossLevel>("BossLevel");
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<MapEditorLevel>("MapEditorLevel");
	GameEngineCore::ChangeLevel("TitleLevel");

	

	// �ڱ� �ؽ�ó �ε��ؾ� �Ѵ�.

}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}