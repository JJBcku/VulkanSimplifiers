module;

#include <SDL2/SDL_events.h>

export module VulkanSimplifiers.EventHandling.SDLModule.WindowEvent;

import std;

export struct SDLModuleWindowEvent
{
    std::uint32_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
    std::uint32_t windowID;    /**< The associated window */
    std::uint8_t event;        /**< SDLModuleWindowEventID */
    std::uint8_t padding1;
    std::uint8_t padding2;
    std::uint8_t padding3;
    std::int32_t data1;       /**< event dependent data */
    std::int32_t data2;       /**< event dependent data */
    std::int32_t padding;       /**< event dependent data */

    SDLModuleWindowEvent(const SDL_WindowEvent& eventData);
};

export enum SDLModuleWindowEventID : std::uint8_t
{
    SDL_MODULE_WINDOWEVENT_NONE,           /**< Never used */
    SDL_MODULE_WINDOWEVENT_SHOWN,          /**< Window has been shown */
    SDL_MODULE_WINDOWEVENT_HIDDEN,         /**< Window has been hidden */
    SDL_MODULE_WINDOWEVENT_EXPOSED,        /**< Window has been exposed and should be
                                         redrawn */
    SDL_MODULE_WINDOWEVENT_MOVED,          /**< Window has been moved to data1, data2
                                     */
    SDL_MODULE_WINDOWEVENT_RESIZED,        /**< Window has been resized to data1xdata2 */
    SDL_MODULE_WINDOWEVENT_SIZE_CHANGED,   /**< The window size has changed, either as
                                         a result of an API call or through the
                                         system or user changing the window size. */
    SDL_MODULE_WINDOWEVENT_MINIMIZED,      /**< Window has been minimized */
    SDL_MODULE_WINDOWEVENT_MAXIMIZED,      /**< Window has been maximized */
    SDL_MODULE_WINDOWEVENT_RESTORED,       /**< Window has been restored to normal size
                                         and position */
    SDL_MODULE_WINDOWEVENT_ENTER,          /**< Window has gained mouse focus */
    SDL_MODULE_WINDOWEVENT_LEAVE,          /**< Window has lost mouse focus */
    SDL_MODULE_WINDOWEVENT_FOCUS_GAINED,   /**< Window has gained keyboard focus */
    SDL_MODULE_WINDOWEVENT_FOCUS_LOST,     /**< Window has lost keyboard focus */
    SDL_MODULE_WINDOWEVENT_CLOSE,          /**< The window manager requests that the window be closed */
    SDL_MODULE_WINDOWEVENT_TAKE_FOCUS,     /**< Window is being offered a focus (should SetWindowInputFocus() on itself or a subwindow, or ignore) */
    SDL_MODULE_WINDOWEVENT_HIT_TEST,       /**< Window had a hit test that wasn't SDL_HITTEST_NORMAL. */
    SDL_MODULE_WINDOWEVENT_ICCPROF_CHANGED,/**< The ICC profile of the window's display has changed. */
    SDL_MODULE_WINDOWEVENT_DISPLAY_CHANGED /**< Window has been moved to display data1. */
};
