// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "K2HPlayerController.generated.h"

class UWidget_PrimaryLayout;
/**
 * Override PlayerController Class in GameMode Defaults, 
 * Currently only used to create the main widget container and add it to viewport.
 */
UCLASS()
class K2H_RPG_API AK2HPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

private:

	//Property for Widget Container to be created in Begin Play
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UWidget_PrimaryLayout> WidgetClass;
	
};
