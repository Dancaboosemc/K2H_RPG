// Daniel McPherson, All Rights Reserved


#include "Subsystems/UISubsystem.h"
#include "Engine/AssetManager.h"
#include "Widgets/Widget_PrimaryLayout.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "Widgets/Widget_ConfirmScreen.h"
#include "FrontEndGameplayTags.h"
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

	UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
		InSoftWidgetClass.ToSoftObjectPath(), FStreamableDelegate::CreateLambda(
			[InSoftWidgetClass, this, InStackTag, AsyncPushStateCallback]()
			{
				UClass* LoadedWidgetClass = InSoftWidgetClass.Get();
				check(LoadedWidgetClass && CreatedPrimaryLayout);

				UCommonActivatableWidgetContainerBase* WidgetStack =
					CreatedPrimaryLayout->FindWidgetStackByTag(InStackTag);

				UWidget_ActivatableBase* CreatedWidget = 
					WidgetStack->AddWidget<UWidget_ActivatableBase>(LoadedWidgetClass,
					[AsyncPushStateCallback](UWidget_ActivatableBase& CreatedWidgetInstance)
					{
						AsyncPushStateCallback(EAsyncPushWidgetState::OnCreatedBeforePush, &CreatedWidgetInstance);
					}
				);

				AsyncPushStateCallback(EAsyncPushWidgetState::AfterPush, CreatedWidget);
			}
		));
}

void UUISubsystem::PushConfirmScreenToModalStackAsync(EConfirmScreenType InScreenType, const FText& InScreenTitle, 
	const FText& InScreenMsg, TFunction<void(EConfirmScreenButtonType)> ButtonClickedCallback)
{
	UConfirmScreenInfoObject* CreatedInfoObject = nullptr;

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
	PushSoftWidgetToStackAsync(
		FrontEndGameplayTags::Frontend_WidgetStack_Modal,
		UK2HFunctionLibrary::GetSoftWidgetClassByTag(FrontEndGameplayTags::Frontend_Widget_ConfirmScreen),
		[CreatedInfoObject, ButtonClickedCallback](EAsyncPushWidgetState InPushedState, UWidget_ActivatableBase* PushedWidget)
		{
			if (InPushedState == EAsyncPushWidgetState::OnCreatedBeforePush)
			{
				UWidget_ConfirmScreen* UConfirmScreen = CastChecked<UWidget_ConfirmScreen>(PushedWidget);
				UConfirmScreen->InitConfirmScreen(CreatedInfoObject, ButtonClickedCallback);
			}
		}
		);
}
