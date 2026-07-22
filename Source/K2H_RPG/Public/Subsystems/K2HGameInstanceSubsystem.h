// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "K2HGameInstanceSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class K2H_RPG_API UK2HGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	//~ Begin USubsyem Interface
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	//~ End USubsyem Interface
};
