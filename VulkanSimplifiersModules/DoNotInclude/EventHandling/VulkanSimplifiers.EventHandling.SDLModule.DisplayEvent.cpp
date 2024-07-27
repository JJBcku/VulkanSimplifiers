module VulkanSimplifiers.EventHandling.SDLModule.DisplayEvent;

SDLModuleDisplayEvent::SDLModuleDisplayEvent(const SDL_DisplayEvent& eventData)
{
	timestamp = eventData.timestamp;
	display = eventData.display;
	event = eventData.event;
	padding1 = eventData.padding1;
	padding2 = eventData.padding2;
	padding3 = eventData.padding3;
	data1 = eventData.data1;
}