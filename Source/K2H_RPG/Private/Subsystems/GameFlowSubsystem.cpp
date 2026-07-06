// Daniel McPherson, All Rights Reserved


#include "Subsystems/GameFlowSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UGameFlowSubsystem::PlayIntro()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 8.0f, FColor::Green, TEXT("Playing Intro"));
    }
	UE_LOG(LogTemp, Log, TEXT("Playing Intro"));
}

void UGameFlowSubsystem::ToMainMenu()
{
    if(GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 8.0f, FColor::Green, TEXT("Main Menu"));
    }
	UE_LOG(LogTemp, Log, TEXT("Main Menu"));

    //setup maps data asset and come back here
    UGameplayStatics::OpenLevel(this, FName("MainMenu"));
}

void UGameFlowSubsystem::QuitGame()
{
    check(GetWorld());

    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        UKismetSystemLibrary::QuitGame(
            this,
            PC,
            EQuitPreference::Quit,
            false
        );
    }
}

void UGameFlowSubsystem::LoadMap(TSoftObjectPtr<UWorld> Map)
{
    UGameplayStatics::OpenLevelBySoftObjectPtr(this, Map);
}
