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

	GameEngineFont::Load("궁서");
	GameEngineFont::Load("메이플스토리");
	{
		// 이걸 세팅하는 순간
		// order가 2d랜더링의 순서가 되는것이 아니라
		// z의 값이 순서를 결정하게 되기 때문에
		D3D11_DEPTH_STENCIL_DESC Desc = { 0, };
		//BOOL DepthEnable;
		//D3D11_DEPTH_WRITE_MASK DepthWriteMask;
		//D3D11_COMPARISON_FUNC DepthFunc;
		//BOOL StencilEnable;
		//UINT8 StencilReadMask;
		//UINT8 StencilWriteMask;
		//D3D11_DEPTH_STENCILOP_DESC FrontFace;
		//D3D11_DEPTH_STENCILOP_DESC BackFace;

		Desc.DepthEnable = true;
		// 깊이 테스트만 하고 안쓸수도 있다.
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
	//기본 샘플러 지정
	//GameEngineSpriteRenderer::SetDefaultSampler("POINT");
	MainRandom = std::make_shared<GameEngineRandom>();

	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<BossLevel>("BossLevel");
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<MapEditorLevel>("MapEditorLevel");
	GameEngineCore::ChangeLevel("PlayLevel");

	

	// 자기 텍스처 로드해야 한다.

}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}