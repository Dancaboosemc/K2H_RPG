// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "OptionsDataRegistry.generated.h"

class UListDataObject_Collection;
/**
 * 
 */
UCLASS()
class K2H_RPG_API UOptionsDataRegistry : public UObject
{
	GENERATED_BODY()

public:

	//Called by Options Screen after UOptionsDataRegistry object is created
	void InitOptionsDataRegistry(ULocalPlayer* InOwningLocalPlayer);

	const TArray<UListDataObject_Collection*>& GetRegisteredOptionsTabCollections() { return RegisteredOptionsTabCollections; };

private:

	void InitGameplayCollectionTab();
	void InitAudioCollectionTab();
	void InitVideoCollectionTab();
	void InitControlCollectionTab();
	void InitLanguageCollectionTab();

	UPROPERTY(Transient)
	TArray<UListDataObject_Collection*> RegisteredOptionsTabCollections;
	
};
