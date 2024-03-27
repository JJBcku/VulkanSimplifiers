#pragma once
#include "../Other/VulkanSimplifierListTemplate.h"
#include "../Include/Device/DeviceSimplifierSharedStructs.h"

namespace VulkanSimplified
{
	struct MemoryObject
	{
		VkDeviceSize _memoryBeggining = std::numeric_limits<VkDeviceSize>::max();
		VkDeviceSize _usedSize = 0;
	};

	class AutoCleanupMemory
	{
	protected:
		VkDevice _device;
		void* _mapping;
		VkDeviceMemory _deviceMemory;
		VkDeviceSize _memorySize;
		ListTemplate<MemoryObject> _usedMemory;

	public:
		AutoCleanupMemory(VkDevice device, VkDeviceMemory deviceMemory, VkDeviceSize memorySize);
		~AutoCleanupMemory();

		AutoCleanupMemory(const AutoCleanupMemory&) noexcept = delete;
		AutoCleanupMemory(AutoCleanupMemory&& other) noexcept;

		AutoCleanupMemory& operator=(const AutoCleanupMemory&) noexcept = delete;
		AutoCleanupMemory& operator=(AutoCleanupMemory&& other) noexcept;
	};

	class AutoCleanupMappedMemory : public AutoCleanupMemory
	{
	public:
		AutoCleanupMappedMemory(VkDevice device, VkDeviceMemory deviceMemory, VkDeviceSize memorySize);
		~AutoCleanupMappedMemory() {}

		AutoCleanupMappedMemory(const AutoCleanupMappedMemory&) noexcept = delete;
		AutoCleanupMappedMemory(AutoCleanupMappedMemory&& other) noexcept : AutoCleanupMemory(std::move(other))
		{
		}

		AutoCleanupMappedMemory& operator=(const AutoCleanupMappedMemory&) noexcept = delete;
		AutoCleanupMappedMemory& operator=(AutoCleanupMappedMemory&& other) noexcept
		{
			*dynamic_cast<AutoCleanupMemory*>(this) = static_cast<AutoCleanupMemory>(std::move(other));
			return *this;
		}
	};

	class AutoCleanupSharedUncachedDeviceMemory : public AutoCleanupMappedMemory
	{
	public:
		AutoCleanupSharedUncachedDeviceMemory(VkDevice device, VkDeviceMemory deviceMemory, VkDeviceSize memorySize) : AutoCleanupMappedMemory(device, deviceMemory, memorySize) {}
		~AutoCleanupSharedUncachedDeviceMemory() {}

		AutoCleanupSharedUncachedDeviceMemory(const AutoCleanupSharedUncachedDeviceMemory&) noexcept = delete;
		AutoCleanupSharedUncachedDeviceMemory(AutoCleanupSharedUncachedDeviceMemory&& other) noexcept : AutoCleanupMappedMemory(std::move(other))
		{
		}

		AutoCleanupSharedUncachedDeviceMemory& operator=(const AutoCleanupSharedUncachedDeviceMemory&) noexcept = delete;
		AutoCleanupSharedUncachedDeviceMemory& operator=(AutoCleanupSharedUncachedDeviceMemory&& other) noexcept
		{
			*dynamic_cast<AutoCleanupMemory*>(this) = static_cast<AutoCleanupMemory>(std::move(other));
			return *this;
		}
	};

	class AutoCleanupSharedCachedCoherentDeviceMemory : public AutoCleanupMappedMemory
	{
	public:
		AutoCleanupSharedCachedCoherentDeviceMemory(VkDevice device, VkDeviceMemory deviceMemory, VkDeviceSize memorySize) : AutoCleanupMappedMemory(device, deviceMemory, memorySize) {}
		~AutoCleanupSharedCachedCoherentDeviceMemory() {}

		AutoCleanupSharedCachedCoherentDeviceMemory(const AutoCleanupSharedCachedCoherentDeviceMemory&) noexcept = delete;
		AutoCleanupSharedCachedCoherentDeviceMemory(AutoCleanupSharedCachedCoherentDeviceMemory&& other) noexcept : AutoCleanupMappedMemory(std::move(other))
		{
		}

