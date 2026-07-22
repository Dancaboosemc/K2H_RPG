// Daniel McPherson, All Rights Reserved


#include "Subsystems/K2HGameInstanceSubsystem.h"

//~ Begin USubsyem Interface

bool UK2HGameInstanceSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
	{
		TArray<UClass*> FoundClasses;
		GetDerivedClasses(GetClass(), FoundClasses);

		return FoundClasses.IsEmpty();
	}

	return false;
}

//~ End USubsyem Interface
