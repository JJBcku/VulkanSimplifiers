module;

#include <SDL2/SDL_events.h>

export module VulkanSimplifiers.EventHandling.SDLModule.TextEvents;

import std;

export constexpr std::uint32_t SDL_MODULES_TEXTEDITINGEVENT_TEXT_SIZE = 32;

export struct SDLModuleTextEditingEvent
{
    std::uint32_t timestamp;                           /**< In milliseconds, populated using SDL_GetTicks() */
    std::uint32_t windowID;                            /**< The window with keyboard focus, if any */
    char text[SDL_MODULES_TEXTEDITINGEVENT_TEXT_SIZE];  /**< The editing text */
    std::int32_t start;                               /**< The start cursor of selected editing text */
    std::int32_t length;                              /**< The length of selected editing text */

    SDLModuleTextEditingEvent(const SDL_TextEditingEvent& eventData);
};

export struct SDLModuleTextEditingExtendedEvent
{
    std::uint32_t timestamp;                           /**< In milliseconds, populated using SDL_GetTicks() */
    std::uint32_t windowID;                            /**< The window with keyboard focus, if any */
    char* text;                                 /**< The editing text, which should be freed with SDL_free(), and will not be NULL */
    void* vpadding;
    std::int32_t start;                               /**< The start cursor of selected editing text */
    std::int32_t length;

    SDLModuleTextEditingExtendedEvent(const SDL_TextEditingExtEvent& eventData);
};

export constexpr std::uint32_t SDL_MODULE_TEXTINPUTEVENT_TEXT_SIZE = 32;

export struct SDLModuleTextInputEvent
{
    std::uint32_t timestamp;                         /**< In milliseconds, populated using SDL_GetTicks() */
    std::uint32_t windowID;                          /**< The window with keyboard focus, if any */
    char text[SDL_MODULE_TEXTINPUTEVENT_TEXT_SIZE];  /**< The input text */

    SDLModuleTextInputEvent(const SDL_TextInputEvent& eventData);
};
