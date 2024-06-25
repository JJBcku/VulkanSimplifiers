export module VulkanSimplifiers.CoreSimplifier.Internal;

import std;
import ListTemplates.UnsortedList;
import VulkanSimplifiers.Instance;
import VulkanSimplifiers.Window.Internal;

export typedef std::unique_ptr<Instance> InstancePointer;

export class CoreSimplifierInternal
{
public:
	explicit CoreSimplifierInternal(size_t reserveInstances, size_t reserveWindows);
	~CoreSimplifierInternal();

	CoreSimplifierInternal(const CoreSimplifierInternal&) = delete;
	CoreSimplifierInternal& operator=(const CoreSimplifierInternal&) = delete;

private:
	UnsortedList<InstancePointer> _instanceList;
	UnsortedList<WindowInternal> _windowList;
};