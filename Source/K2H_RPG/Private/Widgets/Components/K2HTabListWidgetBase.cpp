// Daniel McPherson, All Rights Reserved


#include "Widgets/Components/K2HTabListWidgetBase.h"
#include "Editor/WidgetCompilerLog.h"
#include "Widgets/Components/K2HCommonButtonBase.h"

#if WITH_EDITOR	
void UK2HTabListWidgetBase::RequestRegisterTab(const FName& InTabID, const FText& InTabDisplayName)
{
	RegisterTab(InTabID, TabButtonEntryWidgetClass, nullptr, -1);

	if (UK2HCommonButtonBase* FoundButton = Cast<UK2HCommonButtonBase>(GetTabButtonBaseByID(InTabID)))
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
