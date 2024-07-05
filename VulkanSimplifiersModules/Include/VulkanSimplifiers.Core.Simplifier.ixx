export module VulkanSimplifiers.Core.Simplifier;

import std;
import ListTemplates.IDObject;
import VulkanSimplifiers.Core.Internal;
import VulkanSimplifiers.Window.Data;
import VulkanSimplifiers.Window.Internal;
import VulkanSimplifiers.Window.Simplifier;

export class CoreSimplifier
{
public:
	explicit CoreSimplifier(size_t reserveInstances, size_t reserveWindows);
	~CoreSimplifier();

	CoreSimplifier(const CoreSimplifier&) = delete;
	CoreSimplifier& operator=(const CoreSimplifier&) = delete;

	IDObject<WindowPointer> CreateWindow(WindowCreationData data, size_t addReserved);

	WindowSimplifier GetWindowSimplifier(IDObject<WindowPointer> windowID);

private:
	std::unique_ptr<CoreInternal> _internal;
};