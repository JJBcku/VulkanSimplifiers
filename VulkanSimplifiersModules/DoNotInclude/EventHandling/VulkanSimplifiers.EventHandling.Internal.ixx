module;

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

export module VulkanSimplifiers.EventHandling.Internal;

import std;
import VulkanSimplifiers.EventHandling.SDLModule.QuitEvent;
import VulkanSimplifiers.EventHandling.SDLModule.AppEvents;
import VulkanSimplifiers.EventHandling.SDLModule.LocaleChangedEvent;
import VulkanSimplifiers.EventHandling.SDLModule.DisplayEvent;
import VulkanSimplifiers.EventHandling.SDLModule.WindowEvent;
import VulkanSimplifiers.EventHandling.SDLModule.KeyboardEvent;
import VulkanSimplifiers.EventHandling.SDLModule.TextEvents;
import VulkanSimplifiers.EventHandling.SDLModule.MouseEvents;
import VulkanSimplifiers.EventHandling.SDLModule.JoyEvents;
import VulkanSimplifiers.EventHandling.SDLModule.ControllerEvents;
import VulkanSimplifiers.EventHandling.SDLModule.AudioDeviceEvent;
import VulkanSimplifiers.EventHandling.SDLModule.TouchpadEvents;
import VulkanSimplifiers.EventHandling.SDLModule.ClipboardEvent;
import VulkanSimplifiers.EventHandling.SDLModule.DropEvent;
import VulkanSimplifiers.EventHandling.SDLModule.SensorEvent;
import VulkanSimplifiers.EventHandling.SDLModule.RenderEvents;
import VulkanSimplifiers.EventHandling.SDLModule.SystemEvent;
import VulkanSimplifiers.EventHandling.SDLModule.UserEvent;

import ListTemplates.OrderIndependentDeletionStack;

import VulkanSimplifiers.EventHandling.Data;

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

export class EventHandlingInternal
{
public:
	EventHandlingInternal(const EventHandlerInitData& initData);
	~EventHandlingInternal();

	EventHandlingInternal(const EventHandlingInternal&) noexcept = delete;
	//EventHandlerInternal(EventHandlerInternal&&) noexcept = delete;

	EventHandlingInternal& operator=(const EventHandlingInternal&) noexcept = delete;
	//EventHandlerInternal& operator=(EventHandlerInternal&&) noexcept = delete;

	void HandleEvents() const;

	IDObject<std::pair<QuitEventFunction, void*>> RegisterQuitEventCallback(QuitEventFunction function, void* data, size_t add);

	IDObject<std::pair<AppTerminatingEventFunction, void*>> RegisterAppTerminatingEventCallback(AppTerminatingEventFunction function, void* data, size_t add);
	IDObject<std::pair<AppLowMemoryEventFunction, void*>> RegisterAppLowMemoryWarningEventCallback(AppLowMemoryEventFunction function, void* data, size_t add);
	IDObject<std::pair<AppWillEnterBackgroundEventFunction, void*>> RegisterAppWillEnterBackgroundWarningEventCallback(AppWillEnterBackgroundEventFunction function, void* data, size_t add);
	IDObject<std::pair<AppDidEnterBackgroundEventFunction, void*>> RegisterAppDidEnterBackgroundEventCallback(AppDidEnterBackgroundEventFunction function, void* data, size_t add);
	IDObject<std::pair<AppWillEnterForegroundEventFunction, void*>> RegisterAppWillEnterForegroundWarningEventCallback(AppWillEnterForegroundEventFunction function, void* data, size_t add);
	IDObject<std::pair<AppDidEnterForegroundEventFunction, void*>> RegisterAppDidEnterForegroundEventCallback(AppDidEnterForegroundEventFunction function, void* data, size_t add);

	IDObject<std::pair<LocaleChangedEventFunction, void*>> RegisterLocaleChangingEventCallback(LocaleChangedEventFunction function, void* data, size_t add);

	IDObject<std::pair<DisplayEventFunction, void*>> RegisterDisplayEventCallback(DisplayEventFunction function, void* data, size_t add);
	IDObject<std::pair<WindowEventFunction, void*>> RegisterWindowEventCallback(WindowEventFunction function, void* data, size_t add);

