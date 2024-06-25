module;

#include <SDL2/SDL.h>

module VulkanSimplifiers.CoreSimplifier.Internal;

CoreSimplifierInternal::CoreSimplifierInternal(size_t reserveInstances, size_t reserveWindows) : _instanceList(reserveInstances), _windowList(reserveWindows)
{
	SDL_Init(SDL_INIT_VIDEO);
}

CoreSimplifierInternal::~CoreSimplifierInternal()
{
}