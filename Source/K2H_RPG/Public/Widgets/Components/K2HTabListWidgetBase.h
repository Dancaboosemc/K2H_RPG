// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonTabListWidgetBase.h"
#include "GameplayTagContainer.h"

#include "K2HTabListWidgetBase.generated.h"

class UK2HCommonButtonBase;
/**
 * Provides implementation for using a stored widget class as a list entry,
 * and implementation for viewing the list in editor
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class K2H_RPG_API UK2HTabListWidgetBase : public UCommonTabListWidgetBase
{
	GENERATED_BODY()
	
public:

	//register a button widget with the list and Init it's text
	void RequestRegisterTab(const FGameplayTag& InTabID, const FText& InTabDisplayName);

private:

//Called at the end of Widget Blueprint compilation.
//Allows UMG elements to evaluate their default states and determine whether they are acceptable.
//To trigger compilation failure, add an error to the log. Warnings and notes will be visible, 
// but will not cause compiles to fail. This is where we log errors for when data is not assigned in blueprint
	//~ Begin UWidget Interface
#if WITH_EDITOR	
	virtual void ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const override;
#endif
	//~ End UWidget Interface

	//property for viewing in editor for testing, allowing us to set how many tabs we see 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "K2H Tab List Settings", 
		meta = (AllowPrivateAccess = "true", ClampMin = "1", ClampMax = "10"))
	int32 DebugEditorPreviewTabCount = 3;

	//Property for assigning a Button widget class to be used for list entries
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "K2H Tab List Settings",
		meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UK2HCommonButtonBase> TabButtonEntryWidgetClass;
};
