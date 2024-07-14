module;

#include <SDL2/SDL.h>

export module VulkanSimplifiers.EventHandler.Internal;

import std;

export typedef std::function<void(const SDL_CommonEvent&, void*)> QuitEventFunction;

export typedef std::function<void(const SDL_CommonEvent&, void*)> AppTerminatingEventFunction;
export typedef std::function<void(const SDL_CommonEvent&, void*)> AppLowMemoryEventFunction;
export typedef std::function<void(const SDL_CommonEvent&, void*)> AppWillEnterBackgroundEventFunction;
export typedef std::function<void(const SDL_CommonEvent&, void*)> AppDidEnterBackgroundEventFunction;
export typedef std::function<void(const SDL_CommonEvent&, void*)> AppWillEnterForegroundEventFunction;
export typedef std::function<void(const SDL_CommonEvent&, void*)> AppDidEnterForegroundEventFunction;

export typedef std::function<void(const SDL_CommonEvent&, void*)> LocaleChangedEventFunction;

export typedef std::function<void(const SDL_DisplayEvent&, void*)> DisplayEventFunction;
export typedef std::function<void(const SDL_WindowEvent&, void*)> WindowEventFunction;

export typedef std::function<void(const SDL_KeyboardEvent&, void*)> KeyboardEventFunction;
export typedef std::function<void(const SDL_TextEditingEvent&, void*)> TextEditingEventFunction;
export typedef std::function<void(const SDL_TextEditingExtEvent&, void*)> TextEditingExtendedEventFunction;
export typedef std::function<void(const SDL_TextInputEvent&, void*)> TextInputEventFunction;

export typedef std::function<void(const SDL_MouseMotionEvent&, void*)> MouseMotionEventFunction;
export typedef std::function<void(const SDL_MouseButtonEvent&, void*)> MouseButtonEventFunction;
export typedef std::function<void(const SDL_MouseWheelEvent&, void*)> MouseWheelEventFunction;

export typedef std::function<void(const SDL_JoyAxisEvent&, void*)> JoyAxisEventFunction;
export typedef std::function<void(const SDL_JoyBallEvent&, void*)> JoyBallEventFunction;
export typedef std::function<void(const SDL_JoyHatEvent&, void*)> JoyHatEventFunction;
export typedef std::function<void(const SDL_JoyButtonEvent&, void*)> JoyButtonEventFunction;
export typedef std::function<void(const SDL_JoyDeviceEvent&, void*)> JoyDeviceEventFunction;
export typedef std::function<void(const SDL_JoyBatteryEvent&, void*)> JoyBatteryEventFunction;

export typedef std::function<void(const SDL_ControllerAxisEvent&, void*)> ControllerAxisEventFunction;
export typedef std::function<void(const SDL_ControllerButtonEvent&, void*)> ControllerButtonEventFunction;
export typedef std::function<void(const SDL_ControllerDeviceEvent&, void*)> ControllerDeviceEventFunction;
export typedef std::function<void(const SDL_ControllerTouchpadEvent&, void*)> ControllerTouchpadEventFunction;
export typedef std::function<void(const SDL_ControllerSensorEvent&, void*)> ControllerSensorEventFunction;

export typedef std::function<void(const SDL_AudioDeviceEvent&, void*)> AudioDeviceEventFunction;
export typedef std::function<void(const SDL_TouchFingerEvent&, void*)> TouchFingerEventFunction;
export typedef std::function<void(const SDL_MultiGestureEvent&, void*)> MultiGestureEventFunction;
export typedef std::function<void(const SDL_DollarGestureEvent&, void*)> DollarGestureEventFunction;

export typedef std::function<void(const SDL_DropEvent&, void*)> DropEventFunction;
export typedef std::function<void(const SDL_SensorEvent&, void*)> SensorEventFunction;
export typedef std::function<void(const SDL_OSEvent&, void*)> OSEventFunction;
export typedef std::function<void(const SDL_UserEvent&, void*)> UserEventFunction;
export typedef std::function<void(const SDL_SysWMEvent&, void*)> SystemWindowsManagerEventFunction;

