// Daniel McPherson, All Rights Reserved


#include "AsyncActions/AsyncAction_PushConfirmScreen.h"
#include "Subsystems/UISubsystem.h"

void UAsyncAction_PushConfirmScreen::Activate()
{
	UUISubsystem::Get(CachedOwningWorld.Get())->PushConfirmScreenToModalStackAsync(
		CachedScreenType, CachedScreenTitle, CachedScreenMsg,
		[this](EConfirmScreenButtonType ClickedButtonType)
		{
			OnButtonClicked.Broadcast(ClickedButtonType);

			SetReadyToDestroy();
		}
	);
}

UAsyncAction_PushConfirmScreen* UAsyncAction_PushConfirmScreen::PushConfirmScreen(
	const UObject* WorldContextObject, EConfirmScreenType ScreenType, FText ScreenTitle, FText InScreenMsg)
{
	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, 
			EGetWorldErrorMode::LogAndReturnNull))
		{
			UAsyncAction_PushConfirmScreen* Node = NewObject<UAsyncAction_PushConfirmScreen>();
			Node->CachedOwningWorld = World;
			Node->CachedScreenType = ScreenType;
			Node->CachedScreenTitle = ScreenTitle;
			Node->CachedScreenMsg = InScreenMsg;

			Node->RegisterWithGameInstance(World);

			return Node;
		}
	}

	return nullptr;
}
