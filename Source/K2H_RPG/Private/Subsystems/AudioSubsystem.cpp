// Daniel McPherson, All Rights Reserved


#include "Subsystems/AudioSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "Saves/SettingsSave.h"
#include "K2HAudioDeveloperSettings.h"
#include "Types/AudioTypes.h"

void UAudioSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

    LoadSettings();
}

void UAudioSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

#pragma region PersistantAudio

void UAudioSubsystem::PlayMusic(USoundBase* Music)
{
    if (!Music) return;

    if (!MusicComponent)
    {
        MusicComponent = UGameplayStatics::CreateSound2D(
            GetWorld(),
            Music,
            1.f,
            1.f,
            0.f,
            nullptr,
            true);
        ApplyVolumes();
    }

    MusicComponent->SetSound(Music);
    MusicComponent->Play();
}

void UAudioSubsystem::StopMusic()
{
    if (MusicComponent)
    {
        MusicComponent->Stop();
    }
}

void UAudioSubsystem::PlayAmbient(USoundBase* Track)
{
    if (!Track) return;

    if (!AmbientComponent)
    {
        AmbientComponent = UGameplayStatics::CreateSound2D(
            GetWorld(),
            Track,
            1.f,
            1.f,
            0.f,
            nullptr,
            true);
        ApplyVolumes();
    }

    AmbientComponent->SetSound(Track);
    AmbientComponent->Play();
}

void UAudioSubsystem::StopAmbient()
{
    if (AmbientComponent)
    {
        AmbientComponent->Stop();
    }
}

#pragma endregion

#pragma region OneOffAudio

void UAudioSubsystem::Play2D(USoundBase* Sound, EPlayableAudioChannel Channel)
{
    if (!Sound) return;

    const EAudioChannel AudioChannel = ConvertPlayableChannel(Channel);

    UGameplayStatics::PlaySound2D(GetWorld(), Sound, CurrentSettings.MasterVolume * GetVolume(AudioChannel));
}

void UAudioSubsystem::PlayAtLocation(USoundBase* Sound, const FVector& Location, EPlayableAudioChannel Channel)
{
    if (!Sound) return;

    const EAudioChannel AudioChannel = ConvertPlayableChannel(Channel);

    UGameplayStatics::PlaySoundAtLocation(
        GetWorld(),
        Sound,
        Location,
        FRotator::ZeroRotator,
        CurrentSettings.MasterVolume * GetVolume(AudioChannel));
}

UAudioComponent* UAudioSubsystem::PlayAttached(USoundBase* Sound, USceneComponent* AttachTo, 
    EPlayableAudioChannel Channel)
{
    if (!Sound || !AttachTo)    return nullptr;

    const EAudioChannel AudioChannel = ConvertPlayableChannel(Channel);

    return UGameplayStatics::SpawnSoundAttached(
        Sound,
        AttachTo,
        NAME_None,
        FVector::ZeroVector,
        EAttachLocation::KeepRelativeOffset,
        true,
        CurrentSettings.MasterVolume * GetVolume(AudioChannel));
}

UAudioComponent* UAudioSubsystem::PlayAttachedAdv(USoundBase* Sound, USceneComponent* AttachTo,
    EPlayableAudioChannel Channel, FName SocketName, FVector LocationOffset, bool bStopWhenDestroyed)
{
    if (!Sound || !AttachTo)    return nullptr;

    const EAudioChannel AudioChannel = ConvertPlayableChannel(Channel);

    return UGameplayStatics::SpawnSoundAttached(
        Sound,
        AttachTo,
        SocketName,
        LocationOffset,
        EAttachLocation::KeepRelativeOffset,
        bStopWhenDestroyed,
        CurrentSettings.MasterVolume * GetVolume(AudioChannel));
}

#pragma endregion

#pragma region SettersGetters

float UAudioSubsystem::GetVolume(EAudioChannel Channel) const
{
    switch (Channel)
    {
    case EAudioChannel::Music:
        return CurrentSettings.MusicVolume;

    case EAudioChannel::UI:
        return CurrentSettings.UIVolume;

    case EAudioChannel::SFX:
        return CurrentSettings.SFXVolume;

    case EAudioChannel::Ambience:
        return CurrentSettings.AmbientVolume;

    case EAudioChannel::Dialogue:
        return CurrentSettings.DialogueVolume;

    default:
        return CurrentSettings.MasterVolume;
    }
}

