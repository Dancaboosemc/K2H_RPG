// Daniel McPherson, All Rights Reserved


#include "Widgets/Options/DataAsset_DataListEntryMapping.h"
#include "Widgets/Options/DataObjects/ListDataObject_Base.h"


TSubclassOf<UWidget_ListEntry_Base> UDataAsset_DataListEntryMapping::FindEntryWidgetClassByDataObject
(UListDataObject_Base* InDataObject) const
{
	check(InDataObject);

	//Check InDataObject for a class in it's inheritance hierarchy for a valid key to the DataObjectListEntryMap
	for (UClass* DataObjectClass = InDataObject->GetClass(); DataObjectClass; 
		DataObjectClass = DataObjectClass->GetSuperClass())
	{
		//Convert from UClass and check for success
		if (TSubclassOf<UListDataObject_Base> ConvertedDataObjectClass =
			TSubclassOf<UListDataObject_Base>(DataObjectClass))
		{
			//if the converted class is in the Map, return the associated widget class
			if (DataObjectListEntryMap.Contains(ConvertedDataObjectClass))
			{
				return DataObjectListEntryMap.FindRef(ConvertedDataObjectClass);
			}
		}
	}

	//return Empty Base widget if the is not match
	return TSubclassOf<UWidget_ListEntry_Base>();
}
