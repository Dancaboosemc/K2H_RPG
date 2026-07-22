// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/K2HGameInstanceSubsystem.h"
#include "GameFlowSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class K2H_RPG_API UGameFlowSubsystem : public UK2HGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void PlayIntro();

	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void ToMainMenu();

	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void QuitGame();

private:

	void LoadMap(TSoftObjectPtr<UWorld> Map);
	
};
