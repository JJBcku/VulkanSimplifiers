module VulkanSimplifiers.EventHandler.SDLModule.ClipboardEvent;

SDLModuleClipboardEvent::SDLModuleClipboardEvent(const SDL_CommonEvent& eventData)
{
	timestamp = eventData.timestamp;
}