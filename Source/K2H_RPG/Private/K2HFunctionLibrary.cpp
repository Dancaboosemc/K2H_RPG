// Daniel McPherson, All Rights Reserved


#include "K2HFunctionLibrary.h"
#include "K2HUIDeveloperSettings.h"
#include "K2HGameFlowSettings.h"
#include "Widgets/Widget_ActivatableBase.h"

TSoftClassPtr<UWidget_ActivatableBase> UK2HFunctionLibrary::GetSoftWidgetClassByTag
(UPARAM(meta = (Categories = "Widget")) FGameplayTag InWidgetTag)
{
	const UK2HUIDeveloperSettings* UIDevSettings = GetDefault<UK2HUIDeveloperSettings>();
	
	checkf(UIDevSettings->WidgetMap.Contains(
		InWidgetTag), TEXT("Could not find Widget under Tag: %s"), *InWidgetTag.ToString());
	
	TSoftClassPtr<UUserWidget> WidgetClass = UIDevSettings->WidgetMap.FindRef(InWidgetTag);

	return TSoftClassPtr<UWidget_ActivatableBase>(WidgetClass.ToSoftObjectPath());
}

TSoftObjectPtr<UTexture2D> UK2HFunctionLibrary::GetOptionsSoftImageByTag(
	UPARAM(meta = (Categories = "Image")) FGameplayTag InImageTag)
{
	const UK2HUIDeveloperSettings* UIDevSettings = GetDefault<UK2HUIDeveloperSettings>();

	checkf(UIDevSettings->OptionsScreenSoftImageMap.Contains(
		InImageTag), TEXT("Could not find Image under Tag: %s"), *InImageTag.ToString());

	return UIDevSettings->OptionsScreenSoftImageMap.FindRef(InImageTag);
}

TSoftObjectPtr<UWorld> UK2HFunctionLibrary::GetSoftLevelByTag(
	UPARAM(meta = (Categories = "Level")) FGameplayTag InLevelTag)
{
	const UK2HGameFlowSettings* GameFlowSettings = GetDefault<UK2HGameFlowSettings>();

	checkf(GameFlowSettings->LevelMap.Contains(
		InLevelTag), TEXT("Could not find Image under Tag: %s"), *InLevelTag.ToString());

	return GameFlowSettings->LevelMap.FindRef(InLevelTag);
}

FString UK2HFunctionLibrary::SoftClassToString(TSoftClassPtr<UWidget_ActivatableBase> SoftClass)
{
	return SoftClass.ToSoftObjectPath().ToString();
}
