module;

#include <SDL2/SDL_events.h>

module VulkanSimplifiers.EventHandling.SDLModule.TouchpadEvents;

SDLModuleTouchFingerEvent::SDLModuleTouchFingerEvent(const SDL_TouchFingerEvent& eventData)
{
	switch (eventData.type)
	{
	case SDL_FINGERDOWN:
		type = SDLModuleTouchFingerEventType::FINGER_DOWN;
		break;
	case SDL_FINGERUP:
		type = SDLModuleTouchFingerEventType::FINGER_UP;
		break;
	case SDL_FINGERMOTION:
		type = SDLModuleTouchFingerEventType::FINGER_MOTION;
		break;
	default:
		throw std::runtime_error("SDLModuleTouchFingerEvent error: Program was given wrong type of SDL event!");
	}

	timestamp = eventData.timestamp;
	touchId = eventData.touchId;
	fingerId = eventData.fingerId;
	x = eventData.x;
	y = eventData.y;
	dx = eventData.dx;
	dy = eventData.dy;
	pressure = eventData.pressure;
	windowID = eventData.windowID;
}

SDLModuleMultiGestureEvent::SDLModuleMultiGestureEvent(const SDL_MultiGestureEvent& eventData)
{
	timestamp = eventData.timestamp;
	padding2 = 0;
	touchId = eventData.touchId;
	dTheta = eventData.dTheta;
	dDist = eventData.dDist;
	x = eventData.x;
	y = eventData.y;
	numFingers = eventData.numFingers;
	padding = eventData.padding;
	padding3 = 0;
}

SDLModuleDollarGestureEvent::SDLModuleDollarGestureEvent(const SDL_DollarGestureEvent& eventData)
{
	if (eventData.type == SDL_DOLLARGESTURE)
		type = 1;
	else
		type = 0;

	timestamp = eventData.timestamp;
	touchId = eventData.touchId;
	gestureId = eventData.gestureId;
	numFingers = eventData.numFingers;
	error = eventData.error;
	x = eventData.x;
	y = eventData.y;
}
