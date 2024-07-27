module;

#include <SDL2/SDL_events.h>

module VulkanSimplifiers.EventHandling.SDLModule.DropEvent;

SDLModuleDropEvent::SDLModuleDropEvent(const SDL_DropEvent& eventData)
{
	switch (eventData.type)
	{
	case SDL_DROPBEGIN:
		type = SDLModuleDropEventType::DROPEVENT_BEGIN;
		break;
	case SDL_DROPFILE:
		type = SDLModuleDropEventType::DROPEVENT_FILE;
		break;
	case SDL_DROPTEXT:
		type = SDLModuleDropEventType::DROPEVENT_TEXT;
		break;
	case SDL_DROPCOMPLETE:
		type = SDLModuleDropEventType::DROPEVENT_COMPLETE;
		break;
	default:
		throw std::runtime_error("SDLModuleDropEvent error: Program was given wrong type of SDL event!");
	}

	timestamp = eventData.timestamp;
	file = eventData.file;
	vpadding = nullptr;
	windowID = eventData.windowID;
	padding = 0;
}
