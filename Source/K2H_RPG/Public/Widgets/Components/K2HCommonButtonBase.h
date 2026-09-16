// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "K2HCommonButtonBase.generated.h"

class UCommonTextBlock;
/**
 *  UCommButtonBase child which provides Button Implementation, 
 *	This class provides implementaion for a UCommonTextBlock property,
 *  and functions for managing it. Also has a text property for decribing the button's use.
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class K2H_RPG_API UK2HCommonButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()

public:

	//Gettter & Setter for UCommonTextBlock, can be called from Blueprint
	UFUNCTION(BlueprintCallable)
	void SetButtonText(FText InText);

	UFUNCTION(BlueprintCallable)
	FText GetButtonDisplayText() const;

private:

	//~ Begin UUserWidget Interface
	virtual void NativePreConstruct() override;
	//~ End UUserWidget Interface

	//~ Begin UCommonButtonBase Interface
	//overrided to apply Text Style to UCommonTextBlock
	virtual void NativeOnCurrentTextStyleChanged() override;

	//overrided to use delegate in UUISubsystem to handle 
	//assigning Text to a Description widget
	virtual void NativeOnHovered() override;
	virtual void NativeOnUnhovered() override;
	//~ End UCommonButtonBase Interface

	/* Bound Widgets */

	UPROPERTY(meta = (BindWidgetOptional))
	UCommonTextBlock* CommonTextBlock_ButtonText;

	/* Bound Widgets */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "K2H Button", meta = (AllowPrivateAccess = "true"))
	FText ButtonDisplayText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "K2H Button", meta = (AllowPrivateAccess = "true"))
	bool bUseUpperCaseForButtonText = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "K2H Button", meta = (AllowPrivateAccess = "true"))
	FText ButtonDescriptionText;
};
