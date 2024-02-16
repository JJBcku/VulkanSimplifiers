#include "../Other/pch.h"
#include "DeviceSynchronizationSimplifierInternal.h"

namespace VulkanSimplified
{

	AutoCleanupFence::AutoCleanupFence(VkDevice device, VkFence fence) : _device(device), _ppadding(nullptr), _fence(fence)
	{
	}

	VulkanSimplified::AutoCleanupFence::~AutoCleanupFence()
	{
		if (_fence != VK_NULL_HANDLE)
			vkDestroyFence(_device, _fence, nullptr);
	}

	AutoCleanupFence::AutoCleanupFence(AutoCleanupFence&& other) noexcept : _device(other._device), _ppadding(nullptr), _fence(other._fence)
	{
		other._device = VK_NULL_HANDLE;
		other._fence = VK_NULL_HANDLE;
	}

	AutoCleanupFence& AutoCleanupFence::operator=(AutoCleanupFence&& other) noexcept
	{
		_device = other._device;
		_ppadding = nullptr;
		_fence = other._fence;

		other._device = VK_NULL_HANDLE;
		other._fence = VK_NULL_HANDLE;

		return *this;
	}

	VkFence AutoCleanupFence::GetFence() const
	{
		return _fence;
	}

	AutoCleanupSemaphore::AutoCleanupSemaphore(VkDevice device, VkSemaphore semaphore) : _device(device), _ppadding(nullptr), _semaphore(semaphore)
	{
	}

	AutoCleanupSemaphore::~AutoCleanupSemaphore()
	{
		if (_semaphore != VK_NULL_HANDLE)
			vkDestroySemaphore(_device, _semaphore, nullptr);
	}

	AutoCleanupSemaphore::AutoCleanupSemaphore(AutoCleanupSemaphore&& other) noexcept : _device(other._device), _ppadding(nullptr), _semaphore(other._semaphore)
	{
		other._device = VK_NULL_HANDLE;
		other._semaphore = VK_NULL_HANDLE;
	}

	AutoCleanupSemaphore& AutoCleanupSemaphore::operator=(AutoCleanupSemaphore&& other) noexcept
	{
		_device = other._device;
		_ppadding = nullptr;
		_semaphore = other._semaphore;

		other._device = VK_NULL_HANDLE;
		other._semaphore = VK_NULL_HANDLE;

		return *this;
	}

	VkSemaphore AutoCleanupSemaphore::GetSemaphore() const
	{
		return _semaphore;
	}

	DeviceSynchronizationSimplifierInternal::DeviceSynchronizationSimplifierInternal(VkDevice device) : _device(device), _ppadding(nullptr)
	{
	}

	DeviceSynchronizationSimplifierInternal::~DeviceSynchronizationSimplifierInternal()
	{
	}

	ListObjectID<AutoCleanupSemaphore> DeviceSynchronizationSimplifierInternal::AddSemaphore()
	{
		VkSemaphoreCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkSemaphore add = VK_NULL_HANDLE;

		if (vkCreateSemaphore(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("DeviceSynchronizationSimplifierInternal::AddSemaphore Error: Program failed to create a semaphore!");

		return _semaphores.AddObject(AutoCleanupSemaphore(_device, add));
	}

	ListObjectID<AutoCleanupFence> DeviceSynchronizationSimplifierInternal::AddFence(bool createSignaled)
	{
		VkFenceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		
		if (createSignaled)
			createInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		VkFence add = VK_NULL_HANDLE;

		if (vkCreateFence(_device, &createInfo, nullptr, &add) != VK_SUCCESS)
			throw std::runtime_error("DeviceSynchronizationSimplifierInternal::AddFence Error: Program failed to create a fence!");

		return _fences.AddObject(AutoCleanupFence(_device, add));
	}

	void DeviceSynchronizationSimplifierInternal::ResetFences(const std::vector<ListObjectID<AutoCleanupFence>>& fencesIDList)
	{
		if (fencesIDList.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("DeviceSynchronizationSimplifierInternal::ResetFences Error: Fences Id list overflowed!");

		auto fences = GetFencesList(fencesIDList);

		vkResetFences(_device, static_cast<uint32_t>(fences.size()), fences.data());
	}

	void DeviceSynchronizationSimplifierInternal::WaitForFences(const std::vector<ListObjectID<AutoCleanupFence>>& fencesIDList, uint64_t timeLimitInNanoseconds, bool waitAll)
	{
		if (fencesIDList.size() > std::numeric_limits<uint32_t>::max())
			throw std::runtime_error("DeviceSynchronizationSimplifierInternal::WaitForFences Error: Fences Id list overflowed!");

		VkBool32 wait = waitAll ? VK_TRUE : VK_FALSE;

		auto fences = GetFencesList(fencesIDList);

		vkWaitForFences(_device, static_cast<uint32_t>(fences.size()), fences.data(), wait, timeLimitInNanoseconds);
	}

	VkSemaphore DeviceSynchronizationSimplifierInternal::GetSemaphore(ListObjectID<AutoCleanupSemaphore> semaphoreID) const
	{
		return _semaphores.GetConstObject(semaphoreID).GetSemaphore();
	}

	std::vector<VkSemaphore> DeviceSynchronizationSimplifierInternal::GetSemaphoresList(const std::vector<ListObjectID<AutoCleanupSemaphore>>& semaphoresIDList) const
	{
		std::vector<VkSemaphore> ret;
		ret.reserve(semaphoresIDList.size());

		for (auto& semaphor : semaphoresIDList)
		{
			ret.push_back(GetSemaphore(semaphor));
		}

		return ret;
	}

	VkFence DeviceSynchronizationSimplifierInternal::GetFence(ListObjectID<AutoCleanupFence> fenceID) const
	{
		return _fences.GetConstObject(fenceID).GetFence();
	}

	std::vector<VkFence> DeviceSynchronizationSimplifierInternal::GetFencesList(const std::vector<ListObjectID<AutoCleanupFence>>& fencesIDList) const
	{
		std::vector<VkFence> ret;

		ret.reserve(fencesIDList.size());

		for (auto& fenceID : fencesIDList)
		{
			ret.push_back(GetFence(fenceID));
		}

		return ret;
	}

}