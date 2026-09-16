// Daniel McPherson, All Rights Reserved


#include "Widgets/Components/K2HCommonRotator.h"
#include "CommonTextBlock.h"

void UK2HCommonRotator::SetSelectedOptionByText(const FText& InTextOption)
{
	//Find the index of InTextOption in TextLabels
	const int32 Index = TextLabels.IndexOfByPredicate(
		[InTextOption](const FText& TextItem)->bool
		{
			return TextItem.EqualTo(InTextOption);
		}
	);

	//if valid index is found, then use base class implementation to set the current selection
	//otherwise set the text manually without adding to the options list
	if (Index != INDEX_NONE)
		SetSelectedItem(Index);
	else
		MyText->SetText(InTextOption);
}
