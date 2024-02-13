#include "../Other/pch.h"
#include "../Include/DeviceCommandBufferSimplifier.h"

#include "DeviceCommandBufferSimplifierInternal.h"

namespace VulkanSimplified
{

	DeviceCommandBufferSimplifier::DeviceCommandBufferSimplifier(DeviceCommandBufferSimplifierInternal& ref) : _internal(ref)
	{
	}

	DeviceCommandBufferSimplifier::~DeviceCommandBufferSimplifier()
	{
	}

	ListObjectID<AutoCleanupCommandPool> DeviceCommandBufferSimplifier::AddCommandPool(QueueFamilyType queueFamily, bool transient, bool individualReset)
	{
		return _internal.AddCommandPool(queueFamily, transient, individualReset);
	}

	ListObjectID<DeviceCommandRecorderInternal> DeviceCommandBufferSimplifier::AddPrimaryCommandBuffer(ListObjectID<AutoCleanupCommandPool> commandPool)
	{
		return _internal.AddPrimaryCommandBuffer(commandPool);
	}

	std::vector<ListObjectID<DeviceCommandRecorderInternal>> DeviceCommandBufferSimplifier::AddPrimaryCommandBuffers(ListObjectID<AutoCleanupCommandPool> commandPool, uint32_t bufferAmount)
	{
		return _internal.AddPrimaryCommandBuffers(commandPool, bufferAmount);
	}

	DeviceCommandRecorder DeviceCommandBufferSimplifier::GetPrimaryDeviceCommandBuffersRecorder(ListObjectID<DeviceCommandRecorderInternal> commandBufferID)
	{
		return DeviceCommandRecorder(_internal.GetPrimaryDeviceCommandBuffersRecorder(commandBufferID));
	}

}