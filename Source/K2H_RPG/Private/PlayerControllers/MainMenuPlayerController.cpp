// Daniel McPherson, All Rights Reserved


#include "PlayerControllers/MainMenuPlayerController.h"
#include "Blueprint/UserWidget.h"

void AMainMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    //checkf(!MainMenuWidgetClass, TEXT("MainMenuPlayerController: MainMenuWidget Class not assigned"));
    
    UUserWidget* MainMenuWidget = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);

    MainMenuWidget->AddToViewport();

    bShowMouseCursor = true;

    SetInputMode(FInputModeUIOnly());
}
