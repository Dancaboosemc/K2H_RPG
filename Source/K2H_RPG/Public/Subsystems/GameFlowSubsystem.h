// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameFlowSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class K2H_RPG_API UGameFlowSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void PlayIntro();

	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void ToMainMenu();

	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void QuitGame();

private:

	void LoadMap(TSoftObjectPtr<UWorld> Map);
	
};
