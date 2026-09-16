// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "PropertyPathHelpers.h"

class UK2HGameUserSettings;
/**
 * Used to facilitate getters and setters between ListDataObject_Value's and UK2HGameUserSettings 
 * without them knowing about the other 
 * ListDataObject_Value contains 1 for a setter and 1 for a getter and they are created and assigned in 
 * UOptionsDataRegistr, andlong with ListDataObject_Value 
 */
class K2H_RPG_API FOptionsDataInteractionHelper
{
public:

	//Stores function path and UK2HGameUserSettings into cached properties
	FOptionsDataInteractionHelper(const FString& InSetterOrGetterFuncPath, const FString& InPropertyName);

	//Get/Sets value defined by CachedDynamicFunctionPath and CachedWeakGameUserSettings
	FString GetValueAsString() const;
	void SetValueFromString(const FString& InStringValue);

	const FString& GetPropertyName() const { return CachedPropertyName; }

private:

	FCachedPropertyPath CachedDynamicFunctionPath;
	TWeakObjectPtr<UK2HGameUserSettings> CachedWeakGameUserSettings;

	FString CachedPropertyName;
};
