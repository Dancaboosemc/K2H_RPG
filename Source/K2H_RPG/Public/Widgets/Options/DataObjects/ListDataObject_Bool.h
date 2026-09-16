// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/DataObjects/ListDataObject_Value.h"
#include "ListDataObject_Bool.generated.h"

/**
 * 
 */
UCLASS()
class K2H_RPG_API UListDataObject_Bool : public UListDataObject_Value
{
	GENERATED_BODY()

public:

	FORCEINLINE void InitValue(bool InValue) { CurrentValue = InValue; }
	void SetValue(bool InValue);	//Notifies list data was modified 
	FORCEINLINE bool GetValue() { return CurrentValue; }

	//Functions to handle resetting to defaults
	//~ Begin UListDataObject_Base Interface
	virtual bool CanResetBackToDefaultValue() const override;
	virtual bool TryResetBackToDefaultValue() override;
	//~ End UListDataObject_Base Interface

protected:

	//called and overrided from base class to handle Initialization
	//~ Begin UListDataObject_Base Interface
	virtual void OnDataObjectInitialized() override;
	//~ End UListDataObject_Base Interface

private:

	bool CurrentValue = false;
	
};
