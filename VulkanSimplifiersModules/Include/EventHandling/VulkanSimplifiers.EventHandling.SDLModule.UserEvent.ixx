module;

#include <SDL2/SDL_events.h>

export module VulkanSimplifiers.EventHandling.SDLModule.UserEvent;

import std;

export struct SDLModuleUserEvent
{
    std::uint32_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
    std::uint32_t windowID;    /**< The associated window if any */
    std::int32_t code;        /**< User defined event code */
    std::uint32_t padding;
    void* data1;        /**< User defined data pointer */
    void* data2;        /**< User defined data pointer */

    SDLModuleUserEvent(const SDL_UserEvent& eventData);
};