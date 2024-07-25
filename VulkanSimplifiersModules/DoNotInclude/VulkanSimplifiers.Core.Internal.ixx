export module VulkanSimplifiers.Core.Internal;

import std;
import VulkanSimplifiers.Core.Data;
import ListTemplates.UnsortedList;
import VulkanSimplifiers.EventHandler.Internal;
import VulkanSimplifiers.Instance;
import VulkanSimplifiers.Window.Internal;
import VulkanSimplifiers.Window.Data;
import VulkanSimplifiers.Window.Simplifier;

export typedef std::unique_ptr<Instance> InstancePointer;
export typedef std::unique_ptr<WindowInternal> WindowPointer;

export class CoreInternal
{
public:
	explicit CoreInternal(const CoreSimplifierInitData& initData);
	~CoreInternal();

	CoreInternal(const CoreInternal&) = delete;
	CoreInternal& operator=(const CoreInternal&) = delete;

	IDObject<WindowPointer> CreateWindow(WindowCreationData data, size_t addReserved);

	EventHandlerInternal& GetEventHandler();
	WindowInternal& GetWindowSimplifier(IDObject<WindowPointer> windowID);

	const EventHandlerInternal& GetEventHandler() const;
	const WindowInternal& GetWindowSimplifier(IDObject<WindowPointer> windowID) const;

private:
	NonVulkanVersionData _appVersion;
	std::string _appTitle;
	std::string _appVarianTile;
	EventHandlerInternal _eventHandler;
	UnsortedList<InstancePointer> _instanceList;
	UnsortedList<WindowPointer> _windowList;
};