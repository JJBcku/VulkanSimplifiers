#pragma once

#include "VulkanSimplifierListTemplate.h"

namespace VulkanSimplified
{
	class DeviceSynchronizationSimplifierInternal;

	class AutoCleanupSemaphore;
	class AutoCleanupFence;

	class DeviceSynchronizationSimplifier
	{
		DeviceSynchronizationSimplifierInternal& _internal;

	public:
		DeviceSynchronizationSimplifier(DeviceSynchronizationSimplifierInternal& ref);
		~DeviceSynchronizationSimplifier();

		DeviceSynchronizationSimplifier& operator=(const DeviceSynchronizationSimplifier&) noexcept = delete;

		ListObjectID<AutoCleanupSemaphore> AddSemaphore();
		ListObjectID<AutoCleanupFence> AddFence(bool createSignaled);

		void ResetFences(const std::vector<ListObjectID<AutoCleanupFence>>& fencesIDList);
		void WaitForFences(const std::vector<ListObjectID<AutoCleanupFence>>& fencesIDList, uint64_t timeLimitInNanoseconds, bool waitAll);
	};
}
