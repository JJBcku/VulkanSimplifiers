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

}