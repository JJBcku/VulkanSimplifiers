#include "../Other/pch.h"
#include "../Include/Device/DeviceMemorySimplifier.h"

#include "../Include/Common/ListObjectID.h"
#include "DeviceMemorySimplifierInternal.h"

namespace VulkanSimplified
{

	DeviceMemorySimplifier::DeviceMemorySimplifier(DeviceMemorySimplifierInternal& ref) : _internal(ref)
	{
	}

	DeviceMemorySimplifier::~DeviceMemorySimplifier()
	{
	}

	std::optional<ListObjectID<AutoCleanupExclusiveDeviceMemory>> DeviceMemorySimplifier::AddDeviceLocalMemory(uint64_t memorySize)
	{
		return _internal.AddDeviceLocalMemory(memorySize);
	}

	SharedDeviceMemoryID DeviceMemorySimplifier::AddSharedMemory(uint64_t memorySize, bool canBeUncached, bool canBeIncoherent)
	{
		return _internal.AddSharedMemory(memorySize, canBeUncached, canBeIncoherent);
	}

	AccessibleHostMemoryID DeviceMemorySimplifier::AddExternalAccessibleMemory(uint64_t memorySize, bool canBeUncached, bool canBeIncoherent)
	{
		return _internal.AddExternalAccessibleMemory(memorySize, canBeUncached, canBeIncoherent);
	}

	void DeviceMemorySimplifier::WriteToMemoryObject(SharedDeviceMemoryID sharedMemoryID, ListObjectID<MemoryObject> objectID, VkDeviceSize offset, const char& data, VkDeviceSize dataSize, bool flushOnWrite)
	{
		_internal.WriteToMemoryObject(sharedMemoryID, objectID, offset, data, dataSize, flushOnWrite);
	}

	void DeviceMemorySimplifier::WriteToMemoryObject(AccessibleHostMemoryID hostMemoryID, ListObjectID<MemoryObject> objectID, VkDeviceSize offset, const char& data, VkDeviceSize dataSize, bool flushOnWrite)
	{
		_internal.WriteToMemoryObject(hostMemoryID, objectID, offset, data, dataSize, flushOnWrite);
	}

}