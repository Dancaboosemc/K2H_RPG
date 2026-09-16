// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Types/K2HEnumTypes.h"

#include "Widget_ListEntry_Base.generated.h"

class UCommonTextBlock;
class UListDataObject_Base;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class K2H_RPG_API UWidget_ListEntry_Base : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()


public:

	//Blueprint hover event
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On List Entry Widget Hovered"))
	void BP_OnListEntryWidgetHovered(bool bWasHovered, bool bIsEntryWidgetStillSelected);

	//Native Implementation, calls the BP version
	void NativeOnListEntryWidgetHovered(bool bWasHovered);

protected:

	//Redirects gamepad focus to the widget selected by Blueprint.
	//Child should override for gamepad interaction to function properly
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Get Widget To Focus For Gamepad"))
	UWidget* BP_GetWidgetToFocusForGamepad() const;

	//~ Begin IUserObjectListEntry Interface
	//override for setting the source object
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	// ListView widgets are recycled instead of destroyed.
	// This is called before the entry is reused for another item, making it the proper place
	// to notify Blueprint and clean up any state associated with the current list item.
	virtual void NativeOnEntryReleased() override;
	//~ End IUserObjectListEntry Interface

	//~ Begin IUserWidget Interface
	//
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	//~ End IUserWidget Interface

	//Init with source object info
	//child should override to handle additional initialization. Super call is expected 
	virtual void OnOwningListDataObjectSet(UListDataObject_Base* InOwningListDataObject);

	//child should override to update UI values after the data object has been modified, 
	//Empty Implementation, Super not needed
	virtual void OnOwningListDataObjectModified(UListDataObject_Base* OwningModifiedData, 
		EOptionsListDataModifyReason ModifyReason);

	//set Owning widget's current selection to this widget
	void SelectThisEntryWidget();

private:

	/*	Bound Widgets	*/

	//Text Block for Option name
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, AllowPrivateAccess = "true"))
	UCommonTextBlock* CommonText_SettingDisplayName;

	/*	Bound Widgets	*/
};
