module VulkanSimplifiers.EventHandling.SDLModule.SensorEvent;

SDLModuleSensorEvent::SDLModuleSensorEvent(const SDL_SensorEvent& eventData)
{
	timestamp = eventData.timestamp;
	which = eventData.which;
	data[0] = eventData.data[0];
	data[1] = eventData.data[1];
	data[2] = eventData.data[2];
	data[3] = eventData.data[3];
	data[4] = eventData.data[4];
	data[5] = eventData.data[5];
	timestamp_us = eventData.timestamp_us;
}