	IDObject<std::pair<KeyboardEventFunction, void*>> RegisterKeyboardEventCallback(KeyboardEventFunction function, void* data, size_t add);
	IDObject<std::pair<KeymapChangeEventFunction, void*>> RegisterKeymapChangingEventCallback(KeymapChangeEventFunction function, void* data, size_t add);
	IDObject<std::pair<TextEditingEventFunction, void*>> RegisterTextEditingEventCallback(TextEditingEventFunction function, void* data, size_t add);
	IDObject<std::pair<TextEditingExtendedEventFunction, void*>> RegisterTextEditingExtendedEventCallback(TextEditingExtendedEventFunction function, void* data, size_t add);
	IDObject<std::pair<TextInputEventFunction, void*>> RegisterTextInputEventCallback(TextInputEventFunction function, void* data, size_t add);

	IDObject<std::pair<MouseMotionEventFunction, void*>> RegisterMouseMotionEventCallback(MouseMotionEventFunction function, void* data, size_t add);
	IDObject<std::pair<MouseButtonEventFunction, void*>> RegisterMouseButtonEventCallback(MouseButtonEventFunction function, void* data, size_t add);
	IDObject<std::pair<MouseWheelEventFunction, void*>> RegisterMouseWheelEventCallback(MouseWheelEventFunction function, void* data, size_t add);

	IDObject<std::pair<JoyAxisEventFunction, void*>> RegisterJoystickAxisEventCallback(JoyAxisEventFunction function, void* data, size_t add);
	IDObject<std::pair<JoyBallEventFunction, void*>> RegisterJoystickBallEventCallback(JoyBallEventFunction function, void* data, size_t add);
	IDObject<std::pair<JoyHatEventFunction, void*>> RegisterJoystickHatEventCallback(JoyHatEventFunction function, void* data, size_t add);
	IDObject<std::pair<JoyButtonEventFunction, void*>> RegisterJoystickButtonEventCallback(JoyButtonEventFunction function, void* data, size_t add);
	IDObject<std::pair<JoyDeviceEventFunction, void*>> RegisterJoystickDeviceEventCallback(JoyDeviceEventFunction function, void* data, size_t add);
	IDObject<std::pair<JoyBatteryEventFunction, void*>> RegisterJoystickBatteryEventCallback(JoyBatteryEventFunction function, void* data, size_t add);

	IDObject<std::pair<ControllerAxisEventFunction, void*>> RegisterControllerAxisEventCallback(ControllerAxisEventFunction function, void* data, size_t add);
	IDObject<std::pair<ControllerButtonEventFunction, void*>> RegisterControllerButtonEventCallback(ControllerButtonEventFunction function, void* data, size_t add);
	IDObject<std::pair<ControllerDeviceEventFunction, void*>> RegisterControllerDeviceEventCallback(ControllerDeviceEventFunction function, void* data, size_t add);
	IDObject<std::pair<ControllerTouchpadEventFunction, void*>> RegisterControllerTouchpadEventCallback(ControllerTouchpadEventFunction function, void* data, size_t add);
	IDObject<std::pair<ControllerSensorEventFunction, void*>> RegisterControllerSensorEventCallback(ControllerSensorEventFunction function, void* data, size_t add);

	IDObject<std::pair<AudioDeviceEventFunction, void*>> RegisterAudioDeviceEventCallback(AudioDeviceEventFunction function, void* data, size_t add);
	IDObject<std::pair<TouchFingerEventFunction, void*>> RegisterTouchFingerEventCallback(TouchFingerEventFunction function, void* data, size_t add);
	IDObject<std::pair<MultiGestureEventFunction, void*>> RegisterMultiGestureEventCallback(MultiGestureEventFunction function, void* data, size_t add);
	IDObject<std::pair<DollarGestureEventFunction, void*>> RegisterDollarGestureEventCallback(DollarGestureEventFunction function, void* data, size_t add);
	IDObject<std::pair<ClipboardEventFunction, void*>> RegisterClipboardEventCallback(ClipboardEventFunction function, void* data, size_t add);

