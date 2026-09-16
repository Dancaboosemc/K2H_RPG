// Daniel McPherson, All Rights Reserved


#include "GameSubsystems/K2HGameInstanceSubsystem.h"

bool UK2HGameInstanceSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
	{
		TArray<UClass*> FoundClasses;
		GetDerivedClasses(GetClass(), FoundClasses);

		//Returns false if any subclasses were found
		return FoundClasses.IsEmpty();
	}

	return false;
}
