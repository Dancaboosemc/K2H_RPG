// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Widget_ActivatableBase.h"
#include "Widget_OptionsScreen.generated.h"

class UOptionsDataRegistry;
class UK2HTabListWidgetBase;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class K2H_RPG_API UWidget_OptionsScreen : public UWidget_ActivatableBase
{
	GENERATED_BODY()
	
protected:

	//~ Begin UUserWidget Interface
	virtual void NativeOnInitialized() override;
	//~ End UUserWidget Interface

	//~ Begin UCommonActivatableWidget Interface
	virtual void NativeOnActivated() override;
	//~ End UCommonActivatableWidget Interface

private:

	UOptionsDataRegistry* GetOrCreateDataRegistry();

	void OnResetBoundActiontriggered();
	void OnBackBoundActiontriggered();

	UFUNCTION()
	void OnOptionsTabSelected(FName TabId);

	/*	Bound Widgets	*/
	UPROPERTY(meta = (BindWidget))
	UK2HTabListWidgetBase* TabListWidget_OptionTabs;
	/*	Bound Widgets	*/

	//Handle create of Data in the Options Screen. Driect Access to this variable is forbidden
	UPROPERTY(Transient)
	UOptionsDataRegistry* OwningDataRegistry;

	UPROPERTY(EditDefaultsOnly, Category = "OptionsScreen", meta = 
		(RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle ResetAction;

	FUIActionBindingHandle ResetActionHandle;

};
