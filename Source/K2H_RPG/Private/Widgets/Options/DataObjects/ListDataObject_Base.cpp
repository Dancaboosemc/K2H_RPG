// Daniel McPherson, All Rights Reserved


#include "Widgets/Options/DataObjects/ListDataObject_Base.h"
#include "Settings/K2HGameUserSettings.h"

void UListDataObject_Base::InitDataObject()
{
	OnDataObjectInitialized();
}

void UListDataObject_Base::OnDataObjectInitialized()
{
}

void UListDataObject_Base::NotifyListDataModified(UListDataObject_Base* ModifiedData,
	EOptionsListDataModifyReason ModifyReason)
{
	//Broadcast change
	OnListDataModified.Broadcast(ModifiedData, ModifyReason);

	//Apply if needed immediatly via Game Settings Object
	if (bShouldApplyChangeImmediately)
		UK2HGameUserSettings::Get()->ApplySettings(true);
}
