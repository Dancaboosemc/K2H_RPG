// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/DataObjects/ListDataObject_Value.h"
#include "ListDataObject_String.generated.h"

/**
 * UListDataObject_Value for string values, 
 * Provides Implementation for an option setting that uses a rotator widget
 */
UCLASS()
class K2H_RPG_API UListDataObject_String : public UListDataObject_Value
{
	GENERATED_BODY()

public:

	//Add Options to String and Text arrays
	void AddDynamicOption(const FString& InString, const FText& InDisplayText);

	//Functions for managing value
	void AdvanceToNextOption();												//Keyboard/Mouse
	void BackToPreviousOption();											//Keyboard/Mouse
	void OnRotatorInitiatedValueChange(const FText& InNewSelectedText);		//Gamepad

	//Getters for Rotator widget to use
	FORCEINLINE const TArray<FText>& GetAvailableOptionsTextArray() const { return AvailableOptionsTextArray; };
	FORCEINLINE FText GetCurrentDisplayText() const { return CurrentDisplayText; };

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

	//Helper for coverting String value to Text to be used by UI
	bool TrySetDisplayTextFromStringValue(const FString& InString);

	//Current option
	FString CurrentStringValue;
	FText CurrentDisplayText;

	//Available options
	TArray<FString> AvailableOptionsStringArray;
	TArray<FText> AvailableOptionsTextArray;
};
