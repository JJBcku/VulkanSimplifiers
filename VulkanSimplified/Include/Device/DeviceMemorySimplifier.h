#pragma once
#include "DeviceSimplifierSharedStructs.h"

namespace VulkanSimplified
{
	class DeviceMemorySimplifierInternal;
	class AutoCleanupExclusiveDeviceMemory;

	template<class T>
	class ListObjectID;

	class DeviceMemorySimplifier
	{
		DeviceMemorySimplifierInternal& _internal;
		
	public:
		DeviceMemorySimplifier(DeviceMemorySimplifierInternal& ref);
		~DeviceMemorySimplifier();

		DeviceMemorySimplifier& operator=(const DeviceMemorySimplifier&) noexcept = delete;

		std::optional<ListObjectID<AutoCleanupExclusiveDeviceMemory>> AddDeviceLocalMemory(uint64_t memorySize);
		SharedDeviceMemoryID AddSharedMemory(uint64_t memorySize, bool canBeUncached, bool canBeIncoherent);
		ExternalAccessibleMemoryID AddExternalAccessibleMemory(uint64_t memorySize, bool canBeUncached, bool canBeIncoherent);
	};
}

