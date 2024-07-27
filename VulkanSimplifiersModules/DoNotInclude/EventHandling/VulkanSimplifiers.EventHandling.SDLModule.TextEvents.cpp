module VulkanSimplifiers.EventHandling.SDLModule.TextEvents;

SDLModuleTextEditingEvent::SDLModuleTextEditingEvent(const SDL_TextEditingEvent& eventData)
{
	timestamp = eventData.timestamp;
	windowID = eventData.windowID;
	for (size_t i = 0; i < SDL_MODULES_TEXTEDITINGEVENT_TEXT_SIZE; i++)
		text[i] = eventData.text[i];
	start = eventData.start;
	length = eventData.length;
}

SDLModuleTextEditingExtendedEvent::SDLModuleTextEditingExtendedEvent(const SDL_TextEditingExtEvent& eventData)
{
	timestamp = eventData.timestamp;
	windowID = eventData.windowID;
	text = eventData.text;
	vpadding = nullptr;
	start = eventData.start;
	length = eventData.length;
}

SDLModuleTextInputEvent::SDLModuleTextInputEvent(const SDL_TextInputEvent& eventData)
{
	timestamp = eventData.timestamp;
	windowID = eventData.windowID;
	for (size_t i = 0; i < SDL_MODULE_TEXTINPUTEVENT_TEXT_SIZE; i++)
		text[i] = eventData.text[i];
}
