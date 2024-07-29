export module VulkanSimplifiers.Instance;

import VulkanSimplifiers.Instance.Internal;

export class Instance
{
public:
	Instance(InstanceInternal& ref);
	~Instance();

	Instance& operator=(const Instance&) noexcept = delete;

private:
	InstanceInternal& _internal;
};