export module VulkanSimplifiers.Core.Internal;

import std;
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
	explicit CoreInternal(size_t callbackListInitialCapacity, size_t reserveInstances, size_t reserveWindows);
	~CoreInternal();

	CoreInternal(const CoreInternal&) = delete;
	CoreInternal& operator=(const CoreInternal&) = delete;

	IDObject<WindowPointer> CreateWindow(WindowCreationData data, size_t addReserved);

	WindowSimplifier GetWindowSimplifier(IDObject<WindowPointer> windowID);

private:
	EventHandlerInternal _eventHandler;
	UnsortedList<InstancePointer> _instanceList;
	UnsortedList<WindowPointer> _windowList;
};