// Daniel McPherson, All Rights Reserved


#include "PlayerControllers/K2HPlayerController.h"
#include "Widgets/Widget_PrimaryLayout.h"
#include "Subsystems/UISubsystem.h"

void AK2HPlayerController::BeginPlay()
{
	Super::BeginPlay();

	checkf(WidgetClass, TEXT("K2HPlayerController: Widget Class not assigned"));

	UWidget_PrimaryLayout* PrimaryLayout = CreateWidget<UWidget_PrimaryLayout>(this, WidgetClass);

	PrimaryLayout->AddToViewport();

	if (UUISubsystem* UISubsystem = GetGameInstance()->GetSubsystem<UUISubsystem>())
	{
		UISubsystem->RegisterPrimaryLayoutWidget(PrimaryLayout);
	}
}
