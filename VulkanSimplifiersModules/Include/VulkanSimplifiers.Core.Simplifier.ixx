export module VulkanSimplifiers.Core.Simplifier;

import std;
import VulkanSimplifiers.Core.Data;
import ListTemplates.IDObject;
import VulkanSimplifiers.EventHandler.Simplifier;
import VulkanSimplifiers.Core.Internal;
import VulkanSimplifiers.Window.Data;
import VulkanSimplifiers.Window.Internal;
import VulkanSimplifiers.Window.Simplifier;

export class CoreSimplifier
{
public:
	explicit CoreSimplifier(const CoreSimplifierInitData& initData);
	~CoreSimplifier();

	CoreSimplifier(const CoreSimplifier&) = delete;
	CoreSimplifier& operator=(const CoreSimplifier&) = delete;

	IDObject<WindowPointer> CreateWindow(WindowCreationData data, size_t addReserved = 0);

	EventHandlerSimplifier GetEventHandler();
	WindowSimplifier GetWindowSimplifier(IDObject<WindowPointer> windowID);

private:
	std::unique_ptr<CoreInternal> _internal;
};