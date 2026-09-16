// Daniel McPherson, All Rights Reserved


#include "Widgets/Options/Widget_OptionsDetailsView.h"
#include "CommonTextBlock.h"
#include "CommonLazyImage.h"
#include "CommonRichTextBlock.h"
#include "Widgets/Options/DataObjects/ListDataObject_Base.h"

void UWidget_OptionsDetailsView::UpdateDetailsViewInfo(UListDataObject_Base* InDataObject, const FString& InEntryWidgetClassName)
{
	if (!InDataObject) return;

	//Set Display name
	CommonTextBlock_Title->SetText(InDataObject->GetDataDisplayName());

	//check and Set Image, then make visible
	if (!InDataObject->GetSoftDescriptionImage().IsNull())
	{
		CommonLazyImage_DescriptionImage->SetBrushFromLazyTexture(InDataObject->GetSoftDescriptionImage());
		CommonLazyImage_DescriptionImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	//collapse if not image found
	else
		CommonLazyImage_DescriptionImage->SetVisibility(ESlateVisibility::Collapsed);

	//set Description text
	CommonRichText_Description->SetText(InDataObject->GetDescriptionRichText());

	//construct string for dynamic details
	const FString DynamicDetails = FString::Printf(
		TEXT("Data Object Class: <Bold>%s</>\n\nEntry Widget Class: <Bold>%s</>"),
		*InDataObject->GetClass()->GetName(), *InEntryWidgetClassName);

	//set dynamic details
	CommonRichText_DynamicDetails->SetText(FText::FromString(DynamicDetails));
	
	//set disabled text
	CommonRichText_DisabledReason->SetText(InDataObject->GetDisabledWidgetText());
}

void UWidget_OptionsDetailsView::ClearDetailsViewinfo()
{
	CommonTextBlock_Title->SetText(FText::GetEmpty());
	CommonLazyImage_DescriptionImage->SetVisibility(ESlateVisibility::Collapsed);
	CommonRichText_Description->SetText(FText::GetEmpty());
	CommonRichText_DynamicDetails->SetText(FText::GetEmpty());
	CommonRichText_DisabledReason->SetText(FText::GetEmpty());
}

void UWidget_OptionsDetailsView::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	//when first Initialized, clear of any default data
	ClearDetailsViewinfo();
}
