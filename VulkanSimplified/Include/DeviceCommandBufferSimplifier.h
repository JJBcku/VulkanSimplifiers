#include "VulkanSimplifierListTemplate.h"
#include "DeviceSimplifierSharedEnums.h"

#include "DeviceCommandRecorder.h"

namespace VulkanSimplified
{
	class DeviceCommandBufferSimplifierInternal;

	class AutoCleanupCommandPool;
	class DeviceCommandRecorderInternal;
	class DeviceCommandRecorder;

	class DeviceCommandBufferSimplifier
	{
		DeviceCommandBufferSimplifierInternal& _internal;

	public:
		DeviceCommandBufferSimplifier(DeviceCommandBufferSimplifierInternal& ref);
		~DeviceCommandBufferSimplifier();

		DeviceCommandBufferSimplifier(const DeviceCommandBufferSimplifier&) noexcept = delete;

		DeviceCommandBufferSimplifier& operator=(const DeviceCommandBufferSimplifier&) noexcept = delete;

		ListObjectID<AutoCleanupCommandPool> AddCommandPool(QueueFamilyType queueFamily, bool transient, bool individualReset);

		ListObjectID<DeviceCommandRecorderInternal> AddPrimaryCommandBuffer(ListObjectID<AutoCleanupCommandPool> commandPool);
		std::vector<ListObjectID<DeviceCommandRecorderInternal>> AddPrimaryCommandBuffers(ListObjectID<AutoCleanupCommandPool> commandPool, uint32_t bufferAmount);

		DeviceCommandRecorder GetPrimaryDeviceCommandBuffersRecorder(ListObjectID<DeviceCommandRecorderInternal> commandBufferID);
	};
}