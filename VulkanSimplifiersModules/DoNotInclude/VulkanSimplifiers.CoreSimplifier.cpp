module;

module VulkanSimplifiers.CoreSimplifier;

CoreSimplifier::CoreSimplifier(size_t reserveInstances, size_t reserveWindows)
{
	_internal = std::make_unique<CoreSimplifierInternal>(reserveInstances, reserveWindows);
}

CoreSimplifier::~CoreSimplifier()
{
}