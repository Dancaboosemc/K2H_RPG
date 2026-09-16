// Daniel McPherson, All Rights Reserved


#include "WorldSubsystems/AuidoWorldSubsystem.h"
#include "GameSubsystems/AudioSubsystem.h"

void UAuidoWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	if (UAudioSubsystem* AudioSubsystem = InWorld.GetGameInstance()->GetSubsystem<UAudioSubsystem>())
	{
		AudioSubsystem->OnWorldReady(&InWorld);
	}
}
