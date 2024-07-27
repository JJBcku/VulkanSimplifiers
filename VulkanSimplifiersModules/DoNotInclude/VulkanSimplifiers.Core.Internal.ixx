export module VulkanSimplifiers.Core.Internal;

import std;
import VulkanSimplifiers.Core.Data;
import ListTemplates.UnsortedList;
import VulkanSimplifiers.EventHandling.Internal;
import VulkanSimplifiers.Instance;
import VulkanSimplifiers.WindowList.Internal;
import VulkanSimplifiers.Window.Data;
import VulkanSimplifiers.Window.Simplifier;

export typedef std::unique_ptr<Instance> InstancePointer;

export class CoreInternal
{
public:
	explicit CoreInternal(const CoreSimplifierInitData& initData);
	~CoreInternal();

	CoreInternal(const CoreInternal&) = delete;
	CoreInternal& operator=(const CoreInternal&) = delete;

	EventHandlingInternal& GetEventHandler();
	WindowListInternal& GetWindowListSimplifier();

	const EventHandlingInternal& GetEventHandler() const;
	const WindowListInternal& GetWindowListSimplifier() const;

private:
	NonVulkanVersionData _appVersion;
	std::string _appTitle;
	std::string _appVarianTile;
	EventHandlingInternal _eventHandler;
	UnsortedList<InstancePointer> _instanceList;
	WindowListInternal _windowList;
};