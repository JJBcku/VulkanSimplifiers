#include "../Other/pch.h"
#include "DeviceCommandBufferSimplifierInternal.h"

#include "DeviceCoreSimplifierInternal.h"
#include "DeviceCommandRecorderInternal.h"

#include "../SharedData/SharedDataSimplifierCoreInternal.h"

namespace VulkanSimplified
{

	DeviceCommandBufferSimplifierInternal::DeviceCommandBufferSimplifierInternal(const DeviceCoreSimplifierInternal& deviceCore, const DeviceImageSimplifierInternal& imageData,
		const DevicePipelineDataInternal& pipelineData, const SharedDataSimplifierCoreInternal& sharedData) : _deviceCore(deviceCore), _imageData(imageData), _pipelineData(pipelineData),
		_sharedData(sharedData), _device(deviceCore.GetDevice()), _ppadding(nullptr)
	{
	}

	DeviceCommandBufferSimplifierInternal::~DeviceCommandBufferSimplifierInternal()
	{
	}

	ListObjectID<AutoCleanupCommandPool> DeviceCommandBufferSimplifierInternal::AddCommandPool(QueueFamilyType queueFamily, bool transient, bool individualReset)
	{
		VkCommandPoolCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		createInfo.queueFamilyIndex = _deviceCore.GetBestQueueForTheType(queueFamily);

		if (transient)
			createInfo.flags |= VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;

		if (individualReset)
			createInfo.flags |= VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

		VkCommandPool add = VK_NULL_HANDLE;

		if (vkCreateCommandPool(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("DeviceCommandBufferSimplifierInternal::AddCommandPool Error: Program failed to create a command pool!");

		return _commandPools.AddObject(AutoCleanupCommandPool(_device, add));
	}

	ListObjectID<std::unique_ptr<DeviceCommandRecorderInternal>> DeviceCommandBufferSimplifierInternal::AddPrimaryCommandBuffer(ListObjectID<AutoCleanupCommandPool> commandPool)
	{
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = GetCommandPool(commandPool);
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = 1;

		VkCommandBuffer add = VK_NULL_HANDLE;

		if (vkAllocateCommandBuffers(_device, &allocInfo, &add) != VK_SUCCESS)
			throw std::runtime_error("DeviceCommandBufferSimplifierInternal::AddCommandBuffer Error: Program failed to allocate the command buffer!");

		return _primaryCommandBuffers.AddObject(std::make_unique<DeviceCommandRecorderInternal>(add, _imageData, _pipelineData, _sharedData.GetConstSharedDataPipelineElements()));
	}

	std::vector<ListObjectID<std::unique_ptr<DeviceCommandRecorderInternal>>> DeviceCommandBufferSimplifierInternal::AddPrimaryCommandBuffers(ListObjectID<AutoCleanupCommandPool> commandPool,
		uint32_t bufferAmount)
	{
		std::vector<ListObjectID<std::unique_ptr<DeviceCommandRecorderInternal>>> ret;

		if (bufferAmount == 0)
			throw std::runtime_error("DeviceCommandBufferSimplifierInternal::AddCommandBuffers Error: Program tried to create zero command buffers!");

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = GetCommandPool(commandPool);
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = bufferAmount;

		std::vector<VkCommandBuffer> list(bufferAmount, VK_NULL_HANDLE);

		if (vkAllocateCommandBuffers(_device, &allocInfo, list.data()) != VK_SUCCESS)
			throw std::runtime_error("DeviceCommandBufferSimplifierInternal::AddCommandBuffers Error: Program failed to allocate the command buffers!");

		ret.reserve(bufferAmount);

		for (size_t i = 0; i < list.size(); ++i)
		{
			ret.push_back(_primaryCommandBuffers.AddObject(std::make_unique<DeviceCommandRecorderInternal>(list[i], _imageData, _pipelineData, _sharedData.GetConstSharedDataPipelineElements())));
		}

		return ret;
	}

	VkCommandPool DeviceCommandBufferSimplifierInternal::GetCommandPool(ListObjectID<AutoCleanupCommandPool> commandPoolID) const
	{
		return _commandPools.GetConstObject(commandPoolID).GetCommandPool();
	}

	DeviceCommandRecorderInternal& DeviceCommandBufferSimplifierInternal::GetPrimaryDeviceCommandBuffersRecorder(ListObjectID<std::unique_ptr<DeviceCommandRecorderInternal>> commandBufferID)
	{
		return *_primaryCommandBuffers.GetObject(commandBufferID);
	}

	AutoCleanupCommandPool::AutoCleanupCommandPool(VkDevice device, VkCommandPool commandPool) : _device(device), _ppadding(nullptr), _commandPool(commandPool)
	{
	}

	AutoCleanupCommandPool::~AutoCleanupCommandPool()
	{
		if (_commandPool != VK_NULL_HANDLE)
		{
			vkDestroyCommandPool(_device, _commandPool, nullptr);
		}
	}

	AutoCleanupCommandPool::AutoCleanupCommandPool(AutoCleanupCommandPool&& other) noexcept : _device(other._device), _ppadding(nullptr), _commandPool(other._commandPool)
	{
		other._device = VK_NULL_HANDLE;
		other._commandPool = VK_NULL_HANDLE;
	}

	AutoCleanupCommandPool& AutoCleanupCommandPool::operator=(AutoCleanupCommandPool&& other) noexcept
	{
		_device = other._device;
		_ppadding = nullptr;
		_commandPool = other._commandPool;

		other._device = VK_NULL_HANDLE;
		other._commandPool = VK_NULL_HANDLE;

		return *this;
	}

	VkCommandPool AutoCleanupCommandPool::GetCommandPool() const
	{
		return _commandPool;
	}

}
