module;

#include <SDL2/SDL_events.h>

export module VulkanSimplifiers.EventHandler.SDLModule.SystemEvent;

import std;

export struct SDLModuleOSEvent
{
	std::uint32_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */

	SDLModuleOSEvent(const SDL_OSEvent& eventData);
};