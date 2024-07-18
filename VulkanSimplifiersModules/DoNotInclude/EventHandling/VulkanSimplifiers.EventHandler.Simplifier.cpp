module VulkanSimplifiers.EventHandler.Simplifier;

EventHandlerSimplifier::EventHandlerSimplifier(EventHandlerInternal& ref) : _internal(ref)
{
}

EventHandlerSimplifier::~EventHandlerSimplifier()
{
}

void EventHandlerSimplifier::HandleEvents() const
{
	_internal.HandleEvents();
}

IDObject<std::pair<QuitEventFunction, void*>> EventHandlerSimplifier::RegisterQuitEventCallback(QuitEventFunction function, void* data, size_t add)
{
	return _internal.RegisterQuitEventCallback(function, data, add);
}

IDObject<std::pair<AppTerminatingEventFunction, void*>> EventHandlerSimplifier::RegisterAppTerminatingEventCallback(AppTerminatingEventFunction function, void* data, size_t add)
{
	return _internal.RegisterAppTerminatingEventCallback(function, data, add);
}

IDObject<std::pair<AppLowMemoryEventFunction, void*>> EventHandlerSimplifier::RegisterAppLowMemoryWarningEventCallback(AppLowMemoryEventFunction function, void* data, size_t add)
{
	return _internal.RegisterAppLowMemoryWarningEventCallback(function, data, add);
}

IDObject<std::pair<AppWillEnterBackgroundEventFunction, void*>> EventHandlerSimplifier::RegisterAppWillEnterBackgroundWarningEventCallback(AppWillEnterBackgroundEventFunction function, void* data, size_t add)
{
	return _internal.RegisterAppWillEnterBackgroundWarningEventCallback(function, data, add);
}

IDObject<std::pair<AppDidEnterBackgroundEventFunction, void*>> EventHandlerSimplifier::RegisterAppDidEnterBackgroundEventCallback(AppDidEnterBackgroundEventFunction function, void* data, size_t add)
{
	return _internal.RegisterAppDidEnterBackgroundEventCallback(function, data, add);
}

IDObject<std::pair<AppWillEnterForegroundEventFunction, void*>> EventHandlerSimplifier::RegisterAppWillEnterForegroundWarningEventCallback(AppWillEnterForegroundEventFunction function, void* data, size_t add)
{
	return _internal.RegisterAppWillEnterForegroundWarningEventCallback(function, data, add);
}

IDObject<std::pair<AppDidEnterForegroundEventFunction, void*>> EventHandlerSimplifier::RegisterAppDidEnterForegroundEventCallback(AppDidEnterForegroundEventFunction function, void* data, size_t add)
{
	return _internal.RegisterAppDidEnterForegroundEventCallback(function, data, add);
}

IDObject<std::pair<LocaleChangedEventFunction, void*>> EventHandlerSimplifier::RegisterLocaleChangingEventCallback(LocaleChangedEventFunction function, void* data, size_t add)
{
	return _internal.RegisterLocaleChangingEventCallback(function, data, add);
}

IDObject<std::pair<DisplayEventFunction, void*>> EventHandlerSimplifier::RegisterDisplayEventCallback(DisplayEventFunction function, void* data, size_t add)
{
	return _internal.RegisterDisplayEventCallback(function, data, add);
}

IDObject<std::pair<WindowEventFunction, void*>> EventHandlerSimplifier::RegisterWindowEventCallback(WindowEventFunction function, void* data, size_t add)
{
	return _internal.RegisterWindowEventCallback(function, data, add);
}

IDObject<std::pair<KeyboardEventFunction, void*>> EventHandlerSimplifier::RegisterKeyboardEventCallback(KeyboardEventFunction function, void* data, size_t add)
{
	return _internal.RegisterKeyboardEventCallback(function, data, add);
}

IDObject<std::pair<KeymapChangeEventFunction, void*>> EventHandlerSimplifier::RegisterKeymapChangingEventCallback(KeymapChangeEventFunction function, void* data, size_t add)
{
	return _internal.RegisterKeymapChangingEventCallback(function, data, add);
}

