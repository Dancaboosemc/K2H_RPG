// Daniel McPherson, All Rights Reserved


#include "Widgets/Options/DataObjects/ListDataObject_Bool.h"
#include "Widgets/Options/OptionsDataInteractionHelper.h"
#include "Settings/K2HGameUserSettings.h"

void UListDataObject_Bool::OnDataObjectInitialized()
{
	if (DataDynamicGetter)
	{
		//if has setting saved in config, override current value to the saved value
		if (UK2HGameUserSettings::Get()->HasSavedConfigValue(DataDynamicGetter->GetPropertyName()) &&
			!DataDynamicGetter->GetValueAsString().IsEmpty())
		{
			InitValue(DataDynamicGetter->GetValueAsString().ToBool());
		}
		//if has a default value, override current value to default
		else if (HasDefaultValue())
		{
			InitValue(GetDefaultValueAsString().ToBool());

			if (DataDynamicSetter)
			{
				DataDynamicSetter->SetValueFromString(CurrentValue ? "True" : "False");

				NotifyListDataModified(this, EOptionsListDataModifyReason::ResetToDefault);

				UK2HGameUserSettings::Get()->ApplySettings(true);
			}
		}
	}
}

void UListDataObject_Bool::SetValue(bool InValue)
{
	CurrentValue = InValue;

	NotifyListDataModified(this);
}

bool UListDataObject_Bool::CanResetBackToDefaultValue() const
{
	return HasDefaultValue() && CurrentValue != GetDefaultValueAsString().ToBool();
}

bool UListDataObject_Bool::TryResetBackToDefaultValue()
{
	//if we can reset to default
	if (CanResetBackToDefaultValue())
	{
		//Set String to default
		InitValue(GetDefaultValueAsString().ToBool());

		//Update GameUserSettings and Notify UI and return
		if (DataDynamicSetter)
		{
			DataDynamicSetter->SetValueFromString(CurrentValue? "True" : "False");

			NotifyListDataModified(this, EOptionsListDataModifyReason::ResetToDefault);

			return true;
		}
	}

	//Return false if cannot be reset
	return false;
}