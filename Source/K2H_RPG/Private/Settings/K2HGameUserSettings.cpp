// Daniel McPherson, All Rights Reserved


#include "Settings/K2HGameUserSettings.h"

UK2HGameUserSettings* UK2HGameUserSettings::Get()
{
	if (GEngine)
	{
		return Cast<UK2HGameUserSettings>(GEngine->GetGameUserSettings());
	}

	return nullptr;
}

bool UK2HGameUserSettings::HasSavedConfigValue(const FString& PropertyName) const
{
    FString Value;

    return GConfig->GetString(
        TEXT("/Script/K2H_RPG.K2HGameUserSettings"),
        *PropertyName,
        Value,
        GGameUserSettingsIni
    );
}