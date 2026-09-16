// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Types/K2HEnumTypes.h"
#include "K2HGameplayTags.h"

#include "ListDataObject_Base.generated.h"

//Macro taking a datatype and name, creating a setter and getter
#define LIST_DATA_ACCESSOR(DataType, PropertyName) \
	FORCEINLINE DataType Get##PropertyName() const { return PropertyName; } \
	void Set##PropertyName(DataType In##PropertyName) { PropertyName = In##PropertyName;}

/**
 *	Source object base class for List Widgets in the options screen 
 */
UCLASS(Abstract)
class K2H_RPG_API UListDataObject_Base : public UObject
{
	GENERATED_BODY()
	

public:

	//Delegate for broadcasting when a ListDataObject is Modified
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnListDataModifiedDelegate, UListDataObject_Base*, EOptionsListDataModifyReason)
	FOnListDataModifiedDelegate OnListDataModified;

	//	Setter & Getter Macros
	//LIST_DATA_ACCESSOR(FName, DataID);
	LIST_DATA_ACCESSOR(FGameplayTag, DataID);
	LIST_DATA_ACCESSOR(FText, DataDisplayName);
	LIST_DATA_ACCESSOR(FText, DescriptionRichText);
	LIST_DATA_ACCESSOR(FText, DisabledWidgetText);
	LIST_DATA_ACCESSOR(TSoftObjectPtr<UTexture2D>, SoftDescriptionImage);
	LIST_DATA_ACCESSOR(UListDataObject_Base*, ParentData);
	LIST_DATA_ACCESSOR(ESettingPlatform, PlatformRestriction);

	void InitDataObject();

	//Empty in the base class, Child class ListDataObject_Collection should override
	//Function should return all the child data the tab has
	virtual TArray<UListDataObject_Base*> GetChildListData() const { return TArray<UListDataObject_Base*>(); }
	virtual bool HasChildListData() const { return false; }

	void SetShouldApplySettingsImmediately(bool bShouldApplyImmediately) { bShouldApplyChangeImmediately = bShouldApplyImmediately; }

	//The child class should override these to provide implementations for resetting the data
	virtual bool HasDefaultValue() const { return false; }
	virtual bool CanResetBackToDefaultValue() const { return false; }
	virtual bool TryResetBackToDefaultValue() { return false; }

protected:

	//Child classes should override to handle initialization as needed, Empty in Base class
	virtual void OnDataObjectInitialized();

	//Virtual Function for broadcasting when a ListDataObject is Modified
	virtual void NotifyListDataModified(UListDataObject_Base* ModifiedData, 
		EOptionsListDataModifyReason ModifyReason = EOptionsListDataModifyReason::DirectlyModified);


private:

	//Base Properties for Option display, description, and Id
	//FName DataID;
	FGameplayTag DataID;
	FText DataDisplayName;
	FText DescriptionRichText;
	FText DisabledWidgetText;
	TSoftObjectPtr<UTexture2D> SoftDescriptionImage;

	//Parent data property, intended for collections and Dependent Options
	UPROPERTY(Transient)
	UListDataObject_Base* ParentData;

	ESettingPlatform PlatformRestriction = ESettingPlatform::All;

	//Set to true for options that require Immediate update to the game and config, when ever they are changed.
	//Ex: Good for options like game difficulty, not great for options using sliders that can change quickly
	bool bShouldApplyChangeImmediately = false;
};
