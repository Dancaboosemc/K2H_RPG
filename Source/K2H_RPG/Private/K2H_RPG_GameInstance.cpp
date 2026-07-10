// Daniel McPherson, All Rights Reserved


#include "K2H_RPG_GameInstance.h"
#include "Subsystems/GameFlowSubsystem.h"
#include "Subsystems/AudioSubsystem.h"

void UK2H_RPG_GameInstance::Init()
{
	Super::Init();

	FlowSubsystem = NewObject<UGameFlowSubsystem>(this);
	AudioSubsystem = NewObject<UAudioSubsystem>(this);
	
}

UGameFlowSubsystem* UK2H_RPG_GameInstance::GetFlowSubsystem()
{
	return nullptr;
}

UAudioSubsystem* UK2H_RPG_GameInstance::GetAudioSubsystem()
{
	return nullptr;
}
