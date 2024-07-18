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

import ListTemplates.OrderIndependentDeletionStack;

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
	OrderIndependentDeletionStack<std::pair<QuitEventFunction, void*>> _quitEventFunctions;

	OrderIndependentDeletionStack<std::pair<AppTerminatingEventFunction, void*>> _appTerminatingEventFunctions;
	OrderIndependentDeletionStack<std::pair<AppLowMemoryEventFunction, void*>> _appLowMemoryEventFunctions;
	OrderIndependentDeletionStack<std::pair<AppWillEnterBackgroundEventFunction, void*>> _appWillEnterBackgroundEventFunctions;
	OrderIndependentDeletionStack<std::pair<AppDidEnterBackgroundEventFunction, void*>> _appDidEnterBackgroundEventFunctions;
	OrderIndependentDeletionStack<std::pair<AppWillEnterForegroundEventFunction, void*>> _appWillEnterForegroundEventFunctions;
	OrderIndependentDeletionStack<std::pair<AppDidEnterForegroundEventFunction, void*>> _appDidEnterForegroundEventFunctions;

	OrderIndependentDeletionStack<std::pair<LocaleChangedEventFunction, void*>> _localeChangedEventFunctions;

	OrderIndependentDeletionStack<std::pair<DisplayEventFunction, void*>> _displayEventFunctions;
	OrderIndependentDeletionStack<std::pair<WindowEventFunction, void*>> _windowEventFunctions;

	OrderIndependentDeletionStack<std::pair<KeyboardEventFunction, void*>> _keyboardEventFunctions;
	OrderIndependentDeletionStack<std::pair<TextEditingEventFunction, void*>> _textEditingEventFunctions;
	OrderIndependentDeletionStack<std::pair<TextEditingExtendedEventFunction, void*>> _textEditingExtendedEventFunctions;
	OrderIndependentDeletionStack<std::pair<TextInputEventFunction, void*>> _textInputEventFunctions;

	OrderIndependentDeletionStack<std::pair<MouseMotionEventFunction, void*>> _mouseMotionEventFunctions;
	OrderIndependentDeletionStack<std::pair<MouseButtonEventFunction, void*>> _mouseButtonEventFunctions;
	OrderIndependentDeletionStack<std::pair<MouseWheelEventFunction, void*>> _mouseWheelEventFunctions;

	OrderIndependentDeletionStack<std::pair<JoyAxisEventFunction, void*>> _joyAxisEventFunctions;
	OrderIndependentDeletionStack<std::pair<JoyBallEventFunction, void*>> _joyBallEventFunctions;
	OrderIndependentDeletionStack<std::pair<JoyHatEventFunction, void*>> _joyHatEventFunctions;
	OrderIndependentDeletionStack<std::pair<JoyButtonEventFunction, void*>> _joyButtonEventFunctions;
	OrderIndependentDeletionStack<std::pair<JoyDeviceEventFunction, void*>> _joyDeviceEventFunctions;
	OrderIndependentDeletionStack<std::pair<JoyBatteryEventFunction, void*>> _joyBatteryEventFunctions;

	OrderIndependentDeletionStack<std::pair<ControllerAxisEventFunction, void*>> _controllerAxisEventFunctions;
	OrderIndependentDeletionStack<std::pair<ControllerButtonEventFunction, void*>> _controllerButtonEventFunctions;
	OrderIndependentDeletionStack<std::pair<ControllerDeviceEventFunction, void*>> _controllerDeviceEventFunctions;
	OrderIndependentDeletionStack<std::pair<ControllerTouchpadEventFunction, void*>> _controllerTouchpadEventFunctions;
	OrderIndependentDeletionStack<std::pair<ControllerSensorEventFunction, void*>> _controllerSensorEventFunctions;

	OrderIndependentDeletionStack<std::pair<AudioDeviceEventFunction, void*>> _audioDeviceEventFunctions;
	OrderIndependentDeletionStack<std::pair<TouchFingerEventFunction, void*>> _touchFingerEventFunctions;
	OrderIndependentDeletionStack<std::pair<MultiGestureEventFunction, void*>> _multiGestureEventFunctions;
	OrderIndependentDeletionStack<std::pair<DollarGestureEventFunction, void*>> _dollarGestureEventFunctions;

	OrderIndependentDeletionStack<std::pair<DropEventFunction, void*>> _dropEventFunctions;
	OrderIndependentDeletionStack<std::pair<SensorEventFunction, void*>> _sensorEventFunctions;
	OrderIndependentDeletionStack<std::pair<OSEventFunction, void*>> _OSEventFunctions;
	OrderIndependentDeletionStack<std::pair<UserEventFunction, void*>> _UserEventFunctions;
	//OrderIndependentDeletionStack<std::pair<SystemWindowsManagerEventFunction, void*>> _systemWindowsManagerEventFunctions;
};