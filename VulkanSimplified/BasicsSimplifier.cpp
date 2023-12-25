#include "pch.h"
#include "Include/BasicsSimplifier.h"

#include "WindowSimplifier.h"

namespace VulkanSimplified
{
	BasicsSimplifier::BasicsSimplifier(WindowCreationData windowSettings)
	{
		SDL_Init(SDL_INIT_VIDEO);

		_windows = std::make_unique<WindowSimplifier>(windowSettings);
	}

	BasicsSimplifier::~BasicsSimplifier()
	{
		_windows.reset();
		SDL_Quit();
	}
}