module;

#include <SDL2/SDL_events.h>

export module VulkanSimplifiers.EventHandling.SDLModule.AudioDeviceEvent;

import std;

export struct SDLModuleAudioDeviceEvent
{
    std::uint32_t type;        /**< 1 if device was added, or 0 if it was removed */
    std::uint32_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
    std::uint32_t which;       /**< The audio device index for the ADDED event (valid until next SDL_GetNumAudioDevices() call), SDL_AudioDeviceID for the REMOVED event */
    std::uint8_t iscapture;    /**< zero if an output device, non-zero if a capture device. */
    std::uint8_t padding1;
    std::uint8_t padding2;
    std::uint8_t padding3;

    SDLModuleAudioDeviceEvent(const SDL_AudioDeviceEvent& eventData);
};