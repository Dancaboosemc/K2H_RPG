// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"

#include "K2HFunctionLibrary.generated.h"

class UWidget_ActivatableBase;
/**
 * 
 */
UCLASS()
class K2H_RPG_API UK2HFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintPure, Category = "K2H Function Library")
	static TSoftClassPtr<UWidget_ActivatableBase> GetSoftWidgetClassByTag
	(UPARAM(meta = (Categories = "Frontend.Widget")) FGameplayTag InWidgetTag);

	UFUNCTION(BlueprintPure, Category = "K2H Function Library")
	static FString SoftClassToString(TSoftClassPtr<UWidget_ActivatableBase> SoftClass);
};
