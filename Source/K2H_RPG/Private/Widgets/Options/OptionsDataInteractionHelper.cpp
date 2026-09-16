// Daniel McPherson, All Rights Reserved


#include "Widgets/Options/OptionsDataInteractionHelper.h"
#include "Settings/K2HGameUserSettings.h"

FOptionsDataInteractionHelper::FOptionsDataInteractionHelper(const FString& InSetterOrGetterFuncPath, const FString& InPropertyName)
	: CachedDynamicFunctionPath(InSetterOrGetterFuncPath)
{
	CachedWeakGameUserSettings = UK2HGameUserSettings::Get();
	CachedPropertyName = InPropertyName;
}

FString FOptionsDataInteractionHelper::GetValueAsString() const
{
	FString OutStringValue;

	//Use PropertyPathHelpers to get the value that is retuned by the 
	//Function of the given path in K2HGameUserSettings
	PropertyPathHelpers::GetPropertyValueAsString(
		CachedWeakGameUserSettings.Get(), CachedDynamicFunctionPath, OutStringValue);

	return OutStringValue;
}

void FOptionsDataInteractionHelper::SetValueFromString(const FString& InStringValue)
{

	UE_LOG(LogTemp, Warning,
		TEXT("SetValueFromString: Property=%s Value=%s"),
		*CachedPropertyName,
		*InStringValue);

	//Use PropertyPathHelpers to set the value that is set by the 
	//Function of the given path in K2HGameUserSettings
	PropertyPathHelpers::SetPropertyValueFromString(
		CachedWeakGameUserSettings.Get(), CachedDynamicFunctionPath, InStringValue);
}