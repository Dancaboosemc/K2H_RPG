// Daniel McPherson, All Rights Reserved


#include "Widgets/Widget_ConfirmScreen.h"
#include "CommonTextBlock.h"
#include "Components/DynamicEntryBox.h"
#include "Widgets/Components/K2HCommonButtonBase.h"
#include "ICommonInputModule.h"

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateOKScreen(const FText& InScreenTitle, const FText& InScreenMsg)
{
	UConfirmScreenInfoObject* InforObject = NewObject<UConfirmScreenInfoObject>();
	InforObject->ScreenTitle = InScreenTitle;
	InforObject->ScreenMsg = InScreenMsg;

	FConfirmScreenButtonInfo OkButtonInfo;
	OkButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Closed;
	OkButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("Ok"));

	InforObject->AvailableScreenButtons.Add(OkButtonInfo);

	return InforObject;
}

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateYesNoScreen(const FText& InScreenTitle, const FText& InScreenMsg)
{
	UConfirmScreenInfoObject* InforObject = NewObject<UConfirmScreenInfoObject>();
	InforObject->ScreenTitle = InScreenTitle;
	InforObject->ScreenMsg = InScreenMsg;

	FConfirmScreenButtonInfo YesButtonInfo;
	YesButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Confrimed;
	YesButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("Yes"));

	FConfirmScreenButtonInfo NoButtonInfo;
	NoButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Cancelled;
	NoButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("No"));

	InforObject->AvailableScreenButtons.Add(YesButtonInfo);
	InforObject->AvailableScreenButtons.Add(NoButtonInfo);

	return InforObject;
}

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateOKCancelScreen(const FText& InScreenTitle, const FText& InScreenMsg)
{
	UConfirmScreenInfoObject* InforObject = NewObject<UConfirmScreenInfoObject>();
	InforObject->ScreenTitle = InScreenTitle;
	InforObject->ScreenMsg = InScreenMsg;

	FConfirmScreenButtonInfo OKButtonInfo;
	OKButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Confrimed;
	OKButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("Yes"));

	FConfirmScreenButtonInfo CancelButtonInfo;
	CancelButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Cancelled;
	CancelButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("Cancel"));

	InforObject->AvailableScreenButtons.Add(OKButtonInfo);
	InforObject->AvailableScreenButtons.Add(CancelButtonInfo);

	return InforObject;
}

void UWidget_ConfirmScreen::InitConfirmScreen(UConfirmScreenInfoObject* InScreenInfoObject, 
	TFunction<void(EConfirmScreenButtonType)> ClickedButtonCallback)
{
	check(InScreenInfoObject && CommonTextBlock_Title && 
		CommonTextBlock_Msg && DynamicEntryBox_Buttons);

	CommonTextBlock_Title->SetText(InScreenInfoObject->ScreenTitle);
	CommonTextBlock_Msg->SetText(InScreenInfoObject->ScreenMsg);

	//if entry box has old button created previously
	if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
	{
		/*
			Clearing the old buttons the entry box has. the widget type 
			for the entry box is specified in the child widget blueprint
		*/
		DynamicEntryBox_Buttons->Reset<UK2HCommonButtonBase>(
			[](UK2HCommonButtonBase& ExistingButton)
			{
				ExistingButton.OnClicked().Clear();
			}
		);
	}

	check(!InScreenInfoObject->AvailableScreenButtons.IsEmpty());

	for (const FConfirmScreenButtonInfo& AvailableButtonInfo : InScreenInfoObject->AvailableScreenButtons)
	{
		FDataTableRowHandle InputActionRowHandle;
		switch (AvailableButtonInfo.ConfirmScreenButtonType)
		{
		case EConfirmScreenButtonType::Cancelled:
			InputActionRowHandle = ICommonInputModule::GetSettings().GetDefaultBackAction();
			break;

		case EConfirmScreenButtonType::Closed:
			InputActionRowHandle = ICommonInputModule::GetSettings().GetDefaultBackAction();
			break;

		default:
			break;
		}
		UK2HCommonButtonBase* AddedButton = DynamicEntryBox_Buttons->CreateEntry<UK2HCommonButtonBase>();
		AddedButton->SetButtonText(AvailableButtonInfo.ButtonTextToDisplay);
		AddedButton->SetTriggeringInputAction(InputActionRowHandle);
		AddedButton->OnClicked().AddLambda(
			[ClickedButtonCallback, AvailableButtonInfo,this]()
			{
				ClickedButtonCallback(AvailableButtonInfo.ConfirmScreenButtonType);
				DeactivateWidget();
			}
		);
		DesiredFocusButton = AddedButton;
	}

	if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
	{
		/*
		* Set focus on the last button, so if there are two buttons, one is "yes" and one is "no",
		* the gamepad will focus on "no"
		*/
		//UE_LOG(LogTemp, Warning, TEXT("ConfirmScreen: SetFocus After Button Creation"));
		//DynamicEntryBox_Buttons->GetAllEntries().Last()->SetFocus();
	}
}

UWidget* UWidget_ConfirmScreen::NativeGetDesiredFocusTarget() const
{
	return DesiredFocusButton;
}
