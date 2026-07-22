// Daniel McPherson, All Rights Reserved


#include "Subsystems/GameFlowSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UGameFlowSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
}

void UGameFlowSubsystem::Deinitialize()
{
    Super::Deinitialize();
}

void UGameFlowSubsystem::PlayIntro()
{
   //Not sure if this is needed or not
}

void UGameFlowSubsystem::ToMainMenu()
{
    //setup maps data asset and come back here
    UGameplayStatics::OpenLevel(this, FName("MainMenu"));
}

void UGameFlowSubsystem::QuitGame()
{
    check(GetWorld());

    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        UKismetSystemLibrary::QuitGame(this, PC, EQuitPreference::Quit, false);
    }
}

void UGameFlowSubsystem::LoadMap(TSoftObjectPtr<UWorld> Map)
{
    UGameplayStatics::OpenLevelBySoftObjectPtr(this, Map);
}
