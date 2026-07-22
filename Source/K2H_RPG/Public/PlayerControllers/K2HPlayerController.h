// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "K2HPlayerController.generated.h"

class UWidget_PrimaryLayout;
/**
 * 
 */
UCLASS()
class K2H_RPG_API AK2HPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UWidget_PrimaryLayout> WidgetClass;
	
};
