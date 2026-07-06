// Daniel McPherson, All Rights Reserved


#include "K2H_RPG_GameInstance.h"
#include "Subsystems/GameFlowSubsystem.h"

void UK2H_RPG_GameInstance::Init()
{
	Super::Init();

	FlowSubsystem = NewObject<UGameFlowSubsystem>(this);
}

UGameFlowSubsystem* UK2H_RPG_GameInstance::GetFlowSubsystem()
{
	return nullptr;
}
