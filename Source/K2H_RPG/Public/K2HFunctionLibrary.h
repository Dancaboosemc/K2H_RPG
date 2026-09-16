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

	// Finds soft references, stored in K2HUIDeveloperSettings, by GameplayTag
	UFUNCTION(BlueprintPure, Category = "K2H Function Library")
	static TSoftClassPtr<UWidget_ActivatableBase> GetSoftWidgetClassByTag
	(UPARAM(meta = (Categories = "Widget")) FGameplayTag InWidgetTag);

	UFUNCTION(BlueprintPure, Category = "K2H Function Library")
	static TSoftObjectPtr<UTexture2D> GetOptionsSoftImageByTag
	(UPARAM(meta = (Categories = "Image")) FGameplayTag InImageTag);

	// Finds Level soft references, stored in K2HGameFlowSettings, by GameplayTag
	UFUNCTION(BlueprintPure, Category = "K2H Function Library")
	static TSoftObjectPtr<UWorld> GetSoftLevelByTag
	(UPARAM(meta = (Categories = "Level")) FGameplayTag InLevelTag);

	//Convert SoftClassPtr to string, gives us the class's name
	UFUNCTION(BlueprintPure, Category = "K2H Function Library")
	static FString SoftClassToString(TSoftClassPtr<UWidget_ActivatableBase> SoftClass);

};
