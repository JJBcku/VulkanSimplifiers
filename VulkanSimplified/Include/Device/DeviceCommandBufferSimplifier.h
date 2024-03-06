#include "DeviceSimplifierSharedStructs.h"

#include "DeviceCommandRecorder.h"

namespace VulkanSimplified
{
	template<class T>
	class ListObjectTemplate;

	class DeviceCommandBufferSimplifierInternal;

	class AutoCleanupCommandPool;
	class AutoCleanupFence;
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

		ListObjectID<std::unique_ptr<DeviceCommandRecorderInternal>> AddPrimaryCommandBuffer(ListObjectID<AutoCleanupCommandPool> commandPool);
		std::vector<ListObjectID<std::unique_ptr<DeviceCommandRecorderInternal>>> AddPrimaryCommandBuffers(ListObjectID<AutoCleanupCommandPool> commandPool, uint32_t bufferAmount);

		DeviceCommandRecorder GetPrimaryDeviceCommandBuffersRecorder(ListObjectID<std::unique_ptr<DeviceCommandRecorderInternal>> commandBufferID);

		void SubmitToQueue(QueueFamilyType queueType, const std::vector<QueueSubmitObject>& queueSubmitList, std::optional<ListObjectID<AutoCleanupFence>> fenceId);
	};
}