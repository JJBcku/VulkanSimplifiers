module VulkanSimplifiers.EventHandling.SDLModule.SystemEvent;

SDLModuleOSEvent::SDLModuleOSEvent(const SDL_OSEvent& eventData)
{
	timestamp = eventData.timestamp;
}
