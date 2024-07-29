module VulkanSimplifiers.EventHandling;

EventHandlingSimplifier::EventHandlingSimplifier(EventHandlingInternal& ref) : _internal(ref)
{
}

EventHandlingSimplifier::~EventHandlingSimplifier()
{
}

void EventHandlingSimplifier::HandleEvents() const
{
	_internal.HandleEvents();
}

IDObject<std::pair<QuitEventFunction, void*>> EventHandlingSimplifier::RegisterQuitEventCallback(QuitEventFunction function, void* data, size_t add)
{
	return _internal.RegisterQuitEventCallback(function, data, add);
}

IDObject<std::pair<AppTerminatingEventFunction, void*>> EventHandlingSimplifier::RegisterAppTerminatingEventCallback(AppTerminatingEventFunction function, void* data, size_t add)
{
	return _internal.RegisterAppTerminatingEventCallback(function, data, add);
}

IDObject<std::pair<AppLowMemoryEventFunction, void*>> EventHandlingSimplifier::RegisterAppLowMemoryWarningEventCallback(AppLowMemoryEventFunction function, void* data, size_t add)
{
	return _internal.RegisterAppLowMemoryWarningEventCallback(function, data, add);
}

IDObject<std::pair<AppWillEnterBackgroundEventFunction, void*>> EventHandlingSimplifier::RegisterAppWillEnterBackgroundWarningEventCallback(AppWillEnterBackgroundEventFunction function, void* data, size_t add)
{
	return _internal.RegisterAppWillEnterBackgroundWarningEventCallback(function, data, add);
}

IDObject<std::pair<AppDidEnterBackgroundEventFunction, void*>> EventHandlingSimplifier::RegisterAppDidEnterBackgroundEventCallback(AppDidEnterBackgroundEventFunction function, void* data, size_t add)
{
	return _internal.RegisterAppDidEnterBackgroundEventCallback(function, data, add);
}

IDObject<std::pair<AppWillEnterForegroundEventFunction, void*>> EventHandlingSimplifier::RegisterAppWillEnterForegroundWarningEventCallback(AppWillEnterForegroundEventFunction function, void* data, size_t add)
{
	return _internal.RegisterAppWillEnterForegroundWarningEventCallback(function, data, add);
}

IDObject<std::pair<AppDidEnterForegroundEventFunction, void*>> EventHandlingSimplifier::RegisterAppDidEnterForegroundEventCallback(AppDidEnterForegroundEventFunction function, void* data, size_t add)
{
	return _internal.RegisterAppDidEnterForegroundEventCallback(function, data, add);
}

IDObject<std::pair<LocaleChangedEventFunction, void*>> EventHandlingSimplifier::RegisterLocaleChangingEventCallback(LocaleChangedEventFunction function, void* data, size_t add)
{
	return _internal.RegisterLocaleChangingEventCallback(function, data, add);
}

IDObject<std::pair<DisplayEventFunction, void*>> EventHandlingSimplifier::RegisterDisplayEventCallback(DisplayEventFunction function, void* data, size_t add)
{
	return _internal.RegisterDisplayEventCallback(function, data, add);
}

IDObject<std::pair<WindowEventFunction, void*>> EventHandlingSimplifier::RegisterWindowEventCallback(WindowEventFunction function, void* data, size_t add)
{
	return _internal.RegisterWindowEventCallback(function, data, add);
}

IDObject<std::pair<KeyboardEventFunction, void*>> EventHandlingSimplifier::RegisterKeyboardEventCallback(KeyboardEventFunction function, void* data, size_t add)
{
	return _internal.RegisterKeyboardEventCallback(function, data, add);
}

IDObject<std::pair<KeymapChangeEventFunction, void*>> EventHandlingSimplifier::RegisterKeymapChangingEventCallback(KeymapChangeEventFunction function, void* data, size_t add)
{
	return _internal.RegisterKeymapChangingEventCallback(function, data, add);
}

