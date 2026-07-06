// Daniel McPherson, All Rights Reserved


#include "PlayerControllers/IntroCreditsPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/K2HUserWidget.h"


void AIntroCreditsPlayerController::BeginPlay()
{
    Super::BeginPlay();

    checkf(IntroCreditsWidgetClass, TEXT("MainMenuPlayerController: MainMenuWidget Class not assigned"));

    UK2HUserWidget* IntroCreditsWidget = CreateWidget<UK2HUserWidget>(this, IntroCreditsWidgetClass);

    IntroCreditsWidget->AddToViewport();
    IntroCreditsWidget->OnShown();
}