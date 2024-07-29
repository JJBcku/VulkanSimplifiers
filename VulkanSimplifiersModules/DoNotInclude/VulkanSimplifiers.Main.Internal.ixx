export module VulkanSimplifiers.Main.Internal;

import std;
import VulkanSimplifiers.Main.Data;
import ListTemplates.UnsortedList;
import VulkanSimplifiers.EventHandling.Internal;
import VulkanSimplifiers.InstanceList.Internal;
import VulkanSimplifiers.WindowList.Internal;

export class MainInternal
{
public:
	explicit MainInternal(const MainSimplifierInitData& initData);
	~MainInternal();

	MainInternal(const MainInternal&) = delete;
	MainInternal& operator=(const MainInternal&) = delete;

	EventHandlingInternal& GetEventHandler();
	InstanceListInternal& GetInstanceListSimplifier();
	WindowListInternal& GetWindowListSimplifier();

	const EventHandlingInternal& GetEventHandler() const;
	const InstanceListInternal& GetInstanceListSimplifier() const;
	const WindowListInternal& GetWindowListSimplifier() const;

private:
	NonVulkanVersionData _appVersion;
	std::string _appTitle;
	std::string _appVariantTile;
	EventHandlingInternal _eventHandler;
	InstanceListInternal _instanceList;
	WindowListInternal _windowList;
};