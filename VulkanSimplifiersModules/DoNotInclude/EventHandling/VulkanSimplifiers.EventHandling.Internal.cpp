module;

#include <SDL2/SDL_events.h>

module VulkanSimplifiers.EventHandling.Internal;

EventHandlingInternal::EventHandlingInternal(const EventHandlerInitData& initData) : _quitEventFunctions(initData.quitEventFunctionListInitialCapacity),
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

EventHandlingInternal::~EventHandlingInternal()
{
}

void EventHandlingInternal::HandleEvents() const
{
	SDL_Event event{};

	while (SDL_PollEvent(&event) == 1)
	{
		HandleEvent(event);
	}
}

IDObject<std::pair<QuitEventFunction, void*>> EventHandlingInternal::RegisterQuitEventCallback(QuitEventFunction function, void* data, size_t add)
{
	return _quitEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<AppTerminatingEventFunction, void*>> EventHandlingInternal::RegisterAppTerminatingEventCallback(AppTerminatingEventFunction function, void* data, size_t add)
{
	return _appTerminatingEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<AppLowMemoryEventFunction, void*>> EventHandlingInternal::RegisterAppLowMemoryWarningEventCallback(AppLowMemoryEventFunction function, void* data, size_t add)
{
	return _appLowMemoryEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<AppWillEnterBackgroundEventFunction, void*>> EventHandlingInternal::RegisterAppWillEnterBackgroundWarningEventCallback(AppWillEnterBackgroundEventFunction function, void* data, size_t add)
{
	return _appWillEnterBackgroundEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<AppDidEnterBackgroundEventFunction, void*>> EventHandlingInternal::RegisterAppDidEnterBackgroundEventCallback(AppDidEnterBackgroundEventFunction function, void* data, size_t add)
{
	return _appDidEnterBackgroundEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<AppWillEnterForegroundEventFunction, void*>> EventHandlingInternal::RegisterAppWillEnterForegroundWarningEventCallback(AppWillEnterForegroundEventFunction function, void* data, size_t add)
{
	return _appWillEnterForegroundEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<AppDidEnterForegroundEventFunction, void*>> EventHandlingInternal::RegisterAppDidEnterForegroundEventCallback(AppDidEnterForegroundEventFunction function, void* data, size_t add)
{
	return _appDidEnterForegroundEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<LocaleChangedEventFunction, void*>> EventHandlingInternal::RegisterLocaleChangingEventCallback(LocaleChangedEventFunction function, void* data, size_t add)
{
	return _localeChangedEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<DisplayEventFunction, void*>> EventHandlingInternal::RegisterDisplayEventCallback(DisplayEventFunction function, void* data, size_t add)
{
	return _displayEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<WindowEventFunction, void*>> EventHandlingInternal::RegisterWindowEventCallback(WindowEventFunction function, void* data, size_t add)
{
	return _windowEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<KeyboardEventFunction, void*>> EventHandlingInternal::RegisterKeyboardEventCallback(KeyboardEventFunction function, void* data, size_t add)
{
	return _keyboardEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<KeymapChangeEventFunction, void*>> EventHandlingInternal::RegisterKeymapChangingEventCallback(KeymapChangeEventFunction function, void* data, size_t add)
{
	return _keymapChangedEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<TextEditingEventFunction, void*>> EventHandlingInternal::RegisterTextEditingEventCallback(TextEditingEventFunction function, void* data, size_t add)
{
	return _textEditingEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<TextEditingExtendedEventFunction, void*>> EventHandlingInternal::RegisterTextEditingExtendedEventCallback(TextEditingExtendedEventFunction function, void* data, size_t add)
{
	return _textEditingExtendedEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<TextInputEventFunction, void*>> EventHandlingInternal::RegisterTextInputEventCallback(TextInputEventFunction function, void* data, size_t add)
{
	return _textInputEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<MouseMotionEventFunction, void*>> EventHandlingInternal::RegisterMouseMotionEventCallback(MouseMotionEventFunction function, void* data, size_t add)
{
	return _mouseMotionEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<MouseButtonEventFunction, void*>> EventHandlingInternal::RegisterMouseButtonEventCallback(MouseButtonEventFunction function, void* data, size_t add)
{
	return _mouseButtonEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<MouseWheelEventFunction, void*>> EventHandlingInternal::RegisterMouseWheelEventCallback(MouseWheelEventFunction function, void* data, size_t add)
{
	return _mouseWheelEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<JoyAxisEventFunction, void*>> EventHandlingInternal::RegisterJoystickAxisEventCallback(JoyAxisEventFunction function, void* data, size_t add)
{
	return _joyAxisEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<JoyBallEventFunction, void*>> EventHandlingInternal::RegisterJoystickBallEventCallback(JoyBallEventFunction function, void* data, size_t add)
{
	return _joyBallEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<JoyHatEventFunction, void*>> EventHandlingInternal::RegisterJoystickHatEventCallback(JoyHatEventFunction function, void* data, size_t add)
{
	return _joyHatEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<JoyButtonEventFunction, void*>> EventHandlingInternal::RegisterJoystickButtonEventCallback(JoyButtonEventFunction function, void* data, size_t add)
{
	return _joyButtonEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<JoyDeviceEventFunction, void*>> EventHandlingInternal::RegisterJoystickDeviceEventCallback(JoyDeviceEventFunction function, void* data, size_t add)
{
	return _joyDeviceEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<JoyBatteryEventFunction, void*>> EventHandlingInternal::RegisterJoystickBatteryEventCallback(JoyBatteryEventFunction function, void* data, size_t add)
{
	return _joyBatteryEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<ControllerAxisEventFunction, void*>> EventHandlingInternal::RegisterControllerAxisEventCallback(ControllerAxisEventFunction function, void* data, size_t add)
{
	return _controllerAxisEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<ControllerButtonEventFunction, void*>> EventHandlingInternal::RegisterControllerButtonEventCallback(ControllerButtonEventFunction function, void* data, size_t add)
{
	return _controllerButtonEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<ControllerDeviceEventFunction, void*>> EventHandlingInternal::RegisterControllerDeviceEventCallback(ControllerDeviceEventFunction function, void* data, size_t add)
{
	return _controllerDeviceEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<ControllerTouchpadEventFunction, void*>> EventHandlingInternal::RegisterControllerTouchpadEventCallback(ControllerTouchpadEventFunction function, void* data, size_t add)
{
	return _controllerTouchpadEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<ControllerSensorEventFunction, void*>> EventHandlingInternal::RegisterControllerSensorEventCallback(ControllerSensorEventFunction function, void* data, size_t add)
{
	return _controllerSensorEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<AudioDeviceEventFunction, void*>> EventHandlingInternal::RegisterAudioDeviceEventCallback(AudioDeviceEventFunction function, void* data, size_t add)
{
	return _audioDeviceEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<TouchFingerEventFunction, void*>> EventHandlingInternal::RegisterTouchFingerEventCallback(TouchFingerEventFunction function, void* data, size_t add)
{
	return _touchFingerEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<MultiGestureEventFunction, void*>> EventHandlingInternal::RegisterMultiGestureEventCallback(MultiGestureEventFunction function, void* data, size_t add)
{
	return _multiGestureEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<DollarGestureEventFunction, void*>> EventHandlingInternal::RegisterDollarGestureEventCallback(DollarGestureEventFunction function, void* data, size_t add)
{
	return _dollarGestureEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<ClipboardEventFunction, void*>> EventHandlingInternal::RegisterClipboardEventCallback(ClipboardEventFunction function, void* data, size_t add)
{
	return _clipboardEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<DropEventFunction, void*>> EventHandlingInternal::RegisterDropEventCallback(DropEventFunction function, void* data, size_t add)
{
	return _dropEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<SensorEventFunction, void*>> EventHandlingInternal::RegisterSensorEventCallback(SensorEventFunction function, void* data, size_t add)
{
	return _sensorEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<OSEventFunction, void*>> EventHandlingInternal::RegisterOSEventCallback(OSEventFunction function, void* data, size_t add)
{
	return _OSEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<UserEventFunction, void*>> EventHandlingInternal::RegisterUserEventCallback(UserEventFunction function, void* data, size_t add)
{
	return _userEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<RenderTargetsResetEventFunction, void*>> EventHandlingInternal::RegisterRenderTargetsResetEventCallback(RenderTargetsResetEventFunction function, void* data, size_t add)
{
	return _renderTargetsResetEventFunctions.AddObject(std::pair(function, data), add);
}

IDObject<std::pair<RenderDeviceResetEventFunction, void*>> EventHandlingInternal::RegisterRenderDeviceResetEventCallback(RenderDeviceResetEventFunction function, void* data, size_t add)
{
	return _renderDeviceResetEventFunctions.AddObject(std::pair(function, data), add);
}

void EventHandlingInternal::HandleEvent(SDL_Event& event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleQuitEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleAppTerminatingEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleAppLowMemoryEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleAppWillEnterBackgroundEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleAppDidEnterBackgroundEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleAppWillEnterForegroundEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleAppDidEnterForegroundEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleLocaleChangeEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleDisplayEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleWindowEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleKeyboardEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleKeymapChanged event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleTextEditingEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleTextEditingExtendedEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleTextInputEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleMouseMotionEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleMouseButtonEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleMouseWheelEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleJoyAxisEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleJoyBallEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleJoyHatEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleJoyButtonEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleJoyDeviceEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleJoyBatteryEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleControllerAxisEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleControllerButtonEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleControllerDeviceEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleControllerTouchpadEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleControllerSensorEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleAudioDeviceEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleTouchFingerEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleMultiGestureEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleDollarGestureEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleClipboardEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleDropEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleSensorEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleOSEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleUserEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleRenderTargetsResetEvent event) const
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

void EventHandlingInternal::HandleEvent(SDLModuleRenderDeviceResetEvent event) const
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
