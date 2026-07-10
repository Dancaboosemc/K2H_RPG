#pragma once

#include "K2HAudioSettings.generated.h"

USTRUCT(BlueprintType)
struct FK2HAudioSettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MasterVolume = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MusicVolume = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AmbientVolume = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float UIVolume = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SFXVolume = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DialogueVolume = 1.0f;
};