// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "GameplayTagContainer.h"

#include "AsyncAction_PushSoftWidget.generated.h"

class UWidget_ActivatableBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPushSoftWidgetDelegate, UWidget_ActivatableBase*, PushedWidget);
/**
 * Async Action for pushing a screens to UI, creates a node to be used in Blueprints
 */
UCLASS()
class K2H_RPG_API UAsyncAction_PushSoftWidget : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:

	//~ Begin UBlueprintAsyncActionBase Interface

	//This is where we call cpp implementation
	virtual void Activate() override;

	//~ End UBlueprintAsyncActionBase Interface

	//Constructor Function that creates the node object, used to Init and register the node with the game instance
	//Is required to be static, return a pointer to this class, and be marked with BlueprintInternalUseOnly = "true"
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject", 
		BlueprintInternalUseOnly = "true", DisplayName = "Push Soft Widget To Widget Stack"))
	static UAsyncAction_PushSoftWidget* PushSoftWidget(const UObject* WorldContextObject, 
		APlayerController* OwningPlayerController, TSoftClassPtr<UWidget_ActivatableBase> InsoftWidgetClass,
		UPARAM(meta = (Categories = "WidgetStack")) FGameplayTag  InWidgetStackTag,
			bool bFocusOnNewlyPushedWidget = true);

	//Delegate for returning execution to Blueprint Before Pushing the widget to the stack
	UPROPERTY(BlueprintAssignable)
	FOnPushSoftWidgetDelegate OnWidgetCreatedBeforePush;

	//Delegate for returning execution to Blueprint After Push
	UPROPERTY(BlueprintAssignable)
	FOnPushSoftWidgetDelegate AfterPush;

private:

	//Properties for storeing and passing data
	TWeakObjectPtr<UWorld> CachedOwningWorld;						//World Reference
	TWeakObjectPtr<APlayerController> CachedOwningPC;				//Player Controller Reference
	TSoftClassPtr<UWidget_ActivatableBase> CachedSoftWidgetClass;	//Widget Class to be Pushed
	FGameplayTag CachedWidgetStackTag;								//GameplayTag for stack to be pushed to
	bool bCachedFocusOnNewlyPushedWidget = false;					//bool for determining if to focus the new widget
};
