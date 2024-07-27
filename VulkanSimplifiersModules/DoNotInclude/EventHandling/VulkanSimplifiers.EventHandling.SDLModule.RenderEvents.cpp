module VulkanSimplifiers.EventHandling.SDLModule.RenderEvents;

SDLModuleRenderTargetsResetEvent::SDLModuleRenderTargetsResetEvent(const SDL_CommonEvent& eventData)
{
	timestamp = eventData.timestamp;
}

SDLModuleRenderDeviceResetEvent::SDLModuleRenderDeviceResetEvent(const SDL_CommonEvent& eventData)
{
	timestamp = eventData.timestamp;
}