	IDObject<std::pair<DropEventFunction, void*>> RegisterDropEventCallback(DropEventFunction function, void* data, size_t add);
	IDObject<std::pair<SensorEventFunction, void*>> RegisterSensorEventCallback(SensorEventFunction function, void* data, size_t add);
	IDObject<std::pair<OSEventFunction, void*>> RegisterOSEventCallback(OSEventFunction function, void* data, size_t add);
	IDObject<std::pair<UserEventFunction, void*>> RegisterUserEventCallback(UserEventFunction function, void* data, size_t add);

	IDObject<std::pair<RenderTargetsResetEventFunction, void*>> RegisterRenderTargetsResetEventCallback(RenderTargetsResetEventFunction function, void* data, size_t add);
	IDObject<std::pair<RenderDeviceResetEventFunction, void*>> RegisterRenderDeviceResetEventCallback(RenderDeviceResetEventFunction function, void* data, size_t add);

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

	void HandleEvent(SDL_Event& event) const;

	void HandleEvent(SDLModuleQuitEvent event) const;

	void HandleEvent(SDLModuleAppTerminatingEvent event) const;
	void HandleEvent(SDLModuleAppLowMemoryEvent event) const;
	void HandleEvent(SDLModuleAppWillEnterBackgroundEvent event) const;
	void HandleEvent(SDLModuleAppDidEnterBackgroundEvent event) const;
	void HandleEvent(SDLModuleAppWillEnterForegroundEvent event) const;
	void HandleEvent(SDLModuleAppDidEnterForegroundEvent event) const;

	void HandleEvent(SDLModuleLocaleChangeEvent event) const;

	void HandleEvent(SDLModuleDisplayEvent event) const;
	void HandleEvent(SDLModuleWindowEvent event) const;

	void HandleEvent(SDLModuleKeyboardEvent event) const;
	void HandleEvent(SDLModuleKeymapChanged event) const;
	void HandleEvent(SDLModuleTextEditingEvent event) const;
	void HandleEvent(SDLModuleTextEditingExtendedEvent event) const;
	void HandleEvent(SDLModuleTextInputEvent event) const;

	void HandleEvent(SDLModuleMouseMotionEvent event) const;
	void HandleEvent(SDLModuleMouseButtonEvent event) const;
	void HandleEvent(SDLModuleMouseWheelEvent event) const;

	void HandleEvent(SDLModuleJoyAxisEvent event) const;
	void HandleEvent(SDLModuleJoyBallEvent event) const;
	void HandleEvent(SDLModuleJoyHatEvent event) const;
	void HandleEvent(SDLModuleJoyButtonEvent event) const;
	void HandleEvent(SDLModuleJoyDeviceEvent event) const;
	void HandleEvent(SDLModuleJoyBatteryEvent event) const;

	void HandleEvent(SDLModuleControllerAxisEvent event) const;
	void HandleEvent(SDLModuleControllerButtonEvent event) const;
	void HandleEvent(SDLModuleControllerDeviceEvent event) const;
	void HandleEvent(SDLModuleControllerTouchpadEvent event) const;
	void HandleEvent(SDLModuleControllerSensorEvent event) const;

	void HandleEvent(SDLModuleAudioDeviceEvent event) const;
	void HandleEvent(SDLModuleTouchFingerEvent event) const;
	void HandleEvent(SDLModuleMultiGestureEvent event) const;
	void HandleEvent(SDLModuleDollarGestureEvent event) const;
	void HandleEvent(SDLModuleClipboardEvent event) const;

	void HandleEvent(SDLModuleDropEvent event) const;
	void HandleEvent(SDLModuleSensorEvent event) const;
	void HandleEvent(SDLModuleOSEvent event) const;
	void HandleEvent(SDLModuleUserEvent event) const;

	void HandleEvent(SDLModuleRenderTargetsResetEvent event) const;
	void HandleEvent(SDLModuleRenderDeviceResetEvent event) const;
};
