module VulkanSimplifiers.EventHandling.SDLModule.LocaleChangedEvent;

SDLModuleLocaleChangeEvent::SDLModuleLocaleChangeEvent(const SDL_CommonEvent& eventData)
{
	timestamp = eventData.timestamp;
}