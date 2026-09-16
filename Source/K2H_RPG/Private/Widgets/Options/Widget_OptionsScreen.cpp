// Daniel McPherson, All Rights Reserved


#include "Widgets/Options/Widget_OptionsScreen.h"
#include "Input/CommonUIInputTypes.h"
#include "ICommonInputModule.h"
#include "Widgets/Options/OptionsDataRegistry.h"
#include "Widgets/Components/K2HTabListWidgetBase.h"
#include "Widgets/Options/DataObjects/ListDataObject_Collection.h"
#include "Widgets/Components/K2HCommonListView.h"
#include "Settings/K2HGameUserSettings.h"
#include "Widgets/Options/ListEntries/Widget_ListEntry_Base.h"
#include "Widgets/Options/Widget_OptionsDetailsView.h"
#include "GameSubsystems/UISubsystem.h"
#include "Widgets/Components/K2HCommonButtonBase.h"
#include "GameplayTagContainer.h"

#include "DebugHelper.h"

void UWidget_OptionsScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//Get Action Binding Handle from Data Table Row Handle
	if (!ResetAction.IsNull())
		ResetActionHandle = RegisterUIActionBinding(
			FBindUIActionArgs(
				ResetAction,
				true,
				FSimpleDelegate::CreateUObject(this, &ThisClass::OnResetBoundActiontriggered)
			)
		);

	//Register Back Action with UCommonUserWidget Implementation
	RegisterUIActionBinding(
		FBindUIActionArgs(
			ICommonInputModule::GetSettings().GetDefaultBackAction(),
			true,
			FSimpleDelegate::CreateUObject(this, &ThisClass::OnBackBoundActiontriggered)
		)
	);

	//Bind Tab Select Callback
	TabListWidget_OptionTabs->OnTabSelected.AddUniqueDynamic(this, &ThisClass::OnOptionsTabSelected);

	//Bind Option List Callbacks 
	CommonListView_OptionsList->OnItemIsHoveredChanged().AddUObject(this, &ThisClass::OnListViewItemHovered);
	CommonListView_OptionsList->OnItemSelectionChanged().AddUObject(this, &ThisClass::OnListViewItemSelected);
}

void UWidget_OptionsScreen::NativeOnActivated()
{
	Super::NativeOnActivated();

	//Iterate over OptionsTabCollections in the data registry
	for (UListDataObject_Collection* TabCollection : GetOrCreateDataRegistry()->GetRegisteredOptionsTabCollections())
	{
		if (!TabCollection) continue;

		//if not ALL or Resrtiction does not match current platform, then skip
		if (TabCollection->GetPlatformRestriction() != ESettingPlatform::All && 
			TabCollection->GetPlatformRestriction() != GetCurrentPlatformGroup()) continue;

		//Get Tab ID from collection
		const FGameplayTag TabID = TabCollection->GetDataID();

		//check if valid
		if (TabListWidget_OptionTabs->GetTabButtonBaseByID(FName(*TabID.ToString())) != nullptr) continue;

		//Register Collection with Tab
		TabListWidget_OptionTabs->RequestRegisterTab(TabID, TabCollection->GetDataDisplayName());
	}
}

void UWidget_OptionsScreen::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	//Apply any unapplied settings 
	Debug::Print(TEXT("UWidget_OptionsScreen::NativeOnDeactivated: Settings Applied"));
	UK2HGameUserSettings::Get()->ApplySettings(true);
}

UWidget* UWidget_OptionsScreen::NativeGetDesiredFocusTarget() const
{
	//Check bound widget and get the source object for the currently selected item
	if (UObject* SelectedObject = CommonListView_OptionsList->GetSelectedItem())
		//use source item to return the corrisponding entry widget in the list
		if (UUserWidget* SelectedEntryWidget = CommonListView_OptionsList->GetEntryWidgetFromItem(SelectedObject))
			return SelectedEntryWidget;

	//reutrn focus if List widget not bound or if there is no corrisponding widget
	return Super::NativeGetDesiredFocusTarget();
}

UOptionsDataRegistry* UWidget_OptionsScreen::GetOrCreateDataRegistry()
{
	//Create and Init registry if not already created
	if (!OwningDataRegistry)
	{
		OwningDataRegistry = NewObject<UOptionsDataRegistry>();
		OwningDataRegistry->InitOptionsDataRegistry(GetOwningLocalPlayer());
	}
	checkf(OwningDataRegistry, TEXT("Data Registry for Options Screen is not valid."));

	//return registry
	return OwningDataRegistry;
}

