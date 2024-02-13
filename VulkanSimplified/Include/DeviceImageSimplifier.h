#pragma once

#include "VulkanSimplifierListTemplate.h"

namespace VulkanSimplified
{
	class DeviceImageSimplifierInternal;

	class AutoCleanupSwapchainFramebuffer;
	class AutoCleanupRenderPass;

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
