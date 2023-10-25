#include "PreCompile.h"
#include "ContentObject.h"

ContentObject::ContentObject() 
{
}

ContentObject::~ContentObject()
{
}

void ContentObject::InputDebugUpdate(float _Delta)
{
	if (DebugValue == true)
	{
		GameEngineInput::AddInputObject(this);

		float Speed = 200.0f;

		if (GameEngineInput::IsPress(VK_SPACE, this))
		{
			Speed = 500.f;
		}

		if (GameEngineInput::IsPress(VK_NUMPAD6, this))
		{
			Transform.AddLocalPosition(float4::RIGHT * Speed * _Delta);
		}

		if (GameEngineInput::IsPress(VK_NUMPAD4, this))
		{
			Transform.AddLocalPosition(float4::LEFT * Speed * _Delta);
		}

		if (GameEngineInput::IsPress(VK_NUMPAD8, this))
		{
			Transform.AddLocalPosition(float4::UP * Speed * _Delta);
		}

		if (GameEngineInput::IsPress(VK_NUMPAD2, this))
		{
			Transform.AddLocalPosition(float4::DOWN * Speed * _Delta);
		}

		if (GameEngineInput::IsPress(VK_NUMPAD1, this))
		{
			Transform.AddLocalPosition(float4::FORWARD * Speed * _Delta);
		}

		if (GameEngineInput::IsPress(VK_NUMPAD3, this))
		{
			Transform.AddLocalPosition(float4::BACKWARD * Speed * _Delta);
		}

		if (GameEngineInput::IsPress(VK_NUMPAD7, this))
		{
			ScaleValue += float4::ONE * Speed * 0.00001f;
			MainSpriteRenderer->SetAutoScaleRatio(ScaleValue);
		}

		if (GameEngineInput::IsPress(VK_NUMPAD9, this))
		{
			ScaleValue -= float4::ONE * Speed * 0.00001f;
			MainSpriteRenderer->SetAutoScaleRatio(ScaleValue);
		}

		if (GameEngineInput::IsPress('Z', this))
		{
			Transform.AddLocalPosition(float4::FORWARD * Speed * _Delta);
		}

		if (GameEngineInput::IsPress('X', this))
		{
			Transform.AddLocalPosition(float4::BACKWARD * Speed * _Delta);
		}
		
		if (GameEngineInput::IsPress('C', this))
		{
			Transform.AddLocalRotation(float4::FORWARD * Speed * _Delta * 0.1f);
		}

		if (GameEngineInput::IsPress('V', this))
		{
			Transform.AddLocalRotation(float4::FORWARD * -Speed * _Delta * 0.1f);
		}

		if (GameEngineInput::IsPress('E', this))
		{
			ScaleValue += float4::ONE * Speed * 0.00001f;
			MainSpriteRenderer->SetAutoScaleRatio(ScaleValue);
		}

		if (GameEngineInput::IsPress('Q', this))
		{
			ScaleValue -= float4::ONE * Speed * 0.00001f;
			MainSpriteRenderer->SetAutoScaleRatio(ScaleValue);
		}
		

		if (GameEngineInput::IsPress(VK_NUMPAD5, this))
		{
			
			MainSpriteRenderer->RightFlip();
		}

		if (GameEngineInput::IsPress(VK_LBUTTON, this) and static_cast<Level*>(GetLevel())->OtherWindow == false)
		{

			
			float4 Pos = GetLevel()->GetMainCamera()->GetScreenMouseDir();
			//float4 PrevPos = Transform.GetLocalPosition();
			Pos.X = -Pos.X;
			Transform.AddLocalPosition(Pos);
		}

		std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetMainCamera();
		MainSpriteRenderer->GetImageTransform();

		GameEngineDebug::DrawBox2D(MainSpriteRenderer->GetImageTransform().GetLocalScale(),Transform.GetLocalRotationEuler()
			, Transform.GetLocalPosition(), float4::GREEN, Camera.get());

		
	}
}

