#pragma once
#include "DeviceSimplifierSharedStructs.h"

typedef uint64_t VkDeviceSize;

namespace VulkanSimplified
{
	class DeviceMemorySimplifierInternal;
	class AutoCleanupExclusiveDeviceMemory;

	template<class T>
	class ListObjectID;

	union SharedDeviceMemoryID;
	union AccessibleHostMemoryID;

	struct MemoryObject;

	class DeviceMemorySimplifier
	{
		DeviceMemorySimplifierInternal& _internal;
		
	public:
		DeviceMemorySimplifier(DeviceMemorySimplifierInternal& ref);
		~DeviceMemorySimplifier();

		DeviceMemorySimplifier& operator=(const DeviceMemorySimplifier&) noexcept = delete;

		std::optional<ListObjectID<AutoCleanupExclusiveDeviceMemory>> AddDeviceLocalMemory(uint64_t memorySize);
		SharedDeviceMemoryID AddSharedMemory(uint64_t memorySize, bool canBeUncached, bool canBeIncoherent);
		AccessibleHostMemoryID AddExternalAccessibleMemory(uint64_t memorySize, bool canBeUncached, bool canBeIncoherent);
	};
}

