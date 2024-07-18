module;

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

export module VulkanSimplifiers.EventHandler.Internal;

import std;
import VulkanSimplifiers.EventHandler.SDLModule.QuitEvent;
import VulkanSimplifiers.EventHandler.SDLModule.AppEvents;
import VulkanSimplifiers.EventHandler.SDLModule.LocaleChangedEvent;
import VulkanSimplifiers.EventHandler.SDLModule.DisplayEvent;
import VulkanSimplifiers.EventHandler.SDLModule.WindowEvent;
import VulkanSimplifiers.EventHandler.SDLModule.KeyboardEvent;
import VulkanSimplifiers.EventHandler.SDLModule.TextEvents;
import VulkanSimplifiers.EventHandler.SDLModule.MouseEvents;
import VulkanSimplifiers.EventHandler.SDLModule.JoyEvents;
import VulkanSimplifiers.EventHandler.SDLModule.ControllerEvents;
import VulkanSimplifiers.EventHandler.SDLModule.AudioDeviceEvent;
import VulkanSimplifiers.EventHandler.SDLModule.TouchpadEvents;
import VulkanSimplifiers.EventHandler.SDLModule.ClipboardEvent;
import VulkanSimplifiers.EventHandler.SDLModule.DropEvent;
import VulkanSimplifiers.EventHandler.SDLModule.SensorEvent;
import VulkanSimplifiers.EventHandler.SDLModule.RenderEvents;
import VulkanSimplifiers.EventHandler.SDLModule.SystemEvent;
import VulkanSimplifiers.EventHandler.SDLModule.UserEvent;

import ListTemplates.OrderIndependentDeletionStack;

export typedef std::function<bool(const SDLModuleQuitEvent&, void*)> QuitEventFunction;

export typedef std::function<bool(const SDLModuleAppTerminatingEvent&, void*)> AppTerminatingEventFunction;
export typedef std::function<bool(const SDLModuleAppLowMemoryEvent&, void*)> AppLowMemoryEventFunction;
export typedef std::function<bool(const SDLModuleAppWillEnterBackgroundEvent&, void*)> AppWillEnterBackgroundEventFunction;
export typedef std::function<bool(const SDLModuleAppDidEnterBackgroundEvent&, void*)> AppDidEnterBackgroundEventFunction;
export typedef std::function<bool(const SDLModuleAppWillEnterForegroundEvent&, void*)> AppWillEnterForegroundEventFunction;
export typedef std::function<bool(const SDLModuleAppDidEnterForegroundEvent&, void*)> AppDidEnterForegroundEventFunction;

export typedef std::function<bool(const SDLModuleLocaleChangeEvent&, void*)> LocaleChangedEventFunction;

export typedef std::function<bool(const SDLModuleDisplayEvent&, void*)> DisplayEventFunction;
export typedef std::function<bool(const SDLModuleWindowEvent&, void*)> WindowEventFunction;

export typedef std::function<bool(const SDLModuleKeyboardEvent&, void*)> KeyboardEventFunction;
export typedef std::function<bool(const SDLModuleKeymapChanged&, void*)> KeymapChangeEventFunction;
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

export typedef std::function<bool(const SDLModuleClipboardEvent&, void*)> ClipboardEventFunction;

export typedef std::function<bool(const SDLModuleDropEvent&, void*)> DropEventFunction;
export typedef std::function<bool(const SDLModuleSensorEvent&, void*)> SensorEventFunction;
export typedef std::function<bool(const SDLModuleOSEvent&, void*)> OSEventFunction;
export typedef std::function<bool(const SDLModuleUserEvent&, void*)> UserEventFunction;

export typedef std::function<bool(const SDLModuleRenderTargetsResetEvent&, void*)> RenderTargetsResetEventFunction;
export typedef std::function<bool(const SDLModuleRenderDeviceResetEvent&, void*)> RenderDeviceResetEventFunction;
//export typedef std::function<bool(const SDL_SysWMEvent&, void*)> SystemWindowsManagerEventFunction;

export class EventHandlerInternal
{
public:
	EventHandlerInternal(size_t reserve);
	~EventHandlerInternal();

	EventHandlerInternal(const EventHandlerInternal&) noexcept = delete;
	//EventHandlerInternal(EventHandlerInternal&&) noexcept = delete;

