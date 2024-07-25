module;

#include <SDL2/SDL_events.h>

module VulkanSimplifiers.EventHandler.Internal;

EventHandlerInternal::EventHandlerInternal(const EventHandlerInitData& initData) : _quitEventFunctions(initData.quitEventFunctionListInitialCapacity),
_appTerminatingEventFunctions(initData.appTerminatingEventFunctionListInitialCapacity), _appLowMemoryEventFunctions(initData.appLowMemoryEventFunctionListInitialCapacity),
_appWillEnterBackgroundEventFunctions(initData.appWillEnterBackgroundEventFunctionListInitialCapacity),
_appDidEnterBackgroundEventFunctions(initData.appDidEnterBackgroundEventFunctionListInitialCapacity),
_appWillEnterForegroundEventFunctions(initData.appWillEnterForegroundEventFunctionListInitialCapacity),
_appDidEnterForegroundEventFunctions(initData.appDidEnterForegroundEventFunctionListInitialCapacity),
_localeChangedEventFunctions(initData.localeChangedEventFunctionListInitialCapacity), _displayEventFunctions(initData.displayEventFunctionListInitialCapacity),
_windowEventFunctions(initData.windowEventFunctionListInitialCapacity), _keyboardEventFunctions(initData.keyboardEventFunctionListInitialCapacity),
_keymapChangedEventFunctions(initData.keymapChangeEventFunctionListInitialCapacity), _textEditingEventFunctions(initData.textEditingEventFunctionListInitialCapacity),
_textEditingExtendedEventFunctions(initData.textEditingExtendedEventFunctionListInitialCapacity), _textInputEventFunctions(initData.textInputEventFunctionListInitialCapacity),
_mouseMotionEventFunctions(initData.mouseMotionEventFunctionListInitialCapacity), _mouseButtonEventFunctions(initData.mouseButtonEventFunctionListInitialCapacity),
_mouseWheelEventFunctions(initData.mouseWheelEventFunctionListInitialCapacity), _joyAxisEventFunctions(initData.joyAxisEventFunctionListInitialCapacity),
_joyBallEventFunctions(initData.joyBallEventFunctionListInitialCapacity), _joyHatEventFunctions(initData.joyHatEventFunctionListInitialCapacity),
_joyButtonEventFunctions(initData.joyButtonEventFunctionListInitialCapacity), _joyDeviceEventFunctions(initData.joyDeviceEventFunctionListInitialCapacity),
_joyBatteryEventFunctions(initData.joyBatteryEventFunctionListInitialCapacity), _controllerAxisEventFunctions(initData.controllerAxisEventFunctionListInitialCapacity),
_controllerButtonEventFunctions(initData.controllerButtonEventFunctionListInitialCapacity), _controllerDeviceEventFunctions(initData.controllerDeviceEventFunctionListInitialCapacity),
_controllerTouchpadEventFunctions(initData.controllerTouchpadEventFunctionListInitialCapacity), _controllerSensorEventFunctions(initData.controllerSensorEventFunctionListInitialCapacity),
_audioDeviceEventFunctions(initData.audioDeviceEventFunctionListInitialCapacity), _touchFingerEventFunctions(initData.touchFingerEventFunctionListInitialCapacity),
_multiGestureEventFunctions(initData.multiGestureEventFunctionListInitialCapacity), _dollarGestureEventFunctions(initData.dollarGestureEventFunctionListInitialCapacity),
_clipboardEventFunctions(initData.clipboardEventFunctionListInitialCapacity), _dropEventFunctions(initData.dropEventFunctionListInitialCapacity),
_sensorEventFunctions(initData.sensorEventFunctionListInitialCapacity), _OSEventFunctions(initData.OSEventFunctionListInitialCapacity),
_userEventFunctions(initData.userEventFunctionListInitialCapacity), _renderTargetsResetEventFunctions(initData.renderTargetsResetEventFunctionListInitialCapacity),
_renderDeviceResetEventFunctions(initData.renderDeviceResetEventFunctionListInitialCapacity)
{
}

EventHandlerInternal::~EventHandlerInternal()
{
}

void EventHandlerInternal::HandleEvents() const
{
	SDL_Event event{};

	while (SDL_PollEvent(&event) == 1)
	{
		HandleEvent(event);
	}
}

