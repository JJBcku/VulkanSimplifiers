#pragma once
#include "../Include/VulkanSimplifierListTemplate.h"

#include "../Include/DeviceSimplifierSharedEnums.h"

namespace VulkanSimplified
{
	class DeviceCoreSimplifierInternal;
	class DeviceCommandRecorderInternal;

	class AutoCleanupCommandPool
	{
		VkDevice _device;
		void* _ppadding;
		VkCommandPool _commandPool;

	public:
		AutoCleanupCommandPool(VkDevice device, VkCommandPool commandPool);
		~AutoCleanupCommandPool();

		AutoCleanupCommandPool(const AutoCleanupCommandPool&) noexcept = delete;
		AutoCleanupCommandPool(AutoCleanupCommandPool&& other) noexcept;

		AutoCleanupCommandPool& operator=(const AutoCleanupCommandPool&) noexcept = delete;
		AutoCleanupCommandPool& operator=(AutoCleanupCommandPool&& other) noexcept;

		VkCommandPool GetCommandPool() const;
	};

	class DeviceCommandBufferSimplifierInternal
	{
		const DeviceCoreSimplifierInternal& _deviceCore;

		VkDevice _device;

		ListTemplate<AutoCleanupCommandPool> _commandPools;
		ListTemplate<DeviceCommandRecorderInternal> _primaryCommandBuffers;

	public:
		DeviceCommandBufferSimplifierInternal(const DeviceCoreSimplifierInternal& deviceCore);
		~DeviceCommandBufferSimplifierInternal();

		DeviceCommandBufferSimplifierInternal(DeviceCommandBufferSimplifierInternal&) noexcept = delete;

		DeviceCommandBufferSimplifierInternal& operator=(DeviceCommandBufferSimplifierInternal&) noexcept = delete;

		ListObjectID<AutoCleanupCommandPool> AddCommandPool(QueueFamilyType queueFamily, bool transient, bool individualReset);
		ListObjectID<DeviceCommandRecorderInternal> AddPrimaryCommandBuffer(ListObjectID<AutoCleanupCommandPool> commandPool);
		std::vector<ListObjectID<DeviceCommandRecorderInternal>> AddPrimaryCommandBuffers(ListObjectID<AutoCleanupCommandPool> commandPool, uint32_t bufferAmount);

		VkCommandPool GetCommandPool(ListObjectID<AutoCleanupCommandPool> commandPoolID) const;

		DeviceCommandRecorderInternal& GetPrimaryDeviceCommandBuffersRecorder(ListObjectID<DeviceCommandRecorderInternal> commandBufferID);
	};
}
