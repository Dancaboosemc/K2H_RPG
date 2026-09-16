// Daniel McPherson, All Rights Reserved


#include "Widgets/Components/K2HCommonButtonBase.h"
#include "CommonTextBlock.h"
#include "GameSubsystems/UISubsystem.h"

void UK2HCommonButtonBase::SetButtonText(FText InText)
{
	//Check for optional widget binding
	if (CommonTextBlock_ButtonText && !InText.IsEmpty())
	{
		CommonTextBlock_ButtonText->SetText(bUseUpperCaseForButtonText ? InText.ToUpper() : InText);
	}
}

FText UK2HCommonButtonBase::GetButtonDisplayText() const
{
	//Check for optional widget binding
	if (CommonTextBlock_ButtonText)
		return CommonTextBlock_ButtonText->GetText();

	return FText();
}

void UK2HCommonButtonBase::NativeOnCurrentTextStyleChanged()
{
	Super::NativeOnCurrentTextStyleChanged();

	//Check for optional widget binding
	if (CommonTextBlock_ButtonText && GetCurrentTextStyleClass())
	{
		CommonTextBlock_ButtonText->SetStyle(GetCurrentTextStyleClass());
	}
}

void UK2HCommonButtonBase::NativeOnHovered()
{
	Super::NativeOnHovered();

	//Only broadcast if description text is not empty
	if (!ButtonDescriptionText.IsEmpty())
	{
		//broadcast delegate in UUISubsystem, with ButtonDescriptionText
		UUISubsystem::Get(this)->OnButtonDescriptionTextUpdated.Broadcast(this, ButtonDescriptionText);
	}
}

void UK2HCommonButtonBase::NativeOnUnhovered()
{
	Super::NativeOnUnhovered();

	//broadcast delegate in UUISubsystem, with empty text to clear the widget
	UUISubsystem::Get(this)->OnButtonDescriptionTextUpdated.Broadcast(this, FText::GetEmpty());
}

void UK2HCommonButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	//init CommonTextBlock_ButtonText with ButtonDisplayText FText
	SetButtonText(ButtonDisplayText);
}
