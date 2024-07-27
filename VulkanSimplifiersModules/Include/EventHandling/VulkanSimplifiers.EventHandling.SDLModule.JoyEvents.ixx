module;

#include <SDL2/SDL_events.h>

export module VulkanSimplifiers.EventHandling.SDLModule.JoyEvents;

import std;

export struct SDLModuleJoyAxisEvent
{
    std::uint32_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
    std::int32_t which; /**< The joystick instance id */
    std::uint8_t axis;         /**< The joystick axis index */
    std::uint8_t padding1;
    std::uint8_t padding2;
    std::uint8_t padding3;
    std::int16_t value;       /**< The axis value (range: -32768 to 32767) */
    std::uint16_t padding4;

    SDLModuleJoyAxisEvent(const SDL_JoyAxisEvent& eventData);
};

export struct SDLModuleJoyBallEvent
{
    std::uint32_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
    std::int32_t which; /**< The joystick instance id */
    std::uint8_t ball;         /**< The joystick trackball index */
    std::uint8_t padding1;
    std::uint8_t padding2;
    std::uint8_t padding3;
    std::int16_t xrel;        /**< The relative motion in the X direction */
    std::int16_t yrel;        /**< The relative motion in the Y direction */

    SDLModuleJoyBallEvent(const SDL_JoyBallEvent& eventData);
};

export enum SDLModuleJoyHatPosition : std::uint8_t
{
    SDL_MODULE_HAT_CENTERED = 0x0,
    SDL_MODULE_HAT_UP = 0x1,
    SDL_MODULE_HAT_RIGHT = 0x2,
    SDL_MODULE_HAT_DOWN = 0x4,
    SDL_MODULE_HAT_LEFT = 0x8,
    SDL_MODULE_HAT_RIGHTUP = SDL_MODULE_HAT_UP | SDL_MODULE_HAT_RIGHT,
    SDL_MODULE_HAT_RIGHTDOWN = SDL_MODULE_HAT_DOWN | SDL_MODULE_HAT_RIGHT,
    SDL_MODULE_HAT_LEFTUP = SDL_MODULE_HAT_UP | SDL_MODULE_HAT_LEFT,
    SDL_MODULE_HAT_LEFTDOWN = SDL_MODULE_HAT_DOWN | SDL_MODULE_HAT_LEFT,
};

export struct SDLModuleJoyHatEvent
{
    std::uint32_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
    std::int32_t which; /**< The joystick instance id */
    std::uint8_t hat;          /**< The joystick hat index */
    std::uint8_t value;        /**< The hat position value.
                         *   \sa ::SDL_MODULE_HAT_LEFTUP ::SDL_MODULE_HAT_UP ::SDL_MODULE_HAT_RIGHTUP
                         *   \sa ::SDL_MODULE_HAT_LEFT ::SDL_MODULE_HAT_CENTERED ::SDL_MODULE_HAT_RIGHT
                         *   \sa ::SDL_MODULE_HAT_LEFTDOWN ::SDL_MODULE_HAT_DOWN ::SDL_MODULE_HAT_RIGHTDOWN
                         *
                         *   Note that zero means the POV is centered.
                         */
    std::uint8_t padding1;
    std::uint8_t padding2;
    std::uint32_t padding3;

    SDLModuleJoyHatEvent(const SDL_JoyHatEvent& eventData);
};

export struct SDLModuleJoyButtonEvent
{
    std::uint32_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
    std::int32_t which; /**< The joystick instance id */
    std::uint8_t button;       /**< The joystick button index */
    std::uint8_t state;        /**< 1 for pressed or 0 for released */
    std::uint8_t padding1;
    std::uint8_t padding2;
    std::uint32_t padding3;

    SDLModuleJoyButtonEvent(const SDL_JoyButtonEvent& eventData);
};

export struct SDLModuleJoyDeviceEvent
{
    std::uint32_t type;        /**< 1 for device added or 0 for device removed */
    std::uint32_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
    std::int32_t which;       /**< The joystick device index for the ADDED event, instance id for the REMOVED event */

    SDLModuleJoyDeviceEvent(const SDL_JoyDeviceEvent& eventData);
};

export enum SDLModuleJoystickPowerLevel : std::int32_t
{
    SDL_MODULE_JOYSTICK_POWER_UNKNOWN = -1,
    SDL_MODULE_JOYSTICK_POWER_EMPTY,   /* <= 5% */
    SDL_MODULE_JOYSTICK_POWER_LOW,     /* <= 20% */
    SDL_MODULE_JOYSTICK_POWER_MEDIUM,  /* <= 70% */
    SDL_MODULE_JOYSTICK_POWER_FULL,    /* <= 100% */
    SDL_MODULE_JOYSTICK_POWER_WIRED,
    SDL_MODULE_JOYSTICK_POWER_MAX
};

export struct SDLModuleJoyBatteryEvent
{
    std::uint32_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
    std::int32_t which; /**< The joystick instance id */
    SDLModuleJoystickPowerLevel level; /**< The joystick battery level */

    SDLModuleJoyBatteryEvent(const SDL_JoyBatteryEvent& eventData);
};
