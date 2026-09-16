// Daniel McPherson, All Rights Reserved


#include "AsyncActions/AsyncAction_PushSoftWidget.h"
#include "GameSubsystems/UISubsystem.h"
#include "Widgets/Widget_ActivatableBase.h"

void UAsyncAction_PushSoftWidget::Activate()
{
	UUISubsystem* UISubsystem = UUISubsystem::Get(CachedOwningWorld.Get());

	//Call UISubsytem Function for Pushing Widgets to stacks, Lambda is used to return exectution to BP
	//Before and After pushing the widget to the stack
	UISubsystem->PushSoftWidgetToStackAsync(CachedWidgetStackTag, CachedSoftWidgetClass,
		[this](EAsyncPushWidgetState InPushState, UWidget_ActivatableBase* PushedWidget)
		{
			//Determin Push state
			switch (InPushState)
			{
			case EAsyncPushWidgetState::OnCreatedBeforePush:

				//init PC in created widget
				PushedWidget->SetOwningPlayer(CachedOwningPC.Get());

				//broadcast
				OnWidgetCreatedBeforePush.Broadcast(PushedWidget);
				break;

			case EAsyncPushWidgetState::AfterPush:

				//broadcast
				AfterPush.Broadcast(PushedWidget);

				//handle Focus
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

UAsyncAction_PushSoftWidget* UAsyncAction_PushSoftWidget::PushSoftWidget(const UObject* WorldContextObject,
	APlayerController* OwningPlayerController, TSoftClassPtr<UWidget_ActivatableBase> InsoftWidgetClass, 
	UPARAM(meta = (Categories = "WidgetStack")) FGameplayTag InWidgetStackTag, bool bFocusOnNewlyPushedWidget)
{
	checkf(!InsoftWidgetClass.IsNull(), TEXT("PushSoftWidgetToStack was passed a null soft widget class "));

	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			//Create Object
			UAsyncAction_PushSoftWidget* Node = NewObject<UAsyncAction_PushSoftWidget>();

			//Init Cached properties
			Node->CachedOwningWorld = World;
			Node->CachedOwningPC = OwningPlayerController;
			Node->CachedSoftWidgetClass = InsoftWidgetClass;
			Node->CachedWidgetStackTag = InWidgetStackTag;
			Node->bCachedFocusOnNewlyPushedWidget = bFocusOnNewlyPushedWidget;

			//Register with world
			Node->RegisterWithGameInstance(World);

			return Node;
		}
	}

	return nullptr;
}
