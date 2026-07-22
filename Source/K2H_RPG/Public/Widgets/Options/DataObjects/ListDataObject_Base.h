// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ListDataObject_Base.generated.h"

#define LIST_DATA_ACCESSOR(DataType, PropertyName) \
	FORCEINLINE DataType Get##PropertyName() const { return PropertyName; } \
	void Set##PropertyName(DataType In##PropertyName) { PropertyName = In##PropertyName;}
/**
 * 
 */
UCLASS()
class K2H_RPG_API UListDataObject_Base : public UObject
{
	GENERATED_BODY()
	

public:

	LIST_DATA_ACCESSOR(FName, DataID);
	LIST_DATA_ACCESSOR(FText, DataDisplayName);
	LIST_DATA_ACCESSOR(FText, DescriptionRichText);
	LIST_DATA_ACCESSOR(FText, DisabledWidgetText);
	LIST_DATA_ACCESSOR(TSoftObjectPtr<UTexture2D>, SoftDescriptionImage);
	LIST_DATA_ACCESSOR(UListDataObject_Base*, ParentData);

	void InitDataObject();

	//Empty in the base class, Child class ListDataObject_Collection should override
	//Function should return all the child data the tab has
	virtual TArray<UListDataObject_Base*> GetChildListData() const { return TArray<UListDataObject_Base*>(); }
	virtual bool HasChildListData() const { return false; }

protected:

	//Child classes should override to handle initialization as needed, Empty in Base class
	virtual void OnDataObjectInitialized();

private:

	FName DataID;
	FText DataDisplayName;
	FText DescriptionRichText;
	FText DisabledWidgetText;
	TSoftObjectPtr<UTexture2D> SoftDescriptionImage;

	UPROPERTY(Transient)
	UListDataObject_Base* ParentData;
};
