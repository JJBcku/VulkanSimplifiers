module;

#include <SDL2/SDL_events.h>

export module VulkanSimplifiers.EventHandling.SDLModule.DisplayEvent;

import std;

//SDL_DisplayEvent variant for the modular structure
export struct SDLModuleDisplayEvent
{
    std::uint32_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
    std::uint32_t display;     /**< The associated display index */
    std::uint8_t event;        /**< SDLModuleDisplayEventID */
    std::uint8_t padding1;
    std::uint8_t padding2;
    std::uint8_t padding3;
    std::int32_t data1;       /**< event dependent data */

    SDLModuleDisplayEvent(const SDL_DisplayEvent& eventData);
};

export enum SDLModuleDisplayEventID : std::uint8_t
{
    SDL_MODULE_DISPLAYEVENT_NONE,          /**< Never used */
    SDL_MODULE_DISPLAYEVENT_ORIENTATION,   /**< Display orientation has changed to data1 */
    SDL_MODULE_DISPLAYEVENT_CONNECTED,     /**< Display has been added to the system */
    SDL_MODULE_DISPLAYEVENT_DISCONNECTED,  /**< Display has been removed from the system */
    SDL_MODULE_DISPLAYEVENT_MOVED          /**< Display has changed position */
};