module VulkanSimplifiers.EventHandling.SDLModule.MouseEvents;

SDLModuleMouseMotionEvent::SDLModuleMouseMotionEvent(const SDL_MouseMotionEvent& eventData)
{
	timestamp = eventData.timestamp;
	windowID = eventData.windowID;
	which = eventData.which;
	state = eventData.state;
	x = eventData.x;
	y = eventData.y;
	xrel = eventData.xrel;
	yrel = eventData.yrel;
}

SDLModuleMouseButtonEvent::SDLModuleMouseButtonEvent(const SDL_MouseButtonEvent& eventData)
{
	timestamp = eventData.timestamp;
	windowID = eventData.windowID;
	which = eventData.which;
	button = eventData.button;
	state = eventData.state;
	clicks = eventData.clicks;
	padding1 = eventData.padding1;
	x = eventData.x;
	y = eventData.y;
}

SDLModuleMouseWheelEvent::SDLModuleMouseWheelEvent(const SDL_MouseWheelEvent& eventData)
{
	timestamp = eventData.timestamp;
	windowID = eventData.windowID;
	which = eventData.which;
	x = eventData.x;
	y = eventData.y;
	direction = eventData.direction;
	preciseX = eventData.preciseX;
	preciseY = eventData.preciseY;
	mouseX = eventData.mouseX;
	mouseY = eventData.mouseY;
}