		AutoCleanupSharedCachedCoherentDeviceMemory& operator=(const AutoCleanupSharedCachedCoherentDeviceMemory&) noexcept = delete;
		AutoCleanupSharedCachedCoherentDeviceMemory& operator=(AutoCleanupSharedCachedCoherentDeviceMemory&& other) noexcept
		{
			*dynamic_cast<AutoCleanupMemory*>(this) = static_cast<AutoCleanupMemory>(std::move(other));
			return *this;
		}
	};

	class AutoCleanupSharedCachedIncoherentDeviceMemory : public AutoCleanupMappedMemory
	{
	public:
		AutoCleanupSharedCachedIncoherentDeviceMemory(VkDevice device, VkDeviceMemory deviceMemory, VkDeviceSize memorySize) : AutoCleanupMappedMemory(device, deviceMemory, memorySize) {}
		~AutoCleanupSharedCachedIncoherentDeviceMemory() {}

		AutoCleanupSharedCachedIncoherentDeviceMemory(const AutoCleanupSharedCachedIncoherentDeviceMemory&) noexcept = delete;
		AutoCleanupSharedCachedIncoherentDeviceMemory(AutoCleanupSharedCachedIncoherentDeviceMemory&& other) noexcept : AutoCleanupMappedMemory(std::move(other))
		{
		}

		AutoCleanupSharedCachedIncoherentDeviceMemory& operator=(const AutoCleanupSharedCachedIncoherentDeviceMemory&) noexcept = delete;
		AutoCleanupSharedCachedIncoherentDeviceMemory& operator=(AutoCleanupSharedCachedIncoherentDeviceMemory&& other) noexcept
		{
			*dynamic_cast<AutoCleanupMemory*>(this) = static_cast<AutoCleanupMemory>(std::move(other));
			return *this;
		}
	};

	class AutoCleanupExclusiveDeviceMemory : public AutoCleanupMemory
	{
	public:
		AutoCleanupExclusiveDeviceMemory(VkDevice device, VkDeviceMemory deviceMemory, VkDeviceSize memorySize) : AutoCleanupMemory(device, deviceMemory, memorySize) {}
		~AutoCleanupExclusiveDeviceMemory() {}

		AutoCleanupExclusiveDeviceMemory(const AutoCleanupExclusiveDeviceMemory&) noexcept = delete;
		AutoCleanupExclusiveDeviceMemory(AutoCleanupExclusiveDeviceMemory&& other) noexcept : AutoCleanupMemory(std::move(other))
		{
		}

		AutoCleanupExclusiveDeviceMemory& operator=(const AutoCleanupExclusiveDeviceMemory&) noexcept = delete;
		AutoCleanupExclusiveDeviceMemory& operator=(AutoCleanupExclusiveDeviceMemory&& other) noexcept
		{
			*dynamic_cast<AutoCleanupMemory*>(this) = static_cast<AutoCleanupMemory>(std::move(other));
			return *this;
		}
	};

	class AutoCleanupAccesibleCachedCoherentHostMemory : public AutoCleanupMemory
	{
	public:
		AutoCleanupAccesibleCachedCoherentHostMemory(VkDevice device, VkDeviceMemory deviceMemory, VkDeviceSize memorySize) : AutoCleanupMemory(device, deviceMemory, memorySize) {}
		~AutoCleanupAccesibleCachedCoherentHostMemory() {}

		AutoCleanupAccesibleCachedCoherentHostMemory(const AutoCleanupAccesibleCachedCoherentHostMemory&) noexcept = delete;
		AutoCleanupAccesibleCachedCoherentHostMemory(AutoCleanupAccesibleCachedCoherentHostMemory&& other) noexcept : AutoCleanupMemory(std::move(other)) {}

		AutoCleanupAccesibleCachedCoherentHostMemory& operator=(const AutoCleanupAccesibleCachedCoherentHostMemory&) noexcept = delete;
		AutoCleanupAccesibleCachedCoherentHostMemory& operator=(AutoCleanupAccesibleCachedCoherentHostMemory&& other) noexcept
		{
			*dynamic_cast<AutoCleanupMemory*>(this) = static_cast<AutoCleanupMemory>(std::move(other));
			return *this;
		}
	};

