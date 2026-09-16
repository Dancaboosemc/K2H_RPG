// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/ListEntries/Widget_ListEntry_Base.h"
#include "Widget_ListEntry_Bool.generated.h"

class UListDataObject_Bool;
class UCheckBox;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class K2H_RPG_API UWidget_ListEntry_Bool : public UWidget_ListEntry_Base
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

private:

	//Slider OnValueChanged Binding
	UFUNCTION()
	void OnToggle(bool InValue);

	/*	Bound Widgets	*/

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	UCheckBox* CheckBox;

	/*	Bound Widgets	*/

	UPROPERTY(Transient)
	UListDataObject_Bool* CachedOwningBoolDataObject;
	
};
