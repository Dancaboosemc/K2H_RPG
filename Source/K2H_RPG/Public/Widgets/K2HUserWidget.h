// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "K2HUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class K2H_RPG_API UK2HUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintNativeEvent, Category = "Lifecycle")
	void OnShown();

	UFUNCTION(BlueprintNativeEvent, Category = "UI")
	UWidget* GetInitialFocusWidget() const;

};
