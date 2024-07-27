module;

#include <SDL2/SDL_events.h>

export module VulkanSimplifiers.EventHandling.SDLModule.AppEvents;

import std;

export struct SDLModuleAppTerminatingEvent
{
	std::uint32_t timestamp;

	SDLModuleAppTerminatingEvent(const SDL_CommonEvent& eventData);
};

export struct SDLModuleAppLowMemoryEvent
{
	std::uint32_t timestamp;

	SDLModuleAppLowMemoryEvent(const SDL_CommonEvent& eventData);
};

export struct SDLModuleAppWillEnterBackgroundEvent
{
	std::uint32_t timestamp;

	SDLModuleAppWillEnterBackgroundEvent(const SDL_CommonEvent& eventData);
};

export struct SDLModuleAppDidEnterBackgroundEvent
{
	std::uint32_t timestamp;

	SDLModuleAppDidEnterBackgroundEvent(const SDL_CommonEvent& eventData);
};

export struct SDLModuleAppWillEnterForegroundEvent
{
	std::uint32_t timestamp;

	SDLModuleAppWillEnterForegroundEvent(const SDL_CommonEvent& eventData);
};

export struct SDLModuleAppDidEnterForegroundEvent
{
	std::uint32_t timestamp;

	SDLModuleAppDidEnterForegroundEvent(const SDL_CommonEvent& eventData);
};
