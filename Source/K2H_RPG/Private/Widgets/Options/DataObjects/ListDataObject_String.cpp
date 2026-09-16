// Daniel McPherson, All Rights Reserved


#include "Widgets/Options/DataObjects/ListDataObject_String.h"
#include "Widgets/Options/OptionsDataInteractionHelper.h"

#include "DebugHelper.h"

void UListDataObject_String::OnDataObjectInitialized()
{
	//Assign Current value to first in the array
	if (!AvailableOptionsStringArray.IsEmpty())
		CurrentStringValue = AvailableOptionsStringArray[0];

	//if has a default value, override current value to default
	if (HasDefaultValue())
		CurrentStringValue = GetDefaultValueAsString();

	//if has setting saved in config, override current value to the saved value
	if (DataDynamicGetter)
		if (!DataDynamicGetter->GetValueAsString().IsEmpty())
			CurrentStringValue = DataDynamicGetter->GetValueAsString();

	//Update current text value, set to "Invalid" if no matching Text exists in available options
	if (!TrySetDisplayTextFromStringValue(CurrentStringValue))
		CurrentDisplayText = FText::FromString(TEXT("Invalid Option"));
}

void UListDataObject_String::AddDynamicOption(const FString& InString, const FText& InDisplayText)
{
	AvailableOptionsStringArray.Add(InString);
	AvailableOptionsTextArray.Add(InDisplayText);
}

//Right Button Implemnetation of rotator widget
void UListDataObject_String::AdvanceToNextOption()
{
	//as long as both valuearrays are not empty
	if (AvailableOptionsStringArray.IsEmpty() || AvailableOptionsTextArray.IsEmpty()) return;

	//Determine what is the next Index
	const int32 Index = AvailableOptionsStringArray.IndexOfByKey(CurrentStringValue);
	const int32 NextIndex = Index + 1;

	//Update String value, handling array bounds
	if (AvailableOptionsStringArray.IsValidIndex(NextIndex))
		CurrentStringValue = AvailableOptionsStringArray[NextIndex];
	else
		CurrentStringValue = AvailableOptionsStringArray[0];

	//Update Text Value
	TrySetDisplayTextFromStringValue(CurrentStringValue);

	//Update GameUserSettings and Notify Widget
	if (DataDynamicSetter.IsValid())
	{ 
		DataDynamicSetter->SetValueFromString(CurrentStringValue);

		NotifyListDataModified(this);
	}
}

//Left Button Implemnetation of rotator widget
void UListDataObject_String::BackToPreviousOption()
{
	//as long as both valuearrays are not empty
	if (AvailableOptionsStringArray.IsEmpty() || AvailableOptionsTextArray.IsEmpty()) return;

	//Determine what is the Previous Index
	const int32 Index = AvailableOptionsStringArray.IndexOfByKey(CurrentStringValue);
	const int32 PrevIndex = Index - 1;

	//Update String value, handling array bounds
	if(PrevIndex >= 0)
		CurrentStringValue = AvailableOptionsStringArray[PrevIndex];
	else
		CurrentStringValue = AvailableOptionsStringArray.Last();

	//Update Text Value
	TrySetDisplayTextFromStringValue(CurrentStringValue);

	//Update GameUserSettings and Notify Widget
	if (DataDynamicSetter.IsValid())
	{
		DataDynamicSetter->SetValueFromString(CurrentStringValue);

		NotifyListDataModified(this);
	}
}

//Use text from rotator widget to update source object
void UListDataObject_String::OnRotatorInitiatedValueChange(const FText& InNewSelectedText)
{	
	//Find the corrisponding index in the text array
	//use IndexOfByPredicate, returning a bool for if the index is found there
	const int32 FoundIndex = AvailableOptionsTextArray.IndexOfByPredicate(
		[InNewSelectedText](const FText& AvailableText)->bool
		{
			//is run for every entry in the array
			return AvailableText.EqualTo(InNewSelectedText);
		}
	);

	//if the found Index was found and is valid in the string array
	if (FoundIndex != INDEX_NONE && AvailableOptionsStringArray.IsValidIndex(FoundIndex))
	{
		//Update Current values
		CurrentDisplayText = InNewSelectedText;
		CurrentStringValue = AvailableOptionsStringArray[FoundIndex];

		//Update GameUserSettings and Notify Widget
		if (DataDynamicSetter)
		{
			DataDynamicSetter->SetValueFromString(CurrentStringValue);
			NotifyListDataModified(this);
		}
	}
}

bool UListDataObject_String::CanResetBackToDefaultValue() const
{
	//We can reset this obejct to default if it has a default value and it is not currently equal to it
	return HasDefaultValue() && CurrentStringValue != GetDefaultValueAsString();
}

bool UListDataObject_String::TryResetBackToDefaultValue()
{
	//if we can reset to default
	if (CanResetBackToDefaultValue())
	{
		//Set String to default
		CurrentStringValue = GetDefaultValueAsString();

		//Set Text to default
		TrySetDisplayTextFromStringValue(CurrentStringValue);

		//Update GameUserSettings and Notify UI and return
		if (DataDynamicSetter)
		{
			DataDynamicSetter->SetValueFromString(CurrentStringValue);

			NotifyListDataModified(this, EOptionsListDataModifyReason::ResetToDefault);

			return true;
		}
	}

	//Return false if cannot be reset
	return false;
}

bool UListDataObject_String::TrySetDisplayTextFromStringValue(const FString& InString)
{
	//Find Index of InString in AvailableOptionsStringArray
	const int32 Index = AvailableOptionsStringArray.IndexOfByKey(InString);

	//Check if the found index is valid for the text array
	if (AvailableOptionsTextArray.IsValidIndex(Index))
	{
		//Set current Text and return
		CurrentDisplayText = AvailableOptionsTextArray[Index];
		return true;
	}

	//return false if Index not valid
	return false;
}
