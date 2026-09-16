// Daniel McPherson, All Rights Reserved


#include "GameSubsystems/UISubsystem.h"
#include "Engine/AssetManager.h"
#include "Widgets/Widget_PrimaryLayout.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "Widgets/Widget_ConfirmScreen.h"
#include "K2HGameplayTags.h"
#include "K2HFunctionLibrary.h"

UUISubsystem* UUISubsystem::Get(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);

		return UGameInstance::GetSubsystem<UUISubsystem>(World->GetGameInstance());
	}

	return nullptr;
}

void UUISubsystem::RegisterPrimaryLayoutWidget(UWidget_PrimaryLayout* InCreatedWidget)
{
	check(InCreatedWidget);
	CreatedPrimaryLayout = InCreatedWidget;
}

void UUISubsystem::PushSoftWidgetToStackAsync(const FGameplayTag& InStackTag, 
	TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass,
	TFunction< void(EAsyncPushWidgetState, UWidget_ActivatableBase*) > AsyncPushStateCallback)
{
	check(!InSoftWidgetClass.IsNull());

	//Request Load of SoftWidgetClassRef of widget to be created and pushed to screen,
	//Requires Soft Object Path to the SoftWidgetClassRef, 
	//and a CallbackFunction to be called when the asset is loaded
	UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
		InSoftWidgetClass.ToSoftObjectPath(), FStreamableDelegate::CreateLambda(
			[InSoftWidgetClass, this, InStackTag, AsyncPushStateCallback]()
			{
				//Get the loaded asset
				UClass* LoadedWidgetClass = InSoftWidgetClass.Get();
				check(LoadedWidgetClass && CreatedPrimaryLayout);

				//Get the Widget Stack by tag
				UCommonActivatableWidgetContainerBase* WidgetStack =
					CreatedPrimaryLayout->FindWidgetStackByTag(InStackTag);

				//Create and add the widget to the stack, requires callbacks to be called after 
				//creating the widget but before push, and after push
				UWidget_ActivatableBase* CreatedWidget = 
					WidgetStack->AddWidget<UWidget_ActivatableBase>(LoadedWidgetClass,
					[AsyncPushStateCallback](UWidget_ActivatableBase& CreatedWidgetInstance)
					{
						//Before Push Callback
						AsyncPushStateCallback(EAsyncPushWidgetState::OnCreatedBeforePush, &CreatedWidgetInstance);
					}
				);
				//After Push Callback
				AsyncPushStateCallback(EAsyncPushWidgetState::AfterPush, CreatedWidget);
			}
		));
}

void UUISubsystem::PushConfirmScreenToModalStackAsync(EConfirmScreenType InScreenType, const FText& InScreenTitle, 
	const FText& InScreenMsg, TFunction<void(EConfirmScreenButtonType)> ButtonClickedCallback)
{
	//Create UConfirmScreenInfoObject local variable
	UConfirmScreenInfoObject* CreatedInfoObject = nullptr;

	//Initialize UConfirmScreenInfoObject based off EConfirmScreenType
	switch (InScreenType)
	{
	case EConfirmScreenType::OK:
		
		CreatedInfoObject = UConfirmScreenInfoObject::CreateOKScreen(InScreenTitle, InScreenMsg);
		break;

	case EConfirmScreenType::YesNo:
		CreatedInfoObject = UConfirmScreenInfoObject::CreateYesNoScreen(InScreenTitle, InScreenMsg);
		break;

	case EConfirmScreenType::OKCancel:
		CreatedInfoObject = UConfirmScreenInfoObject::CreateOKCancelScreen(InScreenTitle, InScreenMsg);
		break;

	case EConfirmScreenType::Unknown:
		break;

	default:
		break;
	}

	check(CreatedInfoObject);

	//Push to the Modal Stack which is the top stack
	//Lambda will be called twice, we but only care about the case: before push, 
	//so we can intialize the widget with the Info Object and CallbackFunc
	PushSoftWidgetToStackAsync(
		K2HGameplayTags::WidgetStack_Modal,
		UK2HFunctionLibrary::GetSoftWidgetClassByTag(K2HGameplayTags::Widget_ConfirmScreen),
		[CreatedInfoObject, ButtonClickedCallback](EAsyncPushWidgetState InPushedState, UWidget_ActivatableBase* PushedWidget)
		{
			if (InPushedState == EAsyncPushWidgetState::OnCreatedBeforePush)
			{
				//Convert UWidget_ActivatableBase to child UWidget_ConfirmScreen, and Init the widget
				UWidget_ConfirmScreen* UConfirmScreen = CastChecked<UWidget_ConfirmScreen>(PushedWidget);
				UConfirmScreen->InitConfirmScreen(CreatedInfoObject, ButtonClickedCallback);
			}
		}
		);
}
