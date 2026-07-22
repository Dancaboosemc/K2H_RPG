// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Widget_ActivatableBase.generated.h"

class AK2HPlayerController;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class K2H_RPG_API UWidget_ActivatableBase : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
protected:

	UFUNCTION(BlueprintPure)
	AK2HPlayerController* GetOwningPC();

private:

	TWeakObjectPtr<AK2HPlayerController> CachedOwningPC;
};
