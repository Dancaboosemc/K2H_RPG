// Daniel McPherson, All Rights Reserved


#include "PlayerControllers/K2HPlayerController.h"
#include "Widgets/Widget_PrimaryLayout.h"
#include "GameSubsystems/UISubsystem.h"
#include "GameSubsystems/AudioSubsystem.h"

void AK2HPlayerController::BeginPlay()
{
	Super::BeginPlay();

	checkf(WidgetClass, TEXT("K2HPlayerController: Widget Class not assigned"));

	//Create Widget Since there is very little in the widget container class, a hard ref is fine
	UWidget_PrimaryLayout* PrimaryLayout = CreateWidget<UWidget_PrimaryLayout>(this, WidgetClass);

	//Add Widget To Viewport
	PrimaryLayout->AddToViewport();

	//Register Widget With UISubsystem.
	if (UUISubsystem* UISubsystem = GetGameInstance()->GetSubsystem<UUISubsystem>())
	{
		UISubsystem->RegisterPrimaryLayoutWidget(PrimaryLayout);
	}
}
