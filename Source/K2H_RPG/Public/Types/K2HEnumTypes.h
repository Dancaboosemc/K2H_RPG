#pragma once

#include "CoreMinimal.h"
#include "K2HEnumTypes.generated.h"

UENUM(BlueprintType)
enum class EConfirmScreenType : uint8
{
    OK          UMETA(DisplayName = "OK"),
    YesNo       UMETA(DisplayName = "Yes/No"),
    OKCancel    UMETA(DisplayName = "OK/Cancel"),
    Unknown     UMETA(Hidden)

};

UENUM(BlueprintType)
enum class EConfirmScreenButtonType : uint8
{
    Confrimed   UMETA(DisplayName = "Confrimed"),
    Cancelled    UMETA(DisplayName = "Canceled"),
    Closed      UMETA(DisplayName = "Closed"),
    Unknown     UMETA(Hidden)

};
