// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "K2HGameInstanceSubsystem.generated.h"

/**
 * Base Class for GameInstance Subsystems, implementing ShouldCreateSubsystem()
 */
UCLASS()
class K2H_RPG_API UK2HGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	//~ Begin USubsyem Interface

	// Only create this subsystem if it is the most-derived implementation.
	// Prevents both a base subsystem and one of its child classes from being instantiated.
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	//~ End USubsyem Interface
};
