// Daniel McPherson, All Rights Reserved


#include "Widgets/Options/OptionsDataRegistry.h"
#include "Widgets/Options/DataObjects/ListDataObject_Collection.h"
#include "Widgets/Options/DataObjects/ListDataObject_String.h"
#include "Widgets/Options/DataObjects/ListDataObject_Float.h"
#include "Widgets/Options/DataObjects/ListDataObject_Bool.h"
#include "Widgets/Options/OptionsDataInteractionHelper.h"
#include "Settings/K2HGameUserSettings.h"
#include "K2HFunctionLibrary.h"
#include "K2HGameplayTags.h"
#include "GameSubsystems/AudioSubsystem.h"
#include "AudioModulationStatics.h"

//Macro for creating FOptionsDataInteractionHelper, requires setter or getter function in UK2HGameUserSettings
#define MAKE_OPTIONS_DATA_CONTROL(SetterOrGetterFuncName, SetterOrGetterPropName)	\
	MakeShared<FOptionsDataInteractionHelper>(GET_FUNCTION_NAME_STRING_CHECKED(UK2HGameUserSettings,SetterOrGetterFuncName), TEXT(#SetterOrGetterPropName))

void UOptionsDataRegistry::InitOptionsDataRegistry(ULocalPlayer* InOwningLocalPlayer)
{
	OwningLocalPlayer = InOwningLocalPlayer;

	//Init Collections for for each Option Screen Tab
	InitGameplayCollectionTab();
	InitAudioCollectionTab();
	InitVideoCollectionTab();
	InitControlCollectionTab();
	InitLanguageCollectionTab();
}

TArray<UListDataObject_Base*> UOptionsDataRegistry::GetListSourceItemsBySelectedTabID
	(const FGameplayTag& InSelectedTabID) const
{
	//Find Collection: returns a const* 
	UListDataObject_Collection* const* FoundTabCollectionPtr = RegisteredOptionsTabCollections.FindByPredicate(
		[InSelectedTabID](UListDataObject_Collection* AvailableTabCollection)->bool
		{
			return AvailableTabCollection->GetDataID() == InSelectedTabID;
		}
	);
	
	//check if collection was found
	checkf(FoundTabCollectionPtr, TEXT("No valid tab found under the ID: %s"), *InSelectedTabID.ToString());

	//Convert from const*
	UListDataObject_Collection* FoundTabCollection = *FoundTabCollectionPtr;

	//Return Entry Array found in Collection
	return FoundTabCollection->GetChildListData();
}

void UOptionsDataRegistry::InitGameplayCollectionTab()
{
	//Create and Init Collection
	UListDataObject_Collection* GameplayTabCollection = NewObject<UListDataObject_Collection>();
	GameplayTabCollection->SetDataID(K2HGameplayTags::Tab_Gameplay);
	GameplayTabCollection->SetDataDisplayName(FText::FromString(TEXT("Gameplay")));

	//Create Collection Entries and Add to Collection
	//Game Difficulty
	{
		UListDataObject_String* GameDifficulty = NewObject<UListDataObject_String>();

		GameDifficulty->SetDataID(K2HGameplayTags::Test_Setting_Difficulty);
		GameDifficulty->SetDataDisplayName(FText::FromString(TEXT("Difficulty")));
		GameDifficulty->SetDescriptionRichText(FText::FromString(
			TEXT("Adjusts the difficulty of the game experience.\n\n<Bold>Easy:</> Focuses on the story"
				" experience. Provides the most relaxing combat.\n\n<Bold>Normal:</> Offers slightly harder"
				" combat experience\n\n<Bold>Proud:</> Offers a much more challenging combat"
				" experience\n\n<Bold>Critical:</> Provides the most challenging combat experience. Not "
				"recommended for first play through.")));
		GameDifficulty->SetShouldApplySettingsImmediately(true);

		GameDifficulty->AddDynamicOption(TEXT("Story"), FText::FromString(TEXT("Story")));
		GameDifficulty->AddDynamicOption(TEXT("Normal"), FText::FromString(TEXT("Normal")));
		GameDifficulty->AddDynamicOption(TEXT("Proud"), FText::FromString(TEXT("Proud")));
		GameDifficulty->AddDynamicOption(TEXT("Critical"), FText::FromString(TEXT("Critical")));

		GameDifficulty->SetDefaultValueFromString(TEXT("Story"));

		//Construct FOptionsDataInteractionHelpers for assigning to UListDataObject_Value Dynamic Get/Setters
		GameDifficulty->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetCurrentDifficulty, CurrentDifficulty));
		GameDifficulty->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetCurrentDifficulty, CurrentDifficulty));

		GameplayTabCollection->AddChildListData(GameDifficulty);
	}

	//Test item
	/*{
		UListDataObject_Bool* TestItem = NewObject<UListDataObject_Bool>();
		TestItem->SetDataID(K2HGameplayTags::Test_Setting_Image);
		TestItem->SetDataDisplayName(FText::FromString(TEXT("Test Bool Item")));
		TestItem->SetSoftDescriptionImage(
			UK2HFunctionLibrary::GetOptionsSoftImageByTag(K2HGameplayTags::Image_TestImage));
		TestItem->SetDescriptionRichText(FText::FromString(
			TEXT("<Bold>Test Description:</> This is an example of a Bool setting")));

		TestItem->SetDefaultValueFromString(TEXT("True"));
		TestItem->InitValue(true);

		GameplayTabCollection->AddChildListData(TestItem);

	}*/

	//Add Collection to Collection Array
	RegisteredOptionsTabCollections.Add(GameplayTabCollection);
}

