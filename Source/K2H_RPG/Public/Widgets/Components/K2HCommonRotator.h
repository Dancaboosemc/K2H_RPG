// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonRotator.h"
#include "K2HCommonRotator.generated.h"

/**
 * UCommonRotator class providing implementation for chosing a selected option
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class K2H_RPG_API UK2HCommonRotator : public UCommonRotator
{
	GENERATED_BODY()

public:

	void SetSelectedOptionByText(const FText& InTextOption);
	
};
