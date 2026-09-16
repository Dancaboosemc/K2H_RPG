// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameSubsystems/K2HGameInstanceSubsystem.h"
#include "GameFlowSubsystem.generated.h"

/**
 * Subsytem's purpose is to provide a central place to control game flow. 
 * Currently has only functionality for loading the main menu and quitting the game.
 */
UCLASS()
class K2H_RPG_API UGameFlowSubsystem : public UK2HGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void ToMainMenu();

	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void QuitGame();

private:

	//Helper Function for Loading Levels
	void LoadMap(TSoftObjectPtr<UWorld> Map);
	
};
