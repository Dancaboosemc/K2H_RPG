// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameplayTagContainer.h"

#include "K2HUIDeveloperSettings.generated.h"

class UUserWidget;

/**
 * Has reference maps needed for UI
 */

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "K2H UI Settings"))
class K2HDEVELOPERSETTINGS_API UK2HUIDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:

	//Widget Map
	UPROPERTY(Config, EditAnywhere, Category = "WidgetReference", 
		meta = (ForceInlineRow, Categories = "Widget"))
	TMap<FGameplayTag, TSoftClassPtr<UUserWidget>> WidgetMap;

	//Image Map
	UPROPERTY(Config, EditAnywhere, Category = "OptionsImageReference", 
		meta = (ForceInlineRow, Categories = "Image"))
	TMap<FGameplayTag, TSoftObjectPtr<UTexture2D>> OptionsScreenSoftImageMap;
};
