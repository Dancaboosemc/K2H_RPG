// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/ListEntries/Widget_ListEntry_Base.h"
#include "Widget_ListEntry_String.generated.h"

class UK2HCommonButtonBase;
class UK2HCommonRotator;
class UListDataObject_String;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class K2H_RPG_API UWidget_ListEntry_String : public UWidget_ListEntry_Base
{
	GENERATED_BODY()

protected:

	//~ Begin UUserWidget Interface
	//Handle Binding to Widget Events
	virtual void NativeOnInitialized() override;
	//~ End UUserWidget Interface

	//~Begin UWidget_ListEntry_Base Interface
	//handle additional initialization with source object. Super call is expected
	virtual void OnOwningListDataObjectSet(UListDataObject_Base* InOwningListDataObject) override;

	//update UI values after the data object has been modified, Super not needed
	virtual void OnOwningListDataObjectModified(UListDataObject_Base* OwningModifiedData, 
		EOptionsListDataModifyReason ModifyReason) override;
	//~End UWidget_ListEntry_Base Interface
	
private:

	//Next&Previous button click Bindings
	void OnPreviousOptionButtonClicked();
	void OnNextOptionButtonClicked();

	//Rotator OnRotation Binding
	void OnRotatorValueChanged(int32 Value, bool bUserInitiated);

	/*	Bound Widgets	*/

	//Previous button
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	UK2HCommonButtonBase* CommonButtonPrevious;

	//Rotator
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	UK2HCommonRotator* CommonRotator_AvailableOptions;

	//Next Button
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	UK2HCommonButtonBase* CommonButtonNext;

	/*	Bound Widgets	*/

	//Cahced Source object
	UPROPERTY(Transient)
	UListDataObject_String* CachedOwningStringDataObject;
};
