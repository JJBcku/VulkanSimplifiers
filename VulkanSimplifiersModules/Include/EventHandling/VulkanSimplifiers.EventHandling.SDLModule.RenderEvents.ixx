module;

#include <SDL2/SDL_events.h>

export module VulkanSimplifiers.EventHandling.SDLModule.RenderEvents;

import std;

export struct SDLModuleRenderTargetsResetEvent
{
	std::uint32_t timestamp;

	SDLModuleRenderTargetsResetEvent(const SDL_CommonEvent& eventData);
};

export struct SDLModuleRenderDeviceResetEvent
{
	std::uint32_t timestamp;

	SDLModuleRenderDeviceResetEvent(const SDL_CommonEvent& eventData);
};