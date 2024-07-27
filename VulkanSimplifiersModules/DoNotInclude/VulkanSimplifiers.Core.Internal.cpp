module;

#include <SDL2/SDL.h>

module VulkanSimplifiers.Core.Internal;

CoreInternal::CoreInternal(const CoreSimplifierInitData& initData) : _eventHandler(initData.eventHandlerData),
_instanceList(initData.instancesListInitialCapacity), _windowList(initData.windowsListInitialCapacity)
{
	int result = SDL_Init(SDL_INIT_VIDEO);
	 if (result < 0)
		throw std::runtime_error("Program failed to initialize SDL, error code" + std::to_string(result));

	 _appVersion = initData.appVersion;
	 _appTitle = initData.appTitle;
	 _appVarianTile = initData.appVariantTitle;
}

CoreInternal::~CoreInternal()
{
	SDL_Quit();
}

EventHandlingInternal& CoreInternal::GetEventHandler()
{
	return _eventHandler;
}

WindowListInternal& CoreInternal::GetWindowListSimplifier()
{
	return _windowList;
}

const EventHandlingInternal& CoreInternal::GetEventHandler() const
{
	return _eventHandler;
}

const WindowListInternal& CoreInternal::GetWindowListSimplifier() const
{
	return _windowList;
}
