#pragma once
#include "../Other/VulkanSimplifierListTemplate.h"

#include "../Include/Device/DeviceSimplifierSharedStructs.h"

namespace VulkanSimplified
{
	class DeviceCoreSimplifierInternal;
	class DeviceCommandRecorderInternal;

	class SharedDataSimplifierCoreInternal;
	class DeviceImageSimplifierInternal;
	class DevicePipelineDataInternal;
	class DeviceSynchronizationSimplifierInternal;
	class DeviceDataBufferSimplifierInternal;
	class DeviceDescriptorSimplifierInternal;

	class AutoCleanupFence;

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
		const DeviceImageSimplifierInternal& _imageData;
		const DevicePipelineDataInternal& _pipelineData;
		const SharedDataSimplifierCoreInternal& _sharedData;
		const DeviceSynchronizationSimplifierInternal& _synchronizationData;
		const DeviceDataBufferSimplifierInternal& _dataBuffersList;
		const DeviceDescriptorSimplifierInternal& _descriptorSetsList;

		VkDevice _device;

		ListTemplate<AutoCleanupCommandPool> _commandPools;
		ListTemplate<std::unique_ptr<DeviceCommandRecorderInternal>> _primaryCommandBuffers;

	public:
		DeviceCommandBufferSimplifierInternal(const DeviceCoreSimplifierInternal& deviceCore, const DeviceImageSimplifierInternal& imageData,
			const DevicePipelineDataInternal& pipelineData, const SharedDataSimplifierCoreInternal& sharedData, const DeviceSynchronizationSimplifierInternal& synchronizationData,
			const DeviceDataBufferSimplifierInternal& dataBuffersList, const DeviceDescriptorSimplifierInternal& descriptorSetsList);
		~DeviceCommandBufferSimplifierInternal();

		DeviceCommandBufferSimplifierInternal(DeviceCommandBufferSimplifierInternal&) noexcept = delete;

		DeviceCommandBufferSimplifierInternal& operator=(DeviceCommandBufferSimplifierInternal&) noexcept = delete;

		ListObjectID<AutoCleanupCommandPool> AddCommandPool(QueueFamilyType queueFamily, bool transient, bool individualReset);
		ListObjectID<std::unique_ptr<DeviceCommandRecorderInternal>> AddPrimaryCommandBuffer(ListObjectID<AutoCleanupCommandPool> commandPool);
		std::vector<ListObjectID<std::unique_ptr<DeviceCommandRecorderInternal>>> AddPrimaryCommandBuffers(ListObjectID<AutoCleanupCommandPool> commandPool, uint32_t bufferAmount);

		VkCommandPool GetCommandPool(ListObjectID<AutoCleanupCommandPool> commandPoolID) const;

		DeviceCommandRecorderInternal& GetPrimaryDeviceCommandBuffersRecorder(ListObjectID<std::unique_ptr<DeviceCommandRecorderInternal>> commandBufferID);

		void SubmitToQueue(QueueFamilyType queueType, const std::vector<QueueSubmitObject>& queueSubmitList, std::optional<ListObjectID<AutoCleanupFence>> fenceId);
	};
}
