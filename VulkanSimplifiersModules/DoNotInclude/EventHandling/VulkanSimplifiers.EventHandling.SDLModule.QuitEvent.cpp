module VulkanSimplifiers.EventHandling.SDLModule.QuitEvent;

SDLModuleQuitEvent::SDLModuleQuitEvent(const SDL_QuitEvent& eventData)
{
	timestamp = eventData.timestamp;
}
