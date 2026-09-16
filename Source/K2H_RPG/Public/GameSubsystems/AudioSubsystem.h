// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameSubsystems/K2HGameInstanceSubsystem.h"
#include "Types/K2HEnumTypes.h"
#include "GameplayTagContainer.h"

#include "AudioSubsystem.generated.h"

class UListDataObject_Base;

class USoundControlBus;
class USoundControlBusMix;

//Struct for containing the loaded Control Buses and their Default Values
USTRUCT(BlueprintType)
struct FAudioVolumeObject
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    TObjectPtr<USoundControlBus> ControlBus;

    UPROPERTY(EditAnywhere)
    float DefaultValue;
};
/**
 * Subsystem for Managing Audio, containing implementation for playing music/ambiant continous tracks,
 * and managing volume levels
 */
UCLASS()
class K2H_RPG_API UAudioSubsystem : public UK2HGameInstanceSubsystem
{
	GENERATED_BODY()

public:

    //Callback Function for when Volume Settings are modified
    void OnOwningListDataObjectModified(UListDataObject_Base* OwningModifiedData,
        EOptionsListDataModifyReason ModifyReason);

    FORCEINLINE TObjectPtr<USoundControlBusMix> GetBusMix() { return BusMix; }

    USoundControlBus* GetBusByTag(FGameplayTag InTag);

    float GetDefaultValueByTag(FGameplayTag InTag);

    //Callback function for Activating the Bus Mix and intializing Volume Buses with Defaults
    void OnWorldReady(UWorld* World);

protected:

    //Load Volume Asssests from Developer Settings
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

//Functions for Managing Persistant Audio Components
#pragma region PersistantAudio

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayMusic(USoundBase* Music);

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void StopMusic();

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayAmbient(USoundBase* Track);

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void StopAmbient();

#pragma endregion

    //Helper for Applying new Volume level to a specific Bus
    void ApplyVolumeToBus(USoundControlBusMix* BusMix, USoundControlBus* InBus,float InVolume);

private:

    UPROPERTY()
    TObjectPtr<UAudioComponent> MusicComponent;

    UPROPERTY()
    TObjectPtr<UAudioComponent> AmbientComponent;

    UPROPERTY()
    TObjectPtr<USoundControlBusMix> BusMix = nullptr;

    UPROPERTY()
    TMap<FGameplayTag, FAudioVolumeObject> VolumeDataMap;
};
