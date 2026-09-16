// Daniel McPherson, All Rights Reserved


#include "Widgets/Options/ListEntries/Widget_ListEntry_String.h"
#include "Widgets/Options/DataObjects/ListDataObject_String.h"
#include "Widgets/Components/K2HCommonRotator.h"
#include "Widgets/Components/K2HCommonButtonBase.h"
#include "CommonInputSubsystem.h"

void UWidget_ListEntry_String::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//Handle Next&Previous Button Bindings
	CommonButtonPrevious->OnClicked().AddUObject(this, &ThisClass::OnPreviousOptionButtonClicked);
	CommonButtonNext->OnClicked().AddUObject(this, &ThisClass::OnNextOptionButtonClicked);

	//Handle Rotator Onclick to select this widget in the list
	CommonRotator_AvailableOptions->OnClicked().AddLambda([this]() { SelectThisEntryWidget(); });
	
	//Handle Rotator Gamepad Event
	CommonRotator_AvailableOptions->OnRotatedEvent.AddUObject(this, &ThisClass::OnRotatorValueChanged);
}

void UWidget_ListEntry_String::OnOwningListDataObjectSet(UListDataObject_Base* InOwningListDataObject)
{
	Super::OnOwningListDataObjectSet(InOwningListDataObject);

	//Cache the source object
	CachedOwningStringDataObject = CastChecked<UListDataObject_String>(InOwningListDataObject);

	//Use the object to populate the Rotator's options, then set it's Selection
	CommonRotator_AvailableOptions->PopulateTextLabels(CachedOwningStringDataObject->GetAvailableOptionsTextArray());
	CommonRotator_AvailableOptions->SetSelectedOptionByText(CachedOwningStringDataObject->GetCurrentDisplayText());
}

void UWidget_ListEntry_String::OnOwningListDataObjectModified(UListDataObject_Base* OwningModifiedData, 
	EOptionsListDataModifyReason ModifyReason)
{
	//use cached source object to update the rotator's Selection
	if (CachedOwningStringDataObject)
		CommonRotator_AvailableOptions->SetSelectedOptionByText(
			CachedOwningStringDataObject->GetCurrentDisplayText());
}

void UWidget_ListEntry_String::OnPreviousOptionButtonClicked()
{
	//Call Source object to handle back action
	if (CachedOwningStringDataObject)
		CachedOwningStringDataObject->BackToPreviousOption();

	//Handle Selection in case of not already selected
	SelectThisEntryWidget();
}

void UWidget_ListEntry_String::OnNextOptionButtonClicked()
{
	//Call Source object to handle forward action
	if (CachedOwningStringDataObject)
		CachedOwningStringDataObject->AdvanceToNextOption();

	//Handle Selection in case of not already selected
	SelectThisEntryWidget();
}

void UWidget_ListEntry_String::OnRotatorValueChanged(int32 Value, bool bUserInitiated)
{
	//check for source object
	if (!CachedOwningStringDataObject) return;

	//Get Common Input Subsystem
	UCommonInputSubsystem* CommonInputSubsystem = GetInputSubsystem();

	//Check for subsytem or is not user initiated
	if (!CommonInputSubsystem || !bUserInitiated) return;

	//check for gamepad input type and update source object with new selection
	if (CommonInputSubsystem->GetCurrentInputType() == ECommonInputType::Gamepad)
		CachedOwningStringDataObject->OnRotatorInitiatedValueChange(
			CommonRotator_AvailableOptions->GetSelectedText());


}
