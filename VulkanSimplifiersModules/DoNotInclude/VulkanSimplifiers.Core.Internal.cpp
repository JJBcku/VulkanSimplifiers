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

IDObject<WindowPointer> CoreInternal::CreateWindow(WindowCreationData data, size_t addReserved)
{
	return _windowList.AddObject(std::make_unique<WindowInternal>(data), addReserved);
}

EventHandlingInternal& CoreInternal::GetEventHandler()
{
	return _eventHandler;
}

WindowInternal& CoreInternal::GetWindowSimplifier(IDObject<WindowPointer> windowID)
{
	auto& window = _windowList.GetObject(windowID);

	return *window;
}

const EventHandlingInternal& CoreInternal::GetEventHandler() const
{
	return _eventHandler;
}

const WindowInternal& CoreInternal::GetWindowSimplifier(IDObject<WindowPointer> windowID) const
{
	auto& window = _windowList.GetConstObject(windowID);

	return *window;
}
