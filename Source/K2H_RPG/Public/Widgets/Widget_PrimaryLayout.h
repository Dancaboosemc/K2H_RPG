// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"

#include "Widget_PrimaryLayout.generated.h"

class UCommonActivatableWidgetContainerBase;
/**
 * Widget class to act as a container for widget stacks of UCommonActivatableWidget. 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class K2H_RPG_API UWidget_PrimaryLayout : public UCommonUserWidget
{
	GENERATED_BODY()
	
public:

	//Get widget stack from RegisteredWidgetStackMap via GameplayTag
	UCommonActivatableWidgetContainerBase* FindWidgetStackByTag(const FGameplayTag& InTag) const;

protected:

	//used in to register CommonActivabtableWidgetStack's, that are added in blueprints, 
	//in the RegisteredWidgetStackMap with a WidgetStack GameplayTag
	UFUNCTION(BlueprintCallable)
	void RegisterWidgetStack(UPARAM(meta = (Categories = "WidgetStack")) FGameplayTag InStackTag,
		UCommonActivatableWidgetContainerBase* InStack);

private:

	UPROPERTY(Transient)
	TMap<FGameplayTag, UCommonActivatableWidgetContainerBase*> RegisteredWidgetStackMap;
};