IDObject<std::pair<TextEditingEventFunction, void*>> EventHandlerSimplifier::RegisterTextEditingEventCallback(TextEditingEventFunction function, void* data, size_t add)
{
	return _internal.RegisterTextEditingEventCallback(function, data, add);
}

IDObject<std::pair<TextEditingExtendedEventFunction, void*>> EventHandlerSimplifier::RegisterTextEditingExtendedEventCallback(TextEditingExtendedEventFunction function, void* data, size_t add)
{
	return _internal.RegisterTextEditingExtendedEventCallback(function, data, add);
}

IDObject<std::pair<TextInputEventFunction, void*>> EventHandlerSimplifier::RegisterTextInputEventCallback(TextInputEventFunction function, void* data, size_t add)
{
	return _internal.RegisterTextInputEventCallback(function, data, add);
}

IDObject<std::pair<MouseMotionEventFunction, void*>> EventHandlerSimplifier::RegisterMouseMotionEventCallback(MouseMotionEventFunction function, void* data, size_t add)
{
	return _internal.RegisterMouseMotionEventCallback(function, data, add);
}

IDObject<std::pair<MouseButtonEventFunction, void*>> EventHandlerSimplifier::RegisterMouseButtonEventCallback(MouseButtonEventFunction function, void* data, size_t add)
{
	return _internal.RegisterMouseButtonEventCallback(function, data, add);
}

IDObject<std::pair<MouseWheelEventFunction, void*>> EventHandlerSimplifier::RegisterMouseWheelEventCallback(MouseWheelEventFunction function, void* data, size_t add)
{
	return _internal.RegisterMouseWheelEventCallback(function, data, add);
}

IDObject<std::pair<JoyAxisEventFunction, void*>> EventHandlerSimplifier::RegisterJoystickAxisEventCallback(JoyAxisEventFunction function, void* data, size_t add)
{
	return _internal.RegisterJoystickAxisEventCallback(function, data, add);
}

IDObject<std::pair<JoyBallEventFunction, void*>> EventHandlerSimplifier::RegisterJoystickBallEventCallback(JoyBallEventFunction function, void* data, size_t add)
{
	return _internal.RegisterJoystickBallEventCallback(function, data, add);
}

IDObject<std::pair<JoyHatEventFunction, void*>> EventHandlerSimplifier::RegisterJoystickHatEventCallback(JoyHatEventFunction function, void* data, size_t add)
{
	return _internal.RegisterJoystickHatEventCallback(function, data, add);
}

IDObject<std::pair<JoyButtonEventFunction, void*>> EventHandlerSimplifier::RegisterJoystickButtonEventCallback(JoyButtonEventFunction function, void* data, size_t add)
{
	return _internal.RegisterJoystickButtonEventCallback(function, data, add);
}

IDObject<std::pair<JoyDeviceEventFunction, void*>> EventHandlerSimplifier::RegisterJoystickDeviceEventCallback(JoyDeviceEventFunction function, void* data, size_t add)
{
	return _internal.RegisterJoystickDeviceEventCallback(function, data, add);
}

IDObject<std::pair<JoyBatteryEventFunction, void*>> EventHandlerSimplifier::RegisterJoystickBatteryEventCallback(JoyBatteryEventFunction function, void* data, size_t add)
{
	return _internal.RegisterJoystickBatteryEventCallback(function, data, add);
}

IDObject<std::pair<ControllerAxisEventFunction, void*>> EventHandlerSimplifier::RegisterControllerAxisEventCallback(ControllerAxisEventFunction function, void* data, size_t add)
{
	return _internal.RegisterControllerAxisEventCallback(function, data, add);
}

IDObject<std::pair<ControllerButtonEventFunction, void*>> EventHandlerSimplifier::RegisterControllerButtonEventCallback(ControllerButtonEventFunction function, void* data, size_t add)
{
	return _internal.RegisterControllerButtonEventCallback(function, data, add);
}