	EventHandlerInternal& operator=(const EventHandlerInternal&) noexcept = delete;
	//EventHandlerInternal& operator=(EventHandlerInternal&&) noexcept = delete;

	void HandleEvents();

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
	OrderIndependentDeletionStack<std::pair<KeymapChangeEventFunction, void*>> _keymapChangedEventFunctions;
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

	OrderIndependentDeletionStack<std::pair<ClipboardEventFunction, void*>> _clipboardEventFunctions;

	OrderIndependentDeletionStack<std::pair<DropEventFunction, void*>> _dropEventFunctions;
	OrderIndependentDeletionStack<std::pair<SensorEventFunction, void*>> _sensorEventFunctions;
	OrderIndependentDeletionStack<std::pair<OSEventFunction, void*>> _OSEventFunctions;
	OrderIndependentDeletionStack<std::pair<UserEventFunction, void*>> _userEventFunctions;

	OrderIndependentDeletionStack<std::pair<RenderTargetsResetEventFunction, void*>> _renderTargetsResetEventFunctions;
	OrderIndependentDeletionStack<std::pair<RenderDeviceResetEventFunction, void*>> _renderDeviceResetEventFunctions;
	//OrderIndependentDeletionStack<std::pair<SystemWindowsManagerEventFunction, void*>> _systemWindowsManagerEventFunctions;

	void HandleEvent(SDL_Event& event);

	void HandleEvent(SDLModuleQuitEvent event);

	void HandleEvent(SDLModuleAppTerminatingEvent event);
	void HandleEvent(SDLModuleAppLowMemoryEvent event);
	void HandleEvent(SDLModuleAppWillEnterBackgroundEvent event);
	void HandleEvent(SDLModuleAppDidEnterBackgroundEvent event);
	void HandleEvent(SDLModuleAppWillEnterForegroundEvent event);
	void HandleEvent(SDLModuleAppDidEnterForegroundEvent event);

	void HandleEvent(SDLModuleLocaleChangeEvent event);

	void HandleEvent(SDLModuleDisplayEvent event);
	void HandleEvent(SDLModuleWindowEvent event);

	void HandleEvent(SDLModuleKeyboardEvent event);
	void HandleEvent(SDLModuleKeymapChanged event);
	void HandleEvent(SDLModuleTextEditingEvent event);
	void HandleEvent(SDLModuleTextEditingExtendedEvent event);
	void HandleEvent(SDLModuleTextInputEvent event);

	void HandleEvent(SDLModuleMouseMotionEvent event);
	void HandleEvent(SDLModuleMouseButtonEvent event);
	void HandleEvent(SDLModuleMouseWheelEvent event);

	void HandleEvent(SDLModuleJoyAxisEvent event);
	void HandleEvent(SDLModuleJoyBallEvent event);
	void HandleEvent(SDLModuleJoyHatEvent event);
	void HandleEvent(SDLModuleJoyButtonEvent event);
	void HandleEvent(SDLModuleJoyDeviceEvent event);
	void HandleEvent(SDLModuleJoyBatteryEvent event);

	void HandleEvent(SDLModuleControllerAxisEvent event);
	void HandleEvent(SDLModuleControllerButtonEvent event);
	void HandleEvent(SDLModuleControllerDeviceEvent event);
	void HandleEvent(SDLModuleControllerTouchpadEvent event);
	void HandleEvent(SDLModuleControllerSensorEvent event);

	void HandleEvent(SDLModuleAudioDeviceEvent event);
	void HandleEvent(SDLModuleTouchFingerEvent event);
	void HandleEvent(SDLModuleMultiGestureEvent event);
	void HandleEvent(SDLModuleDollarGestureEvent event);

	void HandleEvent(SDLModuleClipboardEvent event);

	void HandleEvent(SDLModuleDropEvent event);
	void HandleEvent(SDLModuleSensorEvent event);
	void HandleEvent(SDLModuleOSEvent event);
	void HandleEvent(SDLModuleUserEvent event);

	void HandleEvent(SDLModuleRenderTargetsResetEvent event);
	void HandleEvent(SDLModuleRenderDeviceResetEvent event);
};
