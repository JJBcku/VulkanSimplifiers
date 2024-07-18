module;

#include <SDL2/SDL_events.h>

module VulkanSimplifiers.EventHandler.Internal;

EventHandlerInternal::EventHandlerInternal(size_t reserve) : _quitEventFunctions(reserve), _appTerminatingEventFunctions(reserve), _appLowMemoryEventFunctions(reserve),
_appWillEnterBackgroundEventFunctions(reserve), _appDidEnterBackgroundEventFunctions(reserve), _appWillEnterForegroundEventFunctions(reserve),
_appDidEnterForegroundEventFunctions(reserve), _localeChangedEventFunctions(reserve), _displayEventFunctions(reserve), _windowEventFunctions(reserve), _keyboardEventFunctions(reserve),
_keymapChangedEventFunctions(reserve), _textEditingEventFunctions(reserve), _textEditingExtendedEventFunctions(reserve), _textInputEventFunctions(reserve),
_mouseMotionEventFunctions(reserve), _mouseButtonEventFunctions(reserve), _mouseWheelEventFunctions(reserve), _joyAxisEventFunctions(reserve), _joyBallEventFunctions(reserve),
_joyHatEventFunctions(reserve), _joyButtonEventFunctions(reserve), _joyDeviceEventFunctions(reserve), _joyBatteryEventFunctions(reserve), _controllerAxisEventFunctions(reserve),
_controllerButtonEventFunctions(reserve), _controllerDeviceEventFunctions(reserve), _controllerTouchpadEventFunctions(reserve), _controllerSensorEventFunctions(reserve),
_audioDeviceEventFunctions(reserve), _touchFingerEventFunctions(reserve), _multiGestureEventFunctions(reserve), _dollarGestureEventFunctions(reserve), _clipboardEventFunctions(reserve),
_dropEventFunctions(reserve), _sensorEventFunctions(reserve), _OSEventFunctions(reserve), _userEventFunctions(reserve), _renderTargetsResetEventFunctions(reserve),
_renderDeviceResetEventFunctions(reserve)
{
}

EventHandlerInternal::~EventHandlerInternal()
{
}

void EventHandlerInternal::HandleEvents()
{
	SDL_Event event{};

	while (SDL_PollEvent(&event) == 1)
	{
		HandleEvent(event);
	}
}