void UWidget_OptionsScreen::OnResetBoundActiontriggered()
{
	//Do not run if no data to reset
	if (ResettableDataArray.IsEmpty()) return;

	//Get Selected Tab in TabList, Get FName of tab and then use that to get the actual button
	UCommonButtonBase* SelectedTabButton = 
		TabListWidget_OptionTabs->GetTabButtonBaseByID(FName(*TabListWidget_OptionTabs->GetActiveTab().ToString()));

	//Cast to UK2HCommonButtonBase and get the display Text
	const FString SelectedTabButtonName = 
		CastChecked<UK2HCommonButtonBase>(SelectedTabButton)->GetButtonDisplayText().ToString();

	//Puch Yes/No Confrim Screen to UI, Lamdb handles confirm screen buttons implementation
	UUISubsystem::Get(this)->PushConfirmScreenToModalStackAsync(
		EConfirmScreenType::YesNo, 
		FText::FromString(TEXT("Reset")),
		FText::Format(
			FText::FromString(TEXT("Reset all {0} settings to default?")),
			FText::FromString(SelectedTabButtonName)
		),
		[this](EConfirmScreenButtonType ClickedButtonType)
		{
			//if not the confrim button was clicked, then return
			if (ClickedButtonType != EConfirmScreenButtonType::Confrimed) return;

			//bool for stopping modification of ResettableDataArray while iterating over it
			bIsResettingData = true;

			//set bHasDataFailedToReset to default
			bool bHasDataFailedToReset = false;

			//iterate over ResettableDataArray
			for (UListDataObject_Base* DataToReset : ResettableDataArray)
			{
				if (!DataToReset) continue;

				//reset source object and if failes then set bHasDataFailedToReset to true
				if (!DataToReset->TryResetBackToDefaultValue())
				{
					bHasDataFailedToReset = true;
				}
			}

			//if everything reset correctly
			if (!bHasDataFailedToReset)
			{
				//Empty the array and remove the reset action handle from the base class implementation
				ResettableDataArray.Empty();
				RemoveActionBinding(ResetActionHandle);
			}

			//Allow modifaction to ResettableDataArray again
			bIsResettingData = false;
		}
	);
}

void UWidget_OptionsScreen::OnBackBoundActiontriggered()
{
	//manually deactivate widget to activte the widget below it in the stack
	DeactivateWidget();
}

void UWidget_OptionsScreen::OnOptionsTabSelected(FName TabId)
{
	//Clear details view
	DetailsView_ListEntryInfo->ClearDetailsViewinfo();

	//Convert FName to GameplayTag
	const FGameplayTag TabTag = FGameplayTag::RequestGameplayTag(TabId, false);

	if (!TabTag.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid GameplayTag from TabId: %s"), *TabId.ToString());
		return;
	}

	//Get source items for tab from the registry
	TArray<UListDataObject_Base*> FoundListSourceItems = 
		GetOrCreateDataRegistry()->GetListSourceItemsBySelectedTabID(TabTag);

	//Filter Source Items by playtform gorup
	TArray<UListDataObject_Base*> FilteredListSourceItems;

	for (UListDataObject_Base* SourceItem : FoundListSourceItems)
	{
		if (SourceItem->GetPlatformRestriction() != ESettingPlatform::All &&
			SourceItem->GetPlatformRestriction() != GetCurrentPlatformGroup()) continue;

		FilteredListSourceItems.Add(SourceItem);
	}

	//Set Source items for the list view and refresh
	CommonListView_OptionsList->SetListItems(FilteredListSourceItems);
	CommonListView_OptionsList->RequestRefresh();

	//Set default open tab to first tab
	if (CommonListView_OptionsList->GetNumItems() != 0)
	{
		CommonListView_OptionsList->NavigateToIndex(0);
		CommonListView_OptionsList->SetSelectedIndex(0);
	}

	//Clear ResettableDataArray of any data
	ResettableDataArray.Empty();

	//iterate over source items and find any that can be reset to default and add them to ResettableDataArray
	for (UListDataObject_Base* FoundListSourceItem : FoundListSourceItems)
	{
		if (!FoundListSourceItem) continue;

		//Bind Callback to source object's OnListDataModified
		if (!FoundListSourceItem->OnListDataModified.IsBoundToObject(this))
			FoundListSourceItem->OnListDataModified.AddUObject(this, &ThisClass::OnListViewListDataModified);

		//any source object that can be reset to default should be added to ResettableDataArray
		if (FoundListSourceItem->CanResetBackToDefaultValue())
			ResettableDataArray.AddUnique(FoundListSourceItem);
	}

	//Determine if Reset Action is useable, and de/activae accordingly.
	if (ResettableDataArray.IsEmpty())
		RemoveActionBinding(ResetActionHandle);
	else
		if (!GetActionBindings().Contains(ResetActionHandle))
			AddActionBinding(ResetActionHandle);
}

