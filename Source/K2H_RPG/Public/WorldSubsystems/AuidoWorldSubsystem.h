// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "AuidoWorldSubsystem.generated.h"

/**
 * World Subsystem providing a place for Audio system initialzation that is required 
 * when the World has finihed setting up it's Audio Components
 */
UCLASS()
class K2H_RPG_API UAuidoWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
};
