// Daniel McPherson, All Rights Reserved


#include "PlayerControllers/MainMenuPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/K2HUserWidget.h"

void AMainMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    checkf(MainMenuWidgetClass, TEXT("MainMenuPlayerController: MainMenuWidget Class not assigned"));
    
    UK2HUserWidget* MainMenuWidget = CreateWidget<UK2HUserWidget>(this, MainMenuWidgetClass);

    MainMenuWidget->AddToViewport();

    FInputModeUIOnly InputMode;
    InputMode.SetWidgetToFocus(MainMenuWidget->TakeWidget());

    SetInputMode(InputMode);
    SetShowMouseCursor(true);

   if (UWidget* InitialFocus = MainMenuWidget->GetInitialFocusWidget())
    {
        InitialFocus->SetKeyboardFocus();
        UE_LOG(LogTemp, Warning, TEXT("Setting focus to: %s"), *InitialFocus->GetName());
    }
}