IDObject<std::pair<TextEditingEventFunction, void*>> EventHandlingSimplifier::RegisterTextEditingEventCallback(TextEditingEventFunction function, void* data, size_t add)
{
	return _internal.RegisterTextEditingEventCallback(function, data, add);
}

IDObject<std::pair<TextEditingExtendedEventFunction, void*>> EventHandlingSimplifier::RegisterTextEditingExtendedEventCallback(TextEditingExtendedEventFunction function, void* data, size_t add)
{
	return _internal.RegisterTextEditingExtendedEventCallback(function, data, add);
}

IDObject<std::pair<TextInputEventFunction, void*>> EventHandlingSimplifier::RegisterTextInputEventCallback(TextInputEventFunction function, void* data, size_t add)
{
	return _internal.RegisterTextInputEventCallback(function, data, add);
}

IDObject<std::pair<MouseMotionEventFunction, void*>> EventHandlingSimplifier::RegisterMouseMotionEventCallback(MouseMotionEventFunction function, void* data, size_t add)
{
	return _internal.RegisterMouseMotionEventCallback(function, data, add);
}

IDObject<std::pair<MouseButtonEventFunction, void*>> EventHandlingSimplifier::RegisterMouseButtonEventCallback(MouseButtonEventFunction function, void* data, size_t add)
{
	return _internal.RegisterMouseButtonEventCallback(function, data, add);
}

IDObject<std::pair<MouseWheelEventFunction, void*>> EventHandlingSimplifier::RegisterMouseWheelEventCallback(MouseWheelEventFunction function, void* data, size_t add)
{
	return _internal.RegisterMouseWheelEventCallback(function, data, add);
}

IDObject<std::pair<JoyAxisEventFunction, void*>> EventHandlingSimplifier::RegisterJoystickAxisEventCallback(JoyAxisEventFunction function, void* data, size_t add)
{
	return _internal.RegisterJoystickAxisEventCallback(function, data, add);
}

IDObject<std::pair<JoyBallEventFunction, void*>> EventHandlingSimplifier::RegisterJoystickBallEventCallback(JoyBallEventFunction function, void* data, size_t add)
{
	return _internal.RegisterJoystickBallEventCallback(function, data, add);
}

IDObject<std::pair<JoyHatEventFunction, void*>> EventHandlingSimplifier::RegisterJoystickHatEventCallback(JoyHatEventFunction function, void* data, size_t add)
{
	return _internal.RegisterJoystickHatEventCallback(function, data, add);
}

IDObject<std::pair<JoyButtonEventFunction, void*>> EventHandlingSimplifier::RegisterJoystickButtonEventCallback(JoyButtonEventFunction function, void* data, size_t add)
{
	return _internal.RegisterJoystickButtonEventCallback(function, data, add);
}

IDObject<std::pair<JoyDeviceEventFunction, void*>> EventHandlingSimplifier::RegisterJoystickDeviceEventCallback(JoyDeviceEventFunction function, void* data, size_t add)
{
	return _internal.RegisterJoystickDeviceEventCallback(function, data, add);
}

IDObject<std::pair<JoyBatteryEventFunction, void*>> EventHandlingSimplifier::RegisterJoystickBatteryEventCallback(JoyBatteryEventFunction function, void* data, size_t add)
{
	return _internal.RegisterJoystickBatteryEventCallback(function, data, add);
}

IDObject<std::pair<ControllerAxisEventFunction, void*>> EventHandlingSimplifier::RegisterControllerAxisEventCallback(ControllerAxisEventFunction function, void* data, size_t add)
{
	return _internal.RegisterControllerAxisEventCallback(function, data, add);
}

IDObject<std::pair<ControllerButtonEventFunction, void*>> EventHandlingSimplifier::RegisterControllerButtonEventCallback(ControllerButtonEventFunction function, void* data, size_t add)
{
	return _internal.RegisterControllerButtonEventCallback(function, data, add);
}

