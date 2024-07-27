module VulkanSimplifiers.EventHandling.SDLModule.AppEvents;

SDLModuleAppTerminatingEvent::SDLModuleAppTerminatingEvent(const SDL_CommonEvent& eventData)
{
	timestamp = eventData.timestamp;
}

SDLModuleAppLowMemoryEvent::SDLModuleAppLowMemoryEvent(const SDL_CommonEvent& eventData)
{
	timestamp = eventData.timestamp;
}

SDLModuleAppWillEnterBackgroundEvent::SDLModuleAppWillEnterBackgroundEvent(const SDL_CommonEvent& eventData)
{
	timestamp = eventData.timestamp;
}

SDLModuleAppDidEnterBackgroundEvent::SDLModuleAppDidEnterBackgroundEvent(const SDL_CommonEvent& eventData)
{
	timestamp = eventData.timestamp;
}

SDLModuleAppWillEnterForegroundEvent::SDLModuleAppWillEnterForegroundEvent(const SDL_CommonEvent& eventData)
{
	timestamp = eventData.timestamp;
}

SDLModuleAppDidEnterForegroundEvent::SDLModuleAppDidEnterForegroundEvent(const SDL_CommonEvent& eventData)
{
	timestamp = eventData.timestamp;
}