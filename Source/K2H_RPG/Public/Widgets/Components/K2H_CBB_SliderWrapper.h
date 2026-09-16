// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"

#include "K2H_CBB_SliderWrapper.generated.h"

class USlider;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSliderWrapperValueChanged, float, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSliderWrapperMouseCaptureEnd);

/**
 * Slider Wrapper class for having a slider widget respond to CommonUI navigation, 
 * while blocking undesired functionality
 */
UCLASS()
class K2H_RPG_API UK2H_CBB_SliderWrapper : public UCommonButtonBase
{
	GENERATED_BODY()
	
public:

    //~ Begin UUserWidget Interface
    virtual bool Initialize() override;

    //overrided to provide a custom NavigationReply delegate to CommonUI, 
    virtual FNavigationReply NativeOnNavigation(
        const FGeometry& MyGeometry, const FNavigationEvent& InNavigationEvent, const FNavigationReply& InDefaultReply) override;
    //~ End UUserWidget Interface

    //Custom NavigationDelegate to be bound to the navigation logic
    FNavigationDelegate OnNavigation;

    //Handles the navigation logic
    TSharedPtr<SWidget> HandleNavigation(EUINavigation UINavigation);

    //Delegates for facilitating binding to the containing wrapper.
    UPROPERTY(BlueprintAssignable)
    FOnSliderWrapperValueChanged WrapperOnValueChanged;

    UPROPERTY(BlueprintAssignable)
    FOnSliderWrapperMouseCaptureEnd OnMouseCaptureEnd;

    virtual void NativeConstruct() override;

    void InitSlider(float value, float Min, float Max, float Step);
    void SetValue(float Value);

protected:

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<USlider> Slider;

    //overrided to provide logic for Analog Input
    virtual FReply NativeOnAnalogValueChanged(
        const FGeometry& Geometry,
        const FAnalogInputEvent& InAnalogEvent) override;

    //Functions to be bound to containing slider delegates, and should broadcast the wrapper's delegates
    UFUNCTION()
    void HandleSliderValueChanged(float Value);

    UFUNCTION()
    void HandleMouseCaptureEnd();

private:

    //Timer to restrict analog input speed
    FTimerHandle AnalogRepeatTimer;

    float CurrentAnalogValue = 0.f;

    //logic for analog input to be called when timer expires
    void HandleAnalogRepeat();

    //Helper for adjusting slider by an incremment * StepSize
    void AdjustSlider(float increment);
};
