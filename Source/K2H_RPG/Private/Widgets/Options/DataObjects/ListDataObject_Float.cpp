// Daniel McPherson, All Rights Reserved


#include "Widgets/Options/DataObjects/ListDataObject_Float.h"
#include "Widgets/Options/OptionsDataInteractionHelper.h"
#include "Settings/K2HGameUserSettings.h"

void UListDataObject_Float::OnDataObjectInitialized()
{
	if (DataDynamicGetter)
	{
		//if has setting saved in config, override current value to the saved value
		if (UK2HGameUserSettings::Get()->HasSavedConfigValue(DataDynamicGetter->GetPropertyName()) &&
			!DataDynamicGetter->GetValueAsString().IsEmpty())
		{
			SetCurrentValue(FCString::Atof(*DataDynamicGetter->GetValueAsString()));
		}
		//if has a default value, override current value to default
		else if (HasDefaultValue())
		{
			SetCurrentValue(FCString::Atof(*GetDefaultValueAsString()));

			if (DataDynamicSetter)
			{
				DataDynamicSetter->SetValueFromString(FString::SanitizeFloat(CurrentValue));

				NotifyListDataModified(this, EOptionsListDataModifyReason::ResetToDefault);

				UK2HGameUserSettings::Get()->ApplySettings(true);
			}
		}
	}
}

void UListDataObject_Float::CommitValue()
{
	NotifyListDataModified(this);
}

FText UListDataObject_Float::GetCurrentValueAsText() const
{
	FNumberFormattingOptions Options;
	Options.MaximumFractionalDigits = MaximumFractionalDigits;

	float Output = CurrentValue;

	if (bDisplayAsPercentage)
	{
		Output /= ValueMax - ValueMin;	//multiplyer value
		Output *= 100;					//Percentage value

		Options.MaximumFractionalDigits = 0;
		return FText::Format(FText::FromString("{0}%"), FText::AsNumber(Output, &Options));
	}

	return FText::AsNumber(Output, &Options);
}

void UListDataObject_Float::SetCurrentValue(float InFloat)
{
	if (InFloat == CurrentValue) return;

	CurrentValue = FMath::Clamp(InFloat, ValueMin, ValueMax);

	if (StepSize > 0)
		CurrentValue = FMath::GridSnap(CurrentValue, StepSize);

	if (DataDynamicSetter)
		DataDynamicSetter->SetValueFromString(FString::SanitizeFloat(CurrentValue));
}

void UListDataObject_Float::SetRange(float Min, float Max)
{
	if (!ensure(Min < Max))	return;

	ValueMin = Min;
	ValueMax = Max;
}

void UListDataObject_Float::SetDelta(float Delta)
{
	StepSize = FMath::Max(0.f, Delta);
}

void UListDataObject_Float::SetMaximumFractionalDigits(int InNumOfDigits)
{
	MaximumFractionalDigits = FMath::Max(0, InNumOfDigits);
}

bool UListDataObject_Float::CanResetBackToDefaultValue() const
{
	//We can reset this obejct to default if it has a default value and it is not currently equal to it
	return HasDefaultValue() && CurrentValue != FCString::Atof(*GetDefaultValueAsString());
}

bool UListDataObject_Float::TryResetBackToDefaultValue()
{
	//if we can reset to default
	if (CanResetBackToDefaultValue())
	{
		//Set String to default
		SetCurrentValue(FCString::Atof(*GetDefaultValueAsString()));

		//Update GameUserSettings and Notify UI and return
		if (DataDynamicSetter)
		{
			DataDynamicSetter->SetValueFromString(FString::SanitizeFloat(CurrentValue));

			NotifyListDataModified(this, EOptionsListDataModifyReason::ResetToDefault);

			return true;
		}
	}

	//Return false if cannot be reset
	return false;
}
