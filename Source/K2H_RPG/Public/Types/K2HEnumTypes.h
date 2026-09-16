#pragma once

#include "CoreMinimal.h"
#include "K2HEnumTypes.generated.h"

//For creating different Confirm Dialogs
UENUM(BlueprintType)
enum class EConfirmScreenType : uint8
{
    OK          UMETA(DisplayName = "OK"),
    YesNo       UMETA(DisplayName = "Yes/No"),
    OKCancel    UMETA(DisplayName = "OK/Cancel"),
    Unknown     UMETA(Hidden)

};

//For handling different Confirm outcomes
UENUM(BlueprintType)
enum class EConfirmScreenButtonType : uint8
{
    Confrimed    UMETA(DisplayName = "Confrimed"),
    Cancelled    UMETA(DisplayName = "Canceled"),
    Closed       UMETA(DisplayName = "Closed"),
    Unknown      UMETA(Hidden)

};

//Supplies reason for call when FOnListDataModifiedDelegate is used, 
//which is called when Data in a ListDataObject has changed
UENUM(BlueprintType)
enum class EOptionsListDataModifyReason : uint8
{
    DirectlyModified       UMETA(DisplayName = "DirectlyModified"),     //User Change
    DependencyModified     UMETA(DisplayName = "DependencyModified"),   //Change by another setting change
    ResetToDefault         UMETA(DisplayName = "ResetToDefault"),       //Reset to Defaults
};

//Tag for sorting Settings when running on certain platform groups
UENUM(BlueprintType)
enum class ESettingPlatform : uint8
{
    All,
    PC,
    Console
};
