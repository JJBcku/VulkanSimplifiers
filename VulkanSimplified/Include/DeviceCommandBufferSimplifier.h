#include "VulkanSimplifierListTemplate.h"
#include "DeviceSimplifierSharedEnums.h"

namespace VulkanSimplified
{
	class DeviceCommandBufferSimplifierInternal;

	class AutoCleanupCommandPool;

	class DeviceCommandBufferSimplifier
	{
		DeviceCommandBufferSimplifierInternal& _internal;

	public:
		DeviceCommandBufferSimplifier(DeviceCommandBufferSimplifierInternal& ref);
		~DeviceCommandBufferSimplifier();

		DeviceCommandBufferSimplifier(const DeviceCommandBufferSimplifier&) noexcept = delete;

		DeviceCommandBufferSimplifier& operator=(const DeviceCommandBufferSimplifier&) noexcept = delete;

		ListObjectID<AutoCleanupCommandPool> AddCommandPool(QueueFamilyType queueFamily, bool transient, bool individualReset);
	};
}