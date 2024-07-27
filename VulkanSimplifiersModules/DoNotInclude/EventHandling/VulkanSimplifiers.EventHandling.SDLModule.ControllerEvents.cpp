module;

#include <SDL2/SDL_events.h>

module VulkanSimplifiers.EventHandling.SDLModule.ControllerEvents;

SDLModuleControllerAxisEvent::SDLModuleControllerAxisEvent(const SDL_ControllerAxisEvent& eventData)
{
	timestamp = eventData.timestamp;
	which = eventData.which;
	axis = eventData.axis;
	padding1 = eventData.padding1;
	padding2 = eventData.padding2;
	padding3 = eventData.padding3;
	value = eventData.value;
	padding4 = 0;
}

SDLModuleControllerButtonEvent::SDLModuleControllerButtonEvent(const SDL_ControllerButtonEvent& eventData)
{
	timestamp = eventData.timestamp;
	which = eventData.which;
	button = eventData.button;
	state = eventData.state;
	padding1 = eventData.padding1;
	padding2 = eventData.padding2;
	padding3 = 0;
}

SDLModuleControllerDeviceEvent::SDLModuleControllerDeviceEvent(const SDL_ControllerDeviceEvent& eventData)
{
	switch (eventData.type)
	{
	case SDL_CONTROLLERDEVICEADDED:
		type = SDLModuleControllerDeviceEventType::DEVICE_ADDED;
		break;
	case SDL_CONTROLLERDEVICEREMOVED:
		type = SDLModuleControllerDeviceEventType::DEVICE_REMOVED;
		break;
	case SDL_CONTROLLERDEVICEREMAPPED:
		type = SDLModuleControllerDeviceEventType::DEVICE_REMMAPED;
		break;
	default:
		throw std::runtime_error("SDLModuleControllerDeviceEvent error: Wrong event type was passed to the constructor!");
	}
	timestamp = eventData.timestamp;
	which = eventData.which;
	padding = 0;
}

SDLModuleControllerTouchpadEvent::SDLModuleControllerTouchpadEvent(const SDL_ControllerTouchpadEvent& eventData)
{
	switch (eventData.type)
	{
	case SDL_CONTROLLERTOUCHPADDOWN:
		type = SDLModuleControllerTouchpadEventType::TOUCHPAD_DOWN;
		break;
	case SDL_CONTROLLERTOUCHPADMOTION:
		type = SDLModuleControllerTouchpadEventType::TOUCHPAD_MOTION;
		break;
	case SDL_CONTROLLERTOUCHPADUP:
		type = SDLModuleControllerTouchpadEventType::TOUCHPAD_DOWN;
		break;
	default:
		throw std::runtime_error("SDLModuleControllerTouchpadEvent error: Wrong event type was passed to the constructor!");
	}

	timestamp = eventData.timestamp;
	which = eventData.which;
	touchpad = eventData.touchpad;
	finger = eventData.finger;
	x = eventData.x;
	y = eventData.y;
	pressure = eventData.pressure;
}

SDLModuleControllerSensorEvent::SDLModuleControllerSensorEvent(const SDL_ControllerSensorEvent& eventData)
{
	timestamp = eventData.timestamp;
	which = eventData.which;
	sensor = eventData.sensor;
	data[0] = eventData.data[0];
	data[1] = eventData.data[1];
	data[2] = eventData.data[2];
	timestamp_us = eventData.timestamp_us;
}
