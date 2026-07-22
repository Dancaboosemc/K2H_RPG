// Daniel McPherson, All Rights Reserved


#include "Widgets/Options/Widget_OptionsScreen.h"
#include "Input/CommonUIInputTypes.h"
#include "ICommonInputModule.h"
#include "Widgets/Options/OptionsDataRegistry.h"
#include "Widgets/Components/K2HTabListWidgetBase.h"
#include "Widgets/Options/DataObjects/ListDataObject_Collection.h"

#include "DebugHelper.h"

void UWidget_OptionsScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!ResetAction.IsNull())
	{
		ResetActionHandle = RegisterUIActionBinding(
			FBindUIActionArgs(
				ResetAction,
				true,
				FSimpleDelegate::CreateUObject(this, &ThisClass::OnResetBoundActiontriggered)
			)
		);
	}

	ResetActionHandle = RegisterUIActionBinding(
		FBindUIActionArgs(
			ICommonInputModule::GetSettings().GetDefaultBackAction(),
			true,
			FSimpleDelegate::CreateUObject(this, &ThisClass::OnBackBoundActiontriggered)
		)
	);

	TabListWidget_OptionTabs->OnTabSelected.AddUniqueDynamic(this, &ThisClass::OnOptionsTabSelected);
}

void UWidget_OptionsScreen::NativeOnActivated()
{
	Super::NativeOnActivated();

	for (UListDataObject_Collection* TabCollection : GetOrCreateDataRegistry()->GetRegisteredOptionsTabCollections())
	{
		if (!TabCollection) continue;

		const FName TabID = TabCollection->GetDataID();

		if (TabListWidget_OptionTabs->GetTabButtonBaseByID(TabID) != nullptr) continue;

		TabListWidget_OptionTabs->RequestRegisterTab(TabID, TabCollection->GetDataDisplayName());
	}
}

UOptionsDataRegistry* UWidget_OptionsScreen::GetOrCreateDataRegistry()
{
	if (!OwningDataRegistry)
	{
		OwningDataRegistry = NewObject<UOptionsDataRegistry>();
		OwningDataRegistry->InitOptionsDataRegistry(GetOwningLocalPlayer());
	}
	checkf(OwningDataRegistry, TEXT("Data Registry for Options Screen is not valid."));

	return OwningDataRegistry;
}

void UWidget_OptionsScreen::OnResetBoundActiontriggered()
{
	Debug::Print(TEXT("Reset Bound Action Triggered"));
}

void UWidget_OptionsScreen::OnBackBoundActiontriggered()
{
	DeactivateWidget();
}

void UWidget_OptionsScreen::OnOptionsTabSelected(FName TabId)
{
	Debug::Print(TEXT("New Tab Selected. Tab ID: ") + TabId.ToString());
}
