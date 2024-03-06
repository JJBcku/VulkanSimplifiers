#pragma once

namespace VulkanSimplified
{
	class DeviceImageSimplifierInternal;

	class AutoCleanupSwapchainFramebuffer;
	class AutoCleanupRenderPass;

	template<class T>
	class ListObjectID;

	class DeviceImageSimplifier
	{
		DeviceImageSimplifierInternal& _internal;

	public:
		DeviceImageSimplifier(DeviceImageSimplifierInternal& ref);
		~DeviceImageSimplifier();

		DeviceImageSimplifier(const DeviceImageSimplifier&) noexcept = delete;

		DeviceImageSimplifier& operator=(const DeviceImageSimplifier&) = delete;

		ListObjectID<AutoCleanupSwapchainFramebuffer> AddSimpleSwapchainFramebuffer(ListObjectID<AutoCleanupRenderPass> renderPass);
	};
}
