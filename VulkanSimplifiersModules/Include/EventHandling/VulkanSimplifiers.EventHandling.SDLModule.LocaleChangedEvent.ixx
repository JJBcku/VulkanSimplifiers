module;

#include <SDL2/SDL_events.h>

export module VulkanSimplifiers.EventHandling.SDLModule.LocaleChangedEvent;

import std;

export struct SDLModuleLocaleChangeEvent
{
	std::uint32_t timestamp;

	SDLModuleLocaleChangeEvent(const SDL_CommonEvent& eventData);
};