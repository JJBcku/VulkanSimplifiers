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

	ListObjectID<std::unique_ptr<DeviceCommandRecorderInternal>> DeviceCommandBufferSimplifier::AddPrimaryCommandBuffer(ListObjectID<AutoCleanupCommandPool> commandPool)
	{
		return _internal.AddPrimaryCommandBuffer(commandPool);
	}

	std::vector<ListObjectID<std::unique_ptr<DeviceCommandRecorderInternal>>> DeviceCommandBufferSimplifier::AddPrimaryCommandBuffers(ListObjectID<AutoCleanupCommandPool> commandPool, uint32_t bufferAmount)
	{
		return _internal.AddPrimaryCommandBuffers(commandPool, bufferAmount);
	}

	DeviceCommandRecorder DeviceCommandBufferSimplifier::GetPrimaryDeviceCommandBuffersRecorder(ListObjectID<std::unique_ptr<DeviceCommandRecorderInternal>> commandBufferID)
	{
		return DeviceCommandRecorder(_internal.GetPrimaryDeviceCommandBuffersRecorder(commandBufferID));
	}

}