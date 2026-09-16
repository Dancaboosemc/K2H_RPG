// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameSubsystems/K2HGameInstanceSubsystem.h"
#include "Widgets/Widget_ActivatableBase.h"
#include "Types/K2HEnumTypes.h"

#include "UISubsystem.generated.h"

class UK2HCommonButtonBase;
class UWidget_PrimaryLayout;
struct FGameplayTag;

//Enum used in Callbacks for pushing widgets
enum class EAsyncPushWidgetState : uint8
{
	OnCreatedBeforePush,
	AfterPush
};

// Declared For K2HCommonButtonBase's Description Text, 
// Which should only be displayed when a button is being hovered or selected.
// Is Broadcasted from there to update WBP_Text_ButtonDescription
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonDescriptionTextUpdatedDelegate, 
	UK2HCommonButtonBase*, BroadcastingButton, FText, DescriptionText);

/**
 * Subsytem for managing UI, using Common UI plugin
 */

UCLASS()
class K2H_RPG_API UUISubsystem : public UK2HGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	//Easy Getter for subsytem, requires world context object like a widget or the world itself
	static UUISubsystem* Get(const UObject* WorldContextObject);

	//Register(Assign) Container widget, for widget stacks, with the subsystem
	void RegisterPrimaryLayoutWidget(UWidget_PrimaryLayout* InCreatedWidget);

	//Helper Function for loading and pushing widgets to a stack by Gameplay Tag.
	//requires a soft class ptr for the widget to to create, 
	//and Callbacks to be used before and after pushing the widget.
	//Callbacks must match the TFunction Structure of void (EAsyncPushWidgetState, UWidget_ActivatableBase*)
	void PushSoftWidgetToStackAsync(const FGameplayTag& InStackTag,
		TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass, 
		TFunction< void (EAsyncPushWidgetState, UWidget_ActivatableBase*) > AsyncPushStateCallback);

	//Function for pushing confirmation dialogs to the Top Widget Stack
	//Requires an EConfirmScreenType to determin the type of confirmation,
	//a message and title, and A Callback to be passed to the widget for 
	//Initailizing it's button click action.
	//Uses PushSoftWidgetToStackAsync()
	void PushConfirmScreenToModalStackAsync(EConfirmScreenType InScreenType, const FText& InScreenTitle, 
		const FText& InScreenMsg, TFunction<void(EConfirmScreenButtonType)> ButtonClickedCallback);

	//FOnButtonDescriptionTextUpdatedDelegate Definition
	UPROPERTY(BlueprintAssignable)
	FOnButtonDescriptionTextUpdatedDelegate OnButtonDescriptionTextUpdated;

private:

	//Container Widget for widget stacks
	UPROPERTY(Transient)
	UWidget_PrimaryLayout* CreatedPrimaryLayout;
};