	class AutoCleanupAccesibleCachedIncoherentHostMemory : public AutoCleanupMemory
	{
	public:
		AutoCleanupAccesibleCachedIncoherentHostMemory(VkDevice device, VkDeviceMemory deviceMemory, VkDeviceSize memorySize) : AutoCleanupMemory(device, deviceMemory, memorySize) {}
		~AutoCleanupAccesibleCachedIncoherentHostMemory() {}

		AutoCleanupAccesibleCachedIncoherentHostMemory(const AutoCleanupAccesibleCachedIncoherentHostMemory&) noexcept = delete;
		AutoCleanupAccesibleCachedIncoherentHostMemory(AutoCleanupAccesibleCachedIncoherentHostMemory&& other) noexcept : AutoCleanupMemory(std::move(other)) {}

		AutoCleanupAccesibleCachedIncoherentHostMemory& operator=(const AutoCleanupAccesibleCachedIncoherentHostMemory&) noexcept = delete;
		AutoCleanupAccesibleCachedIncoherentHostMemory& operator=(AutoCleanupAccesibleCachedIncoherentHostMemory&& other) noexcept
		{
			*dynamic_cast<AutoCleanupMemory*>(this) = static_cast<AutoCleanupMemory>(std::move(other));
			return *this;
		}
	};

	class AutoCleanupAccesibleUncachedHostMemory : public AutoCleanupMemory
	{
	public:
		AutoCleanupAccesibleUncachedHostMemory(VkDevice device, VkDeviceMemory deviceMemory, VkDeviceSize memorySize) : AutoCleanupMemory(device, deviceMemory, memorySize) {}
		~AutoCleanupAccesibleUncachedHostMemory() {}

		AutoCleanupAccesibleUncachedHostMemory(const AutoCleanupAccesibleUncachedHostMemory&) noexcept = delete;
		AutoCleanupAccesibleUncachedHostMemory(AutoCleanupAccesibleUncachedHostMemory&& other) noexcept : AutoCleanupMemory(std::move(other)) {}

		AutoCleanupAccesibleUncachedHostMemory& operator=(const AutoCleanupAccesibleUncachedHostMemory&) noexcept = delete;
		AutoCleanupAccesibleUncachedHostMemory& operator=(AutoCleanupAccesibleUncachedHostMemory&& other) noexcept
		{
			*dynamic_cast<AutoCleanupMemory*>(this) = static_cast<AutoCleanupMemory>(std::move(other));
			return *this;
		}
	};

	class DeviceMemorySimplifierInternal
	{
		ListTemplate<AutoCleanupSharedUncachedDeviceMemory> _sharedUncachedDeviceMemories;
		ListTemplate<AutoCleanupSharedCachedCoherentDeviceMemory> _sharedCachedCoherentDeviceMemories;
		ListTemplate<AutoCleanupSharedCachedIncoherentDeviceMemory> _sharedCachedIncoherentDeviceMemories;
		ListTemplate<AutoCleanupExclusiveDeviceMemory> _exclusiveDeviceMemories;
		ListTemplate<AutoCleanupAccesibleCachedCoherentHostMemory> _accessibleCachedCoherentExternalMemories;
		ListTemplate<AutoCleanupAccesibleCachedIncoherentHostMemory> _accessibleCachedIncoherentExternalMemories;
		ListTemplate<AutoCleanupAccesibleUncachedHostMemory> _accessibleUncachedExternalMemories;

		VkPhysicalDevice _physicalDevice;
		VkDevice _device;

		VkPhysicalDeviceMemoryProperties _memoryProperties;
		VkDeviceSize _usedheapMemory[VK_MAX_MEMORY_HEAPS];

