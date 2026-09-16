// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/DataObjects/ListDataObject_Base.h"
#include "ListDataObject_Value.generated.h"

class FOptionsDataInteractionHelper;
/**
 * Base class for different ListDataObject to represent different datatypes
 * Provides Implementation for Dynamic Setter/Getter's for Reading/Writing to the Config,
 * and Implementation for Setting/Getting a Default Value by String for UI to display
 */
UCLASS(Abstract)
class K2H_RPG_API UListDataObject_Value : public UListDataObject_Base
{
	GENERATED_BODY()
	
public:

	//~ Begin UListDataObject_Base Interface
	virtual bool HasDefaultValue() const override { return DefaultStringValue.IsSet(); }
	//~ End UListDataObject_Base Interface


	void SetDataDynamicGetter(const TSharedPtr<FOptionsDataInteractionHelper>& InDynamicGetter);
	void SetDataDynamicSetter(const TSharedPtr<FOptionsDataInteractionHelper>& InDynamicSetter);

	void SetDefaultValueFromString(const FString& InDefaultValue) { DefaultStringValue = InDefaultValue; }

protected:

	FString GetDefaultValueAsString() const { return DefaultStringValue.GetValue(); }

	TSharedPtr<FOptionsDataInteractionHelper> DataDynamicGetter;
	TSharedPtr<FOptionsDataInteractionHelper> DataDynamicSetter;

private:

	TOptional<FString> DefaultStringValue;
};
