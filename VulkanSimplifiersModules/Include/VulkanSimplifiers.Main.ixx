export module VulkanSimplifiers.Main;

import std;
import VulkanSimplifiers.Main.Data;
import ListTemplates.IDObject;
import VulkanSimplifiers.EventHandling;
import VulkanSimplifiers.Main.Internal;
import VulkanSimplifiers.WindowList;

export class MainSimplifier
{
public:
	explicit MainSimplifier(const MainSimplifierInitData& initData);
	~MainSimplifier();

	MainSimplifier(const MainSimplifier&) = delete;
	MainSimplifier& operator=(const MainSimplifier&) = delete;

	EventHandlingSimplifier GetEventHandler();
	WindowListSimplifier GetWindowListSimplifier();

private:
	std::unique_ptr<MainInternal> _internal;
};