void UOptionsDataRegistry::InitAudioCollectionTab()
{
	//Create and Init Collection
	UListDataObject_Collection* AudioTabCollection = NewObject<UListDataObject_Collection>();
	AudioTabCollection->SetDataID(K2HGameplayTags::Tab_Audio);
	AudioTabCollection->SetDataDisplayName(FText::FromString(TEXT("Audio")));

	//Create Collection Entries and Add to Collection
	//MASTER SLIDER
	{
		UAudioSubsystem* AudioSubsystem = OwningLocalPlayer->GetGameInstance()->GetSubsystem<UAudioSubsystem>();
		UListDataObject_Float* MasterVol = NewObject<UListDataObject_Float>();
		FGameplayTag Tag = K2HGameplayTags::Audio_Volume_Master;

		MasterVol->SetDataID(Tag);
		MasterVol->SetDataDisplayName(FText::FromString(TEXT("Master Volume")));

		MasterVol->SetRange(0.f, 1.f);
		MasterVol->SetDelta(.01f);
		MasterVol->SetMaximumFractionalDigits(0);
		MasterVol->SetDisplayAsPercentage(true);

		MasterVol->SetCurrentValue(UAudioModulationStatics::GetModulatorValue(GetWorld(), AudioSubsystem->GetBusByTag(Tag)));
		MasterVol->SetDefaultValueFromString(FString::SanitizeFloat(AudioSubsystem->GetDefaultValueByTag(Tag)));

		MasterVol->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetMasterVolume, MasterVolume));
		MasterVol->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetMasterVolume, MasterVolume));

		MasterVol->OnListDataModified.AddUObject(AudioSubsystem, &UAudioSubsystem::OnOwningListDataObjectModified);

		AudioTabCollection->AddChildListData(MasterVol);
	}

	//Music SLIDER
	{
		UAudioSubsystem* AudioSubsystem = OwningLocalPlayer->GetGameInstance()->GetSubsystem<UAudioSubsystem>();
		UListDataObject_Float* MusicVol = NewObject<UListDataObject_Float>();
		FGameplayTag Tag = K2HGameplayTags::Audio_Volume_Music;

		MusicVol->SetDataID(Tag);
		MusicVol->SetDataDisplayName(FText::FromString(TEXT("Music Volume")));

		MusicVol->SetRange(0.f, 1.f);
		MusicVol->SetDelta(.01f);
		MusicVol->SetMaximumFractionalDigits(0);
		MusicVol->SetDisplayAsPercentage(true);

		MusicVol->SetCurrentValue(UAudioModulationStatics::GetModulatorValue(GetWorld(), AudioSubsystem->GetBusByTag(Tag)));
		MusicVol->SetDefaultValueFromString(FString::SanitizeFloat(AudioSubsystem->GetDefaultValueByTag(Tag)));

		MusicVol->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetMusicVolume, MusicVolume));
		MusicVol->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetMusicVolume, MusicVolume));

		MusicVol->OnListDataModified.AddUObject(AudioSubsystem, &UAudioSubsystem::OnOwningListDataObjectModified);


		AudioTabCollection->AddChildListData(MusicVol);
	}

	//UI SLIDER
	{
		UAudioSubsystem* AudioSubsystem = OwningLocalPlayer->GetGameInstance()->GetSubsystem<UAudioSubsystem>();
		UListDataObject_Float* UIVol = NewObject<UListDataObject_Float>();
		FGameplayTag Tag = K2HGameplayTags::Audio_Volume_UI;

		UIVol->SetDataID(Tag);
		UIVol->SetDataDisplayName(FText::FromString(TEXT("UI Volume")));

		UIVol->SetRange(0.f, 1.f);
		UIVol->SetDelta(.01f);
		UIVol->SetMaximumFractionalDigits(0);
		UIVol->SetDisplayAsPercentage(true);

		UIVol->SetCurrentValue(UAudioModulationStatics::GetModulatorValue(GetWorld(), AudioSubsystem->GetBusByTag(Tag)));
		UIVol->SetDefaultValueFromString(FString::SanitizeFloat(AudioSubsystem->GetDefaultValueByTag(Tag)));

		UIVol->SetDataDynamicGetter(MAKE_OPTIONS_DATA_CONTROL(GetUIVolume, UIVolume));
		UIVol->SetDataDynamicSetter(MAKE_OPTIONS_DATA_CONTROL(SetUIVolume, UIVolume));

		UIVol->OnListDataModified.AddUObject(AudioSubsystem, &UAudioSubsystem::OnOwningListDataObjectModified);

		AudioTabCollection->AddChildListData(UIVol);
	}

	//Add Collection to Collection Array
	RegisteredOptionsTabCollections.Add(AudioTabCollection);
}

