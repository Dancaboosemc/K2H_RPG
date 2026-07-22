// Daniel McPherson, All Rights Reserved


#include "K2HFunctionLibrary.h"
#include "K2HUIDeveloperSettings.h"
#include "Widgets/Widget_ActivatableBase.h"

TSoftClassPtr<UWidget_ActivatableBase> UK2HFunctionLibrary::GetSoftWidgetClassByTag
(UPARAM(meta = (Categories = "Frontend.Widget"))FGameplayTag InWidgetTag)
{
	const UK2HUIDeveloperSettings* UIDevSettings = GetDefault<UK2HUIDeveloperSettings>();
	
	checkf(UIDevSettings->WidgetMap.Contains(InWidgetTag), TEXT("Could not find Widget under Tag: %s"), *InWidgetTag.ToString());
	
	TSoftClassPtr<UUserWidget> WidgetClass = UIDevSettings->WidgetMap.FindRef(InWidgetTag);

	return TSoftClassPtr<UWidget_ActivatableBase>(WidgetClass.ToSoftObjectPath());
}

FString UK2HFunctionLibrary::SoftClassToString(TSoftClassPtr<UWidget_ActivatableBase> SoftClass)
{
	return SoftClass.ToSoftObjectPath().ToString();
}
