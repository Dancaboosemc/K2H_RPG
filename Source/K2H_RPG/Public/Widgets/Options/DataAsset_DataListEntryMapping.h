// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_DataListEntryMapping.generated.h"

class UListDataObject_Base;
class UWidget_ListEntry_Base;
/**
 * Provides Implementation for maping and accessing List Entry Widgets 
 * to their corrisponding List Entry Object datatypes
 */
UCLASS()
class K2H_RPG_API UDataAsset_DataListEntryMapping : public UDataAsset
{
	GENERATED_BODY()

public:

	//Find a matching widget in the map by source object
	TSubclassOf<UWidget_ListEntry_Base> FindEntryWidgetClassByDataObject(UListDataObject_Base* InDataObject) const;

private:

	//property for mapping source object types to widget class types
	UPROPERTY(EditDefaultsOnly)
	TMap<TSubclassOf<UListDataObject_Base>, TSubclassOf<UWidget_ListEntry_Base>> DataObjectListEntryMap;
	
};
