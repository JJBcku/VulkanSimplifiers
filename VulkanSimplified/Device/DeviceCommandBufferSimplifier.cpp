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

	ListObjectID<DeviceCommandRecorderInternal> DeviceCommandBufferSimplifier::AddCommandBuffer(ListObjectID<AutoCleanupCommandPool> commandPool, bool primaryBuffer)
	{
		return _internal.AddCommandBuffer(commandPool, primaryBuffer);
	}

	std::vector<ListObjectID<DeviceCommandRecorderInternal>> DeviceCommandBufferSimplifier::AddCommandBuffers(ListObjectID<AutoCleanupCommandPool> commandPool, uint32_t bufferAmount, bool primaryBuffers)
	{
		return _internal.AddCommandBuffers(commandPool, bufferAmount, primaryBuffers);
	}

	DeviceCommandRecorder DeviceCommandBufferSimplifier::GetCommandBufferRecorder(ListObjectID<DeviceCommandRecorderInternal> commandBufferID)
	{
		return DeviceCommandRecorder(_internal.GetDeviceCommandBufferRecorder(commandBufferID));
	}

}