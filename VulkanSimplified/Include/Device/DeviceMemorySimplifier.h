#pragma once
#include "DeviceSimplifierSharedStructs.h"

typedef uint64_t uint64_t;

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

		ListObjectID<AutoCleanupExclusiveDeviceMemory> AddDeviceLocalMemory(uint64_t memorySize);
		SharedDeviceMemoryID AddSharedMemory(uint64_t memorySize, bool canBeUncached, bool canBeIncoherent);
		AccessibleHostMemoryID AddExternalAccessibleMemory(uint64_t memorySize, bool canBeUncached, bool canBeIncoherent);

		bool IsThereExclusiveDeviceMemory() const;
		bool IsThereSharedDeviceMemory() const;
		bool IsThereHostDeviceAccessibleMemory() const;

		bool IsThereHostDeviceUncachedAccessibleMemory() const;
		bool IsThereHostDeviceCachedCoherentAccessibleMemory() const;
		bool IsThereHostDeviceCachedIncoherentAccessibleMemory() const;

		bool IsThereSharedUncachedMemory() const;
		bool IsThereSharedCachedCoherentMemory() const;
		bool IsThereSharedCachedIncoherentMemory() const;
	};
}

