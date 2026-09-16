// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/DataObjects/ListDataObject_Value.h"
#include "ListDataObject_Float.generated.h"

/**
 * UListDataObject_Value for Float values,
 * Provides Implementation for an option setting that uses a slider widget
 */
UCLASS()
class K2H_RPG_API UListDataObject_Float : public UListDataObject_Value
{
	GENERATED_BODY()

public:

	//Function that accesses protected function from widget,
	//used to notify that a value has changed
	void CommitValue();

	FText GetCurrentValueAsText() const;
	FORCEINLINE float GetCurrentValue() const { return CurrentValue; }
	FORCEINLINE float GetMinValue() { return ValueMin; }
	FORCEINLINE float GetMaxValue() { return ValueMax; }
	FORCEINLINE float GetDelta() { return StepSize; }


	void SetCurrentValue(float InFloat);
	void SetRange(float Min, float Max);
	void SetDelta(float Delta);
	void SetMaximumFractionalDigits(int InNumOfDigits);
	FORCEINLINE void SetDisplayAsPercentage(bool InBool) { bDisplayAsPercentage = InBool; }

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

	float CurrentValue = 0;
	float ValueMin = 0;
	float ValueMax = 1;
	float StepSize = 0.1f;
	bool bDisplayAsPercentage = false;
	int  MaximumFractionalDigits = 0;	
};
