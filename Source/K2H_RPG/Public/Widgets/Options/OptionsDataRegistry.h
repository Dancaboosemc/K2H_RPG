// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameplayTagContainer.h"

#include "OptionsDataRegistry.generated.h"

class UListDataObject_Collection;
class UListDataObject_Base;
/**
 *	Class for handling creating and registering source objects for setting entries 
 *	with source object collections for specific tabs
 */
UCLASS()
class K2H_RPG_API UOptionsDataRegistry : public UObject
{
	GENERATED_BODY()

public:

	//Called by Options Screen after UOptionsDataRegistry object is created
	void InitOptionsDataRegistry(ULocalPlayer* InOwningLocalPlayer);

	//Collection Array Getter
	const TArray<UListDataObject_Collection*>& GetRegisteredOptionsTabCollections() 
	{ return RegisteredOptionsTabCollections; };

	//Get Collection by it's Data ID
	TArray<UListDataObject_Base*> GetListSourceItemsBySelectedTabID(const FGameplayTag& InSelectedTabID) const;

private:

	// Create/Init Collections and Entries for each Options Screen tab, then adds the collections to an array
	// Is also is where Collections get a Data ID assigned.
	void InitGameplayCollectionTab();
	void InitAudioCollectionTab();
	void InitVideoCollectionTab();
	void InitControlCollectionTab();
	void InitLanguageCollectionTab();

	//Collection Array
	UPROPERTY(Transient)
	TArray<UListDataObject_Collection*> RegisteredOptionsTabCollections;

	TWeakObjectPtr<ULocalPlayer> OwningLocalPlayer;
	
};
