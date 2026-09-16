// Daniel McPherson, All Rights Reserved


#include "Widgets/Components/K2HCommonListView.h"
#include "Editor/WidgetCompilerLog.h"
#include "Widgets/Options/DataAsset_DataListEntryMapping.h"
#include "Widgets/Options/ListEntries/Widget_ListEntry_Base.h"
#include "Widgets/Options/DataObjects/ListDataObject_Base.h"

UUserWidget& UK2HCommonListView::OnGenerateEntryWidgetInternal(UObject* Item, 
	TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable)
{
	//if Design time, return super
	if (IsDesignTime())
	{
		return Super::OnGenerateEntryWidgetInternal(Item, DesiredEntryClass, OwnerTable);
	}

	//Get and check for Widget Entry class in data asset using Item parameter,
	//if found, return Entry genreation function with the found class and the OwnerTable parameter
	if (TSubclassOf<UWidget_ListEntry_Base> FoundWidgetClass =
		DataListEntryMapping->FindEntryWidgetClassByDataObject(CastChecked<UListDataObject_Base>(Item)))
	{
		return GenerateTypedEntry<UWidget_ListEntry_Base>(FoundWidgetClass, OwnerTable);
	}
	//if not widget class is found, return super
	else
	{
		return Super::OnGenerateEntryWidgetInternal(Item, DesiredEntryClass, OwnerTable);
	}
}

#if WITH_EDITOR	
void UK2HCommonListView::ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledDefaults(CompileLog);

	if (!DataListEntryMapping)
	{
		CompileLog.Error(FText::FromString(TEXT("UK2HCommonListView: ValidateCompiledDefaults: The variable DataListEntryMapping has no vaild entry specified.")));
	}
}
#endif