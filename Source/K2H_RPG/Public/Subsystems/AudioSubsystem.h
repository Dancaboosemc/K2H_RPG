// Daniel McPherson, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Types/K2HAudioSettings.h"

#include "AudioSubsystem.generated.h"

enum class EAudioChannel : uint8;

UENUM(BlueprintType)
enum class EPlayableAudioChannel : uint8
{
    Music,
    UI,
    SFX,
    Ambience,
    Dialogue
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAudioSettingsChanged,const FK2HAudioSettings&);
/**
 * 
 */
UCLASS()
class K2H_RPG_API UAudioSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

    FOnAudioSettingsChanged OnAudioSettingsChanged;

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

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

#pragma region OneOffAudio

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void Play2D(USoundBase* Sound, EPlayableAudioChannel Channel);

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayAtLocation(USoundBase* Sound, const FVector& Location, EPlayableAudioChannel Channel);

    //returns UAudioComponent* to give you the option to stop, fade, 
    //or otherwise manage the sound later if you need to.
    UFUNCTION(BlueprintCallable, Category = "Audio")
    UAudioComponent* PlayAttached(USoundBase* Sound, USceneComponent* AttachTo, EPlayableAudioChannel Channel);

    UFUNCTION(BlueprintCallable, Category = "Audio")
    UAudioComponent* PlayAttachedAdv(USoundBase* Sound, USceneComponent* AttachTo, EPlayableAudioChannel Channel,
        FName SocketName = NAME_None, FVector LocationOffset = FVector::ZeroVector, bool bStopWhenDestroyed = true);

#pragma endregion

#pragma region Setters/Getters

    UFUNCTION(BlueprintCallable, Category = "Audio")
    float GetVolume(EAudioChannel Channel) const;

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void SetVolume(float Volume, EAudioChannel Channel);

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void ResetToDefaults();
#pragma endregion

private:

    UPROPERTY()
    TObjectPtr<UAudioComponent> MusicComponent;

    UPROPERTY()
    TObjectPtr<UAudioComponent> AmbientComponent;

    FK2HAudioSettings CurrentSettings;

    void ApplyVolumes();

    void LoadSettings();
    void SaveSettings();

    EAudioChannel ConvertPlayableChannel(EPlayableAudioChannel Channel) const;
};
