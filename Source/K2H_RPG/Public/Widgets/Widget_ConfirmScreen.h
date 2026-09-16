// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Widget_ActivatableBase.h"
#include "Types/K2HEnumTypes.h"

#include "Widget_ConfirmScreen.generated.h"

class UCommonTextBlock;
class UDynamicEntryBox;
class UK2HCommonButtonBase;

//Button Info struct for assigning functionality and text to the buttons of the screen
USTRUCT(BlueprintType)
struct FConfirmScreenButtonInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EConfirmScreenButtonType ConfirmScreenButtonType = EConfirmScreenButtonType::Unknown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ButtonTextToDisplay;
};

/**
 *	Source Object for the screen. Proveds Implementation for Construction different formats of the confrim screen.
 *	Has Properties for storing the nessecary text needed for the screen
 */
UCLASS()
class K2H_RPG_API UConfirmScreenInfoObject : public UObject
{
	GENERATED_BODY()

public:

	//Functions for constructing different kinds of confirmation screens
	static UConfirmScreenInfoObject* CreateOKScreen(const FText& InScreenTitle, const FText& InScreenMsg);
	static UConfirmScreenInfoObject* CreateYesNoScreen(const FText& InScreenTitle, const FText& InScreenMsg);
	static UConfirmScreenInfoObject* CreateOKCancelScreen(const FText& InScreenTitle, const FText& InScreenMsg);

	//Title
	UPROPERTY(Transient)
	FText ScreenTitle;
	//Message
	UPROPERTY(Transient)
	FText ScreenMsg;

	//Button info array
	UPROPERTY(Transient)
	TArray<FConfirmScreenButtonInfo> AvailableScreenButtons;
};
/**
 *	Widget Class for a Confirm screen
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class K2H_RPG_API UWidget_ConfirmScreen : public UWidget_ActivatableBase
{
	GENERATED_BODY()

public:

	//Should be called before widget is pushed, but after construction
	void InitConfirmScreen(UConfirmScreenInfoObject* InScreenInfoObject, 
		TFunction<void(EConfirmScreenButtonType)> ClickedButtonCallback);

	
private:

	UPROPERTY(meta = (BindWidget))
	UCommonTextBlock* CommonTextBlock_Title;

	UPROPERTY(meta = (BindWidget))
	UCommonTextBlock* CommonTextBlock_Msg;

	UPROPERTY(meta = (BindWidget))
	UDynamicEntryBox* DynamicEntryBox_Buttons;

	//Cached property to store the widge we wish to start focus on
	UPROPERTY(Transient)
	TObjectPtr<UK2HCommonButtonBase> DesiredFocusButton;

protected:

	//overrided to supply our foucs target
	virtual UWidget* NativeGetDesiredFocusTarget() const override;
};
