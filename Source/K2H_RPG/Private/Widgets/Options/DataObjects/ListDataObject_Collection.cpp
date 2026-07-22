// Daniel McPherson, All Rights Reserved


#include "Widgets/Options/DataObjects/ListDataObject_Collection.h"

TArray<UListDataObject_Base*> UListDataObject_Collection::GetChildListData() const
{
	return ChildListDataArray;
}

bool UListDataObject_Collection::HasChildListData() const
{
	return !ChildListDataArray.IsEmpty();
}

void UListDataObject_Collection::AddChildListData(UListDataObject_Base* InChildListData)
{
	//Notify ChildListData to Init self
	InChildListData->InitDataObject();
	
	//Set ChildListData's Parent to this
	InChildListData->SetParentData(this);

	ChildListDataArray.Add(InChildListData);
}
