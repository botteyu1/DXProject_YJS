#include "PreCompile.h"
#include "Cape.h"


std::shared_ptr< Cape> Cape::CapeDataManager;

Cape::Cape() 
{
	Data.reserve(static_cast<int>(CapeType::Max));
}

Cape::~Cape()
{
}

