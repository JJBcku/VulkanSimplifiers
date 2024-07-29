export module VulkanSimplifiers.InstanceList.Internal;

import std;
import ListTemplates.UnsortedList;
import VulkanSimplifiers.Instance.Internal;

export typedef std::unique_ptr<InstanceInternal> InstancePointer;

export class InstanceListInternal
{
public:
	InstanceListInternal(size_t initialListCapacity);
	~InstanceListInternal();

	InstanceListInternal(const InstanceListInternal&) noexcept = delete;

	InstanceListInternal& operator=(const InstanceListInternal&) noexcept = delete;

private:
	UnsortedList<InstancePointer> _instanceList;
};