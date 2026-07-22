// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/K2HGameInstanceSubsystem.h"
#include "Widgets/Widget_ActivatableBase.h"
#include "Types/K2HEnumTypes.h"

#include "UISubsystem.generated.h"

class UK2HCommonButtonBase;
class UWidget_PrimaryLayout;
struct FGameplayTag;

enum class EAsyncPushWidgetState : uint8
{
	OnCreatedBeforePush,
	AfterPush
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonDescriptionTextUpdatedDelegate, 
	UK2HCommonButtonBase*, BroadcastingButton, FText, DescriptionText);
/**
 * 
 */
UCLASS()
class K2H_RPG_API UUISubsystem : public UK2HGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UUISubsystem* Get(const UObject* WorldContextObject);

	void RegisterPrimaryLayoutWidget(UWidget_PrimaryLayout* InCreatedWidget);

	void PushSoftWidgetToStackAsync(const FGameplayTag& InStackTag,
		TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass, 
		TFunction< void (EAsyncPushWidgetState, UWidget_ActivatableBase*) > AsyncPushStateCallback);

	void PushConfirmScreenToModalStackAsync(EConfirmScreenType InScreenType, const FText& InScreenTitle, 
		const FText& InScreenMsg, TFunction<void(EConfirmScreenButtonType)> ButtonClickedCallback);

	UPROPERTY(BlueprintAssignable)
	FOnButtonDescriptionTextUpdatedDelegate OnButtonDescriptionTextUpdated;

private:

	UPROPERTY(Transient)
	UWidget_PrimaryLayout* CreatedPrimaryLayout;
};
