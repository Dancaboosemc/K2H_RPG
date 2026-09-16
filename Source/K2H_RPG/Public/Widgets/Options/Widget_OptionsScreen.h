// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Widget_ActivatableBase.h"
#include "Types/K2HEnumTypes.h"

#include "Widget_OptionsScreen.generated.h"

class UOptionsDataRegistry;
class UK2HTabListWidgetBase;
class UK2HCommonListView;
class UWidget_OptionsDetailsView;
class UListDataObject_Base;
/**
 * Options Screen Implementation. Inherits from UWidget_ActivatableBase so can be pushed to widget stacks
 * Implements a Tab list and uses a registry to populate an options list by tab. Also has a details widget to explain
 * option entries
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class K2H_RPG_API UWidget_OptionsScreen : public UWidget_ActivatableBase
{
	GENERATED_BODY()
	
protected:

	//~ Begin UUserWidget Interface
	virtual void NativeOnInitialized() override;
	//~ End UUserWidget Interface

	//~ Begin UCommonActivatableWidget Interface
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	//~ End UCommonActivatableWidget Interface

private:

	//Callback for TabListWidget_OptionTabs->OnTabSelected delegate
	UFUNCTION()
	void OnOptionsTabSelected(FName TabId);

	/*	OPTIONS LIST EVENTS	*/
	//Callback for CommonListView_OptionsList->OnItemIsHoveredChanged() delegate
	void OnListViewItemHovered(UObject* InHoveredItem, bool bWasHovered);

	//Callback for CommonListView_OptionsList->OnItemSelectionChanged() delegate
	void OnListViewItemSelected(UObject* InSelectedItem);

	//Helper function used to help set dynamic details TODO: Dynamic details might be removed
	FString TryGetEntryWidgetClassName(UObject* InOwningListItem) const;

	//Callback for a source object's OnListDataModified delegate
	void OnListViewListDataModified(UListDataObject_Base* ModifiedData, EOptionsListDataModifyReason ModifyReason);
	/*	OPTIONS LIST EVENTS	*/

	/*	BOUND WIDGETS	*/
	//Tabs Widget
	UPROPERTY(meta = (BindWidget))
	UK2HTabListWidgetBase* TabListWidget_OptionTabs;

	//Options Widget
	UPROPERTY(meta = (BindWidget))
	UK2HCommonListView* CommonListView_OptionsList;

	//Option Details
	UPROPERTY(meta = (BindWidget))
	UWidget_OptionsDetailsView* DetailsView_ListEntryInfo;
	/*	BOUND WIDGETS	*/

	/*	OPTIONS DATA REGISTRY	*/
	//Handles creating data in the Options Screen. Direct access to this variable is forbidden
	UPROPERTY(Transient)
	UOptionsDataRegistry* OwningDataRegistry;

	UOptionsDataRegistry* GetOrCreateDataRegistry();
	/*	OPTIONS DATA REGISTRY	*/

	/* ACTION BINDINGS	*/
	void OnResetBoundActiontriggered();
	void OnBackBoundActiontriggered();
	/* ACTION BINDINGS	*/

	/* RESTET HANDLING	*/
	//Assign DataTable and Row in Blueprint child
	UPROPERTY(EditDefaultsOnly, Category = "OptionsScreen", meta = 
		(RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle ResetAction;

	//Cached Action Binding handle
	FUIActionBindingHandle ResetActionHandle;

	//Array to hold the source object of any option that can be retset back to default
	UPROPERTY(Transient)
	TArray<UListDataObject_Base*> ResettableDataArray;

	//used to avoid modifying ResettableDataArray while interating over it
	bool bIsResettingData = false;
	/* RESTET HANDLING	*/

	//Helper for determing the current platform group
	ESettingPlatform GetCurrentPlatformGroup();
};
