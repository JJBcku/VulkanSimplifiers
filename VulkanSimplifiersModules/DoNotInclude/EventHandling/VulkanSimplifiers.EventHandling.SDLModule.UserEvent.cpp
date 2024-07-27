module VulkanSimplifiers.EventHandling.SDLModule.UserEvent;

SDLModuleUserEvent::SDLModuleUserEvent(const SDL_UserEvent& eventData)
{
	timestamp = eventData.timestamp;
	windowID = eventData.windowID;
	code = eventData.code;
	padding = 0;
	data1 = eventData.data1;
	data2 = eventData.data2;
}