void EventHandlerInternal::HandleEvent(SDL_Event& event)
{
	auto& type = event.type;

	switch (type)
	{
	case SDL_FIRSTEVENT:
		break;
	case SDL_QUIT:
		HandleEvent(SDLModuleQuitEvent(event.quit));
		break;
	case SDL_APP_TERMINATING:
		HandleEvent(SDLModuleAppTerminatingEvent(event.common));
		break;
	case SDL_APP_LOWMEMORY:
		HandleEvent(SDLModuleAppLowMemoryEvent(event.common));
		break;
	case SDL_APP_WILLENTERBACKGROUND:
		HandleEvent(SDLModuleAppWillEnterBackgroundEvent(event.common));
		break;
	case SDL_APP_DIDENTERBACKGROUND:
		HandleEvent(SDLModuleAppDidEnterBackgroundEvent(event.common));
		break;
	case SDL_APP_WILLENTERFOREGROUND:
		HandleEvent(SDLModuleAppWillEnterForegroundEvent(event.common));
		break;
	case SDL_APP_DIDENTERFOREGROUND:
		HandleEvent(SDLModuleAppDidEnterForegroundEvent(event.common));
		break;
	case SDL_LOCALECHANGED:
		HandleEvent(SDLModuleLocaleChangeEvent(event.common));
		break;
	case SDL_DISPLAYEVENT:
		HandleEvent(event.display);
		break;
	case SDL_WINDOWEVENT:
		HandleEvent(event.window);
		break;
	case SDL_KEYDOWN:
	case SDL_KEYUP:
		HandleEvent(event.key);
		break;
	case SDL_TEXTEDITING:
		HandleEvent(event.edit);
		break;
	case SDL_TEXTINPUT:
		HandleEvent(event.text);
		break;
	case SDL_KEYMAPCHANGED:
		HandleEvent(SDLModuleKeymapChanged(event.common));
		break;
	case SDL_TEXTEDITING_EXT:
		HandleEvent(event.editExt);
		break;
	case SDL_MOUSEMOTION:
		HandleEvent(event.motion);
		break;
	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP:
		HandleEvent(event.button);
		break;
	case SDL_MOUSEWHEEL:
		HandleEvent(event.wheel);
		break;
	case SDL_JOYAXISMOTION:
		HandleEvent(event.jaxis);
		break;
	case SDL_JOYBALLMOTION:
		HandleEvent(event.jball);
		break;
	case SDL_JOYHATMOTION:
		HandleEvent(event.jhat);
		break;
	case SDL_JOYBUTTONDOWN:
	case SDL_JOYBUTTONUP:
		HandleEvent(event.jbutton);
		break;
	case SDL_JOYDEVICEADDED:
	case SDL_JOYDEVICEREMOVED:
		HandleEvent(event.jdevice);
		break;
	case SDL_JOYBATTERYUPDATED:
		HandleEvent(event.jbattery);
		break;
	case SDL_CONTROLLERAXISMOTION:
		HandleEvent(event.caxis);
		break;
	case SDL_CONTROLLERBUTTONDOWN:
	case SDL_CONTROLLERBUTTONUP:
		HandleEvent(event.cbutton);
		break;
	case SDL_CONTROLLERDEVICEADDED:
	case SDL_CONTROLLERDEVICEREMOVED:
	case SDL_CONTROLLERDEVICEREMAPPED:
		HandleEvent(event.cdevice);
		break;
	case SDL_CONTROLLERTOUCHPADDOWN:
	case SDL_CONTROLLERTOUCHPADMOTION:
	case SDL_CONTROLLERTOUCHPADUP:
		HandleEvent(event.ctouchpad);
		break;
	case SDL_CONTROLLERSENSORUPDATE:
		HandleEvent(event.csensor);
		break;
	case SDL_FINGERDOWN:
	case SDL_FINGERUP:
	case SDL_FINGERMOTION:
		HandleEvent(event.tfinger);
		break;
	case SDL_DOLLARGESTURE:
	case SDL_DOLLARRECORD:
		HandleEvent(event.dgesture);
		break;
	case SDL_MULTIGESTURE:
		HandleEvent(event.mgesture);
		break;
	case SDL_CLIPBOARDUPDATE:
		HandleEvent(SDLModuleClipboardEvent(event.common));
		break;
	case SDL_DROPFILE:
	case SDL_DROPTEXT:
	case SDL_DROPBEGIN:
	case SDL_DROPCOMPLETE:
		HandleEvent(event.drop);
		break;
	case SDL_AUDIODEVICEADDED:
	case SDL_AUDIODEVICEREMOVED:
		HandleEvent(event.adevice);
		break;
	case SDL_SENSORUPDATE:
		HandleEvent(event.sensor);
		break;
	case SDL_RENDER_TARGETS_RESET:
		HandleEvent(SDLModuleRenderTargetsResetEvent(event.common));
		break;
	case SDL_RENDER_DEVICE_RESET:
		HandleEvent(SDLModuleRenderDeviceResetEvent(event.common));
		break;
	case SDL_POLLSENTINEL:
		break;
	case SDL_USEREVENT:
		HandleEvent(event.user);
		break;
	case SDL_LASTEVENT:
		break;
	default:
		break;
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleQuitEvent event)
{
	auto size = _quitEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _quitEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleAppTerminatingEvent event)
{
	auto size = _appTerminatingEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _appTerminatingEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleAppLowMemoryEvent event)
{
	auto size = _appLowMemoryEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _appLowMemoryEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleAppWillEnterBackgroundEvent event)
{
	auto size = _appWillEnterBackgroundEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _appWillEnterBackgroundEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleAppDidEnterBackgroundEvent event)
{
	auto size = _appDidEnterBackgroundEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _appDidEnterBackgroundEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleAppWillEnterForegroundEvent event)
{
	auto size = _appWillEnterForegroundEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _appWillEnterForegroundEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleAppDidEnterForegroundEvent event)
{
	auto size = _appDidEnterForegroundEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _appDidEnterForegroundEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleLocaleChangeEvent event)
{
	auto size = _localeChangedEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _localeChangedEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleDisplayEvent event)
{
	auto size = _displayEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _displayEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleWindowEvent event)
{
	auto size = _windowEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _windowEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleKeyboardEvent event)
{
	auto size = _keyboardEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _keyboardEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleKeymapChanged event)
{
	auto size = _keymapChangedEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _keymapChangedEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleTextEditingEvent event)
{
	auto size = _textEditingEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _textEditingEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleTextEditingExtendedEvent event)
{
	auto size = _textEditingExtendedEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _textEditingExtendedEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleTextInputEvent event)
{
	auto size = _textInputEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _textInputEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleMouseMotionEvent event)
{
	auto size = _mouseMotionEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _mouseMotionEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleMouseButtonEvent event)
{
	auto size = _mouseButtonEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _mouseButtonEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleMouseWheelEvent event)
{
	auto size = _mouseWheelEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _mouseWheelEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleJoyAxisEvent event)
{
	auto size = _joyAxisEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _joyAxisEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleJoyBallEvent event)
{
	auto size = _joyBallEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _joyBallEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleJoyHatEvent event)
{
	auto size = _joyHatEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _joyHatEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleJoyButtonEvent event)
{
	auto size = _joyButtonEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _joyButtonEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleJoyDeviceEvent event)
{
	auto size = _joyDeviceEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _joyDeviceEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleJoyBatteryEvent event)
{
	auto size = _joyBatteryEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _joyBatteryEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleControllerAxisEvent event)
{
	auto size = _controllerAxisEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _controllerAxisEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleControllerButtonEvent event)
{
	auto size = _controllerButtonEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _controllerButtonEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleControllerDeviceEvent event)
{
	auto size = _controllerDeviceEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _controllerDeviceEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleControllerTouchpadEvent event)
{
	auto size = _controllerTouchpadEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _controllerTouchpadEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleControllerSensorEvent event)
{
	auto size = _controllerSensorEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _controllerSensorEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleAudioDeviceEvent event)
{
	auto size = _audioDeviceEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _audioDeviceEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleTouchFingerEvent event)
{
	auto size = _touchFingerEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _touchFingerEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleMultiGestureEvent event)
{
	auto size = _multiGestureEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _multiGestureEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleDollarGestureEvent event)
{
	auto size = _dollarGestureEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _dollarGestureEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleClipboardEvent event)
{
	auto size = _clipboardEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _clipboardEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleDropEvent event)
{
	auto size = _dropEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _dropEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleSensorEvent event)
{
	auto size = _sensorEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _sensorEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleOSEvent event)
{
	auto size = _OSEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _OSEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleUserEvent event)
{
	auto size = _userEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _userEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleRenderTargetsResetEvent event)
{
	auto size = _renderTargetsResetEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _renderTargetsResetEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleRenderDeviceResetEvent event)
{
	auto size = _renderDeviceResetEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _renderDeviceResetEventFunctions.GetObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}
