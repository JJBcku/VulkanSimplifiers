module;

#include <SDL2/SDL.h>

module VulkanSimplifiers.Core.Internal;

CoreInternal::CoreInternal(size_t reserveInstances, size_t reserveWindows) : _instanceList(reserveInstances), _windowList(reserveWindows)
{
	int result = SDL_Init(SDL_INIT_VIDEO);
	 if (result < 0)
		throw std::runtime_error("Program failed to initialize SDL, error code" + std::to_string(result));
}

CoreInternal::~CoreInternal()
{
	SDL_Quit();
}

IDObject<WindowPointer> CoreInternal::CreateWindow(WindowCreationData data, size_t addReserved)
{
	return _windowList.AddObject(std::make_unique<WindowInternal>(data), addReserved);
}

WindowSimplifier CoreInternal::GetWindowSimplifier(IDObject<WindowPointer> windowID)
{
	auto& window = _windowList.GetObject(windowID);

	return WindowSimplifier(*window);
}