void UOptionsDataRegistry::InitVideoCollectionTab()
{
	//Create and Init Collection
	UListDataObject_Collection* VideoTabCollection = NewObject<UListDataObject_Collection>();
	VideoTabCollection->SetDataID(K2HGameplayTags::Tab_Video);
	VideoTabCollection->SetDataDisplayName(FText::FromString(TEXT("Video")));

	//TODO: Create Collection Entries and Add to Collection


	//Add Collection to Collection Array
	RegisteredOptionsTabCollections.Add(VideoTabCollection);
}

void UOptionsDataRegistry::InitControlCollectionTab()
{
	//Create and Init Collection
	UListDataObject_Collection* ControlTabCollection = NewObject<UListDataObject_Collection>();
	ControlTabCollection->SetDataID(K2HGameplayTags::Tab_Control);
	ControlTabCollection->SetDataDisplayName(FText::FromString(TEXT("Control")));

	//TODO: Create Collection Entries and Add to Collection


	//Add Collection to Collection Array
	RegisteredOptionsTabCollections.Add(ControlTabCollection);
}

void UOptionsDataRegistry::InitLanguageCollectionTab()
{
	//Create and Init Collection
	UListDataObject_Collection* LanguageTabCollection = NewObject<UListDataObject_Collection>();
	LanguageTabCollection->SetDataID(K2HGameplayTags::Tab_Language);
	LanguageTabCollection->SetDataDisplayName(FText::FromString(TEXT("Language")));

	//TODO: Create Collection Entries and Add to Collection

	//Add Collection to Collection Array
	RegisteredOptionsTabCollections.Add(LanguageTabCollection);
}