		std::array<uint32_t, VK_MAX_MEMORY_HEAPS> _sharedUnchachedDeviceHeaps;
		std::array<uint32_t, VK_MAX_MEMORY_HEAPS> _sharedCachedCoherentDeviceHeaps;
		std::array<uint32_t, VK_MAX_MEMORY_HEAPS> _sharedCachedIncoherentDeviceHeaps;
		std::array<uint32_t, VK_MAX_MEMORY_HEAPS> _exclusiveDeviceHeaps;
		std::array<uint32_t, VK_MAX_MEMORY_HEAPS> _accessibleCachedCoherentDeviceHeaps;
		std::array<uint32_t, VK_MAX_MEMORY_HEAPS> _accessibleCachedIncoherentDeviceHeaps;
		std::array<uint32_t, VK_MAX_MEMORY_HEAPS> _accessibleUncachedDeviceHeaps;

		VkMemoryPropertyFlags _deviceLocalMemoryProperties;
		VkMemoryPropertyFlags _externalUncachedMemoryProperties;
		VkMemoryPropertyFlags _externalCachedCoherentMemoryProperties;
		VkMemoryPropertyFlags _externalCachedIncoherentMemoryProperties;
		VkMemoryPropertyFlags _sharedUncachedMemoryProperties;
		VkMemoryPropertyFlags _sharedCachedCoherentMemoryProperties;
		VkMemoryPropertyFlags _sharedCachedIncoherentMemoryProperties;
		VkMemoryPropertyFlags _flagsPadding;

		bool IsHeapInTheArray(uint32_t heapID, const std::array<uint32_t, VK_MAX_MEMORY_HEAPS>& array) const;
		std::optional<size_t> GetFirstEmptySpace(const std::array<uint32_t, VK_MAX_MEMORY_HEAPS>& array) const;

		size_t GetArrayUsedSize(const std::array<uint32_t, VK_MAX_MEMORY_HEAPS>& array) const;

		void AddHeapToArray(uint32_t heapID, std::array<uint32_t, VK_MAX_MEMORY_HEAPS>& array);

		std::optional<size_t> PickHeapToAddMemoryTo(uint64_t neededSize, const std::array<uint32_t, VK_MAX_MEMORY_HEAPS>& array) const;

		void IncreaseUsedHeapMemory(uint64_t addedMemory, uint32_t heapID);
		void DecreaseUsedHeapMemory(uint64_t substractedMemory, uint32_t heapID);

		uint32_t FindMemoryType(uint32_t heapID, VkMemoryPropertyFlags includeFlags);

		std::optional<ListObjectID<AutoCleanupAccesibleCachedCoherentHostMemory>> AddCachedCoherentExternalMemory(uint64_t memorySize);
		std::optional<ListObjectID<AutoCleanupAccesibleCachedIncoherentHostMemory>> AddCachedIncoherentExternalMemory(uint64_t memorySize);
		std::optional<ListObjectID<AutoCleanupAccesibleUncachedHostMemory>> AddUncachedExternalMemory(uint64_t memorySize);

		std::optional<ListObjectID<AutoCleanupSharedCachedCoherentDeviceMemory>> AddCachedCoherentSharedMemory(uint64_t memorySize);
		std::optional<ListObjectID<AutoCleanupSharedCachedIncoherentDeviceMemory>> AddCachedIncoherentSharedMemory(uint64_t memorySize);
		std::optional<ListObjectID<AutoCleanupSharedUncachedDeviceMemory>> AddUncachedSharedMemory(uint64_t memorySize);

	public:
		DeviceMemorySimplifierInternal(VkPhysicalDevice physicalDevice, VkDevice device);

		DeviceMemorySimplifierInternal(const DeviceMemorySimplifierInternal&) noexcept = delete;
		DeviceMemorySimplifierInternal(DeviceMemorySimplifierInternal&&) noexcept = delete;

		DeviceMemorySimplifierInternal& operator=(const DeviceMemorySimplifierInternal&) noexcept = delete;
		DeviceMemorySimplifierInternal& operator=(DeviceMemorySimplifierInternal&&) noexcept = delete;

		std::optional<ListObjectID<AutoCleanupExclusiveDeviceMemory>> AddDeviceLocalMemory(uint64_t memorySize);
		SharedDeviceMemoryID AddSharedMemory(uint64_t memorySize, bool canBeUncached, bool canBeIncoherent);
		AccessibleHostMemoryID AddExternalAccessibleMemory(uint64_t memorySize, bool canBeUncached, bool canBeIncoherent);
	};
}