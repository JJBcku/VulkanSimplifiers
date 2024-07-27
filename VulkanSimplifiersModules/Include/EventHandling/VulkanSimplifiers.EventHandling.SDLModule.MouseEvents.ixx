module;

#include <SDL2/SDL_events.h>

export module VulkanSimplifiers.EventHandling.SDLModule.MouseEvents;

import std;

export enum SDLModuleMouseButtonIndex : std::uint8_t
{
    SDL_MODULE_BUTTON_INDEX_LEFT = 1,
    SDL_MODULE_BUTTON_INDEX_MIDDLE,
    SDL_MODULE_BUTTON_INDEX_RIGHT,
    SDL_MODULE_BUTTON_INDEX_X1,
    SDL_MODULE_BUTTON_INDEX_X2,
    SDL_MODULE_BUTTON_INDEX_X3,
    SDL_MODULE_BUTTON_INDEX_X4,
    SDL_MODULE_BUTTON_INDEX_X5,
    SDL_MODULE_BUTTON_INDEX_X6,
    SDL_MODULE_BUTTON_INDEX_X7,
    SDL_MODULE_BUTTON_INDEX_X8,
    SDL_MODULE_BUTTON_INDEX_X9,
    SDL_MODULE_BUTTON_INDEX_X10,
    SDL_MODULE_BUTTON_INDEX_X11,
    SDL_MODULE_BUTTON_INDEX_X12,
    SDL_MODULE_BUTTON_INDEX_X13,
    SDL_MODULE_BUTTON_INDEX_X14,
    SDL_MODULE_BUTTON_INDEX_X15,
    SDL_MODULE_BUTTON_INDEX_X16,
    SDL_MODULE_BUTTON_INDEX_X17,
    SDL_MODULE_BUTTON_INDEX_X18,
    SDL_MODULE_BUTTON_INDEX_X19,
    SDL_MODULE_BUTTON_INDEX_X20,
    SDL_MODULE_BUTTON_INDEX_X21,
    SDL_MODULE_BUTTON_INDEX_X22,
    SDL_MODULE_BUTTON_INDEX_X23,
    SDL_MODULE_BUTTON_INDEX_X24,
    SDL_MODULE_BUTTON_INDEX_X25,
    SDL_MODULE_BUTTON_INDEX_X26,
    SDL_MODULE_BUTTON_INDEX_X27,
    SDL_MODULE_BUTTON_INDEX_X28,
    SDL_MODULE_BUTTON_INDEX_X29,
};

export enum SDLModuleMouseButtonState : std::uint32_t
{
    SDL_MODULE_BUTTON_STATE_LEFT = 0X1,
    SDL_MODULE_BUTTON_STATE_MIDDLE = 0X2,
    SDL_MODULE_BUTTON_STATE_RIGHT = 0X4,
    SDL_MODULE_BUTTON_STATE_X1 = 0X8,
    SDL_MODULE_BUTTON_STATE_X2 = 0X10,
    SDL_MODULE_BUTTON_STATE_X3 = 0X20,
    SDL_MODULE_BUTTON_STATE_X4 = 0X40,
    SDL_MODULE_BUTTON_STATE_X5 = 0X80,
    SDL_MODULE_BUTTON_STATE_X6 = 0X100,
    SDL_MODULE_BUTTON_STATE_X7 = 0X200,
    SDL_MODULE_BUTTON_STATE_X8 = 0X400,
    SDL_MODULE_BUTTON_STATE_X9 = 0X800,
    SDL_MODULE_BUTTON_STATE_X10 = 0X1000,
    SDL_MODULE_BUTTON_STATE_X11 = 0X2000,
    SDL_MODULE_BUTTON_STATE_X12 = 0X4000,
    SDL_MODULE_BUTTON_STATE_X13 = 0X8000,
    SDL_MODULE_BUTTON_STATE_X14 = 0X10000,
    SDL_MODULE_BUTTON_STATE_X15 = 0X20000,
    SDL_MODULE_BUTTON_STATE_X16 = 0X40000,
    SDL_MODULE_BUTTON_STATE_X17 = 0X80000,
    SDL_MODULE_BUTTON_STATE_X18 = 0X100000,
    SDL_MODULE_BUTTON_STATE_X19 = 0X200000,
    SDL_MODULE_BUTTON_STATE_X20 = 0X400000,
    SDL_MODULE_BUTTON_STATE_X21 = 0X800000,
    SDL_MODULE_BUTTON_STATE_X22 = 0X1000000,
    SDL_MODULE_BUTTON_STATE_X23 = 0X2000000,
    SDL_MODULE_BUTTON_STATE_X24 = 0X4000000,
    SDL_MODULE_BUTTON_STATE_X25 = 0X8000000,
    SDL_MODULE_BUTTON_STATE_X26 = 0X10000000,
    SDL_MODULE_BUTTON_STATE_X27 = 0X20000000,
    SDL_MODULE_BUTTON_STATE_X28 = 0X40000000,
    SDL_MODULE_BUTTON_STATE_X29 = 0X80000000,
};