export class EventHandlerInternal
{
private:
	std::vector<std::pair<QuitEventFunction, void*>> _quitEventFunctions;

	std::vector<std::pair<AppTerminatingEventFunction, void*>> _appTerminatingEventFunctions;
	std::vector<std::pair<AppLowMemoryEventFunction, void*>> _appLowMemoryEventFunctions;
	std::vector<std::pair<AppWillEnterBackgroundEventFunction, void*>> _appWillEnterBackgroundEventFunctions;
	std::vector<std::pair<AppDidEnterBackgroundEventFunction, void*>> _appDidEnterBackgroundEventFunctions;
	std::vector<std::pair<AppWillEnterForegroundEventFunction, void*>> _appWillEnterForegroundEventFunctions;
	std::vector<std::pair<AppDidEnterForegroundEventFunction, void*>> _appDidEnterForegroundEventFunctions;

	std::vector<std::pair<LocaleChangedEventFunction, void*>> _localeChangedEventFunctions;

	std::vector<std::pair<DisplayEventFunction, void*>> _displayEventFunctions;
	std::vector<std::pair<WindowEventFunction, void*>> _windowEventFunctions;

	std::vector<std::pair<KeyboardEventFunction, void*>> _keyboardEventFunctions;
	std::vector<std::pair<TextEditingEventFunction, void*>> _textEditingEventFunctions;
	std::vector<std::pair<TextEditingExtendedEventFunction, void*>> _textEditingExtendedEventFunctions;
	std::vector<std::pair<TextInputEventFunction, void*>> _textInputEventFunctions;

	std::vector<std::pair<MouseMotionEventFunction, void*>> _mouseMotionEventFunctions;
	std::vector<std::pair<MouseButtonEventFunction, void*>> _mouseButtonEventFunctions;
	std::vector<std::pair<MouseWheelEventFunction, void*>> _mouseWheelEventFunctions;

	std::vector<std::pair<JoyAxisEventFunction, void*>> _joyAxisEventFunctions;
	std::vector<std::pair<JoyBallEventFunction, void*>> _joyBallEventFunctions;
	std::vector<std::pair<JoyHatEventFunction, void*>> _joyHatEventFunctions;
	std::vector<std::pair<JoyButtonEventFunction, void*>> _joyButtonEventFunctions;
	std::vector<std::pair<JoyDeviceEventFunction, void*>> _joyDeviceEventFunctions;
	std::vector<std::pair<JoyBatteryEventFunction, void*>> _joyBatteryEventFunctions;

	std::vector<std::pair<ControllerAxisEventFunction, void*>> _controllerAxisEventFunctions;
	std::vector<std::pair<ControllerButtonEventFunction, void*>> _controllerButtonEventFunctions;
	std::vector<std::pair<ControllerDeviceEventFunction, void*>> _controllerDeviceEventFunctions;
	std::vector<std::pair<ControllerTouchpadEventFunction, void*>> _controllerTouchpadEventFunctions;
	std::vector<std::pair<ControllerSensorEventFunction, void*>> _controllerSensorEventFunctions;

	std::vector<std::pair<AudioDeviceEventFunction, void*>> _audioDeviceEventFunctions;
	std::vector<std::pair<TouchFingerEventFunction, void*>> _touchFingerEventFunctions;
	std::vector<std::pair<MultiGestureEventFunction, void*>> _multiGestureEventFunctions;
	std::vector<std::pair<DollarGestureEventFunction, void*>> _dollarGestureEventFunctions;

	std::vector<std::pair<DropEventFunction, void*>> _dropEventFunctions;
	std::vector<std::pair<SensorEventFunction, void*>> _sensorEventFunctions;
	std::vector<std::pair<OSEventFunction, void*>> _OSEventFunctions;
	std::vector<std::pair<UserEventFunction, void*>> _UserEventFunctions;
	std::vector<std::pair<SystemWindowsManagerEventFunction, void*>> _systemWindowsManagerEventFunctions;
};