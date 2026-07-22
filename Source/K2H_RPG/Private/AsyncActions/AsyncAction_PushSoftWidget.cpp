// Daniel McPherson, All Rights Reserved


#include "AsyncActions/AsyncAction_PushSoftWidget.h"
#include "Subsystems/UISubsystem.h"
#include "Widgets/Widget_ActivatableBase.h"

//~ Begin UBlueprintAsyncActionBase Interface
void UAsyncAction_PushSoftWidget::Activate()
{
	UUISubsystem* UISubsystem = UUISubsystem::Get(CachedOwningWorld.Get());

	UISubsystem->PushSoftWidgetToStackAsync(CachedWidgetStackTag, CachedSoftWidgetClass,
		[this](EAsyncPushWidgetState InPushState, UWidget_ActivatableBase* PushedWidget)
		{
			switch (InPushState)
			{
			case EAsyncPushWidgetState::OnCreatedBeforePush:

				PushedWidget->SetOwningPlayer(CachedOwningPC.Get());
				OnWidgetCreatedBeforePush.Broadcast(PushedWidget);
				break;

			case EAsyncPushWidgetState::AfterPush:

				AfterPush.Broadcast(PushedWidget);

				if (bCachedFocusOnNewlyPushedWidget)
				{
					if (UWidget* FocusTarget = PushedWidget->GetDesiredFocusTarget())
					{
						FocusTarget->SetFocus();
					}
				}

				SetReadyToDestroy();
				break;

			default:
				break;
			}
		}
	);
}
//~ End UBlueprintAsyncActionBase Interface

UAsyncAction_PushSoftWidget* UAsyncAction_PushSoftWidget::PushSoftWidget(const UObject* WorldContextObject,
	APlayerController* OwningPlayerController, TSoftClassPtr<UWidget_ActivatableBase> InsoftWidgetClass, 
	UPARAM(meta = (Categories = "Frontend.WidgetStack")) FGameplayTag InWidgetStackTag, bool bFocusOnNewlyPushedWidget)
{
	checkf(!InsoftWidgetClass.IsNull(), TEXT("PushSoftWidgetToStack was passed a null soft widget class "));

	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			UAsyncAction_PushSoftWidget* Node = NewObject<UAsyncAction_PushSoftWidget>();

			Node->RegisterWithGameInstance(World);
			Node->CachedOwningWorld = World;
			Node->CachedOwningPC = OwningPlayerController;
			Node->CachedSoftWidgetClass = InsoftWidgetClass;
			Node->CachedWidgetStackTag = InWidgetStackTag;
			Node->bCachedFocusOnNewlyPushedWidget = bFocusOnNewlyPushedWidget;

			return Node;
		}
	}

	return nullptr;
}
