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
		float Speed = 200.0f;

		if (GameEngineInput::IsPress(VK_LSHIFT, this))
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
	}
	
}

