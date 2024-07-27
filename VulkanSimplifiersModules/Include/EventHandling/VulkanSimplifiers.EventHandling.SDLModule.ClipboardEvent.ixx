module;

#include <SDL2/SDL_events.h>

export module VulkanSimplifiers.EventHandling.SDLModule.ClipboardEvent;

import std;

export struct SDLModuleClipboardEvent
{
	std::uint32_t timestamp;

	SDLModuleClipboardEvent(const SDL_CommonEvent& eventData);
};