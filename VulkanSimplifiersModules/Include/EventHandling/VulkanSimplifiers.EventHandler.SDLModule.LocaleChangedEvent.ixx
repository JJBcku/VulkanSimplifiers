module;

#include <SDL2/SDL_events.h>

export module VulkanSimplifiers.EventHandler.SDLModule.LocaleChangedEvent;

import std;

export struct SDLModuleLocaleChangeEvents
{
	std::uint32_t timestamp;

	SDLModuleLocaleChangeEvents(const SDL_CommonEvent& eventData);
};