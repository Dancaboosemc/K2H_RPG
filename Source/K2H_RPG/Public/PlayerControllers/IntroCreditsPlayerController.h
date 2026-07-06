// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "IntroCreditsPlayerController.generated.h"

class UK2HUserWidget;
/**
 * 
 */
UCLASS()
class K2H_RPG_API AIntroCreditsPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UK2HUserWidget> IntroCreditsWidgetClass;
};
