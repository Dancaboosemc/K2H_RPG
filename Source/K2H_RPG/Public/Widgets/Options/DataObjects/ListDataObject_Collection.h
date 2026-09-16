// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/DataObjects/ListDataObject_Base.h"
#include "ListDataObject_Collection.generated.h"

/**
 * Collection Of UListDataObject_Base, to be registered with Option Tabs, 
 * or to provide structure for Dependent Options
 */
UCLASS()
class K2H_RPG_API UListDataObject_Collection : public UListDataObject_Base
{
	GENERATED_BODY()

public:

	//~ Begin UListDataObject_Base Interface
	virtual TArray<UListDataObject_Base*> GetChildListData() const override;
	virtual bool HasChildListData() const override;
	//~ End UListDataObject_Base Interface

	void AddChildListData(UListDataObject_Base* InChildListData);

private:

	UPROPERTY(Transient)
	TArray<UListDataObject_Base*> ChildListDataArray;
	
};
