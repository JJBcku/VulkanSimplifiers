export module VulkanSimplifiers.Core.Simplifier;

import std;
import VulkanSimplifiers.Core.Data;
import ListTemplates.IDObject;
import VulkanSimplifiers.EventHandling.Simplifier;
import VulkanSimplifiers.Core.Internal;
import VulkanSimplifiers.WindowList.Simplifier;

export class CoreSimplifier
{
public:
	explicit CoreSimplifier(const CoreSimplifierInitData& initData);
	~CoreSimplifier();

	CoreSimplifier(const CoreSimplifier&) = delete;
	CoreSimplifier& operator=(const CoreSimplifier&) = delete;

	EventHandlingSimplifier GetEventHandler();
	WindowListSimplifier GetWindowListSimplifier();

private:
	std::unique_ptr<CoreInternal> _internal;
};