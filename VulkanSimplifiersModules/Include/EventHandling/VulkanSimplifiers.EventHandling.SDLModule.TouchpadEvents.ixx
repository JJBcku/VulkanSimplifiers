module;

#include <SDL2/SDL_events.h>

export module VulkanSimplifiers.EventHandling.SDLModule.TouchpadEvents;

import std;

export enum class SDLModuleTouchFingerEventType : std::uint32_t
{
    FINGER_DOWN,
    FINGER_UP,
    FINGER_MOTION,
};

export struct SDLModuleTouchFingerEvent
{
    SDLModuleTouchFingerEventType type;
    std::uint32_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
    std::int64_t touchId; /**< The touch device id */
    std::int64_t fingerId;
    float x;            /**< Normalized in the range 0...1 */
    float y;            /**< Normalized in the range 0...1 */
    float dx;           /**< Normalized in the range -1...1 */
    float dy;           /**< Normalized in the range -1...1 */
    float pressure;     /**< Normalized in the range 0...1 */
    std::uint32_t windowID;    /**< The window underneath the finger, if any */

    SDLModuleTouchFingerEvent(const SDL_TouchFingerEvent& eventData);
};

export struct SDLModuleMultiGestureEvent
{
    std::uint32_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
    std::uint32_t padding2;
    std::int64_t touchId; /**< The touch device id */
    float dTheta;
    float dDist;
    float x;
    float y;
    std::uint16_t numFingers;
    std::uint16_t padding;
    std::uint32_t padding3;

    SDLModuleMultiGestureEvent(const SDL_MultiGestureEvent& eventData);
};

export struct SDLModuleDollarGestureEvent
{
    std::uint32_t type;        /**< 1 for gesture performed or 0 for gesture recorded */
    std::uint32_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
    std::int64_t touchId; /**< The touch device id */
    std::int64_t gestureId;
    std::uint32_t numFingers;
    float error;
    float x;            /**< Normalized center of gesture */
    float y;            /**< Normalized center of gesture */

    SDLModuleDollarGestureEvent(const SDL_DollarGestureEvent& eventData);
};