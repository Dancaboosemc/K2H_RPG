// Daniel McPherson, All Rights Reserved


#include "Widgets/Components/K2H_CBB_SliderWrapper.h"
#include "Components/Slider.h"
#include "Settings/K2HGameUserSettings.h"

#include "DebugHelper.h"

bool UK2H_CBB_SliderWrapper::Initialize()
{
	if (Super::Initialize())
	{
		OnNavigation.BindUObject(this, &ThisClass::HandleNavigation);
		return true;
	}

	return false;
}

FNavigationReply UK2H_CBB_SliderWrapper::NativeOnNavigation(const FGeometry& MyGeometry, const FNavigationEvent& InNavigationEvent, const FNavigationReply& InDefaultReply)
{
	switch (InNavigationEvent.GetNavigationType())
	{
	case EUINavigation::Left:
	case EUINavigation::Right:
		return FNavigationReply::Custom(OnNavigation);
	default:
		return InDefaultReply;
	}
}

TSharedPtr<SWidget> UK2H_CBB_SliderWrapper::HandleNavigation(EUINavigation UINavigation)
{
	if (UINavigation == EUINavigation::Left)
	{
		if (Slider->GetValue() > Slider->GetMinValue())
		{
			AdjustSlider(-1.f);
		}
	}
	else if (UINavigation == EUINavigation::Right)
	{
		if (Slider->GetValue() < Slider->GetMaxValue())
		{
			AdjustSlider(1.f);
		}
	}

	UK2HGameUserSettings::Get()->ApplySettings(true);

	return nullptr;
}

void UK2H_CBB_SliderWrapper::NativeConstruct()
{
	Super::NativeConstruct();

	Slider->OnValueChanged.AddDynamic(this, &ThisClass::HandleSliderValueChanged);
}

void UK2H_CBB_SliderWrapper::InitSlider(float value, float Min, float Max, float Step)
{
	Slider->OnMouseCaptureEnd.AddUniqueDynamic(this, &ThisClass::HandleMouseCaptureEnd);
	Slider->SetMinValue(Min);
	Slider->SetMaxValue(Max);
	Slider->SetStepSize(Step);
	SetValue(value);
}

void UK2H_CBB_SliderWrapper::SetValue(float Value)
{
	Slider->SetValue(Value);
}

FReply UK2H_CBB_SliderWrapper::NativeOnAnalogValueChanged(
	const FGeometry& Geometry, const FAnalogInputEvent& InAnalogEvent)
{
	const FKey Key = InAnalogEvent.GetKey();

	if (Key == EKeys::Gamepad_LeftX)
	{
		CurrentAnalogValue = InAnalogEvent.GetAnalogValue();

		if (!GetWorld()->GetTimerManager().IsTimerActive(AnalogRepeatTimer))
		{
			GetWorld()->GetTimerManager().SetTimer(
				AnalogRepeatTimer,
				this,
				&UK2H_CBB_SliderWrapper::HandleAnalogRepeat,
				0.1f,
				true,
				0.3f
			);
		}

		return FReply::Handled();
	}

	return Super::NativeOnAnalogValueChanged(Geometry, InAnalogEvent);
}

void UK2H_CBB_SliderWrapper::HandleSliderValueChanged(float Value)
{
	WrapperOnValueChanged.Broadcast(Value);
}

void UK2H_CBB_SliderWrapper::HandleMouseCaptureEnd()
{
	OnMouseCaptureEnd.Broadcast();
}

void UK2H_CBB_SliderWrapper::HandleAnalogRepeat()
{
	if (FMath::Abs(CurrentAnalogValue) < 0.3f)
	{
		GetWorld()->GetTimerManager().ClearTimer(AnalogRepeatTimer);

		return;
	}
	
	if (CurrentAnalogValue > 0.f && Slider->GetValue() < Slider->GetMaxValue())
	{
		AdjustSlider(1.f);
	}
	
	if (CurrentAnalogValue < 0.f && Slider->GetValue() > Slider->GetMinValue())
	{
		AdjustSlider(-1.f);
	}

	Debug::Print(TEXT("UK2H_CBB_SliderWrapper::HandleAnalogRepeat: Settings Applied"));
	UK2HGameUserSettings::Get()->ApplySettings(true);
}

void UK2H_CBB_SliderWrapper::AdjustSlider(float increment)
{
	SetValue(Slider->GetValue() + increment * Slider->GetStepSize());
}
