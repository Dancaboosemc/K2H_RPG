#pragma once

#include "CoreMinimal.h"
#include "AudioTypes.generated.h"

UENUM(BlueprintType)
enum class EAudioChannel : uint8
{
    Master     UMETA(DisplayName = "Master"),
    Music      UMETA(DisplayName = "Music"),
    UI         UMETA(DisplayName = "UI"),
    SFX        UMETA(DisplayName = "SFX"),
    Ambience   UMETA(DisplayName = "Ambience"),
    Dialogue   UMETA(DisplayName = "Dialogue")
};