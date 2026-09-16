// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "K2HGameUserSettings.generated.h"

/**
 * Override GameUserSettings property in Property Settings.
 * Used to Save Persistant Settings to Config file. 
 * 
 * TODO: GameDifficulty should be moved to a USave class, 
 * it is an option that needs to be per save, not per application
 */
UCLASS()
class K2H_RPG_API UK2HGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()
	
public:

	//Easy getter for this class
	static UK2HGameUserSettings* Get();

	bool HasSavedConfigValue(const FString& PropertyName) const;

	// Setters and Getters for every Option Setting, 
	// These are used in OptionsDataRegistry to set Dynamic Setter/Getter's when creating ListDataObject's
	/*	Gameplay Collection Tab	*/

	//Game Difficulty
	UFUNCTION()
	FString GetCurrentDifficulty() const { return CurrentDifficulty; }

	UFUNCTION()
	void SetCurrentDifficulty(const FString& InNewDifficulty) { CurrentDifficulty = InNewDifficulty; }

	/*	Gameplay Collection Tab	*/


	/*	Audio Collection Tab	*/

	UFUNCTION()
	FString GetMasterVolume() const { return MasterVolume; }

	UFUNCTION()
	void SetMasterVolume(const FString& InNewVolume) { MasterVolume = InNewVolume; }

	UFUNCTION()
	FString GetMusicVolume() const { return MusicVolume; }

	UFUNCTION()
	void SetMusicVolume(const FString& InNewVolume) { MusicVolume = InNewVolume; }

	UFUNCTION()
	FString GetUIVolume() const { return UIVolume; }

	UFUNCTION()
	void SetUIVolume(const FString& InNewVolume) { UIVolume = InNewVolume; }
	
	/*	Audio Collection Tab	*/
private:

	// Properties to represent current settings, must be marked Config to be saved to the config file
	UPROPERTY(Config)
	FString CurrentDifficulty;

	//Volume Settings Stored as FString so we are able to tell if the user has altered the value
	UPROPERTY(Config)
	FString MasterVolume;

	UPROPERTY(Config)
	FString MusicVolume;

	UPROPERTY(Config)
	FString UIVolume;
};
