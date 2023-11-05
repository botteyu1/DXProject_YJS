#include "PreCompile.h"
#include "Cape.h"


std::shared_ptr< Cape> Cape::CapeDataManager;

Cape::Cape() 
{
	Data.resize(static_cast<int>(CapeType::None));
}

Cape::~Cape()
{
}

void Cape::Start()
{
	Cape::CapeDataManager->SetImgName(CapeType::Katana, "PLACEHOLDER_KatanasB.Png");
	Cape::CapeDataManager->SetImgName(CapeType::EvilHands, "PLACEHOLDER_Big_Hands.Png");
	Cape::CapeDataManager->SetImgName(CapeType::EvilBirds, "PLACEHOLDER_EvilBirds.Png");
	Cape::CapeDataManager->SetImgName(CapeType::Tornado, "PLACEHOLDER_Wind.Png");
}

