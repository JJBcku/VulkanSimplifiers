module;

#include <SDL2/SDL.h>

module VulkanSimplifiers.Main.Internal;

MainInternal::MainInternal(const MainSimplifierInitData& initData) : _eventHandler(initData.eventHandlerData),
_instanceList(initData.instancesListInitialCapacity), _windowList(initData.windowsListInitialCapacity)
{
	int result = SDL_Init(SDL_INIT_VIDEO);
	 if (result < 0)
		throw std::runtime_error("Program failed to initialize SDL, error code" + std::to_string(result));

	 _appVersion = initData.appVersion;
	 _appTitle = initData.appTitle;
	 _appVariantTile = initData.appVariantTitle;
}

MainInternal::~MainInternal()
{
	SDL_Quit();
}

EventHandlingInternal& MainInternal::GetEventHandler()
{
	return _eventHandler;
}

InstanceListInternal& MainInternal::GetInstanceListSimplifier()
{
	return _instanceList;
}

WindowListInternal& MainInternal::GetWindowListSimplifier()
{
	return _windowList;
}

const EventHandlingInternal& MainInternal::GetEventHandler() const
{
	return _eventHandler;
}

const InstanceListInternal& MainInternal::GetInstanceListSimplifier() const
{
	return _instanceList;
}

const WindowListInternal& MainInternal::GetWindowListSimplifier() const
{
	return _windowList;
}
