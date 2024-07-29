export module VulkanSimplifiers.InstanceList;

import VulkanSimplifiers.InstanceList.Internal;

export class InstanceListSimplifier
{
public:
	InstanceListSimplifier(InstanceListInternal& ref);
	~InstanceListSimplifier();

	InstanceListSimplifier& operator=(const InstanceListSimplifier&) noexcept = delete;

private:
	InstanceListInternal& _internal;
};