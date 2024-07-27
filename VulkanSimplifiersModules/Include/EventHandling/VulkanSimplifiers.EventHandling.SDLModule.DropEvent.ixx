module;

#include <SDL2/SDL_events.h>

export module VulkanSimplifiers.EventHandling.SDLModule.DropEvent;

import std;

export enum class SDLModuleDropEventType : std::uint32_t
{
	DROPEVENT_BEGIN,
	DROPEVENT_FILE,
	DROPEVENT_TEXT,
	DROPEVENT_COMPLETE,
};

export struct SDLModuleDropEvent
{
	SDLModuleDropEventType type;
	std::uint32_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
	char* file;         /**< The file name, which should be freed with SDL_free(), is NULL on begin/complete */
	void* vpadding;
	std::uint32_t windowID;    /**< The window that was dropped on, if any */
	std::uint32_t padding;

	SDLModuleDropEvent(const SDL_DropEvent& eventData);
};