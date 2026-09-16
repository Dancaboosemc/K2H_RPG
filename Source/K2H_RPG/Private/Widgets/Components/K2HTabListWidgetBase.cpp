// Daniel McPherson, All Rights Reserved


#include "Widgets/Components/K2HTabListWidgetBase.h"
#include "Editor/WidgetCompilerLog.h"
#include "Widgets/Components/K2HCommonButtonBase.h"

#if WITH_EDITOR	
void UK2HTabListWidgetBase::RequestRegisterTab(const FGameplayTag& InTabID, const FText& InTabDisplayName)
{
	//pass ID and widget class to base implementation to register the tab with the list
	RegisterTab(FName(*InTabID.ToString()), TabButtonEntryWidgetClass, nullptr, -1);

	//Check if button was registered and set it's display text
	if (UK2HCommonButtonBase* FoundButton = Cast<UK2HCommonButtonBase>(GetTabButtonBaseByID(FName(*InTabID.ToString()))))
	{
		FoundButton->SetButtonText(InTabDisplayName);
	}
}

void UK2HTabListWidgetBase::ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledDefaults(CompileLog);

	if (!TabButtonEntryWidgetClass)
	{
		CompileLog.Error(FText::FromString(TEXT("K2HTabListWidgetBase: ValidateCompiledDefaults: The variable TabButtonEntryWidgetClass has no vaild entry specified.")));
	}
}
#endif
