// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameplayTagContainer.h"

#include "K2HUIDeveloperSettings.generated.h"

class UUserWidget;
/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "K2H UI Settings"))
class K2HDEVELOPERSETTINGS_API UK2HUIDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:

	UPROPERTY(Config, EditAnywhere, Category = "WidgetReference", meta = (ForceInlineRow, Categories = "Frontend.Widget"))
	TMap<FGameplayTag, TSoftClassPtr<UUserWidget>> WidgetMap;
};
