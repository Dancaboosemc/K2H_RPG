// Daniel McPherson, All Rights Reserved

#pragma once

#include "NativeGameplayTags.h"

namespace FrontEndGameplayTags
{
	//Widget Stack
	K2H_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_WidgetStack_Modal);
	K2H_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_WidgetStack_GameMenu);
	K2H_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_WidgetStack_GameHud);
	K2H_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_WidgetStack_FrontEnd);

	//Widgets
	K2H_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_Widget_PressAnyKeyScreen);
	K2H_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_Widget_MainMenuScreen);
	K2H_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_Widget_IntroScreen);
	K2H_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_Widget_OptionsScreen);

	K2H_RPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_Widget_ConfirmScreen);
}