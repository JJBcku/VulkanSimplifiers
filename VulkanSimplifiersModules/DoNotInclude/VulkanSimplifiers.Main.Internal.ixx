export module VulkanSimplifiers.Main.Internal;

import std;
import VulkanSimplifiers.Main.Data;
import ListTemplates.UnsortedList;
import VulkanSimplifiers.EventHandling.Internal;
import VulkanSimplifiers.Instance;
import VulkanSimplifiers.WindowList.Internal;

export typedef std::unique_ptr<Instance> InstancePointer;

export class MainInternal
{
public:
	explicit MainInternal(const MainSimplifierInitData& initData);
	~MainInternal();

	MainInternal(const MainInternal&) = delete;
	MainInternal& operator=(const MainInternal&) = delete;

	EventHandlingInternal& GetEventHandler();
	WindowListInternal& GetWindowListSimplifier();

	const EventHandlingInternal& GetEventHandler() const;
	const WindowListInternal& GetWindowListSimplifier() const;

private:
	NonVulkanVersionData _appVersion;
	std::string _appTitle;
	std::string _appVariantTile;
	EventHandlingInternal _eventHandler;
	UnsortedList<InstancePointer> _instanceList;
	WindowListInternal _windowList;
};