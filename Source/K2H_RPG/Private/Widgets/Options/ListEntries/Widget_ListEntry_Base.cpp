// Daniel McPherson, All Rights Reserved


#include "Widgets/Options/ListEntries/Widget_ListEntry_Base.h"
#include "Widgets/Options/DataObjects/ListDataObject_Base.h"
#include "CommonTextBlock.h"
#include "Components/ListView.h"
#include "CommonInputSubsystem.h"

#include "DebugHelper.h"

void UWidget_ListEntry_Base::NativeOnListEntryWidgetHovered(bool bWasHovered)
{
	BP_OnListEntryWidgetHovered(bWasHovered, IsListItemSelected());
}

void UWidget_ListEntry_Base::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	//Super
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	//Make widget visible
	SetVisibility(ESlateVisibility::Visible);

	//Start Initialization
	OnOwningListDataObjectSet(CastChecked<UListDataObject_Base>(ListItemObject));
}

void UWidget_ListEntry_Base::NativeOnEntryReleased()
{
	//Super
	IUserObjectListEntry::NativeOnEntryReleased();

	//Set hover status to false
	NativeOnListEntryWidgetHovered(false);
}

FReply UWidget_ListEntry_Base::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	//Get Common Input Subsystem accessable through any UCommonUserWidget, like this class
	UCommonInputSubsystem* InputSubsystem = GetInputSubsystem();

	//check for gamepad Input type
	if (InputSubsystem && InputSubsystem->GetCurrentInputType() == ECommonInputType::Gamepad)
		//Get and check for widget returned by blueprint override
		if (UWidget* WidgeToFocus = BP_GetWidgetToFocusForGamepad())
			//Get and check Slate Focus
			if(TSharedPtr<SWidget> SlateWidgetToFocus = WidgeToFocus->GetCachedWidget())
				//return Handle setting user focus via a TSharedRef
				return FReply::Handled().SetUserFocus(SlateWidgetToFocus.ToSharedRef());

	//return super if any checks fail
	return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
}

void UWidget_ListEntry_Base::OnOwningListDataObjectSet(UListDataObject_Base* InOwningListDataObject)
{
	//Init the display name
	if (CommonText_SettingDisplayName)
	{
		CommonText_SettingDisplayName->SetText(InOwningListDataObject->GetDataDisplayName());
	}

	//bind to source object delegate for updating widget when the source is modified
	//check to be sure has not already been bound
	if (!InOwningListDataObject->OnListDataModified.IsBoundToObject(this))
	{
		InOwningListDataObject->OnListDataModified.AddUObject(this, &ThisClass::OnOwningListDataObjectModified);
	}
}

void UWidget_ListEntry_Base::OnOwningListDataObjectModified(UListDataObject_Base* OwningModifiedData, 
	EOptionsListDataModifyReason ModifyReason)
{
}

void UWidget_ListEntry_Base::SelectThisEntryWidget()
{
	//Get the Owning List and this widget's source object to set the Owning List's Selected item
	CastChecked<UListView>(GetOwningListView())->SetSelectedItem(GetListItem());
}
