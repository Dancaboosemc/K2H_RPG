// Daniel McPherson, All Rights Reserved


#include "Widgets/Options/ListEntries/Widget_ListEntry_Bool.h"
#include "Widgets/Options/DataObjects/ListDataObject_Bool.h"
#include "Components/CheckBox.h"

void UWidget_ListEntry_Bool::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &ThisClass::OnToggle);
}

void UWidget_ListEntry_Bool::OnOwningListDataObjectSet(UListDataObject_Base* InOwningListDataObject)
{
	Super::OnOwningListDataObjectSet(InOwningListDataObject);

	CachedOwningBoolDataObject = CastChecked<UListDataObject_Bool>(InOwningListDataObject);

	if (CheckBox)
		CheckBox->SetIsChecked(CachedOwningBoolDataObject->GetValue());
}

void UWidget_ListEntry_Bool::OnToggle(bool InValue)
{
	SelectThisEntryWidget();

	CachedOwningBoolDataObject->SetValue(InValue);
}
