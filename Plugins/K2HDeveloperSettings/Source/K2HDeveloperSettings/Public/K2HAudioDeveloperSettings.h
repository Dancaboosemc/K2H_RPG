// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"

#include "K2HAudioDeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "K2H Audio Settings"))
class K2HDEVELOPERSETTINGS_API UK2HAudioDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

    UPROPERTY(Config, EditAnywhere, Category = "Audio")
    float DefaultMasterVolume = 1.0f;

    UPROPERTY(Config, EditAnywhere, Category = "Audio")
    float DefaultMusicVolume = 1.0f;

    UPROPERTY(Config, EditAnywhere, Category = "Audio")
    float DefaultAmbientVolume = 1.0f;

    UPROPERTY(Config, EditAnywhere, Category = "Audio")
    float DefaultUIVolume = 1.0f;

    UPROPERTY(Config, EditAnywhere, Category = "Audio")
    float DefaultSFXVolume = 1.0f;

    UPROPERTY(Config, EditAnywhere, Category = "Audio")
    float DefaultDialogueVolume = 1.0f;
};
