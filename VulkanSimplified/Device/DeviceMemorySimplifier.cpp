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

	ListObjectID<AutoCleanupExclusiveDeviceMemory> DeviceMemorySimplifier::AddDeviceLocalMemory(uint64_t memorySize)
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

	bool DeviceMemorySimplifier::IsThereExclusiveDeviceMemory() const
	{
		return _internal.IsThereExclusiveDeviceMemory();
	}

	bool DeviceMemorySimplifier::IsThereSharedDeviceMemory() const
	{
		return _internal.IsThereSharedDeviceMemory();
	}

	bool DeviceMemorySimplifier::IsThereHostDeviceAccessibleMemory() const
	{
		return _internal.IsThereHostDeviceAccessibleMemory();
	}

	bool DeviceMemorySimplifier::IsThereHostDeviceUncachedAccessibleMemory() const
	{
		return _internal.IsThereHostDeviceUncachedAccessibleMemory();
	}

	bool DeviceMemorySimplifier::IsThereHostDeviceCachedCoherentAccessibleMemory() const
	{
		return _internal.IsThereHostDeviceCachedCoherentAccessibleMemory();
	}

	bool DeviceMemorySimplifier::IsThereHostDeviceCachedIncoherentAccessibleMemory() const
	{
		return _internal.IsThereHostDeviceCachedIncoherentAccessibleMemory();
	}

	bool DeviceMemorySimplifier::IsThereSharedUncachedMemory() const
	{
		return _internal.IsThereSharedUncachedMemory();
	}

	bool DeviceMemorySimplifier::IsThereSharedCachedCoherentMemory() const
	{
		return _internal.IsThereSharedCachedCoherentMemory();
	}

	bool DeviceMemorySimplifier::IsThereSharedCachedIncoherentMemory() const
	{
		return _internal.IsThereSharedCachedIncoherentMemory();
	}

}