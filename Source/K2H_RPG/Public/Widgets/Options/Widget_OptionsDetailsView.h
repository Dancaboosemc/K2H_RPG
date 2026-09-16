// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_OptionsDetailsView.generated.h"

class UCommonTextBlock;
class UCommonLazyImage;
class UCommonRichTextBlock;
class UListDataObject_Base;

/**
 *  Provides Implementation for a Widget to be displayed in the Options screen 
 *	to provide addition information about the selected option
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class K2H_RPG_API UWidget_OptionsDetailsView : public UUserWidget
{
	GENERATED_BODY()
	
public:

	//Update widget with new source object info
	void UpdateDetailsViewInfo(UListDataObject_Base* InDataObject, const FString& InEntryWidgetClassName = FString());
	//cleat widget info
	void ClearDetailsViewinfo();

protected:

	//~ Begin UUserWidget Interface
	virtual void NativeOnInitialized() override;
	//~ End UUserWidget Interface

private:

	/*	Bound Widgets	*/	

	//Title
	UPROPERTY(meta=(BindWidget))
	UCommonTextBlock* CommonTextBlock_Title;

	//Image
	UPROPERTY(meta = (BindWidget))
	UCommonLazyImage* CommonLazyImage_DescriptionImage;

	//Description Message
	UPROPERTY(meta = (BindWidget))
	UCommonRichTextBlock* CommonRichText_Description;

	//dynamic details currently used to display testing data. TODO: this may need to be removed in teh future
	UPROPERTY(meta = (BindWidget))
	UCommonRichTextBlock* CommonRichText_DynamicDetails;

	//messgae for informing reason for option being disabled
	UPROPERTY(meta = (BindWidget))
	UCommonRichTextBlock* CommonRichText_DisabledReason;

	/*	Bound Widgets	*/
};
