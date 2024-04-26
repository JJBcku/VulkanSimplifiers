#include "../Other/pch.h"
#include "DeviceCommandBufferSimplifierInternal.h"

#include "DeviceCoreSimplifierInternal.h"
#include "DeviceCommandRecorderInternal.h"

#include "../SharedData/SharedDataSimplifierCoreInternal.h"
#include "DeviceSynchronizationSimplifierInternal.h"

#include "DeviceCommandBufferSimplifierInternal.h"

namespace VulkanSimplified
{
	DeviceCommandBufferSimplifierInternal::DeviceCommandBufferSimplifierInternal(const DeviceCoreSimplifierInternal& deviceCore, const DeviceImageSimplifierInternal& imageData,
		const DevicePipelineDataInternal& pipelineData, const SharedDataSimplifierCoreInternal& sharedData, const DeviceSynchronizationSimplifierInternal& synchronizationData,
		const DeviceDataBufferSimplifierInternal& dataBuffersList) : _deviceCore(deviceCore), _imageData(imageData), _pipelineData(pipelineData), _sharedData(sharedData),
		_synchronizationData(synchronizationData), _dataBuffersList(dataBuffersList), _ppadding(nullptr), _device(deviceCore.GetDevice())
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

		return _primaryCommandBuffers.AddObject(std::make_unique<DeviceCommandRecorderInternal>(add, _imageData, _pipelineData, _sharedData.GetConstSharedDataPipelineElements(), _dataBuffersList));
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
			ret.push_back(_primaryCommandBuffers.AddObject(std::make_unique<DeviceCommandRecorderInternal>(list[i], _imageData, _pipelineData, _sharedData.GetConstSharedDataPipelineElements(), _dataBuffersList)));
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

	void DeviceCommandBufferSimplifierInternal::SubmitToQueue(QueueFamilyType queueType, const std::vector<QueueSubmitObject>& queueSubmitList,
		std::optional<ListObjectID<AutoCleanupFence>> fenceId)
	{
		if (queueSubmitList.empty())
			throw std::runtime_error("DeviceCommandBufferSimplifierInternal::SubmitToQueue Error: Program tried to submit an empty list!");

		if (queueSubmitList.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("DeviceCommandBufferSimplifierInternal::SubmitToQueue Error: queue submit list overflow!");

		VkQueue queue = _deviceCore.GetQueue(queueType);

		std::vector<VkSubmitInfo> submitInfo;
		std::vector<std::vector<VkSemaphore>> waitSemaphores;
		std::vector<std::vector<VkPipelineStageFlags>> semaphoreStageFlags;
		std::vector<std::vector<VkCommandBuffer>> commandBuffers;
		std::vector<std::vector<VkSemaphore>> signalSemaphores;

		submitInfo.reserve(queueSubmitList.size());

		waitSemaphores.resize(queueSubmitList.size());
		semaphoreStageFlags.resize(queueSubmitList.size());
		commandBuffers.resize(queueSubmitList.size());
		signalSemaphores.resize(queueSubmitList.size());

		for (size_t i = 0; i < queueSubmitList.size(); ++i)
		{
			auto& submitObject = queueSubmitList[i];

			if (submitObject._waitSemaphores.size() > std::numeric_limits<uint32_t>::max())
				throw std::runtime_error("DeviceCommandBufferSimplifierInternal::SubmitToQueue Error: wait semaphores list overflow!");

			if (submitObject._commandBuffers.empty())
				throw std::runtime_error("DeviceCommandBufferSimplifierInternal::SubmitToQueue Error: Program tried to submit zero command buffers to queue!");

			if (submitObject._commandBuffers.size() > std::numeric_limits<uint32_t>::max())
				throw std::runtime_error("DeviceCommandBufferSimplifierInternal::SubmitToQueue Error: command buffer list overflow!");

			if (submitObject._signalSemaphores.size() > std::numeric_limits<uint32_t>::max())
				throw std::runtime_error("DeviceCommandBufferSimplifierInternal::SubmitToQueue Error: signal semaphores list overflow!");

			VkSubmitInfo add{};
			add.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			
			if (!submitObject._waitSemaphores.empty())
			{
				auto& waitData = submitObject._waitSemaphores;

				waitSemaphores[i].reserve(waitData.size());
				semaphoreStageFlags[i].reserve(waitData.size());

				for (size_t j = 0; j < waitData.size(); ++j)
				{
					semaphoreStageFlags[i].push_back(TranslatePipelineStage(waitData[j].first));
					waitSemaphores[i].push_back(_synchronizationData.GetSemaphore(waitData[j].second));
				}

				add.waitSemaphoreCount = static_cast<uint32_t>(waitData.size());
				add.pWaitSemaphores = waitSemaphores[i].data();
				add.pWaitDstStageMask = semaphoreStageFlags[i].data();
			}

			{
				auto& commandData = submitObject._commandBuffers;

				commandBuffers[i].reserve(commandData.size());
				for (size_t j = 0; j < commandData.size(); ++j)
				{
					commandBuffers[i].push_back(GetPrimaryDeviceCommandBuffersRecorder(commandData[j]).GetCommandBuffer());
				}
				add.commandBufferCount = static_cast<uint32_t>(commandData.size());
				add.pCommandBuffers = commandBuffers[i].data();
			}

			if (!submitObject._signalSemaphores.empty())
			{
				signalSemaphores[i] = _synchronizationData.GetSemaphoresList(submitObject._signalSemaphores);

				add.signalSemaphoreCount = static_cast<uint32_t>(signalSemaphores[i].size());
				add.pSignalSemaphores = signalSemaphores[i].data();
			}

			submitInfo.push_back(add);
		}

		VkFence fence = VK_NULL_HANDLE;

		if (fenceId.has_value())
			fence = _synchronizationData.GetFence(fenceId.value());

		if (vkQueueSubmit(queue, static_cast<uint32_t>(submitInfo.size()), submitInfo.data(), fence) != VK_SUCCESS)
			throw std::runtime_error("DeviceCommandBufferSimplifierInternal::SubmitToQueue Error: Program failed to submit to the queue!");
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
