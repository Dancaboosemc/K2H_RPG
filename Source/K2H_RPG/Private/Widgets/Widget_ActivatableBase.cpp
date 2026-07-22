// Daniel McPherson, All Rights Reserved


#include "Widgets/Widget_ActivatableBase.h"
#include "PlayerControllers/K2HPlayerController.h"


AK2HPlayerController* UWidget_ActivatableBase::GetOwningPC()
{
	if (!CachedOwningPC.IsValid())
	{
		CachedOwningPC = GetOwningPlayer<AK2HPlayerController>();
	}
	return CachedOwningPC.IsValid()? CachedOwningPC.Get() : nullptr;
}