IDObject<std::pair<QuitEventFunction, void*>> EventHandlerInternal::RegisterQuitEventCallback(QuitEventFunction function, void* data, size_t add)
{
	return _quitEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<AppTerminatingEventFunction, void*>> EventHandlerInternal::RegisterAppTerminatingEventCallback(AppTerminatingEventFunction function, void* data, size_t add)
{
	return _appTerminatingEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<AppLowMemoryEventFunction, void*>> EventHandlerInternal::RegisterAppLowMemoryWarningEventCallback(AppLowMemoryEventFunction function, void* data, size_t add)
{
	return _appLowMemoryEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<AppWillEnterBackgroundEventFunction, void*>> EventHandlerInternal::RegisterAppWillEnterBackgroundWarningEventCallback(AppWillEnterBackgroundEventFunction function, void* data, size_t add)
{
	return _appWillEnterBackgroundEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<AppDidEnterBackgroundEventFunction, void*>> EventHandlerInternal::RegisterAppDidEnterBackgroundEventCallback(AppDidEnterBackgroundEventFunction function, void* data, size_t add)
{
	return _appDidEnterBackgroundEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<AppWillEnterForegroundEventFunction, void*>> EventHandlerInternal::RegisterAppWillEnterForegroundWarningEventCallback(AppWillEnterForegroundEventFunction function, void* data, size_t add)
{
	return _appWillEnterForegroundEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<AppDidEnterForegroundEventFunction, void*>> EventHandlerInternal::RegisterAppDidEnterForegroundEventCallback(AppDidEnterForegroundEventFunction function, void* data, size_t add)
{
	return _appDidEnterForegroundEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<LocaleChangedEventFunction, void*>> EventHandlerInternal::RegisterLocaleChangingEventCallback(LocaleChangedEventFunction function, void* data, size_t add)
{
	return _localeChangedEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<DisplayEventFunction, void*>> EventHandlerInternal::RegisterDisplayEventCallback(DisplayEventFunction function, void* data, size_t add)
{
	return _displayEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<WindowEventFunction, void*>> EventHandlerInternal::RegisterWindowEventCallback(WindowEventFunction function, void* data, size_t add)
{
	return _windowEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<KeyboardEventFunction, void*>> EventHandlerInternal::RegisterKeyboardEventCallback(KeyboardEventFunction function, void* data, size_t add)
{
	return _keyboardEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<KeymapChangeEventFunction, void*>> EventHandlerInternal::RegisterKeymapChangingEventCallback(KeymapChangeEventFunction function, void* data, size_t add)
{
	return _keymapChangedEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<TextEditingEventFunction, void*>> EventHandlerInternal::RegisterTextEditingEventCallback(TextEditingEventFunction function, void* data, size_t add)
{
	return _textEditingEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<TextEditingExtendedEventFunction, void*>> EventHandlerInternal::RegisterTextEditingExtendedEventCallback(TextEditingExtendedEventFunction function, void* data, size_t add)
{
	return _textEditingExtendedEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<TextInputEventFunction, void*>> EventHandlerInternal::RegisterTextInputEventCallback(TextInputEventFunction function, void* data, size_t add)
{
	return _textInputEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<MouseMotionEventFunction, void*>> EventHandlerInternal::RegisterMouseMotionEventCallback(MouseMotionEventFunction function, void* data, size_t add)
{
	return _mouseMotionEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<MouseButtonEventFunction, void*>> EventHandlerInternal::RegisterMouseButtonEventCallback(MouseButtonEventFunction function, void* data, size_t add)
{
	return _mouseButtonEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<MouseWheelEventFunction, void*>> EventHandlerInternal::RegisterMouseWheelEventCallback(MouseWheelEventFunction function, void* data, size_t add)
{
	return _mouseWheelEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<JoyAxisEventFunction, void*>> EventHandlerInternal::RegisterJoystickAxisEventCallback(JoyAxisEventFunction function, void* data, size_t add)
{
	return _joyAxisEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<JoyBallEventFunction, void*>> EventHandlerInternal::RegisterJoystickBallEventCallback(JoyBallEventFunction function, void* data, size_t add)
{
	return _joyBallEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<JoyHatEventFunction, void*>> EventHandlerInternal::RegisterJoystickHatEventCallback(JoyHatEventFunction function, void* data, size_t add)
{
	return _joyHatEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<JoyButtonEventFunction, void*>> EventHandlerInternal::RegisterJoystickButtonEventCallback(JoyButtonEventFunction function, void* data, size_t add)
{
	return _joyButtonEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<JoyDeviceEventFunction, void*>> EventHandlerInternal::RegisterJoystickDeviceEventCallback(JoyDeviceEventFunction function, void* data, size_t add)
{
	return _joyDeviceEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<JoyBatteryEventFunction, void*>> EventHandlerInternal::RegisterJoystickBatteryEventCallback(JoyBatteryEventFunction function, void* data, size_t add)
{
	return _joyBatteryEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<ControllerAxisEventFunction, void*>> EventHandlerInternal::RegisterControllerAxisEventCallback(ControllerAxisEventFunction function, void* data, size_t add)
{
	return _controllerAxisEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<ControllerButtonEventFunction, void*>> EventHandlerInternal::RegisterControllerButtonEventCallback(ControllerButtonEventFunction function, void* data, size_t add)
{
	return _controllerButtonEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<ControllerDeviceEventFunction, void*>> EventHandlerInternal::RegisterControllerDeviceEventCallback(ControllerDeviceEventFunction function, void* data, size_t add)
{
	return _controllerDeviceEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<ControllerTouchpadEventFunction, void*>> EventHandlerInternal::RegisterControllerTouchpadEventCallback(ControllerTouchpadEventFunction function, void* data, size_t add)
{
	return _controllerTouchpadEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<ControllerSensorEventFunction, void*>> EventHandlerInternal::RegisterControllerSensorEventCallback(ControllerSensorEventFunction function, void* data, size_t add)
{
	return _controllerSensorEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<AudioDeviceEventFunction, void*>> EventHandlerInternal::RegisterAudioDeviceEventCallback(AudioDeviceEventFunction function, void* data, size_t add)
{
	return _audioDeviceEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<TouchFingerEventFunction, void*>> EventHandlerInternal::RegisterTouchFingerEventCallback(TouchFingerEventFunction function, void* data, size_t add)
{
	return _touchFingerEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<MultiGestureEventFunction, void*>> EventHandlerInternal::RegisterMultiGestureEventCallback(MultiGestureEventFunction function, void* data, size_t add)
{
	return _multiGestureEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<DollarGestureEventFunction, void*>> EventHandlerInternal::RegisterDollarGestureEventCallback(DollarGestureEventFunction function, void* data, size_t add)
{
	return _dollarGestureEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<ClipboardEventFunction, void*>> EventHandlerInternal::RegisterClipboardEventCallback(ClipboardEventFunction function, void* data, size_t add)
{
	return _clipboardEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<DropEventFunction, void*>> EventHandlerInternal::RegisterDropEventCallback(DropEventFunction function, void* data, size_t add)
{
	return _dropEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<SensorEventFunction, void*>> EventHandlerInternal::RegisterSensorEventCallback(SensorEventFunction function, void* data, size_t add)
{
	return _sensorEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<OSEventFunction, void*>> EventHandlerInternal::RegisterOSEventCallback(OSEventFunction function, void* data, size_t add)
{
	return _OSEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<UserEventFunction, void*>> EventHandlerInternal::RegisterUserEventCallback(UserEventFunction function, void* data, size_t add)
{
	return _userEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<RenderTargetsResetEventFunction, void*>> EventHandlerInternal::RegisterRenderTargetsResetEventCallback(RenderTargetsResetEventFunction function, void* data, size_t add)
{
	return _renderTargetsResetEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<RenderDeviceResetEventFunction, void*>> EventHandlerInternal::RegisterRenderDeviceResetEventCallback(RenderDeviceResetEventFunction function, void* data, size_t add)
{
	return _renderDeviceResetEventFunctions.AddObject(std::pair(function, data), add);
}

void EventHandlerInternal::HandleEvent(SDL_Event& event) const
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

void EventHandlerInternal::HandleEvent(SDLModuleQuitEvent event) const
{
	auto size = _quitEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _quitEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleAppTerminatingEvent event) const
{
	auto size = _appTerminatingEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _appTerminatingEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleAppLowMemoryEvent event) const
{
	auto size = _appLowMemoryEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _appLowMemoryEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleAppWillEnterBackgroundEvent event) const
{
	auto size = _appWillEnterBackgroundEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _appWillEnterBackgroundEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleAppDidEnterBackgroundEvent event) const
{
	auto size = _appDidEnterBackgroundEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _appDidEnterBackgroundEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleAppWillEnterForegroundEvent event) const
{
	auto size = _appWillEnterForegroundEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _appWillEnterForegroundEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleAppDidEnterForegroundEvent event) const
{
	auto size = _appDidEnterForegroundEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _appDidEnterForegroundEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleLocaleChangeEvent event) const
{
	auto size = _localeChangedEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _localeChangedEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleDisplayEvent event) const
{
	auto size = _displayEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _displayEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleWindowEvent event) const
{
	auto size = _windowEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _windowEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleKeyboardEvent event) const
{
	auto size = _keyboardEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _keyboardEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleKeymapChanged event) const
{
	auto size = _keymapChangedEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _keymapChangedEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleTextEditingEvent event) const
{
	auto size = _textEditingEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _textEditingEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleTextEditingExtendedEvent event) const
{
	auto size = _textEditingExtendedEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _textEditingExtendedEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleTextInputEvent event) const
{
	auto size = _textInputEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _textInputEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleMouseMotionEvent event) const
{
	auto size = _mouseMotionEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _mouseMotionEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleMouseButtonEvent event) const
{
	auto size = _mouseButtonEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _mouseButtonEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleMouseWheelEvent event) const
{
	auto size = _mouseWheelEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _mouseWheelEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleJoyAxisEvent event) const
{
	auto size = _joyAxisEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _joyAxisEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleJoyBallEvent event) const
{
	auto size = _joyBallEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _joyBallEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleJoyHatEvent event) const
{
	auto size = _joyHatEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _joyHatEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleJoyButtonEvent event) const
{
	auto size = _joyButtonEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _joyButtonEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleJoyDeviceEvent event) const
{
	auto size = _joyDeviceEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _joyDeviceEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleJoyBatteryEvent event) const
{
	auto size = _joyBatteryEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _joyBatteryEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleControllerAxisEvent event) const
{
	auto size = _controllerAxisEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _controllerAxisEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleControllerButtonEvent event) const
{
	auto size = _controllerButtonEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _controllerButtonEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleControllerDeviceEvent event) const
{
	auto size = _controllerDeviceEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _controllerDeviceEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleControllerTouchpadEvent event) const
{
	auto size = _controllerTouchpadEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _controllerTouchpadEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleControllerSensorEvent event) const
{
	auto size = _controllerSensorEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _controllerSensorEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleAudioDeviceEvent event) const
{
	auto size = _audioDeviceEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _audioDeviceEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleTouchFingerEvent event) const
{
	auto size = _touchFingerEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _touchFingerEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleMultiGestureEvent event) const
{
	auto size = _multiGestureEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _multiGestureEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleDollarGestureEvent event) const
{
	auto size = _dollarGestureEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _dollarGestureEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleClipboardEvent event) const
{
	auto size = _clipboardEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _clipboardEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleDropEvent event) const
{
	auto size = _dropEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _dropEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleSensorEvent event) const
{
	auto size = _sensorEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _sensorEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleOSEvent event) const
{
	auto size = _OSEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _OSEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleUserEvent event) const
{
	auto size = _userEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _userEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleRenderTargetsResetEvent event) const
{
	auto size = _renderTargetsResetEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _renderTargetsResetEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}

void EventHandlerInternal::HandleEvent(SDLModuleRenderDeviceResetEvent event) const
{
	auto size = _renderDeviceResetEventFunctions.GetUsedSize();
	size_t current = 0;

	bool fallthrough = true;

	while (fallthrough)
	{
		if (current == size)
			break;

		auto& functiondata = _renderDeviceResetEventFunctions.GetConstObject(current++);

		fallthrough = functiondata.first(event, functiondata.second);
	}
}
