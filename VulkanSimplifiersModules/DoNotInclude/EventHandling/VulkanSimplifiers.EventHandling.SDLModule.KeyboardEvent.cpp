module VulkanSimplifiers.EventHandling.SDLModule.KeyboardEvent;

SDLModuleKeysym::SDLModuleKeysym(const SDL_Keysym& keyData)
{
	scancode = static_cast<SDLModuleScancode>(keyData.scancode);
	sym = static_cast<SDLModuleKeycode>(keyData.sym);
	mod = keyData.mod;
	padding = 0;
	unused = keyData.unused;
}

SDLModuleKeyboardEvent::SDLModuleKeyboardEvent(const SDL_KeyboardEvent& eventData) : keysym(eventData.keysym)
{
	timestamp = eventData.timestamp;
	windowID = eventData.windowID;
	state = eventData.state;
	repeat = eventData.repeat;
	padding2 = eventData.padding2;
	padding3 = eventData.padding3;
	padding = 0;
}

SDLModuleKeymapChanged::SDLModuleKeymapChanged(const SDL_CommonEvent& eventData)
{
	timestamp = eventData.timestamp;
}