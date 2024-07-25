module VulkanSimplifiers.EventHandler.Data;

EventHandlerInitData::EventHandlerInitData()
{
	quitEventFunctionListInitialCapacity = 0;

	appTerminatingEventFunctionListInitialCapacity = 0;
	appLowMemoryEventFunctionListInitialCapacity = 0;
	appWillEnterBackgroundEventFunctionListInitialCapacity = 0;
	appDidEnterBackgroundEventFunctionListInitialCapacity = 0;
	appWillEnterForegroundEventFunctionListInitialCapacity = 0;
	appDidEnterForegroundEventFunctionListInitialCapacity = 0;

	localeChangedEventFunctionListInitialCapacity = 0;

	displayEventFunctionListInitialCapacity = 0;
	windowEventFunctionListInitialCapacity = 0;

	keyboardEventFunctionListInitialCapacity = 0;
	keymapChangeEventFunctionListInitialCapacity = 0;
	textEditingEventFunctionListInitialCapacity = 0;
	textEditingExtendedEventFunctionListInitialCapacity = 0;
	textInputEventFunctionListInitialCapacity = 0;

	mouseMotionEventFunctionListInitialCapacity = 0;
	mouseButtonEventFunctionListInitialCapacity = 0;
	mouseWheelEventFunctionListInitialCapacity = 0;

	joyAxisEventFunctionListInitialCapacity = 0;
	joyBallEventFunctionListInitialCapacity = 0;
	joyHatEventFunctionListInitialCapacity = 0;
	joyButtonEventFunctionListInitialCapacity = 0;
	joyDeviceEventFunctionListInitialCapacity = 0;
	joyBatteryEventFunctionListInitialCapacity = 0;

	controllerAxisEventFunctionListInitialCapacity = 0;
	controllerButtonEventFunctionListInitialCapacity = 0;
	controllerDeviceEventFunctionListInitialCapacity = 0;
	controllerTouchpadEventFunctionListInitialCapacity = 0;
	controllerSensorEventFunctionListInitialCapacity = 0;

	audioDeviceEventFunctionListInitialCapacity = 0;
	touchFingerEventFunctionListInitialCapacity = 0;
	multiGestureEventFunctionListInitialCapacity = 0;
	dollarGestureEventFunctionListInitialCapacity = 0;
	clipboardEventFunctionListInitialCapacity = 0;

	dropEventFunctionListInitialCapacity = 0;
	sensorEventFunctionListInitialCapacity = 0;
	OSEventFunctionListInitialCapacity = 0;
	userEventFunctionListInitialCapacity = 0;

	renderTargetsResetEventFunctionListInitialCapacity = 0;
	renderDeviceResetEventFunctionListInitialCapacity = 0;
}