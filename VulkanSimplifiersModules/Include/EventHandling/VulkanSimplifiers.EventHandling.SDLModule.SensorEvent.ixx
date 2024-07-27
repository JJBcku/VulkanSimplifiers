module;

#include <SDL2/SDL_events.h>

export module VulkanSimplifiers.EventHandling.SDLModule.SensorEvent;

import std;

export struct SDLModuleSensorEvent
{
    std::uint32_t timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
    std::int32_t which;       /**< The instance ID of the sensor */
    float data[6];      /**< Up to 6 values from the sensor - additional values can be queried using SDL_SensorGetData() */
    std::uint64_t timestamp_us; /**< The timestamp of the sensor reading in microseconds, if the hardware provides this information. */

    SDLModuleSensorEvent(const SDL_SensorEvent& eventData);
};