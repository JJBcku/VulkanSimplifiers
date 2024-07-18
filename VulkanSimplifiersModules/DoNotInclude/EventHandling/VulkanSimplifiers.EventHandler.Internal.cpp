module VulkanSimplifiers.EventHandler.Internal;

EventHandlerInternal::EventHandlerInternal(size_t reserve) : _quitEventFunctions(reserve), _appTerminatingEventFunctions(reserve), _appLowMemoryEventFunctions(reserve),
_appWillEnterBackgroundEventFunctions(reserve), _appDidEnterBackgroundEventFunctions(reserve), _appWillEnterForegroundEventFunctions(reserve),
_appDidEnterForegroundEventFunctions(reserve), _localeChangedEventFunctions(reserve), _displayEventFunctions(reserve), _windowEventFunctions(reserve), _keyboardEventFunctions(reserve),
_textEditingEventFunctions(reserve), _textEditingExtendedEventFunctions(reserve), _textInputEventFunctions(reserve), _mouseMotionEventFunctions(reserve),
_mouseButtonEventFunctions(reserve), _mouseWheelEventFunctions(reserve), _joyAxisEventFunctions(reserve), _joyBallEventFunctions(reserve), _joyHatEventFunctions(reserve),
_joyButtonEventFunctions(reserve), _joyDeviceEventFunctions(reserve), _joyBatteryEventFunctions(reserve), _controllerAxisEventFunctions(reserve),
_controllerButtonEventFunctions(reserve), _controllerDeviceEventFunctions(reserve), _controllerTouchpadEventFunctions(reserve), _controllerSensorEventFunctions(reserve),
_audioDeviceEventFunctions(reserve), _touchFingerEventFunctions(reserve), _multiGestureEventFunctions(reserve), _dollarGestureEventFunctions(reserve), _dropEventFunctions(reserve),
_sensorEventFunctions(reserve), _OSEventFunctions(reserve), _userEventFunctions(reserve)
{
}

EventHandlerInternal::~EventHandlerInternal()
{
}