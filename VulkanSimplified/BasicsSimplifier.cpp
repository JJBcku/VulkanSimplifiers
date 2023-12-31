#include "pch.h"
#include "Include/BasicsSimplifier.h"

#include "VulkanCoreSimplifier.h"
#include "WindowSimplifier.h"

namespace VulkanSimplified
{
	BasicsSimplifier::BasicsSimplifier(WindowCreationData windowSettings, AppData appSettings)
	{
		SDL_Init(SDL_INIT_VIDEO);

		_core = std::make_unique<VulkanCoreSimplifier>(appSettings);
		_windows = std::make_unique<WindowSimplifier>(windowSettings);
	}

	BasicsSimplifier::~BasicsSimplifier()
	{
		_windows.reset();
		SDL_Quit();
	}
}