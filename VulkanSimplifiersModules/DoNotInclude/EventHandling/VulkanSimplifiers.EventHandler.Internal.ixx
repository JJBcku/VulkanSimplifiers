module;

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

export module VulkanSimplifiers.EventHandler.Internal;

import std;
import VulkanSimplifiers.EventHandler.SDLModule.QuitEvent;
import VulkanSimplifiers.EventHandler.SDLModule.CommonEvent;
import VulkanSimplifiers.EventHandler.SDLModule.DisplayEvent;
import VulkanSimplifiers.EventHandler.SDLModule.WindowEvent;
import VulkanSimplifiers.EventHandler.SDLModule.KeyboardEvent;
import VulkanSimplifiers.EventHandler.SDLModule.TextEvents;
import VulkanSimplifiers.EventHandler.SDLModule.MouseEvents;
import VulkanSimplifiers.EventHandler.SDLModule.JoyEvents;
import VulkanSimplifiers.EventHandler.SDLModule.ControllerEvents;
import VulkanSimplifiers.EventHandler.SDLModule.AudioDeviceEvent;
import VulkanSimplifiers.EventHandler.SDLModule.TouchpadEvents;
import VulkanSimplifiers.EventHandler.SDLModule.DropEvent;
import VulkanSimplifiers.EventHandler.SDLModule.SensorEvent;
import VulkanSimplifiers.EventHandler.SDLModule.SystemEvent;
import VulkanSimplifiers.EventHandler.SDLModule.UserEvent;

export typedef std::function<bool(const SDLModuleQuitEvent&, void*)> QuitEventFunction;

export typedef std::function<bool(const SDLModuleCommonEvent&, void*)> AppTerminatingEventFunction;
export typedef std::function<bool(const SDLModuleCommonEvent&, void*)> AppLowMemoryEventFunction;
export typedef std::function<bool(const SDLModuleCommonEvent&, void*)> AppWillEnterBackgroundEventFunction;
export typedef std::function<bool(const SDLModuleCommonEvent&, void*)> AppDidEnterBackgroundEventFunction;
export typedef std::function<bool(const SDLModuleCommonEvent&, void*)> AppWillEnterForegroundEventFunction;
export typedef std::function<bool(const SDLModuleCommonEvent&, void*)> AppDidEnterForegroundEventFunction;

export typedef std::function<bool(const SDLModuleCommonEvent&, void*)> LocaleChangedEventFunction;

export typedef std::function<bool(const SDLModuleDisplayEvent&, void*)> DisplayEventFunction;
export typedef std::function<bool(const SDLModuleWindowEvent&, void*)> WindowEventFunction;

export typedef std::function<bool(const SDLModuleKeyboardEvent&, void*)> KeyboardEventFunction;
export typedef std::function<bool(const SDLModuleTextEditingEvent&, void*)> TextEditingEventFunction;
export typedef std::function<bool(const SDLModuleTextEditingExtendedEvent&, void*)> TextEditingExtendedEventFunction;
export typedef std::function<bool(const SDLModuleTextInputEvent&, void*)> TextInputEventFunction;

export typedef std::function<bool(const SDLModuleMouseMotionEvent&, void*)> MouseMotionEventFunction;
export typedef std::function<bool(const SDLModuleMouseButtonEvent&, void*)> MouseButtonEventFunction;
export typedef std::function<bool(const SDLModuleMouseWheelEvent&, void*)> MouseWheelEventFunction;

export typedef std::function<bool(const SDLModuleJoyAxisEvent&, void*)> JoyAxisEventFunction;
export typedef std::function<bool(const SDLModuleJoyBallEvent&, void*)> JoyBallEventFunction;
export typedef std::function<bool(const SDLModuleJoyHatEvent&, void*)> JoyHatEventFunction;
export typedef std::function<bool(const SDLModuleJoyButtonEvent&, void*)> JoyButtonEventFunction;
export typedef std::function<bool(const SDLModuleJoyDeviceEvent&, void*)> JoyDeviceEventFunction;
export typedef std::function<bool(const SDLModuleJoyBatteryEvent&, void*)> JoyBatteryEventFunction;

export typedef std::function<bool(const SDLModuleControllerAxisEvent&, void*)> ControllerAxisEventFunction;
export typedef std::function<bool(const SDLModuleControllerButtonEvent&, void*)> ControllerButtonEventFunction;
export typedef std::function<bool(const SDLModuleControllerDeviceEvent&, void*)> ControllerDeviceEventFunction;
export typedef std::function<bool(const SDLModuleControllerTouchpadEvent&, void*)> ControllerTouchpadEventFunction;
export typedef std::function<bool(const SDLModuleControllerSensorEvent&, void*)> ControllerSensorEventFunction;

export typedef std::function<bool(const SDLModuleAudioDeviceEvent&, void*)> AudioDeviceEventFunction;
export typedef std::function<bool(const SDLModuleTouchFingerEvent&, void*)> TouchFingerEventFunction;
export typedef std::function<bool(const SDLModuleMultiGestureEvent&, void*)> MultiGestureEventFunction;
export typedef std::function<bool(const SDLModuleDollarGestureEvent&, void*)> DollarGestureEventFunction;

export typedef std::function<bool(const SDLModuleDropEvent&, void*)> DropEventFunction;
export typedef std::function<bool(const SDLModuleSensorEvent&, void*)> SensorEventFunction;
export typedef std::function<bool(const SDLModuleOSEvent&, void*)> OSEventFunction;
export typedef std::function<bool(const SDLModuleUserEvent&, void*)> UserEventFunction;
//export typedef std::function<bool(const SDL_SysWMEvent&, void*)> SystemWindowsManagerEventFunction;

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
	//std::vector<std::pair<SystemWindowsManagerEventFunction, void*>> _systemWindowsManagerEventFunctions;
};