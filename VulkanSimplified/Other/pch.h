// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"

#include <stdint.h>
#include <vector>
#include <stdexcept>
#include <memory>
#include <iostream>
#include <functional>
#include <optional>
#include <limits>
#include <iterator>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_structs.hpp>

#endif //PCH_H
