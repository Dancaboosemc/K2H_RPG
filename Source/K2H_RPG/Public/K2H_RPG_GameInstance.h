// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "K2H_RPG_GameInstance.generated.h"

/**
 * 
 */

class UGameFlowSubsystem;
UCLASS()
class K2H_RPG_API UK2H_RPG_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	virtual void Init() override;

	UGameFlowSubsystem* GetFlowSubsystem();

private:

	TObjectPtr<UGameFlowSubsystem> FlowSubsystem;

};
