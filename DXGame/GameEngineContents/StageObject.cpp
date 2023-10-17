#include "PreCompile.h"
#include "StageObject.h"

StageObject::StageObject() 
{
}

StageObject::~StageObject()
{
}

void StageObject::Start()
{
}

void StageObject::Update(float _Delta)
{
	if (DebugValue == true)
	{
		InputDebugUpdate(_Delta);
		return;
	}
}