void UAudioSubsystem::SetVolume(float Volume, EAudioChannel Channel)
{
    Volume = FMath::Clamp(Volume, 0.0f, 1.0f);

    switch (Channel)
    {
    case EAudioChannel::Music:
        CurrentSettings.MusicVolume = Volume;
        ApplyVolumes();
        break;

    case EAudioChannel::UI:
        CurrentSettings.UIVolume = Volume;
        break;

    case EAudioChannel::SFX:
        CurrentSettings.SFXVolume = Volume;
        break;

    case EAudioChannel::Ambience:
        CurrentSettings.AmbientVolume = Volume;
        ApplyVolumes();
        break;

    case EAudioChannel::Dialogue:
        CurrentSettings.DialogueVolume = Volume;
        break;

    default:
        CurrentSettings.MasterVolume = Volume;
        ApplyVolumes();
        break;
    }
}

void UAudioSubsystem::ResetToDefaults()
{
    const UK2HAudioDeveloperSettings* Settings = GetDefault<UK2HAudioDeveloperSettings>();
    SetVolume(Settings->DefaultMasterVolume, EAudioChannel::Master);
    SetVolume(Settings->DefaultMusicVolume, EAudioChannel::Music);
    SetVolume(Settings->DefaultUIVolume, EAudioChannel::UI);
    SetVolume(Settings->DefaultAmbientVolume, EAudioChannel::Ambience);
    SetVolume(Settings->DefaultSFXVolume, EAudioChannel::SFX);
    SetVolume(Settings->DefaultDialogueVolume, EAudioChannel::Dialogue);

    OnAudioSettingsChanged.Broadcast(CurrentSettings);
}

#pragma endregion

void UAudioSubsystem::ApplyVolumes()
{
    if (MusicComponent)
    {
        MusicComponent->SetVolumeMultiplier(CurrentSettings.MasterVolume * CurrentSettings.MusicVolume);
    }
    if (AmbientComponent)
    {
        AmbientComponent->SetVolumeMultiplier(CurrentSettings.MasterVolume * CurrentSettings.AmbientVolume);
    }
}

void UAudioSubsystem::LoadSettings()
{
    USettingsSave* SaveGame;
    if (UGameplayStatics::DoesSaveGameExist(TEXT("K2H_Settings"), 0))
    {
        SaveGame = Cast<USettingsSave>(UGameplayStatics::LoadGameFromSlot(TEXT("K2H_Settings"), 0));
        CurrentSettings = SaveGame->AudioSettings;
    }
    else
    {
        const UK2HAudioDeveloperSettings* Settings = GetDefault<UK2HAudioDeveloperSettings>();

        CurrentSettings.MasterVolume = Settings->DefaultMasterVolume;
        CurrentSettings.MusicVolume = Settings->DefaultMusicVolume;
        CurrentSettings.UIVolume = Settings->DefaultUIVolume;
        CurrentSettings.AmbientVolume = Settings->DefaultAmbientVolume;
        CurrentSettings.DialogueVolume = Settings->DefaultDialogueVolume;
        CurrentSettings.SFXVolume = Settings->DefaultSFXVolume;
    }
    ApplyVolumes();
}

void UAudioSubsystem::SaveSettings()
{
    USettingsSave* SaveGame = Cast<USettingsSave>(
        UGameplayStatics::CreateSaveGameObject(USettingsSave::StaticClass()));
    SaveGame->AudioSettings = CurrentSettings;

    UGameplayStatics::SaveGameToSlot(SaveGame,TEXT("K2H_Settings"),0);
}

EAudioChannel UAudioSubsystem::ConvertPlayableChannel(EPlayableAudioChannel Channel) const
{
    switch (Channel)
    {
    case EPlayableAudioChannel::Music:
        return EAudioChannel::Music;

    case EPlayableAudioChannel::UI:
        return EAudioChannel::UI;

    case EPlayableAudioChannel::SFX:
        return EAudioChannel::SFX;

    case EPlayableAudioChannel::Ambience:
        return EAudioChannel::Ambience;

    default:
        return EAudioChannel::Dialogue;
    }
}
