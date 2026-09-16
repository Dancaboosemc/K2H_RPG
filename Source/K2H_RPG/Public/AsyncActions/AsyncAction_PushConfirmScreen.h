// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Types/K2HEnumTypes.h"

#include "AsyncAction_PushConfirmScreen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConfirmScreenButtonClickedDelegate, 
	EConfirmScreenButtonType, ClickedButtontype);
/**
 * Async Action for pushing a confirmation screen to UI, creates a node to be used in Blueprints
 */
UCLASS()
class K2H_RPG_API UAsyncAction_PushConfirmScreen : public UBlueprintAsyncActionBase
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
		BlueprintInternalUseOnly = "true", DisplayName = "Show Confirmation Screen"))
	static UAsyncAction_PushConfirmScreen* PushConfirmScreen(const UObject* WorldContextObject,  
		EConfirmScreenType ScreenType, FText ScreenTitle, FText InScreenMsg);

	//Delegate for returning execution to Blueprint after a confrim button is clicked
	UPROPERTY(BlueprintAssignable)
	FOnConfirmScreenButtonClickedDelegate OnButtonClicked;

private:

	//Properties for storeing and passing data
	TWeakObjectPtr<UWorld> CachedOwningWorld;	//World Reference
	EConfirmScreenType CachedScreenType;		//Determins the type of confrim screen that is created
	FText CachedScreenTitle;					//Message Title
	FText CachedScreenMsg;						//Messgae
};
