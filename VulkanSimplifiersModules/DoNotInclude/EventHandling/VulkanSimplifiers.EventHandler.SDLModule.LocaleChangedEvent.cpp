module VulkanSimplifiers.EventHandler.SDLModule.LocaleChangedEvent;

SDLModuleLocaleChangeEvents::SDLModuleLocaleChangeEvents(const SDL_CommonEvent& eventData)
{
	timestamp = eventData.timestamp;
}