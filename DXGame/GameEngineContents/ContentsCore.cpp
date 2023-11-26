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

	GameEngineFont::Load("궁서");
	GameEngineFont::Load("메이플스토리");

	ContentsCoreSoundLoad();

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

		Desc.DepthEnable = false;
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
	GameEngineCore::CreateLevel<PlayLevel2>("PlayLevel2");
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

void ContentsCore::ContentsCoreSoundLoad()
{
	
	
	{
		GameEngineDirectory FilePath;
		FilePath.MoveParentToExistsChild("GameEngineResources");
		FilePath.MoveChild("ContentsResources\\Sound\\Effect");


		GameEngineSound::SoundLoad("LevelChangeEnd", FilePath.PlusFilePath("LevelChangeEnd.wav"));
		GameEngineSound::SoundLoad("Click", FilePath.PlusFilePath("Click.wav"));
		GameEngineSound::SoundLoad("ComboAttack1", FilePath.PlusFilePath("ComboAttack1.wav"));
		GameEngineSound::SoundLoad("ComboAttack2", FilePath.PlusFilePath("ComboAttack2.wav"));
		GameEngineSound::SoundLoad("ComboAttack3", FilePath.PlusFilePath("ComboAttack3.wav"));
		GameEngineSound::SoundLoad("ComboAttack4", FilePath.PlusFilePath("ComboAttack4.wav"));

		GameEngineSound::SoundLoad("JumpComboAttack1", FilePath.PlusFilePath("JumpComboAttack1.wav"));
		GameEngineSound::SoundLoad("JumpComboAttack2", FilePath.PlusFilePath("JumpComboAttack2.wav"));
		GameEngineSound::SoundLoad("JumpComboAttack3", FilePath.PlusFilePath("JumpComboAttack3.wav"));
		GameEngineSound::SoundLoad("Katana", FilePath.PlusFilePath("Katana.wav"));
		GameEngineSound::SoundLoad("EvilBirds", FilePath.PlusFilePath("EvilBirds.wav"));
		GameEngineSound::SoundLoad("EvilHandsAerial", FilePath.PlusFilePath("EvilHandsAerial.wav"));
		GameEngineSound::SoundLoad("EvilHandsGround", FilePath.PlusFilePath("EvilHandsGround.wav"));
		GameEngineSound::SoundLoad("DownAttack", FilePath.PlusFilePath("DownAttack.wav"));
		GameEngineSound::SoundLoad("AerialAttack", FilePath.PlusFilePath("AerialAttack.wav"));
		GameEngineSound::SoundLoad("Dash", FilePath.PlusFilePath("Dash.wav"));
		GameEngineSound::SoundLoad("BookAttackInit", FilePath.PlusFilePath("BookAttackInit.wav"));
		GameEngineSound::SoundLoad("BookAttack", FilePath.PlusFilePath("BookAttack.wav"));
		GameEngineSound::SoundLoad("ManAttackInit", FilePath.PlusFilePath("ManAttackInit.wav"));
		GameEngineSound::SoundLoad("ManAttack", FilePath.PlusFilePath("ManAttack.wav"));
		GameEngineSound::SoundLoad("Jump", FilePath.PlusFilePath("Jump.wav"));

		GameEngineSound::SoundLoad("EnemyHit1", FilePath.PlusFilePath("EnemyHit1.wav"));
		GameEngineSound::SoundLoad("EnemyHit2", FilePath.PlusFilePath("EnemyHit2.wav"));
		GameEngineSound::SoundLoad("EnemyDeath1", FilePath.PlusFilePath("EnemyDeath1.wav"));
		GameEngineSound::SoundLoad("EnemyDeath2", FilePath.PlusFilePath("EnemyDeath2.wav"));

		GameEngineSound::SoundLoad("PlayerHit", FilePath.PlusFilePath("PlayerHit.wav"));
		GameEngineSound::SoundLoad("WomanAttackInit", FilePath.PlusFilePath("WomanAttackInit.wav"));
		GameEngineSound::SoundLoad("WomanAttack", FilePath.PlusFilePath("WomanAttack.wav"));
		GameEngineSound::SoundLoad("WeaponGet", FilePath.PlusFilePath("WeaponGet.wav"));
		GameEngineSound::SoundLoad("WeaponDrop", FilePath.PlusFilePath("WeaponDrop.wav"));
		GameEngineSound::SoundLoad("TransitionOuttro", FilePath.PlusFilePath("TransitionOuttro.wav"));
		GameEngineSound::SoundLoad("TransitionIntro", FilePath.PlusFilePath("TransitionIntro.wav"));
		GameEngineSound::SoundLoad("PaperWallOn", FilePath.PlusFilePath("PaperWallOn.wav"));
		GameEngineSound::SoundLoad("ElevatorEnter", FilePath.PlusFilePath("ElevatorEnter.wav"));


		
	}


	{
		GameEngineDirectory FilePath;
		FilePath.MoveParentToExistsChild("GameEngineResources");
		FilePath.MoveChild("ContentsResources\\Sound\\BG");

		GameEngineSound::SoundLoad("OST Main Menu", FilePath.PlusFilePath("OST Main Menu.wav"));
		GameEngineSound::SoundLoad("Modern Warfare Department", FilePath.PlusFilePath("Modern Warfare Department.wav"));
		GameEngineSound::SoundLoad("It’s About Time", FilePath.PlusFilePath("It’s About Time (Original Soundtrack).wav"));
		GameEngineSound::SoundLoad("Head of Security Gargoyle", FilePath.PlusFilePath("Head of Security Gargoyle (Original Soundtrack).wav"));
		GameEngineSound::SoundLoad("Hall of Eternity", FilePath.PlusFilePath("Hall of Eternity (Original Soundtrack).wav"));
		GameEngineSound::SoundLoad("Brad in Shape", FilePath.PlusFilePath("Brad in Shape (Original Soundtrack).wav"));
	}
	
	
}
