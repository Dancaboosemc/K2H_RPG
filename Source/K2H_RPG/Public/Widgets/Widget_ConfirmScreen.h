// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Widget_ActivatableBase.h"
#include "Types/K2HEnumTypes.h"

#include "Widget_ConfirmScreen.generated.h"

class UCommonTextBlock;
class UDynamicEntryBox;
class UK2HCommonButtonBase;

USTRUCT(BlueprintType)
struct FConfirmScreenButtonInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EConfirmScreenButtonType ConfirmScreenButtonType = EConfirmScreenButtonType::Unknown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ButtonTextToDisplay;
};

UCLASS()
class K2H_RPG_API UConfirmScreenInfoObject : public UObject
{
	GENERATED_BODY()

public:

	static UConfirmScreenInfoObject* CreateOKScreen(const FText& InScreenTitle, const FText& InScreenMsg);
	static UConfirmScreenInfoObject* CreateYesNoScreen(const FText& InScreenTitle, const FText& InScreenMsg);
	static UConfirmScreenInfoObject* CreateOKCancelScreen(const FText& InScreenTitle, const FText& InScreenMsg);

	UPROPERTY(Transient)
	FText ScreenTitle;

	UPROPERTY(Transient)
	FText ScreenMsg;

	UPROPERTY(Transient)
	TArray<FConfirmScreenButtonInfo> AvailableScreenButtons;
};
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class K2H_RPG_API UWidget_ConfirmScreen : public UWidget_ActivatableBase
{
	GENERATED_BODY()

public:

	//Gets called before widget is pushed, but after construction
	void InitConfirmScreen(UConfirmScreenInfoObject* InScreenInfoObject, 
		TFunction<void(EConfirmScreenButtonType)> ClickedButtonCallback);

	
private:

	UPROPERTY(meta = (BindWidget))
	UCommonTextBlock* CommonTextBlock_Title;

	UPROPERTY(meta = (BindWidget))
	UCommonTextBlock* CommonTextBlock_Msg;

	UPROPERTY(meta = (BindWidget))
	UDynamicEntryBox* DynamicEntryBox_Buttons;

	UPROPERTY(Transient)
	TObjectPtr<UK2HCommonButtonBase> DesiredFocusButton;

protected:

	virtual UWidget* NativeGetDesiredFocusTarget() const override;
};