void UWidget_OptionsScreen::OnListViewItemHovered(UObject* InHoveredItem, bool bWasHovered)
{
	if (!InHoveredItem) return;

	//Get the Entry Widget using the source object
	UWidget_ListEntry_Base* HoveredEntryWidget = 
		CommonListView_OptionsList->GetEntryWidgetFromItem<UWidget_ListEntry_Base>(InHoveredItem);
	check(HoveredEntryWidget);

	//Call hover event in UWidget_ListEntry_Base, passing in hover status
	HoveredEntryWidget->NativeOnListEntryWidgetHovered(bWasHovered);

	//if is hovered, update the details view to show the hoverd entry's info
	if (bWasHovered)
		DetailsView_ListEntryInfo->UpdateDetailsViewInfo(
			CastChecked<UListDataObject_Base>(InHoveredItem), TryGetEntryWidgetClassName(InHoveredItem));

	//else was unhovered, so we need to update the details view to show the selected entry's info
	else
		if (UListDataObject_Base* SelectedItem = CommonListView_OptionsList->GetSelectedItem<UListDataObject_Base>())
			DetailsView_ListEntryInfo->UpdateDetailsViewInfo(SelectedItem, TryGetEntryWidgetClassName(SelectedItem));
}

void UWidget_OptionsScreen::OnListViewItemSelected(UObject* InSelectedItem)
{
	if (!InSelectedItem) return;

	//Update DetailsView with info in source object
	DetailsView_ListEntryInfo->UpdateDetailsViewInfo(
		CastChecked<UListDataObject_Base>(InSelectedItem), TryGetEntryWidgetClassName(InSelectedItem));
}

FString UWidget_OptionsScreen::TryGetEntryWidgetClassName(UObject* InOwningListItem) const
{
	//Get entry class with source item, and return it's class name
	if (UUserWidget* FoundEntryWidget = CommonListView_OptionsList->GetEntryWidgetFromItem(InOwningListItem))
		return FoundEntryWidget->GetClass()->GetName();
	
	//return not valid if fails
	return TEXT("Entry Widget Not Valid");
}

void UWidget_OptionsScreen::OnListViewListDataModified(
	UListDataObject_Base* ModifiedData, EOptionsListDataModifyReason ModifyReason)
{
	//check source object. do not run if currently resetting data
	if (!ModifiedData || bIsResettingData) return;

	//check if Data can be reset back to defaults
	if (ModifiedData->CanResetBackToDefaultValue())
	{
		//add data to ResettableDataArray
		ResettableDataArray.AddUnique(ModifiedData);

		//Add Reset Action binding if not already bound
		if (!GetActionBindings().Contains(ResetActionHandle))
			AddActionBinding(ResetActionHandle);
	}
	//else data should not be in ResettableDataArray so remove in case it is.
	else
		if (ResettableDataArray.Contains(ModifiedData))
			ResettableDataArray.Remove(ModifiedData);

	//check if ResettableDataArray has any data left, and unbind the reset action if no data remains.
	if (ResettableDataArray.IsEmpty())
		RemoveActionBinding(ResetActionHandle);
}

ESettingPlatform UWidget_OptionsScreen::GetCurrentPlatformGroup()
{
	FString CurrentPlatformName = FPlatformProperties::PlatformName();

	const FDataDrivenPlatformInfo& PlatformInfo = FDataDrivenPlatformInfoRegistry::GetPlatformInfo(CurrentPlatformName);

	if (PlatformInfo.PlatformGroupName == FName("Console"))
		return ESettingPlatform::Console;

	return ESettingPlatform::PC;
}
