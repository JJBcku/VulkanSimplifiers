module VulkanSimplifiers.EventHandler.SDLModule.CommonEvent;

SDLModuleCommonEvent::SDLModuleCommonEvent(const SDL_CommonEvent& eventData)
{
	timestamp = eventData.timestamp;
	padding = 0;
}