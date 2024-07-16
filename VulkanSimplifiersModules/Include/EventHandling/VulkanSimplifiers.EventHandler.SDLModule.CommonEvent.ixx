module;

#include <SDL2/SDL_events.h>

export module VulkanSimplifiers.EventHandler.SDLModule.CommonEvent;

import std;

export struct SDLModuleCommonEvent
{
	std::uint32_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
	std::uint32_t padding;

	SDLModuleCommonEvent(const SDL_CommonEvent& eventData);
};