IDObject<std::pair<ControllerDeviceEventFunction, void*>> EventHandlingSimplifier::RegisterControllerDeviceEventCallback(ControllerDeviceEventFunction function, void* data, size_t add)
{
	return _internal.RegisterControllerDeviceEventCallback(function, data, add);
}

IDObject<std::pair<ControllerTouchpadEventFunction, void*>> EventHandlingSimplifier::RegisterControllerTouchpadEventCallback(ControllerTouchpadEventFunction function, void* data, size_t add)
{
	return _internal.RegisterControllerTouchpadEventCallback(function, data, add);
}

IDObject<std::pair<ControllerSensorEventFunction, void*>> EventHandlingSimplifier::RegisterControllerSensorEventCallback(ControllerSensorEventFunction function, void* data, size_t add)
{
	return _internal.RegisterControllerSensorEventCallback(function, data, add);
}

IDObject<std::pair<AudioDeviceEventFunction, void*>> EventHandlingSimplifier::RegisterAudioDeviceEventCallback(AudioDeviceEventFunction function, void* data, size_t add)
{
	return _internal.RegisterAudioDeviceEventCallback(function, data, add);
}

IDObject<std::pair<TouchFingerEventFunction, void*>> EventHandlingSimplifier::RegisterTouchFingerEventCallback(TouchFingerEventFunction function, void* data, size_t add)
{
	return _internal.RegisterTouchFingerEventCallback(function, data, add);
}

IDObject<std::pair<MultiGestureEventFunction, void*>> EventHandlingSimplifier::RegisterMultiGestureEventCallback(MultiGestureEventFunction function, void* data, size_t add)
{
	return _internal.RegisterMultiGestureEventCallback(function, data, add);
}

IDObject<std::pair<DollarGestureEventFunction, void*>> EventHandlingSimplifier::RegisterDollarGestureEventCallback(DollarGestureEventFunction function, void* data, size_t add)
{
	return _internal.RegisterDollarGestureEventCallback(function, data, add);
}

IDObject<std::pair<ClipboardEventFunction, void*>> EventHandlingSimplifier::RegisterClipboardEventCallback(ClipboardEventFunction function, void* data, size_t add)
{
	return _internal.RegisterClipboardEventCallback(function, data, add);
}

IDObject<std::pair<DropEventFunction, void*>> EventHandlingSimplifier::RegisterDropEventCallback(DropEventFunction function, void* data, size_t add)
{
	return _internal.RegisterDropEventCallback(function, data, add);
}

IDObject<std::pair<SensorEventFunction, void*>> EventHandlingSimplifier::RegisterSensorEventCallback(SensorEventFunction function, void* data, size_t add)
{
	return _internal.RegisterSensorEventCallback(function, data, add);
}

IDObject<std::pair<OSEventFunction, void*>> EventHandlingSimplifier::RegisterOSEventCallback(OSEventFunction function, void* data, size_t add)
{
	return _internal.RegisterOSEventCallback(function, data, add);
}

IDObject<std::pair<UserEventFunction, void*>> EventHandlingSimplifier::RegisterUserEventCallback(UserEventFunction function, void* data, size_t add)
{
	return _internal.RegisterUserEventCallback(function, data, add);
}

IDObject<std::pair<RenderTargetsResetEventFunction, void*>> EventHandlingSimplifier::RegisterRenderTargetsResetEventCallback(RenderTargetsResetEventFunction function, void* data, size_t add)
{
	return _internal.RegisterRenderTargetsResetEventCallback(function, data, add);
}

IDObject<std::pair<RenderDeviceResetEventFunction, void*>> EventHandlingSimplifier::RegisterRenderDeviceResetEventCallback(RenderDeviceResetEventFunction function, void* data, size_t add)
{
	return _internal.RegisterRenderDeviceResetEventCallback(function, data, add);
}
