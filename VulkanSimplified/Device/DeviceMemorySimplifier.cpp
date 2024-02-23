#include "../Other/pch.h"
#include "../Include/DeviceMemorySimplifier.h"

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

	ExternalAccessibleMemoryID DeviceMemorySimplifier::AddExternalAccessibleMemory(uint64_t memorySize, bool canBeUncached, bool canBeIncoherent)
	{
		return _internal.AddExternalAccessibleMemory(memorySize, canBeUncached, canBeIncoherent);
	}

}