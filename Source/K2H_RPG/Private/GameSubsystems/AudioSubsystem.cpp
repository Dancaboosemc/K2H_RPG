// Daniel McPherson, All Rights Reserved


#include "GameSubsystems/AudioSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "K2HAudioDeveloperSettings.h"
#include "Settings/K2HGameUserSettings.h"
#include "SoundControlBusMix.h"
#include "SoundControlBus.h"
#include "AudioModulationStatics.h"
#include "K2HGameplayTags.h"
#include "Widgets/Options/DataObjects/ListDataObject_Float.h"
#include "AudioModulation.h"
#include "Engine/World.h"

#include "AudioDevice.h"
#include "DebugHelper.h"

void UAudioSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

    //Get Audio Developer Settings
    const UK2HAudioDeveloperSettings* AudioSettings =
        GetDefault<UK2HAudioDeveloperSettings>();

    if (AudioSettings->DefaultBusMix.IsNull()) return;

    //Load and Cache BusMix
    //TODO optimaization: Load Async
    BusMix = AudioSettings->DefaultBusMix.LoadSynchronous();

    //Load Control Buses and Default Values and cache in the VolumeMap
    if (AudioSettings->AudioMap.Contains(K2HGameplayTags::Audio_Volume_Master))
        if (const FAudioVolumeSetting* MasterMaping = AudioSettings->AudioMap.Find(K2HGameplayTags::Audio_Volume_Master))
        {
            if (USoundControlBus* MasterBus = MasterMaping->ControlBus.LoadSynchronous())
            {
                FAudioVolumeObject VolumeObject = FAudioVolumeObject{ MasterBus, MasterMaping->DefaultValue };
                VolumeDataMap.Add(K2HGameplayTags::Audio_Volume_Master, VolumeObject);
            }
        }

    if (AudioSettings->AudioMap.Contains(K2HGameplayTags::Audio_Volume_Music))
        if (const FAudioVolumeSetting* MusicMaping = AudioSettings->AudioMap.Find(K2HGameplayTags::Audio_Volume_Music))
        {
            if (USoundControlBus* MusicBus = MusicMaping->ControlBus.LoadSynchronous())
            {
                FAudioVolumeObject VolumeObject = FAudioVolumeObject{ MusicBus, MusicMaping->DefaultValue };
                VolumeDataMap.Add(K2HGameplayTags::Audio_Volume_Music, VolumeObject);
            }
        }

    if (AudioSettings->AudioMap.Contains(K2HGameplayTags::Audio_Volume_UI))
        if (const FAudioVolumeSetting* UIMaping = AudioSettings->AudioMap.Find(K2HGameplayTags::Audio_Volume_UI))
        {
            if (USoundControlBus* UIBus = UIMaping->ControlBus.LoadSynchronous())
            {
                FAudioVolumeObject VolumeObject = FAudioVolumeObject{ UIBus, UIMaping->DefaultValue };
                VolumeDataMap.Add(K2HGameplayTags::Audio_Volume_UI, VolumeObject);
            }
        }
}

void UAudioSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UAudioSubsystem::OnOwningListDataObjectModified(UListDataObject_Base* OwningModifiedData,
    EOptionsListDataModifyReason ModifyReason)
{
    if (!OwningModifiedData) return;

    //Check Volume Map using source object as key
    if (VolumeDataMap.Contains(OwningModifiedData->GetDataID()))
    {
        //Get the VolumeObject
        FAudioVolumeObject* VolumeObject = VolumeDataMap.Find(OwningModifiedData->GetDataID());

        //Check VolumeObject and containing ControlBus
        if (!VolumeObject || !VolumeObject->ControlBus) return;

        //Cast Source Object
        UListDataObject_Float* FloatDataObject = Cast<UListDataObject_Float>(OwningModifiedData);

        if (!FloatDataObject) return;

        //Use Source Object and Volume Object to Adjust Control Bus
        ApplyVolumeToBus(BusMix, VolumeObject->ControlBus, FloatDataObject->GetCurrentValue());
    }
}

USoundControlBus* UAudioSubsystem::GetBusByTag(FGameplayTag InTag)
{
    if (!VolumeDataMap.Contains(InTag)) return nullptr;

    return VolumeDataMap.Find(InTag)->ControlBus;
}

float UAudioSubsystem::GetDefaultValueByTag(FGameplayTag InTag)
{
    if (!VolumeDataMap.Contains(InTag)) return -1.f;

    return VolumeDataMap.Find(InTag)->DefaultValue;
}

void UAudioSubsystem::OnWorldReady(UWorld* World)
{
    //Activate BusMix
    if (BusMix)
    {
        UAudioModulationStatics::ActivateBusMix(World, BusMix);
    }

    //Determine if to apply Default value or Saved value
    if (VolumeDataMap.Contains(K2HGameplayTags::Audio_Volume_Master))
    {
        //Get Bus And Default Value From VolumeMap
        USoundControlBus* MasterBus = VolumeDataMap.Find(K2HGameplayTags::Audio_Volume_Master)->ControlBus;
        float DefaultValue = VolumeDataMap.Find(K2HGameplayTags::Audio_Volume_Master)->DefaultValue;
        if (MasterBus)
        {
            //if setting has been altered by the user then use the saved value, otherwise use DefaultValue
            if (!UK2HGameUserSettings::Get()->GetMasterVolume().IsEmpty())
            {
                ApplyVolumeToBus(BusMix, MasterBus, FCString::Atof(*UK2HGameUserSettings::Get()->GetMasterVolume()));
            }
            else
                ApplyVolumeToBus(BusMix, MasterBus, DefaultValue);
        }
    }

    if (VolumeDataMap.Contains(K2HGameplayTags::Audio_Volume_Music))
    {
        USoundControlBus* MusicBus = VolumeDataMap.Find(K2HGameplayTags::Audio_Volume_Music)->ControlBus;
        float DefaultValue = VolumeDataMap.Find(K2HGameplayTags::Audio_Volume_Music)->DefaultValue;
        if (MusicBus)
        {
            if (!UK2HGameUserSettings::Get()->GetMusicVolume().IsEmpty())
                ApplyVolumeToBus(BusMix, MusicBus, FCString::Atof(*UK2HGameUserSettings::Get()->GetMusicVolume()));
            else
                ApplyVolumeToBus(BusMix, MusicBus, DefaultValue);
        }
    }

    if (VolumeDataMap.Contains(K2HGameplayTags::Audio_Volume_UI))
    {
        USoundControlBus* UIBus = VolumeDataMap.Find(K2HGameplayTags::Audio_Volume_UI)->ControlBus;
        float DefaultValue = VolumeDataMap.Find(K2HGameplayTags::Audio_Volume_UI)->DefaultValue;
        if (UIBus)
        {
            if (!UK2HGameUserSettings::Get()->GetUIVolume().IsEmpty())
                ApplyVolumeToBus(BusMix, UIBus, FCString::Atof(*UK2HGameUserSettings::Get()->GetUIVolume()));
            else
                ApplyVolumeToBus(BusMix, UIBus, DefaultValue);
        }
    }
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
    }

    MusicComponent->SetSound(Music);
    MusicComponent->Play();
}

void UAudioSubsystem::StopMusic()
{
    if (MusicComponent)
        MusicComponent->Stop();
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

void UAudioSubsystem::ApplyVolumeToBus(USoundControlBusMix* InBusMix, USoundControlBus* InBus, float InVolume)
{
    if (!InBus || !InBusMix) return;

    FSoundControlBusMixStage Stage(InBus, InVolume);

    UAudioModulationStatics::UpdateMix(GetWorld(), InBusMix,{ Stage });
}