// Daniel McPherson, All Rights Reserved


#include "K2HGameplayTags.h"

namespace K2HGameplayTags
{
	//Widget Stack
	UE_DEFINE_GAMEPLAY_TAG(WidgetStack_Modal, "WidgetStack.Modal");
	UE_DEFINE_GAMEPLAY_TAG(WidgetStack_GameMenu, "WidgetStack.GameMenu");
	UE_DEFINE_GAMEPLAY_TAG(WidgetStack_GameHud, "WidgetStack.GameHud");
	UE_DEFINE_GAMEPLAY_TAG(WidgetStack_Frontend, "WidgetStack.Frontend");

	//Widgets
	UE_DEFINE_GAMEPLAY_TAG(Widget_PressAnyKeyScreen, "Widget.PressAnyKeyScreen");
	UE_DEFINE_GAMEPLAY_TAG(Widget_MainMenuScreen, "Widget.MainMenuScreen");
	UE_DEFINE_GAMEPLAY_TAG(Widget_IntroScreen, "Widget.IntroScreen");
	UE_DEFINE_GAMEPLAY_TAG(Widget_OptionsScreen, "Widget.OptionsScreen");

	UE_DEFINE_GAMEPLAY_TAG(Widget_ConfirmScreen, "Widget.ConfirmScreen");

	//Options Image
	UE_DEFINE_GAMEPLAY_TAG(Image_TestImage, "Image.TestImage");

	//Levels
	UE_DEFINE_GAMEPLAY_TAG(Level_MainMenu, "Level.MainMenu");

	//Options Tab ID's
	UE_DEFINE_GAMEPLAY_TAG(Tab_Gameplay, "Tab.Gameplay");
	UE_DEFINE_GAMEPLAY_TAG(Tab_Audio, "Tab.Audio");
	UE_DEFINE_GAMEPLAY_TAG(Tab_Video, "Tab.Video");
	UE_DEFINE_GAMEPLAY_TAG(Tab_Control, "Tab.Control");
	UE_DEFINE_GAMEPLAY_TAG(Tab_Language, "Tab.Language");

	//Test Setting ID's
	UE_DEFINE_GAMEPLAY_TAG(Test_Setting_Difficulty, "Test.Setting.Difficulty");
	UE_DEFINE_GAMEPLAY_TAG(Test_Setting_Image, "Test.Setting.Image");
	UE_DEFINE_GAMEPLAY_TAG(Test_Setting_SliderPercent, "Test.Setting.SliderPercent");
	UE_DEFINE_GAMEPLAY_TAG(Test_Setting_SliderValue, "Test.Setting.SliderValue");

	//Audio Settings
	UE_DEFINE_GAMEPLAY_TAG(Audio_Volume_Master, "Audio.Volume.Master");
	UE_DEFINE_GAMEPLAY_TAG(Audio_Volume_Music, "Audio.Volume.Music");
	UE_DEFINE_GAMEPLAY_TAG(Audio_Volume_UI, "Audio.Volume.UI");
}
