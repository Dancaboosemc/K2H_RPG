// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameplayTagContainer.h"

#include "K2HGameFlowSettings.generated.h"

/**
 * Dev Settings for storing World Map assets with GameplayTags
 */
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "K2H Game Flow Settings"))
class K2HDEVELOPERSETTINGS_API UK2HGameFlowSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UPROPERTY(Config, EditAnywhere, Category = "LevelReference",
		meta = (ForceInlineRow, Categories = "Level"))
	TMap<FGameplayTag, TSoftObjectPtr<UWorld>> LevelMap;
	
};
