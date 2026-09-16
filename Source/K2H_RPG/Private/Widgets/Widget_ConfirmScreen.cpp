// Daniel McPherson, All Rights Reserved


#include "Widgets/Widget_ConfirmScreen.h"
#include "CommonTextBlock.h"
#include "Components/DynamicEntryBox.h"
#include "Widgets/Components/K2HCommonButtonBase.h"
#include "ICommonInputModule.h"

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateOKScreen(const FText& InScreenTitle, const FText& InScreenMsg)
{
	//Create and Init InfoObject
	UConfirmScreenInfoObject* InforObject = NewObject<UConfirmScreenInfoObject>();
	InforObject->ScreenTitle = InScreenTitle;
	InforObject->ScreenMsg = InScreenMsg;

	//Create and init Button Info
	FConfirmScreenButtonInfo OkButtonInfo;
	OkButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Closed;
	OkButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("Ok"));

	//add button to AvailableScreenButtons array
	InforObject->AvailableScreenButtons.Add(OkButtonInfo);

	return InforObject;
}

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateYesNoScreen(const FText& InScreenTitle, const FText& InScreenMsg)
{
	//Create and Init InfoObject
	UConfirmScreenInfoObject* InforObject = NewObject<UConfirmScreenInfoObject>();
	InforObject->ScreenTitle = InScreenTitle;
	InforObject->ScreenMsg = InScreenMsg;

	//Create and init Button Info
	FConfirmScreenButtonInfo YesButtonInfo;
	YesButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Confrimed;
	YesButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("Yes"));

	FConfirmScreenButtonInfo NoButtonInfo;
	NoButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Cancelled;
	NoButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("No"));

	//add button to AvailableScreenButtons array
	InforObject->AvailableScreenButtons.Add(YesButtonInfo);
	InforObject->AvailableScreenButtons.Add(NoButtonInfo);

	return InforObject;
}

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateOKCancelScreen(const FText& InScreenTitle, const FText& InScreenMsg)
{
	//Create and Init InfoObject
	UConfirmScreenInfoObject* InforObject = NewObject<UConfirmScreenInfoObject>();
	InforObject->ScreenTitle = InScreenTitle;
	InforObject->ScreenMsg = InScreenMsg;

	//Create and init Button Info
	FConfirmScreenButtonInfo OKButtonInfo;
	OKButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Confrimed;
	OKButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("Yes"));

	FConfirmScreenButtonInfo CancelButtonInfo;
	CancelButtonInfo.ConfirmScreenButtonType = EConfirmScreenButtonType::Cancelled;
	CancelButtonInfo.ButtonTextToDisplay = FText::FromString(TEXT("Cancel"));

	//add button to AvailableScreenButtons array
	InforObject->AvailableScreenButtons.Add(OKButtonInfo);
	InforObject->AvailableScreenButtons.Add(CancelButtonInfo);

	return InforObject;
}

void UWidget_ConfirmScreen::InitConfirmScreen(UConfirmScreenInfoObject* InScreenInfoObject, 
	TFunction<void(EConfirmScreenButtonType)> ClickedButtonCallback)
{
	//Check for Info Object and Widget Bindings
	check(InScreenInfoObject && CommonTextBlock_Title && 
		CommonTextBlock_Msg && DynamicEntryBox_Buttons);

	//set title and message
	CommonTextBlock_Title->SetText(InScreenInfoObject->ScreenTitle);
	CommonTextBlock_Msg->SetText(InScreenInfoObject->ScreenMsg);

	//if entry box has old button created previously
	if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
	{
		/*
			Clears the old buttons the entry box has. the widget type 
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

	//iterate over InScreenInfoObject->AvailableScreenButtons
	for (const FConfirmScreenButtonInfo& AvailableButtonInfo : InScreenInfoObject->AvailableScreenButtons)
	{
		//Create FDataTableRowHandle
		FDataTableRowHandle InputActionRowHandle;

		//Determine button type and Init Row Handle accordingly.
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

	//Create/Add and Init Button to DynamicEntryBox_Buttons.
		//Create Button
		UK2HCommonButtonBase* AddedButton = DynamicEntryBox_Buttons->CreateEntry<UK2HCommonButtonBase>();

		//Set Button text
		AddedButton->SetButtonText(AvailableButtonInfo.ButtonTextToDisplay);

		//Set Triggering action with InputActionRowHandle
		AddedButton->SetTriggeringInputAction(InputActionRowHandle);

		//Bind Callback to Button OnClick
		AddedButton->OnClicked().AddLambda(
			[ClickedButtonCallback, AvailableButtonInfo,this]()
			{
				//releases execution to BP, and we handle there based off the ConfirmScreenButtonType
				ClickedButtonCallback(AvailableButtonInfo.ConfirmScreenButtonType);

				//deactivae the widget
				DeactivateWidget();
			}
		);

		//Cache the Last Button for supplying as focus target
		DesiredFocusButton = AddedButton;
	}
}

UWidget* UWidget_ConfirmScreen::NativeGetDesiredFocusTarget() const
{
	return DesiredFocusButton;
}
