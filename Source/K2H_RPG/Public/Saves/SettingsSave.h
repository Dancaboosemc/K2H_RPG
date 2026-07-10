// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Types/K2HAudioSettings.h"

#include "SettingsSave.generated.h"

class K2HAudioSettings;
/**
 * 
 */
UCLASS()
class K2H_RPG_API USettingsSave : public USaveGame
{
	GENERATED_BODY()
	
public:

	UPROPERTY()
	FK2HAudioSettings AudioSettings;
};
