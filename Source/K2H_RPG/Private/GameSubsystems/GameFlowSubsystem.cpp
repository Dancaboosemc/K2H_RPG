// Daniel McPherson, All Rights Reserved


#include "GameSubsystems/GameFlowSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "K2HFunctionLibrary.h"
#include "K2HGameplayTags.h"

void UGameFlowSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
}

void UGameFlowSubsystem::Deinitialize()
{
    Super::Deinitialize();
}

void UGameFlowSubsystem::ToMainMenu()
{
    const TSoftObjectPtr<UWorld> Level = UK2HFunctionLibrary::GetSoftLevelByTag(K2HGameplayTags::Level_MainMenu);

    //TODO GAME FlOW: Revist here when thinking about load times and Loading screen flow
    if (!Level.IsNull())
        UGameplayStatics::OpenLevel(this, FName(*Level.GetLongPackageName()));
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
