#include "../Other/pch.h"
#include "../Include/DeviceSynchronizationSimplifier.h"

#include "DeviceSynchronizationSimplifierInternal.h"

namespace VulkanSimplified
{

	DeviceSynchronizationSimplifier::DeviceSynchronizationSimplifier(DeviceSynchronizationSimplifierInternal& ref) : _internal(ref)
	{
	}

	DeviceSynchronizationSimplifier::~DeviceSynchronizationSimplifier()
	{
	}

	ListObjectID<AutoCleanupSemaphore> DeviceSynchronizationSimplifier::AddSemaphore()
	{
		return _internal.AddSemaphore();
	}

	ListObjectID<AutoCleanupFence> DeviceSynchronizationSimplifier::AddFence(bool createSignaled)
	{
		return _internal.AddFence(createSignaled);
	}

	void DeviceSynchronizationSimplifier::ResetFences(const std::vector<ListObjectID<AutoCleanupFence>>& fencesIDList)
	{
		_internal.ResetFences(fencesIDList);
	}

	void DeviceSynchronizationSimplifier::WaitForFences(const std::vector<ListObjectID<AutoCleanupFence>>& fencesIDList, uint64_t timeLimitInNanoseconds, bool waitAll)
	{
		_internal.WaitForFences(fencesIDList, timeLimitInNanoseconds, waitAll);
	}

}