module;

#include <SDL2/SDL_events.h>

export module VulkanSimplifiers.EventHandling.SDLModule.ControllerEvents;

import std;

export enum SDLModuleGameControllerAxis : std::uint8_t
{
    SDL_MODULE_CONTROLLER_AXIS_INVALID = std::numeric_limits<std::uint8_t>::max(),
    SDL_MODULE_CONTROLLER_AXIS_LEFTX = 0,
    SDL_MODULE_CONTROLLER_AXIS_LEFTY,
    SDL_MODULE_CONTROLLER_AXIS_RIGHTX,
    SDL_MODULE_CONTROLLER_AXIS_RIGHTY,
    SDL_MODULE_CONTROLLER_AXIS_TRIGGERLEFT,
    SDL_MODULE_CONTROLLER_AXIS_TRIGGERRIGHT,
    SDL_MODULE_CONTROLLER_AXIS_MAX
};

export struct SDLModuleControllerAxisEvent
{
    std::uint32_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
    std::int32_t which; /**< The joystick instance id */
    std::uint8_t axis;         /**< The controller axis (SDLModuleGameControllerAxis) */
    std::uint8_t padding1;
    std::uint8_t padding2;
    std::uint8_t padding3;
    std::int16_t value;       /**< The axis value (range: -32768 to 32767) */
    std::uint16_t padding4;

    SDLModuleControllerAxisEvent(const SDL_ControllerAxisEvent& eventData);
};

export enum SDLModuleGameControllerButtons : std::uint8_t
{
    SDL_MODULE_CONTROLLER_BUTTON_INVALID = std::numeric_limits<std::uint8_t>::max(),
    SDL_MODULE_CONTROLLER_BUTTON_A = 0,
    SDL_MODULE_CONTROLLER_BUTTON_B,
    SDL_MODULE_CONTROLLER_BUTTON_X,
    SDL_MODULE_CONTROLLER_BUTTON_Y,
    SDL_MODULE_CONTROLLER_BUTTON_BACK,
    SDL_MODULE_CONTROLLER_BUTTON_GUIDE,
    SDL_MODULE_CONTROLLER_BUTTON_START,
    SDL_MODULE_CONTROLLER_BUTTON_LEFTSTICK,
    SDL_MODULE_CONTROLLER_BUTTON_RIGHTSTICK,
    SDL_MODULE_CONTROLLER_BUTTON_LEFTSHOULDER,
    SDL_MODULE_CONTROLLER_BUTTON_RIGHTSHOULDER,
    SDL_MODULE_CONTROLLER_BUTTON_DPAD_UP,
    SDL_MODULE_CONTROLLER_BUTTON_DPAD_DOWN,
    SDL_MODULE_CONTROLLER_BUTTON_DPAD_LEFT,
    SDL_MODULE_CONTROLLER_BUTTON_DPAD_RIGHT,
    SDL_MODULE_CONTROLLER_BUTTON_MISC1,    /* Xbox Series X share button, PS5 microphone button, Nintendo Switch Pro capture button, Amazon Luna microphone button */
    SDL_MODULE_CONTROLLER_BUTTON_PADDLE1,  /* Xbox Elite paddle P1 (upper left, facing the back) */
    SDL_MODULE_CONTROLLER_BUTTON_PADDLE2,  /* Xbox Elite paddle P3 (upper right, facing the back) */
    SDL_MODULE_CONTROLLER_BUTTON_PADDLE3,  /* Xbox Elite paddle P2 (lower left, facing the back) */
    SDL_MODULE_CONTROLLER_BUTTON_PADDLE4,  /* Xbox Elite paddle P4 (lower right, facing the back) */
    SDL_MODULE_CONTROLLER_BUTTON_TOUCHPAD, /* PS4/PS5 touchpad button */
    SDL_MODULE_CONTROLLER_BUTTON_MAX
};

export struct SDLModuleControllerButtonEvent
{
    std::uint32_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
    std::int32_t which; /**< The joystick instance id */
    std::uint8_t button;       /**< The controller button (SDL_GameControllerButton) */
    std::uint8_t state;        /**< 1 if pressed or 0 if released */
    std::uint8_t padding1;
    std::uint8_t padding2;
    std::uint32_t padding3;

    SDLModuleControllerButtonEvent(const SDL_ControllerButtonEvent& eventData);
};

export enum class SDLModuleControllerDeviceEventType : std::uint32_t
{
    DEVICE_ADDED = 0,
    DEVICE_REMOVED = 1,
    DEVICE_REMMAPED = 2,
};

export struct SDLModuleControllerDeviceEvent
{
    SDLModuleControllerDeviceEventType type;
    std::uint32_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
    std::int32_t which;       /**< The joystick device index for the ADDED event, instance id for the REMOVED or REMAPPED event */
    std::uint32_t padding;

    SDLModuleControllerDeviceEvent(const SDL_ControllerDeviceEvent& eventData);
};

export enum class SDLModuleControllerTouchpadEventType : std::uint32_t
{
    TOUCHPAD_DOWN = 0,
    TOUCHPAD_MOTION = 1,
    TOUCHPAD_UP = 2,
};

export struct SDLModuleControllerTouchpadEvent
{
    SDLModuleControllerTouchpadEventType type;
    std::uint32_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
    std::int32_t which; /**< The joystick instance id */
    std::int32_t touchpad;    /**< The index of the touchpad */
    std::int32_t finger;      /**< The index of the finger on the touchpad */
    float x;            /**< Normalized in the range 0...1 with 0 being on the left */
    float y;            /**< Normalized in the range 0...1 with 0 being at the top */
    float pressure;     /**< Normalized in the range 0...1 */

    SDLModuleControllerTouchpadEvent(const SDL_ControllerTouchpadEvent& eventData);
};

export struct SDLModuleControllerSensorEvent
{
    std::uint32_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
    std::int32_t which; /**< The joystick instance id */
    std::int32_t sensor;      /**< The type of the sensor, one of the values of ::SDL_SensorType */
    float data[3];      /**< Up to 3 values from the sensor, as defined in SDL_sensor.h */
    std::uint64_t timestamp_us; /**< The timestamp of the sensor reading in microseconds, if the hardware provides this information. */

    SDLModuleControllerSensorEvent(const SDL_ControllerSensorEvent& eventData);
};
