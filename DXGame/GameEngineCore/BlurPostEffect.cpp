#include "PreCompile.h"
#include "BlurPostEffect.h"

BlurPostEffect::BlurPostEffect() 
{
	RenderBaseInfoValue.ScreenSize = GameEngineCore::MainWindow.GetScale();
}

BlurPostEffect::~BlurPostEffect() 
{
}

void BlurPostEffect::Start()
{
	std::shared_ptr<GameEngineRenderTarget> Target = GameEngineCore::GetCurLevel()->GetMainCamera()->GetCameraAllRenderTarget();

	if (nullptr != Target)
	{
		ResultTarget = Target->CreateChildRenderTarget({ 0 });
	}

	EffectUnit.SetMesh("fullrect");
	EffectUnit.SetMaterial("BlurPostEffect");

	EffectUnit.ShaderResHelper.SetConstantBufferLink("RenderBaseInfo", RenderBaseInfoValue);
	EffectUnit.ShaderResHelper.SetTexture("DiffuseTex", EffectTarget->GetTexture(1));
	EffectUnit.ShaderResHelper.SetSampler("DiffuseTexSampler", "LINEAR");

	/*float4 WindowScale = GameEngineCore::MainWindow.GetScale();
	ResultTarget = GameEngineRenderTarget::Create();
	ResultTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);*/
}
void BlurPostEffect::EffectProcess(float _DeltaTime)
{
	ResultTarget->Setting();
	EffectUnit.Render();
	EffectUnit.ShaderResHelper.AllShaderResourcesReset();


	GameEngineRenderTarget::RenderTargetReset();
	//EffectTarget->Copy(0, ResultTarget, 0);
}