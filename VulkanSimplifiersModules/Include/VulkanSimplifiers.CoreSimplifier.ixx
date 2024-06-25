export module VulkanSimplifiers.CoreSimplifier;

import VulkanSimplifiers.CoreSimplifier.Internal;
import std;

export class CoreSimplifier
{
public:
	explicit CoreSimplifier(size_t reserveInstances, size_t reserveWindows);
	~CoreSimplifier();

	CoreSimplifier(const CoreSimplifier&) = delete;
	CoreSimplifier& operator=(const CoreSimplifier&) = delete;

private:
	std::unique_ptr<CoreSimplifierInternal> _internal;
};