// Daniel McPherson, All Rights Reserved


#include "K2H_RPG_GameInstance.h"
#include "Subsystems/GameFlowSubsystem.h"
#include "Subsystems/AudioSubsystem.h"
#include "Subsystems/UISubsystem.h"

void UK2H_RPG_GameInstance::Init()
{
	Super::Init();

	FlowSubsystem = NewObject<UGameFlowSubsystem>(this);
	AudioSubsystem = NewObject<UAudioSubsystem>(this);
	UISubsystem = NewObject<UUISubsystem>(this);
	
}
