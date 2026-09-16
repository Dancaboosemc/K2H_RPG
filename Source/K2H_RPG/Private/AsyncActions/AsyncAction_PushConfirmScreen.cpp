// Daniel McPherson, All Rights Reserved


#include "AsyncActions/AsyncAction_PushConfirmScreen.h"
#include "GameSubsystems/UISubsystem.h"

void UAsyncAction_PushConfirmScreen::Activate()
{
	//Call UISubsytem Function for Pushing Confrim screens, Lambda is used to return exectution to BP when
	//when the a confim button is clicked. Canceled selection does nothing by default so no need to cover that case
	UUISubsystem::Get(CachedOwningWorld.Get())->PushConfirmScreenToModalStackAsync(
		CachedScreenType, CachedScreenTitle, CachedScreenMsg,
		[this](EConfirmScreenButtonType ClickedButtonType)
		{
			//Broadcast
			OnButtonClicked.Broadcast(ClickedButtonType);

			//Prepare object for destruction
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
			//Create Object
			UAsyncAction_PushConfirmScreen* Node = NewObject<UAsyncAction_PushConfirmScreen>();

			//Init Cached properties
			Node->CachedOwningWorld = World;
			Node->CachedScreenType = ScreenType;
			Node->CachedScreenTitle = ScreenTitle;
			Node->CachedScreenMsg = InScreenMsg;

			//Register with world
			Node->RegisterWithGameInstance(World);

			return Node;
		}
	}

	return nullptr;
}
