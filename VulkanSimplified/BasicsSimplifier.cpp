#include "pch.h"
#include "Include/BasicsSimplifier.h"

#include "VulkanCoreSimplifier.h"
#include "WindowSimplifier.h"
#include "SurfaceSimplifier.h"

namespace VulkanSimplified
{
	BasicsSimplifier::BasicsSimplifier(WindowCreationData windowSettings, AppData appSettings)
	{
		SDL_Init(SDL_INIT_VIDEO);

		_windows = std::make_unique<WindowSimplifier>(windowSettings);
		_core = std::make_unique<VulkanCoreSimplifier>(appSettings);
		_surface = std::make_unique<SurfaceSimplifier>(_windows->GetWindow(), _core->GetInstance());
	}

	BasicsSimplifier::~BasicsSimplifier()
	{
		_surface->PreDestructionCall(_core->GetInstance());
		_surface.reset();
		_core.reset();
		_windows.reset();
		SDL_Quit();
	}
}