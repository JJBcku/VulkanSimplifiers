module;

#include <SDL2/SDL_events.h>

module VulkanSimplifiers.EventHandling.SDLModule.JoyEvents;

SDLModuleJoyAxisEvent::SDLModuleJoyAxisEvent(const SDL_JoyAxisEvent& eventData)
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

SDLModuleJoyBallEvent::SDLModuleJoyBallEvent(const SDL_JoyBallEvent& eventData)
{
	timestamp = eventData.timestamp;
	which = eventData.which;
	ball = eventData.ball;
	padding1 = eventData.padding1;
	padding2 = eventData.padding2;
	padding3 = eventData.padding3;
	xrel = eventData.xrel;
	yrel = eventData.yrel;
}

SDLModuleJoyHatEvent::SDLModuleJoyHatEvent(const SDL_JoyHatEvent& eventData)
{
	timestamp = eventData.timestamp;
	which = eventData.which;
	hat = eventData.hat;
	value = eventData.value;
	padding1 = eventData.padding1;
	padding2 = eventData.padding2;
	padding3 = 0;
}

SDLModuleJoyButtonEvent::SDLModuleJoyButtonEvent(const SDL_JoyButtonEvent& eventData)
{
	timestamp = eventData.timestamp;
	which = eventData.which;
	button = eventData.button;
	state = eventData.state;
	padding1 = eventData.padding1;
	padding2 = eventData.padding2;
	padding3 = 0;
}

SDLModuleJoyDeviceEvent::SDLModuleJoyDeviceEvent(const SDL_JoyDeviceEvent& eventData)
{
	if (eventData.type == static_cast<std::uint32_t>(SDL_EventType::SDL_JOYDEVICEADDED))
		type = 1;
	else
		type = 0;

	timestamp = eventData.timestamp;
	which = eventData.which;
}

SDLModuleJoyBatteryEvent::SDLModuleJoyBatteryEvent(const SDL_JoyBatteryEvent& eventData)
{
	timestamp = eventData.timestamp;
	which = eventData.which;
	level = static_cast<SDLModuleJoystickPowerLevel>(eventData.level);
}
