#pragma once

#include "../Include/VulkanSimplifierListTemplate.h"

namespace VulkanSimplified
{
	class AutoCleanupFence
	{
		VkDevice _device;
		void* _ppadding;
		VkFence _fence;

	public:
		AutoCleanupFence(VkDevice device, VkFence fence);
		~AutoCleanupFence();

		AutoCleanupFence(const AutoCleanupFence&) noexcept = delete;
		AutoCleanupFence(AutoCleanupFence&& other) noexcept;

		AutoCleanupFence& operator=(const AutoCleanupFence&) noexcept = delete;
		AutoCleanupFence& operator=(AutoCleanupFence&& other) noexcept;

		VkFence GetFence() const;
	};

	class AutoCleanupSemaphore
	{
		VkDevice _device;
		void* _ppadding;
		VkSemaphore _semaphore;

	public:
		AutoCleanupSemaphore(VkDevice device, VkSemaphore semaphore);
		~AutoCleanupSemaphore();

		AutoCleanupSemaphore(const AutoCleanupSemaphore&) noexcept = delete;
		AutoCleanupSemaphore(AutoCleanupSemaphore&& other) noexcept;

		AutoCleanupSemaphore& operator=(const AutoCleanupSemaphore&) noexcept = delete;
		AutoCleanupSemaphore& operator=(AutoCleanupSemaphore&& other) noexcept;

		VkSemaphore GetSemaphore() const;
	};

	class DeviceSynchronizationSimplifierInternal
	{
		VkDevice _device;
		void* _ppadding;

		ListTemplate<AutoCleanupSemaphore> _semaphores;
		ListTemplate<AutoCleanupFence> _fences;

	public:
		DeviceSynchronizationSimplifierInternal(VkDevice device);
		~DeviceSynchronizationSimplifierInternal();

		DeviceSynchronizationSimplifierInternal(const DeviceSynchronizationSimplifierInternal&) noexcept = delete;

		DeviceSynchronizationSimplifierInternal& operator=(const DeviceSynchronizationSimplifierInternal&) noexcept = delete;

		ListObjectID<AutoCleanupSemaphore> AddSemaphore();
		ListObjectID<AutoCleanupFence> AddFence(bool createSignaled);

		void ResetFences(const std::vector<ListObjectID<AutoCleanupFence>>& fencesIDList);
		void WaitForFences(const std::vector<ListObjectID<AutoCleanupFence>>& fencesIDList, uint64_t timeLimitInNanoseconds, bool waitAll);

		VkSemaphore GetSemaphore(ListObjectID<AutoCleanupSemaphore> semaphoreID) const;
		std::vector<VkSemaphore> GetSemaphoresList(const std::vector<ListObjectID<AutoCleanupSemaphore>>& semaphoresIDList) const;
		VkFence GetFence(ListObjectID<AutoCleanupFence> fenceID) const;
		std::vector<VkFence> GetFencesList(const std::vector<ListObjectID<AutoCleanupFence>>& fencesIDList) const;
	};
}