/* Used as the device ID for mouse events simulated with touch input */
export constexpr std::uint32_t SDL_MODULE_TOUCH_MOUSEID = std::numeric_limits<std::uint32_t>::max();

export struct SDLModuleMouseMotionEvent
{
    std::uint32_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
    std::uint32_t windowID;    /**< The window with mouse focus, if any */
    std::uint32_t which;       /**< The mouse instance id, or SDL_MODULE_TOUCH_MOUSEID */
    std::uint32_t state;       /**< The current button state */
    std::int32_t x;           /**< X coordinate, relative to window */
    std::int32_t y;           /**< Y coordinate, relative to window */
    std::int32_t xrel;        /**< The relative motion in the X direction */
    std::int32_t yrel;        /**< The relative motion in the Y direction */

    SDLModuleMouseMotionEvent(const SDL_MouseMotionEvent& eventData);
};

export struct SDLModuleMouseButtonEvent
{
    std::uint32_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
    std::uint32_t windowID;    /**< The window with mouse focus, if any */
    std::uint32_t which;       /**< The mouse instance id, or SDL_MODULE_TOUCH_MOUSEID */
    std::uint8_t button;       /**< The mouse button index */
    std::uint8_t state;        /**< 1 if pressed or 0 if released */
    std::uint8_t clicks;       /**< 1 for single-click, 2 for double-click, etc. */
    std::uint8_t padding1;
    std::int32_t x;           /**< X coordinate, relative to window */
    std::int32_t y;           /**< Y coordinate, relative to window */

    SDLModuleMouseButtonEvent(const SDL_MouseButtonEvent& eventData);
};

export enum SDLModuleMouseWheelDirection : std::uint32_t
{
    SDL_MODULE_MOUSEWHEEL_NORMAL,    /**< The scroll direction is normal */
    SDL_MODULE_MOUSEWHEEL_FLIPPED    /**< The scroll direction is flipped / natural */
};

export struct SDLModuleMouseWheelEvent
{
    std::uint32_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
    std::uint32_t windowID;    /**< The window with mouse focus, if any */
    std::uint32_t which;       /**< The mouse instance id, or SDL_MODULE_TOUCH_MOUSEID */
    std::int32_t x;           /**< The amount scrolled horizontally, positive to the right and negative to the left */
    std::int32_t y;           /**< The amount scrolled vertically, positive away from the user and negative toward the user */
    std::uint32_t direction;   /**< Set to one of the SDL_MOUSEWHEEL_* defines. When FLIPPED the values in X and Y will be opposite. Multiply by -1 to change them back */
    float preciseX;     /**< The amount scrolled horizontally, positive to the right and negative to the left, with float precision (added in 2.0.18) */
    float preciseY;     /**< The amount scrolled vertically, positive away from the user and negative toward the user, with float precision (added in 2.0.18) */
    std::int32_t mouseX;      /**< X coordinate, relative to window (added in 2.26.0) */
    std::int32_t mouseY;      /**< Y coordinate, relative to window (added in 2.26.0) */

    SDLModuleMouseWheelEvent(const SDL_MouseWheelEvent& eventData);
};
