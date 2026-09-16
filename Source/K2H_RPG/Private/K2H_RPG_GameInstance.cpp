// Daniel McPherson, All Rights Reserved


#include "K2H_RPG_GameInstance.h"
#include "GameSubsystems/GameFlowSubsystem.h"
#include "GameSubsystems/AudioSubsystem.h"
#include "GameSubsystems/UISubsystem.h"

void UK2H_RPG_GameInstance::Init()
{
	Super::Init();

	//Create subsystems
	FlowSubsystem = NewObject<UGameFlowSubsystem>(this);
	AudioSubsystem = NewObject<UAudioSubsystem>(this);
	UISubsystem = NewObject<UUISubsystem>(this);
}
