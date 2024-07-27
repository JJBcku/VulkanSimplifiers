module;

#include <SDL2/SDL_events.h>

export module VulkanSimplifiers.EventHandling.SDLModule.QuitEvent;

import std;

export struct SDLModuleQuitEvent
{
	std::uint32_t timestamp;

	SDLModuleQuitEvent(const SDL_QuitEvent& eventData);
};