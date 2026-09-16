// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/ListEntries/Widget_ListEntry_Base.h"
#include "Widget_ListEntry_Float.generated.h"

class UK2H_CBB_SliderWrapper;
class UListDataObject_Float;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class K2H_RPG_API UWidget_ListEntry_Float : public UWidget_ListEntry_Base
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

	//Slider OnValueChanged Binding :Keyboard Mouse
	UFUNCTION()
	void OnSliderValueChanged(float Value);

	//OnMouseCapturEnd Binding
	UFUNCTION()
	void OnMouseRelease();

	/*	Bound Widgets	*/

	//Slider
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UK2H_CBB_SliderWrapper> SliderWrapper;

	//Display text
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, AllowPrivateAccess = "true"))
	UCommonTextBlock* CommonText_ValueDisplay;

	/*	Bound Widgets	*/

	//Cahced Source object
	UPROPERTY(Transient)
	UListDataObject_Float* CachedOwningFloatDataObject;
};
