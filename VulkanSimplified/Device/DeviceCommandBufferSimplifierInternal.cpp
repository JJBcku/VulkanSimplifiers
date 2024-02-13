#include "../Other/pch.h"
#include "DeviceCommandBufferSimplifierInternal.h"

#include "DeviceCoreSimplifierInternal.h"

namespace VulkanSimplified
{

	DeviceCommandBufferSimplifierInternal::DeviceCommandBufferSimplifierInternal(const DeviceCoreSimplifierInternal& deviceCore) : _deviceCore(deviceCore), _device(deviceCore.GetDevice())
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

}
