// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameplayTagContainer.h"

#include "K2HAudioDeveloperSettings.generated.h"

class USoundControlBusMix;
class USoundControlBus;

//Struct for mapping ControlBus and Default Value to GameplayTag
USTRUCT(BlueprintType)
struct FAudioVolumeSetting
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Config)
	TSoftObjectPtr<USoundControlBus> ControlBus;

	UPROPERTY(EditAnywhere, Config)
	float DefaultValue = 1.0f;
};
/**
 * Developer Settings, contains a BusMix and FAudioVolumeSetting map for managing Volume levels
 */
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "K2H Audio Settings"))
class K2HDEVELOPERSETTINGS_API UK2HAudioDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:

	UPROPERTY(Config, EditAnywhere, Category = "Audio|Modulation")
	TSoftObjectPtr<USoundControlBusMix> DefaultBusMix;

	UPROPERTY(Config, EditAnywhere, Category = "Audio|Modulation",
		meta = (ForceInlineRow, Categories = "Audio.Volume"))
	TMap<FGameplayTag, FAudioVolumeSetting> AudioMap;
};