IDObject<std::pair<ControllerDeviceEventFunction, void*>> EventHandlerSimplifier::RegisterControllerDeviceEventCallback(ControllerDeviceEventFunction function, void* data, size_t add)
{
	return _internal.RegisterControllerDeviceEventCallback(function, data, add);
}

IDObject<std::pair<ControllerTouchpadEventFunction, void*>> EventHandlerSimplifier::RegisterControllerTouchpadEventCallback(ControllerTouchpadEventFunction function, void* data, size_t add)
{
	return _internal.RegisterControllerTouchpadEventCallback(function, data, add);
}

IDObject<std::pair<ControllerSensorEventFunction, void*>> EventHandlerSimplifier::RegisterControllerSensorEventCallback(ControllerSensorEventFunction function, void* data, size_t add)
{
	return _internal.RegisterControllerSensorEventCallback(function, data, add);
}

IDObject<std::pair<AudioDeviceEventFunction, void*>> EventHandlerSimplifier::RegisterAudioDeviceEventCallback(AudioDeviceEventFunction function, void* data, size_t add)
{
	return _internal.RegisterAudioDeviceEventCallback(function, data, add);
}

IDObject<std::pair<TouchFingerEventFunction, void*>> EventHandlerSimplifier::RegisterTouchFingerEventCallback(TouchFingerEventFunction function, void* data, size_t add)
{
	return _internal.RegisterTouchFingerEventCallback(function, data, add);
}

IDObject<std::pair<MultiGestureEventFunction, void*>> EventHandlerSimplifier::RegisterMultiGestureEventCallback(MultiGestureEventFunction function, void* data, size_t add)
{
	return _internal.RegisterMultiGestureEventCallback(function, data, add);
}

IDObject<std::pair<DollarGestureEventFunction, void*>> EventHandlerSimplifier::RegisterDollarGestureEventCallback(DollarGestureEventFunction function, void* data, size_t add)
{
	return _internal.RegisterDollarGestureEventCallback(function, data, add);
}

IDObject<std::pair<ClipboardEventFunction, void*>> EventHandlerSimplifier::RegisterClipboardEventCallback(ClipboardEventFunction function, void* data, size_t add)
{
	return _internal.RegisterClipboardEventCallback(function, data, add);
}

IDObject<std::pair<DropEventFunction, void*>> EventHandlerSimplifier::RegisterDropEventCallback(DropEventFunction function, void* data, size_t add)
{
	return _internal.RegisterDropEventCallback(function, data, add);
}

IDObject<std::pair<SensorEventFunction, void*>> EventHandlerSimplifier::RegisterSensorEventCallback(SensorEventFunction function, void* data, size_t add)
{
	return _internal.RegisterSensorEventCallback(function, data, add);
}

IDObject<std::pair<OSEventFunction, void*>> EventHandlerSimplifier::RegisterOSEventCallback(OSEventFunction function, void* data, size_t add)
{
	return _internal.RegisterOSEventCallback(function, data, add);
}

IDObject<std::pair<UserEventFunction, void*>> EventHandlerSimplifier::RegisterUserEventCallback(UserEventFunction function, void* data, size_t add)
{
	return _internal.RegisterUserEventCallback(function, data, add);
}

IDObject<std::pair<RenderTargetsResetEventFunction, void*>> EventHandlerSimplifier::RegisterRenderTargetsResetEventCallback(RenderTargetsResetEventFunction function, void* data, size_t add)
{
	return _internal.RegisterRenderTargetsResetEventCallback(function, data, add);
}

IDObject<std::pair<RenderDeviceResetEventFunction, void*>> EventHandlerSimplifier::RegisterRenderDeviceResetEventCallback(RenderDeviceResetEventFunction function, void* data, size_t add)
{
	return _internal.RegisterRenderDeviceResetEventCallback(function, data, add);
}
