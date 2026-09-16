// Daniel McPherson, All Rights Reserved


#include "Widgets/Options/ListEntries/Widget_ListEntry_Float.h"
#include "Widgets/Options/DataObjects/ListDataObject_Float.h"
#include "CommonTextBlock.h"
#include "Settings/K2HGameUserSettings.h"
#include "K2HGameplayTags.h"
#include "Input/CommonUIInputTypes.h"
#include "Widgets/Components/K2H_CBB_SliderWrapper.h"

void UWidget_ListEntry_Float::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (SliderWrapper)
	{
		//Bind setting source object value to Slider OnValueChanged
		SliderWrapper->WrapperOnValueChanged.AddDynamic(this, &ThisClass::OnSliderValueChanged);
		SliderWrapper->OnMouseCaptureEnd.AddDynamic(this, &ThisClass::OnMouseRelease);
	}
}

void UWidget_ListEntry_Float::OnOwningListDataObjectSet(UListDataObject_Base* InOwningListDataObject)
{
	Super::OnOwningListDataObjectSet(InOwningListDataObject);

	//Cache the source object
	CachedOwningFloatDataObject = CastChecked<UListDataObject_Float>(InOwningListDataObject);

	//Init Slider with source object info
	if (SliderWrapper && CachedOwningFloatDataObject)
	{
		//Use the source object to init the slider, slider expects normalized input for value
		float NormalizedValue =
			(CachedOwningFloatDataObject->GetCurrentValue() - CachedOwningFloatDataObject->GetMinValue()) /
			(CachedOwningFloatDataObject->GetMaxValue() - CachedOwningFloatDataObject->GetMinValue());

		SliderWrapper->InitSlider(NormalizedValue, CachedOwningFloatDataObject->GetMinValue(), 
			CachedOwningFloatDataObject->GetMaxValue(), CachedOwningFloatDataObject->GetDelta());

		//Bind to OnListDataModified in Source with OnOwningListDataObjectModified
		CachedOwningFloatDataObject->OnListDataModified.AddUObject(this, &ThisClass::OnOwningListDataObjectModified);
	}

	//Use the source object to Set the display text
	if (CommonText_ValueDisplay)
		CommonText_ValueDisplay->SetText(CachedOwningFloatDataObject->GetCurrentValueAsText());
}

void UWidget_ListEntry_Float::OnOwningListDataObjectModified(
	UListDataObject_Base* OwningModifiedData, EOptionsListDataModifyReason ModifyReason)
{
	//use cached source object to update the Slider's position and display text
	if (CachedOwningFloatDataObject)
	{
		float NormalizedValue =
			(CachedOwningFloatDataObject->GetCurrentValue() - CachedOwningFloatDataObject->GetMinValue()) /
			(CachedOwningFloatDataObject->GetMaxValue() - CachedOwningFloatDataObject->GetMinValue());

		if(SliderWrapper)
			SliderWrapper->SetValue(NormalizedValue);

		if (CommonText_ValueDisplay)
		CommonText_ValueDisplay->SetText(CachedOwningFloatDataObject->GetCurrentValueAsText());
	}
}

void UWidget_ListEntry_Float::OnSliderValueChanged(float Value)
{
	SelectThisEntryWidget();

	if (CachedOwningFloatDataObject)
	{
		CachedOwningFloatDataObject->SetCurrentValue(Value);
		CachedOwningFloatDataObject->CommitValue();
	}

	if (CommonText_ValueDisplay)
		CommonText_ValueDisplay->SetText(CachedOwningFloatDataObject->GetCurrentValueAsText());
}

void UWidget_ListEntry_Float::OnMouseRelease()
{
	if (CachedOwningFloatDataObject)
		CachedOwningFloatDataObject->CommitValue();

	UK2HGameUserSettings::Get()->ApplySettings(true);
}
